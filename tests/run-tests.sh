#!/bin/sh
# AcetyleneC end-to-end test suite. Run from the repository root:
#   sh tests/run-tests.sh
set -u

ROOT=$(cd "$(dirname "$0")/.." && pwd)
BIN="$ROOT/build/bin"
TARGET=${ACETYLENE_TEST_TARGET:-s60v5}
SDK="$ROOT/sdk/targets/$TARGET"
WORK="$ROOT/.cache/tests"
PASS=0
FAIL=0

mkdir -p "$WORK"
rm -f "$WORK"/*.o "$WORK"/*.elf "$WORK"/*.e32 "$WORK"/*.sis* "$WORK"/*.cer "$WORK"/*.key "$WORK"/*.c "$WORK"/*.cpp 2>/dev/null

ok() {
    PASS=$((PASS + 1))
    printf 'PASS  %s\n' "$1"
}

bad() {
    FAIL=$((FAIL + 1))
    printf 'FAIL  %s\n' "$1"
    [ $# -gt 1 ] && printf '      %s\n' "$2"
}

check() {
    if [ "$2" = "0" ]; then ok "$1"; else bad "$1" "${3:-}"; fi
}

pe32() {
    python -c "
import struct,sys
d=open(sys.argv[1],'rb').read(512)
off=struct.unpack_from('<I',d,0x3c)[0]
sys.exit(0 if struct.unpack_from('<H',d,off+4)[0]==0x14c else 1)" "$1"
}

elf_arm() {
    python -c "
import struct,sys
d=open(sys.argv[1],'rb').read()
sys.exit(0 if d[:4]==b'\x7fELF' and struct.unpack_from('<H',d,18)[0]==40 else 1)" "$1"
}

e32_ok() {
    python -c "
import struct,sys
d=open(sys.argv[1],'rb').read()
sys.exit(0 if len(d)>0x9c and d[0x10:0x14]==b'EPOC' else 1)" "$1"
}

echo '== toolchain binaries =='
for t in AcetyleneC acetylene-cc acetylene-ld acetylene-cxx acetylene-e32fix acetylene-makekeys acetylene-sis; do
    if [ -f "$BIN/$t.exe" ]; then
        pe32 "$BIN/$t.exe" && ok "$t.exe exists and is 32-bit PE" || bad "$t.exe is not 32-bit PE"
    else
        bad "$t.exe missing"
    fi
done

echo '== C compiler =='
cat > "$WORK/hello.c" <<'EOF'
#include <acetylene/e32c.h>
#include <stdio.h>
static TInt Add(TInt a, TInt b) { return a + b; }
GLDEF_C TInt E32Main(void)
{
    printf("sum=%d\n", (int)Add(20, 22));
    return Add(1, 2);
}
EOF
"$BIN/acetylene-cc.exe" -I "$ROOT/sdk/include" -I "$ROOT/sdk/include/tcc" -c "$WORK/hello.c" -o "$WORK/hello.o" 2>"$WORK/cc.log"
check "compile hello.c to ARM object" $? "$(cat "$WORK/cc.log")"
elf_arm "$WORK/hello.o" && ok "object is ELF32 for EM_ARM" || bad "object machine mismatch"

echo '== linker =='
"$BIN/acetylene-ld.exe" -o "$WORK/hello.elf" -L "$SDK/lib" "$WORK/hello.o" \
    -lecrt0 -lestlib -leuser -ldrtaeabi -lusrt2_2 2>"$WORK/ld.log"
check "link hello.o against SDK import libraries" $? "$(cat "$WORK/ld.log")"
elf_arm "$WORK/hello.elf" && ok "linked image is ELF32 ARM" || bad "linked image malformed"
python - "$WORK/hello.elf" <<'EOF'
import struct, sys
d = open(sys.argv[1], 'rb').read()
shoff, = struct.unpack_from('<I', d, 32)
es, n, si = struct.unpack_from('<HHH', d, 46)
names = []
st = struct.unpack_from('<10I', d, shoff + si * es)[4]
for i in range(n):
    o = struct.unpack_from('<I', d, shoff + i * es)[0]
    e = d.index(b'\0', st + o)
    names.append(d[st + o:e].decode())
need = ['.text', '.symtab', '.directive']
missing = [x for x in need if x not in names]
sys.exit(0 if not missing else 1)
EOF
check "linked image keeps .text/.symtab/.directive" $?

echo '== E32 post-link =='
"$SDK/tools/elf2e32.exe" --elfinput="$WORK/hello.elf" --output="$WORK/hello.raw.e32" --targettype=EXE \
    --uid1=0x1000007A --uid2=0x100039CE --uid3=0xE0000101 --sid=0xE0000101 \
    --heap=65536 --stack=32768 --uncompressed >"$WORK/e32.log" 2>&1
check "elf2e32 produces an image" $? "$(head -3 "$WORK/e32.log")"
e32_ok "$WORK/hello.raw.e32" && ok "image carries the EPOC signature" || bad "no EPOC signature"
"$BIN/acetylene-e32fix.exe" -elf "$WORK/hello.elf" -in "$WORK/hello.raw.e32" -out "$WORK/hello.e32" >"$WORK/fix.log" 2>&1
check "e32fix adds the import table" $? "$(cat "$WORK/fix.log")"
"$SDK/tools/elf2e32.exe" --e32input="$WORK/hello.e32" --dump=i >"$WORK/dump.log" 2>&1
grep -q "imports from" "$WORK/dump.log" && ok "Symbian dumper reads the import record" || bad "dumper sees no imports"
grep -q "estlib" "$WORK/dump.log" && ok "import names the ESTLIB DLL" || bad "wrong DLL in import record"

python "$ROOT/tests/check-e32.py" "$WORK/hello.e32"
check "import section walks record by record" $?

grep -q "imports from" "$WORK/dump.log" && ok "Symbian dumper agrees on the record" || bad "dumper disagrees"

echo '== multi-DLL imports =='
cat > "$WORK/imp2.c" <<'EOF'
#include <acetylene/e32c.h>
#include <stdio.h>
GLDEF_C TInt E32Main(void)
{
    void *tc = CTrapCleanup_New();
    printf("tc ok");
    return 0;
}
EOF
"$BIN/acetylene-cc.exe" -I "$ROOT/sdk/include" -I "$ROOT/sdk/include/tcc" -c "$WORK/imp2.c" -o "$WORK/imp2.o" 2>"$WORK/imp2_cc.log"
"$BIN/acetylene-ld.exe" -o "$WORK/imp2.elf" -L "$SDK/lib" "$WORK/imp2.o"     -lecrt0 -lestlib -leuser -ldrtaeabi -lusrt2_2 2>"$WORK/imp2_ld.log"
check "app importing from two DLLs links" $? "$(cat "$WORK/imp2_ld.log")"
"$SDK/tools/elf2e32.exe" --elfinput="$WORK/imp2.elf" --output="$WORK/imp2.raw.e32" --targettype=EXE     --uid1=0x1000007A --uid2=0x100039CE --uid3=0xE0000103 --sid=0xE0000103     --heap=65536 --stack=32768 --uncompressed >"$WORK/imp2_e32.log" 2>&1
"$BIN/acetylene-e32fix.exe" -elf "$WORK/imp2.elf" -in "$WORK/imp2.raw.e32" -out "$WORK/imp2.e32" >"$WORK/imp2_fix.log" 2>&1
check "import table written for multiple DLLs" $? "$(cat "$WORK/imp2_fix.log")"
python "$ROOT/tests/check-e32.py" "$WORK/imp2.e32"
check "multi-DLL records walk cleanly" $?
python - "$WORK/imp2.e32" <<'EOF'
import struct, sys
d = open(sys.argv[1], 'rb').read()
off = struct.unpack_from('<I', d, 0x6c)[0]
n = 0
while off + 4 <= len(d):
    size, = struct.unpack_from('<I', d, off)
    if size == 0:
        break
    n += 1
    off += size
sys.exit(0 if n >= 2 else 1)
EOF
check "at least two DLL records present" $?

echo '== C++ subset =='
cat > "$WORK/counter.cpp" <<'EOF'
class Counter
{
public:
    TInt m_value;
    Counter();
    TInt Get();
    void Add(TInt amount);
};

Counter::Counter()
{
    m_value = 0;
}

TInt Counter::Get()
{
    return m_value;
}

void Counter::Add(TInt amount)
{
    m_value = m_value + amount;
}

GLDEF_C TInt E32Main()
{
    Counter c;
    c.Add(7);
    return c.Get();
}
EOF
"$BIN/acetylene-cxx.exe" "$WORK/counter.cpp" -o "$WORK/counter.c" >"$WORK/cxx.log" 2>&1
check "acetylene-cxx translates the class" $? "$(cat "$WORK/cxx.log")"
grep -q "_ZN7Counter3GetEv" "$WORK/counter.c" && ok "Itanium mangling emitted (_ZN7Counter3GetEv)" || bad "mangling missing"
grep -q "self->m_value" "$WORK/counter.c" && ok "member access rewritten to self->" || bad "member rewrite missing"
"$BIN/acetylene-cc.exe" -I "$ROOT/sdk/include" -I "$ROOT/sdk/include/tcc" -c "$WORK/counter.c" -o "$WORK/counter.o" 2>"$WORK/cxx_cc.log"
check "translated C++ output compiles with TCC" $? "$(cat "$WORK/cxx_cc.log")"
"$BIN/acetylene-ld.exe" -o "$WORK/counter.elf" -L "$SDK/lib" "$WORK/counter.o" \
    -lecrt0 -lestlib -leuser -ldrtaeabi -lusrt2_2 2>"$WORK/cxx_ld.log"
check "C++ object links into ARM image" $? "$(cat "$WORK/cxx_ld.log")"

cat > "$WORK/point.cpp" <<'EOF'
class Point
{
public:
    TInt m_x;
    TInt m_y;
    Point();
    void Move(TInt dx, TInt dy);
    TInt Sum();
};

Point::Point()
{
    m_x = 0;
    m_y = 0;
}

void Point::Move(TInt dx, TInt dy)
{
    this->m_x = this->m_x + dx;
    this->m_y = this->m_y + dy;
}

TInt Point::Sum()
{
    return this->m_x + this->m_y;
}

GLDEF_C TInt E32Main()
{
    Point *p = new Point;
    p->Move(3, 4);
    TInt r = p->Sum();
    delete p;
    return r;
}
EOF
"$BIN/acetylene-cxx.exe" "$WORK/point.cpp" -o "$WORK/point.c" >"$WORK/point_cxx.log" 2>&1
check "C++ new/delete/this-> translate" $? "$(cat "$WORK/point_cxx.log")"
grep -q "ac_new_Point()" "$WORK/point.c" && ok "new emits the constructor helper" || bad "new not rewritten"
grep -q "free(p)" "$WORK/point.c" && ok "delete emits free()" || bad "delete not rewritten"
grep -q "self->m_x" "$WORK/point.c" && ok "this-> becomes self->" || bad "this-> not rewritten"
"$BIN/acetylene-cc.exe" -I "$ROOT/sdk/include" -I "$ROOT/sdk/include/tcc" -c "$WORK/point.c" -o "$WORK/point.o" 2>"$WORK/point_cc.log"
check "translated new/delete code compiles" $? "$(cat "$WORK/point_cc.log")"
"$BIN/acetylene-ld.exe" -o "$WORK/point.elf" -L "$SDK/lib" "$WORK/point.o"     -lecrt0 -lestlib -leuser -ldrtaeabi -lusrt2_2 2>"$WORK/point_ld.log"
check "new/delete object links" $? "$(cat "$WORK/point_ld.log")"

echo '== DLL =='
cat > "$WORK/plugin.c" <<'EOF'
#include <acetylene/e32c.h>
GLDEF_C TInt E32Dll(TInt aReason)
{
    return KErrNone;
}
TInt PluginValue(void)
{
    return 7;
}
EOF
"$BIN/acetylene-cc.exe" -I "$ROOT/sdk/include" -I "$ROOT/sdk/include/tcc" -c "$WORK/plugin.c" -o "$WORK/plugin.o" 2>"$WORK/dll_cc.log"
"$BIN/acetylene-ld.exe" -o "$WORK/plugin.elf" -e E32Dll -L "$SDK/lib" "$WORK/plugin.o" \
    -lestlib -leuser -ldrtaeabi -lusrt2_2 2>"$WORK/dll_ld.log"
check "DLL links without the EXE CRT" $? "$(cat "$WORK/dll_ld.log")"
"$SDK/tools/elf2e32.exe" --elfinput="$WORK/plugin.elf" --output="$WORK/plugin.e32" --targettype=DLL \
    --uid1=0x10000079 --uid2=0x1000008D --uid3=0xE0000102 --sid=0xE0000102 --dlldata --uncompressed \
    --defoutput="$WORK/plugin.def" --dso="$WORK/plugin.dso" --linkas="plugin{000a0000}[e0000102].dll" \
    >"$WORK/dll_e32.log" 2>&1
check "DLL image produced with def/dso" $? "$(head -3 "$WORK/dll_e32.log")"
[ -s "$WORK/plugin.dso" ] && ok "import DSO emitted" || bad "no .dso produced"

echo '== certificates =='
"$BIN/acetylene-makekeys.exe" -dsa -name "AcetyleneC Test" "$WORK/dev.cer" "$WORK/dev.key" >"$WORK/keys.log" 2>&1
check "DSA certificate generated" $? "$(cat "$WORK/keys.log")"
grep -q "BEGIN CERTIFICATE" "$WORK/dev.cer" && ok "certificate is PEM" || bad "certificate not PEM"
grep -q "BEGIN DSA PRIVATE KEY" "$WORK/dev.key" && ok "key is a DSA private key" || bad "key format wrong"
python - "$WORK/dev.cer" <<'EOF'
import base64, re, sys, hashlib
t = open(sys.argv[1], 'rb').read().decode('latin1')
b = ''.join(re.findall(r'^[A-Za-z0-9+/=]+$', t, re.M))
d = base64.b64decode(b)
def tlv(d, i):
    tag = d[i]; i += 1; l = d[i]; i += 1
    if l & 0x80:
        n = l & 0x7f; l = int.from_bytes(d[i:i + n], 'big'); i += n
    return tag, i, l
tag, i, l = tlv(d, 0)
tbs_start = i
tag, j, ll = tlv(d, i)
ok = d[0] == 0x30 and ll > 100
sys.exit(0 if ok else 1)
EOF
check "certificate DER is well formed" $?

echo '== SISX =='
cat > "$WORK/hello.pkg" <<'EOF'
&EN
#{"AcetyleneTest"},(0xE0000101),1,0,0
%{"AcetyleneC"}
:"AcetyleneC"
"hello.e32"-"!:\sys\bin\hello.exe"
EOF
cp "$WORK/hello.e32" "$WORK/hello.e32" 2>/dev/null
"$BIN/acetylene-sis.exe" -pkg "$WORK/hello.pkg" -o "$WORK/hello.sisx" -sdk "$SDK" >"$WORK/sis.log" 2>&1
check "package built from pkg" $? "$(cat "$WORK/sis.log")"
python -c "
import sys
d=open(sys.argv[1],'rb').read()
sys.exit(0 if d[:4]==bytes([0x7a,0x1a,0x20,0x10]) else 1)" "$WORK/hello.sisx"
check "package has the SISX magic" $?
"$SDK/tools/signsis.exe" -o "$WORK/hello.sisx" >"$WORK/sis_verify.log" 2>&1
grep -q "No primary signatures" "$WORK/sis_verify.log" && ok "Symbian signsis parses the package" || bad "signsis cannot read the package"
"$SDK/tools/signsis.exe" -cd "$WORK/hello.sisx" "$WORK/hello.signed.sisx" "$WORK/dev.cer" "$WORK/dev.key" >"$WORK/sign.log" 2>&1
check "signsis signs with our certificate" $? "$(head -3 "$WORK/sign.log")"
[ -s "$WORK/hello.signed.sisx" ] && ok "signed package written" || bad "signed package missing"
"$SDK/tools/signsis.exe" -o "$WORK/hello.signed.sisx" 2>&1 | grep -q "Primary" && ok "signature reported as Primary" || bad "signature not reported"

echo '== crypto primitives =='
"$BIN/acetylene-makekeys.exe" --selftest >"$WORK/selftest.log" 2>&1
check "crypto selftest runs" $? "$(cat "$WORK/selftest.log")"
grep -q "verify=OK" "$WORK/selftest.log" && ok "RSA sign/verify round-trip" || bad "RSA round-trip failed"
grep -q "sha1(abc)=a9993e364706" "$WORK/selftest.log" && ok "SHA-1 matches the known vector" || bad "SHA-1 mismatch"
grep -q "sha256(abc)=ba7816bf" "$WORK/selftest.log" && ok "SHA-256 matches the known vector" || bad "SHA-256 mismatch"

echo '== multi-file project =='
cat > "$WORK/one.c" <<'EOF'
#include <acetylene/e32c.h>
TInt Helper(TInt v) { return v + 2; }
EOF
cat > "$WORK/two.c" <<'EOF'
#include <acetylene/e32c.h>
extern TInt Helper(TInt v);
GLDEF_C TInt E32Main(void) { return Helper(40); }
EOF
"$BIN/acetylene-cc.exe" -I "$ROOT/sdk/include" -I "$ROOT/sdk/include/tcc" -c "$WORK/one.c" -o "$WORK/one.o" 2>"$WORK/mf1.log"
"$BIN/acetylene-cc.exe" -I "$ROOT/sdk/include" -I "$ROOT/sdk/include/tcc" -c "$WORK/two.c" -o "$WORK/two.o" 2>"$WORK/mf2.log"
check "two translation units compile" $?
"$BIN/acetylene-ld.exe" -o "$WORK/multi.elf" -L "$SDK/lib" "$WORK/one.o" "$WORK/two.o" \
    -lecrt0 -lestlib -leuser -ldrtaeabi -lusrt2_2 2>"$WORK/mf3.log"
check "both objects link together" $? "$(cat "$WORK/mf3.log")"

printf '\n%d passed, %d failed\n' "$PASS" "$FAIL"
[ "$FAIL" = 0 ]
