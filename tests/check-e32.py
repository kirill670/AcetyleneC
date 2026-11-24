import struct
import sys

path = sys.argv[1]
d = open(path, 'rb').read()
if len(d) < 0xa0:
    sys.exit(1)
imp, = struct.unpack_from('<I', d, 0x6c)
code_off, = struct.unpack_from('<I', d, 0x64)
if imp == 0 or imp >= len(d):
    sys.exit(1)
off = imp
seen = 0
while off + 4 <= len(d):
    size, = struct.unpack_from('<I', d, off)
    if size == 0:
        break
    if size < 20 or off + size > len(d):
        sys.exit(1)
    name_off, count, addr_off, ord_off = struct.unpack_from('<IIII', d, off + 4)
    if count <= 0:
        sys.exit(1)
    if name_off >= size:
        sys.exit(1)
    if code_off + addr_off + 4 * count > len(d):
        sys.exit(1)
    if code_off + ord_off + 4 * count > len(d):
        sys.exit(1)
    name = d[off + name_off:off + size].split(bytes([0]))[0]
    if not name or b'.dll' not in name.lower():
        sys.exit(1)
    seen += 1
    off += size
sys.exit(0 if seen >= 1 else 1)
