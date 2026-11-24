import struct
import sys
import subprocess

NUL = bytes([0])
BS = chr(92)

ELF = sys.argv[1]
BASE_E32 = sys.argv[2]
TOOL = sys.argv[3]

d = open(ELF, 'rb').read()
e_shoff, = struct.unpack_from('<I', d, 32)
es, n, si = struct.unpack_from('<HHH', d, 46)
secs = [list(struct.unpack_from('<10I', d, e_shoff + i * es)) for i in range(n)]


def sname(off):
    st = secs[si][4]
    e = d.index(NUL, st + off)
    return d[st + off:e].decode('latin1')


names = [sname(s[0]) for s in secs]
idx = {nm: i for i, nm in enumerate(names)}
symi = idx['.symtab']
sym = secs[symi]
strt = secs[sym[6]][4]


def symval(i):
    base = sym[4] + i * 16
    no, val, sz, info, oth, shndx = struct.unpack_from('<IIIBBH', d, base)
    e = d.index(NUL, strt + no)
    return d[strt + no:e].decode('latin1'), val, shndx


rel = secs[idx['.rel.text']]
imports = []
for k in range(rel[5] // 8):
    off, info = struct.unpack_from('<II', d, rel[4] + k * 8)
    nm, val, shndx = symval(info >> 8)
    if nm.startswith('#<'):
        imports.append((off, nm))

DLL_TAG = '#<DLL>'
END_TAG = '#<' + BS + 'DLL>'

dll = ""
ordinal = 0
site = 0
if imports:
    site, nm = imports[0]
    body = nm
    if body.startswith(DLL_TAG):
        body = body[len(DLL_TAG):]
    if END_TAG in body:
        head, tail = body.split(END_TAG, 1)
        dll = head
        try:
            ordinal = int(tail or '0', 16)
        except ValueError:
            ordinal = 0
    else:
        dll = body
print('import site', hex(site), 'dll', dll, 'ordinal', hex(ordinal))

base = bytearray(open(BASE_E32, 'rb').read())
code_off, = struct.unpack_from('<I', base, 0x64)


def L(data):
    c = 0
    for b in data:
        c ^= b
        for _ in range(8):
            c = (c >> 1) ^ 0xEDB88320 if c & 1 else c >> 1
    return c


def fix_crc(x):
    h = bytearray(x[0:0x9c])
    h[0x14:0x18] = NUL * 4
    struct.pack_into('<I', x, 0x14, (L(bytes(h)) ^ 0x7601236A) & 0xffffffff)


def build(order, ordsize, count_at, iat_rel):
    img = bytearray(base)
    sec = bytearray(NUL * 20)
    while len(sec) % 4:
        sec.extend(NUL)
    addr_off = len(sec)
    sec.extend(struct.pack('<I', site))
    ord_off = len(sec)
    if ordsize == 4:
        sec.extend(struct.pack('<I', ordinal))
    else:
        sec.extend(struct.pack('<H', ordinal))
    while len(sec) % 4:
        sec.extend(NUL)
    name_off = len(sec)
    sec.extend(dll.encode() + NUL)
    while len(sec) % 4:
        sec.extend(NUL)
    sec.extend(struct.pack('<I', 0))
    rec_size = len(sec) - 4
    if order == 'name-ord-addr':
        rec = struct.pack('<IIIII', rec_size, name_off, ord_off, addr_off, 1)
    else:
        rec = struct.pack('<IIIII', rec_size, name_off, 1, ord_off, addr_off)
    sec[0:20] = rec
    imp_off = len(img)
    img.extend(sec)
    struct.pack_into('<I', img, 0x6c, imp_off)
    if iat_rel == 'code':
        struct.pack_into('<I', img, 0x7c, imp_off + addr_off - code_off)
    else:
        struct.pack_into('<I', img, 0x7c, imp_off + addr_off)
    struct.pack_into('<I', img, count_at, 1)
    fix_crc(img)
    return img


variants = []
for order in ('name-ord-addr', 'name-count-ord'):
    for ordsize in (4, 2):
        for count_at in (0x54, 0x58):
            for iat_rel in ('code', 'abs'):
                variants.append((order, ordsize, count_at, iat_rel))

for i, v in enumerate(variants):
    img = build(*v)
    path = 'iv_%02d.e32' % i
    open(path, 'wb').write(img)
    r = subprocess.run([TOOL, '--e32input=' + path, '--dump=i'], capture_output=True, text=True)
    out = ((r.stdout or '') + (r.stderr or '')).strip()
    first = ' | '.join(out.splitlines()[1:4])
    print(i, v, '->', first)
