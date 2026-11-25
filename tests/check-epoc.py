import struct
import sys

path = sys.argv[1]
d = open(path, "rb").read()

fails = []


def need(cond, msg):
    if not cond:
        fails.append(msg)


if len(d) < 0x7C:
    print("FAIL: file shorter than the image header")
    sys.exit(1)

uid1, uid2, uid3, check = struct.unpack_from("<4I", d, 0)
sig, cpu, codechk, fmt = struct.unpack_from("<4I", d, 0x10)
ver = struct.unpack_from("<I", d, 0x20)[0]
flags = struct.unpack_from("<I", d, 0x2C)[0]
code, data, heapmin, heapmax, stack, bss = struct.unpack_from("<6I", d, 0x30)
entry, codebase, database, dllref = struct.unpack_from("<4I", d, 0x48)
expdir, expcnt, text, codeoff, dataoff, impoff = struct.unpack_from("<6I", d, 0x58)
codrel, datrel, prio = struct.unpack_from("<3I", d, 0x70)

need(sig == 0x434F5045, "signature is not EPOC")
need(cpu == 0x2000, "cpu is not ARM")
need(uid1 == 0x100039CE, "uid1 is not the app uid")
need(ver == 0x00C00001, "version is not 1.0(192)")
need(flags & 0x01000000, "image is not in format J")
need(codebase == 0x400000, "code base is not 0x400000")
need(entry < text, "entry point is outside the text")
need(codeoff == 0x7C, "code does not start at 0x7C")
need(codeoff + code <= len(d), "code section runs past the end of the file")
need(bss == 0 or database == codebase + code, "data base does not follow the code")

code_bytes = d[codeoff:codeoff + code]
total = 0
for i in range(0, len(code_bytes) - 3, 4):
    total = (total + struct.unpack_from("<I", code_bytes, i)[0]) & 0xFFFFFFFF
need(total == codechk, "code checksum does not match the text words")

if impoff:
    isize, nameoff, count = struct.unpack_from("<3I", d, impoff)
    need(impoff + isize + 4 <= len(d), "import section runs past the end of the file")
    st = impoff + nameoff
    end = d.find(b"\0", st)
    need(end > st, "dll name is not terminated")
    name = d[st:end]
    need(b"[" in name and name.endswith(b".DLL"), "dll name is not NAME[uid].DLL")
    need(count > 0, "import section lists no imports")
    need(text + dllref * 4 <= code, "iat does not fit into the code section")
    for i in range(count):
        ordv = struct.unpack_from("<I", d, impoff + 12 + i * 4)[0]
        need(ordv != 0, "import %d has ordinal 0" % i)
        slot = struct.unpack_from("<I", d, codeoff + text + i * 4)[0]
        need(slot == ordv, "iat slot %d does not hold its ordinal" % i)
    thunk = bytes.fromhex("04c09fe500c09ce51cff2fe1")
    pos = code_bytes.find(thunk)
    need(pos >= 0, "no import thunk in the code")
    if pos >= 0:
        lit = struct.unpack_from("<I", code_bytes, pos + 12)[0]
        need(lit == codebase + text, "import thunk does not point at the iat")

if fails:
    for f in fails:
        print("FAIL: " + f)
    sys.exit(1)

print("ok: %s code=%#x data=%#x bss=%#x entry=%#x imports=%d" % (path, code, data, bss, entry, dllref))
