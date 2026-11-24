#include "ac_crypto.h"
#include <windows.h>

static u32 rol32(u32 x, int n) { return (x << n) | (x >> (32 - n)); }
static u32 ror32(u32 x, int n) { return (x >> n) | (x << (32 - n)); }

void sha1(const void *data, size_t len, u8 out[20])
{
    Sha1 c;
    sha1_init(&c);
    sha1_update(&c, data, len);
    sha1_final(&c, out);
}

static void sha1_block(Sha1 *c, const u8 *p)
{
    u32 w[80], a, b, d, e, f, k, t, cc;
    int i;
    for (i = 0; i < 16; i++)
        w[i] = ((u32)p[i * 4] << 24) | ((u32)p[i * 4 + 1] << 16) | ((u32)p[i * 4 + 2] << 8) | p[i * 4 + 3];
    for (i = 16; i < 80; i++)
        w[i] = rol32(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
    a = c->h[0];
    b = c->h[1];
    cc = c->h[2];
    d = c->h[3];
    e = c->h[4];
    for (i = 0; i < 80; i++) {
        if (i < 20) {
            f = (b & cc) | ((~b) & d);
            k = 0x5a827999u;
        } else if (i < 40) {
            f = b ^ cc ^ d;
            k = 0x6ed9eba1u;
        } else if (i < 60) {
            f = (b & cc) | (b & d) | (cc & d);
            k = 0x8f1bbcdcu;
        } else {
            f = b ^ cc ^ d;
            k = 0xca62c1d6u;
        }
        t = rol32(a, 5) + f + e + k + w[i];
        e = d;
        d = cc;
        cc = rol32(b, 30);
        b = a;
        a = t;
    }
    c->h[0] += a;
    c->h[1] += b;
    c->h[2] += cc;
    c->h[3] += d;
    c->h[4] += e;
}

void sha1_init(Sha1 *c)
{
    c->h[0] = 0x67452301u;
    c->h[1] = 0xefcdab89u;
    c->h[2] = 0x98badcfeu;
    c->h[3] = 0x10325476u;
    c->h[4] = 0xc3d2e1f0u;
    c->len = 0;
    c->n = 0;
}

void sha1_update(Sha1 *c, const void *data, size_t len)
{
    const u8 *p = data;
    c->len += len;
    while (len) {
        u32 take = 64 - c->n;
        if (take > len)
            take = (u32)len;
        memcpy(c->buf + c->n, p, take);
        c->n += take;
        p += take;
        len -= take;
        if (c->n == 64) {
            sha1_block(c, c->buf);
            c->n = 0;
        }
    }
}

void sha1_final(Sha1 *c, u8 out[20])
{
    u64 bits = c->len * 8;
    u8 pad = 0x80;
    u8 zeros[64];
    u8 lenb[8];
    int i;
    memset(zeros, 0, sizeof(zeros));
    sha1_update(c, &pad, 1);
    while (c->n != 56)
        sha1_update(c, zeros, 1);
    for (i = 0; i < 8; i++)
        lenb[i] = (u8)(bits >> (56 - i * 8));
    memcpy(c->buf + c->n, lenb, 8);
    c->n += 8;
    sha1_block(c, c->buf);
    for (i = 0; i < 5; i++) {
        out[i * 4] = (u8)(c->h[i] >> 24);
        out[i * 4 + 1] = (u8)(c->h[i] >> 16);
        out[i * 4 + 2] = (u8)(c->h[i] >> 8);
        out[i * 4 + 3] = (u8)c->h[i];
    }
}

static const u32 k256[64] = {
    0x428a2f98u, 0x71374491u, 0xb5c0fbcfu, 0xe9b5dba5u, 0x3956c25bu, 0x59f111f1u, 0x923f82a4u, 0xab1c5ed5u,
    0xd807aa98u, 0x12835b01u, 0x243185beu, 0x550c7dc3u, 0x72be5d74u, 0x80deb1feu, 0x9bdc06a7u, 0xc19bf174u,
    0xe49b69c1u, 0xefbe4786u, 0x0fc19dc6u, 0x240ca1ccu, 0x2de92c6fu, 0x4a7484aau, 0x5cb0a9dcu, 0x76f988dau,
    0x983e5152u, 0xa831c66du, 0xb00327c8u, 0xbf597fc7u, 0xc6e00bf3u, 0xd5a79147u, 0x06ca6351u, 0x14292967u,
    0x27b70a85u, 0x2e1b2138u, 0x4d2c6dfcu, 0x53380d13u, 0x650a7354u, 0x766a0abbu, 0x81c2c92eu, 0x92722c85u,
    0xa2bfe8a1u, 0xa81a664bu, 0xc24b8b70u, 0xc76c51a3u, 0xd192e819u, 0xd6990624u, 0xf40e3585u, 0x106aa070u,
    0x19a4c116u, 0x1e376c08u, 0x2748774cu, 0x34b0bcb5u, 0x391c0cb3u, 0x4ed8aa4au, 0x5b9cca4fu, 0x682e6ff3u,
    0x748f82eeu, 0x78a5636fu, 0x84c87814u, 0x8cc70208u, 0x90befffau, 0xa4506cebu, 0xbef9a3f7u, 0xc67178f2u};

static void sha256_block(Sha256 *c, const u8 *p)
{
    u32 w[64], a, b, cc, d, e, f, g, h, t1, t2;
    int i;
    for (i = 0; i < 16; i++)
        w[i] = ((u32)p[i * 4] << 24) | ((u32)p[i * 4 + 1] << 16) | ((u32)p[i * 4 + 2] << 8) | p[i * 4 + 3];
    for (i = 16; i < 64; i++) {
        u32 s0 = ror32(w[i - 15], 7) ^ ror32(w[i - 15], 18) ^ (w[i - 15] >> 3);
        u32 s1 = ror32(w[i - 2], 17) ^ ror32(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }
    a = c->h[0];
    b = c->h[1];
    cc = c->h[2];
    d = c->h[3];
    e = c->h[4];
    f = c->h[5];
    g = c->h[6];
    h = c->h[7];
    for (i = 0; i < 64; i++) {
        t1 = h + (ror32(e, 6) ^ ror32(e, 11) ^ ror32(e, 25)) + ((e & f) ^ ((~e) & g)) + k256[i] + w[i];
        t2 = (ror32(a, 2) ^ ror32(a, 13) ^ ror32(a, 22)) + ((a & b) ^ (a & cc) ^ (b & cc));
        h = g;
        g = f;
        f = e;
        e = d + t1;
        d = cc;
        cc = b;
        b = a;
        a = t1 + t2;
    }
    c->h[0] += a;
    c->h[1] += b;
    c->h[2] += cc;
    c->h[3] += d;
    c->h[4] += e;
    c->h[5] += f;
    c->h[6] += g;
    c->h[7] += h;
}

void sha256_init(Sha256 *c)
{
    static const u32 iv[8] = {0x6a09e667u, 0xbb67ae85u, 0x3c6ef372u, 0xa54ff53au,
                              0x510e527fu, 0x9b05688cu, 0x1f83d9abu, 0x5be0cd19u};
    memcpy(c->h, iv, sizeof(iv));
    c->len = 0;
    c->n = 0;
}

void sha256_update(Sha256 *c, const void *data, size_t len)
{
    const u8 *p = data;
    c->len += len;
    while (len) {
        u32 take = 64 - c->n;
        if (take > len)
            take = (u32)len;
        memcpy(c->buf + c->n, p, take);
        c->n += take;
        p += take;
        len -= take;
        if (c->n == 64) {
            sha256_block(c, c->buf);
            c->n = 0;
        }
    }
}

void sha256_final(Sha256 *c, u8 out[32])
{
    u64 bits = c->len * 8;
    u8 pad = 0x80;
    u8 zeros[64];
    u8 lenb[8];
    int i;
    memset(zeros, 0, sizeof(zeros));
    sha256_update(c, &pad, 1);
    while (c->n != 56)
        sha256_update(c, zeros, 1);
    for (i = 0; i < 8; i++)
        lenb[i] = (u8)(bits >> (56 - i * 8));
    memcpy(c->buf + c->n, lenb, 8);
    c->n += 8;
    sha256_block(c, c->buf);
    for (i = 0; i < 8; i++) {
        out[i * 4] = (u8)(c->h[i] >> 24);
        out[i * 4 + 1] = (u8)(c->h[i] >> 16);
        out[i * 4 + 2] = (u8)(c->h[i] >> 8);
        out[i * 4 + 3] = (u8)c->h[i];
    }
}

void sha256(const void *data, size_t len, u8 out[32])
{
    Sha256 c;
    sha256_init(&c);
    sha256_update(&c, data, len);
    sha256_final(&c, out);
}

u32 crc32_ieee(const void *data, size_t len)
{
    const u8 *p = data;
    u32 crc = 0xffffffffu;
    size_t i;
    int k;
    for (i = 0; i < len; i++) {
        crc ^= p[i];
        for (k = 0; k < 8; k++)
            crc = (crc >> 1) ^ (0xedb88320u & (0u - (crc & 1u)));
    }
    return ~crc;
}

void ac_random(void *buf, size_t len)
{
    typedef BOOLEAN (WINAPI *RtlGenRandomFn)(PVOID, ULONG);
    static RtlGenRandomFn fn;
    if (!fn) {
        HMODULE h = LoadLibraryA("advapi32.dll");
        if (h)
            fn = (RtlGenRandomFn)(void *)GetProcAddress(h, "SystemFunction036");
    }
    if (fn && fn(buf, (ULONG)len))
        return;
    {
        static u64 seed;
        u8 *p = buf;
        size_t i;
        if (!seed)
            seed = (u64)GetTickCount64() ^ ((u64)(uintptr_t)&seed << 17) ^ 0x9e3779b97f4a7c15ull;
        for (i = 0; i < len; i++) {
            seed ^= seed << 13;
            seed ^= seed >> 7;
            seed ^= seed << 17;
            p[i] = (u8)(seed >> 24);
        }
    }
}
