import struct
import sys

src, dst = sys.argv[1], sys.argv[2]
soname = sys.argv[3] if len(sys.argv) > 3 else "app{000a0000}[0xe0000001].exe"

d = bytearray(open(src, 'rb').read())
e_shoff, = struct.unpack_from('<I', d, 32)
es, n, si = struct.unpack_from('<HHH', d, 46)
secs = [list(struct.unpack_from('<10I', d, e_shoff + i * es)) for i in range(n)]


def sname(off):
    st = secs[si][4]
    e = d.index(b'\0', st + off)
    return d[st + off:e].decode('latin1')


names = [sname(s[0]) for s in secs]
idx = {nm: i for i, nm in enumerate(names)}
symi = idx['.symtab']
sym = secs[symi]
strt = secs[sym[6]][4]


def syminfo(i):
    base = sym[4] + i * 16
    no, val, sz, info, oth, shndx = struct.unpack_from('<IIIBBH', d, base)
    e = d.index(b'\0', strt + no)
    return d[strt + no:e].decode('latin1'), val, shndx


rel = secs[idx['.rel.text']]
markers = []
for k in range(rel[5] // 8):
    off, info = struct.unpack_from('<II', d, rel[4] + k * 8)
    nm = syminfo(info >> 8)[0]
    if nm.startswith('#<'):
        entry = (off, nm)
        if nm not in [m[1] for m in markers]:
            markers.append(entry)
        else:
            markers.append(entry)

dynstr = bytearray(b'\0')
stroff = {}
for _, nm in markers:
    if nm in stroff:
        continue
    stroff[nm] = len(dynstr)
    dynstr.extend(nm.encode() + b'\0')

dynsym = bytearray(16)
for _, nm in markers:
    dynsym.extend(struct.pack('<IIIBBH', stroff[nm], 0, 0, 0x10, 0, 0))

nb = 101
buckets = [0] * nb
chains = [0] * (len(stroff) + 1)


def elfh(s):
    h = 0
    for c in s.encode():
        h = ((h << 4) + c) & 0xffffffff
        g = h & 0xf0000000
        if g:
            h ^= g >> 24
        h &= ~g
    return h


order = []
for nm in stroff:
    order.append(nm)
for i, nm in enumerate(order):
    b = elfh(nm) % nb
    chains[i + 1] = buckets[b]
    buckets[b] = i + 1

hasht = bytearray(struct.pack('<II', nb, len(order) + 1))
for b in buckets:
    hasht.extend(struct.pack('<I', b))
for c in chains:
    hasht.extend(struct.pack('<I', c))

orderindex = {nm: i + 1 for i, nm in enumerate(order)}
reldyn = bytearray()
for off, nm in markers:
    reldyn.extend(struct.pack('<II', off, (orderindex[nm] << 8) | 2))


def app(buf, al=4):
    while len(d) % al:
        d.append(0)
    o = len(d)
    d.extend(buf)
    return o


o_ds = app(dynsym)
o_dstr = app(dynstr)
o_hash = app(hasht)
o_rel = app(reldyn)

soname_off = len(dynstr)
dynstr.extend(soname.encode() + b'\0')

dyn = bytearray()
dyn.extend(struct.pack('<II', 4, o_hash))
dyn.extend(struct.pack('<II', 5, o_dstr))
dyn.extend(struct.pack('<II', 6, o_ds))
dyn.extend(struct.pack('<II', 10, len(dynstr)))
dyn.extend(struct.pack('<II', 11, 16))
dyn.extend(struct.pack('<II', 0x90000001, len(order) + 1))
dyn.extend(struct.pack('<II', 14, soname_off))
dyn.extend(struct.pack('<II', 0, 0))
o_dyn = app(dyn)

shstr = bytearray(d[secs[si][4]:secs[si][4] + secs[si][5]])


def addname(s):
    p = len(shstr)
    shstr.extend(s.encode() + b'\0')
    return p


n_ds = addname('.dynsym')
n_dstr = addname('.dynstr')
n_hash = addname('.hash')
n_dyn = addname('.dynamic')
n_rel = addname('.rel.dyn')
o_sh = app(shstr)
secs[si][4] = o_sh
secs[si][5] = len(shstr)

base = len(secs)
secs.append([n_ds, 11, 2, 0, o_ds, len(dynsym), base + 1, 1, 4, 16])
secs.append([n_dstr, 3, 2, 0, o_dstr, len(dynstr), 0, 0, 1, 0])
secs.append([n_hash, 5, 2, 0, o_hash, len(hasht), 0, 0, 4, 4])
secs.append([n_dyn, 6, 3, 0, o_dyn, len(dyn), base + 1, 0, 4, 8])
secs.append([n_rel, 9, 0, 0, o_rel, len(reldyn), 0, 0, 4, 8])

while len(d) % 4:
    d.append(0)
ns = len(d)
for s in secs:
    d.extend(struct.pack('<10I', *s))
struct.pack_into('<H', d, 16, 3)
struct.pack_into('<I', d, 32, ns)
struct.pack_into('<H', d, 48, len(secs))
struct.pack_into('<H', d, 50, si)
open(dst, 'wb').write(d)
print('imports', len(order), 'relocs', len(markers))
