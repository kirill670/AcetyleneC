#include "ac_crypto.h"

static void bn_set_small(BigNum *a, u32 v);
static u32 bn_mod_small(const BigNum *a, u32 m);
static int bn_shl(BigNum *a, int bits);

void bn_zero(BigNum *a)
{
    memset(a->d, 0, sizeof(a->d));
    a->n = 0;
}

void bn_from_bytes(BigNum *a, const u8 *data, size_t len)
{
    size_t i;
    bn_zero(a);
    while (len > 0 && data[0] == 0) {
        data++;
        len--;
    }
    for (i = 0; i < len; i++) {
        size_t byte = len - 1 - i;
        size_t limb = byte / 4;
        int shift = (int)(byte % 4) * 8;
        if (limb >= AC_BN_LIMBS)
            break;
        a->d[limb] |= (u32)data[i] << shift;
    }
    a->n = 0;
    for (i = 0; i < AC_BN_LIMBS; i++)
        if (a->d[i])
            a->n = (int)i + 1;
}

size_t bn_to_bytes(const BigNum *a, u8 *out, size_t outlen)
{
    size_t need = (size_t)a->n * 4;
    size_t i;
    if (need > outlen)
        need = outlen;
    memset(out, 0, outlen);
    for (i = 0; i < need; i++) {
        size_t byte = need - 1 - i;
        size_t limb = byte / 4;
        int shift = (int)(byte % 4) * 8;
        if (limb < (size_t)a->n)
            out[outlen - need + i] = (u8)(a->d[limb] >> shift);
    }
    return outlen;
}

int bn_cmp(const BigNum *a, const BigNum *b)
{
    int i;
    if (a->n != b->n)
        return a->n < b->n ? -1 : 1;
    for (i = a->n - 1; i >= 0; i--)
        if (a->d[i] != b->d[i])
            return a->d[i] < b->d[i] ? -1 : 1;
    return 0;
}

int bn_is_zero(const BigNum *a)
{
    int i;
    for (i = 0; i < a->n; i++)
        if (a->d[i])
            return 0;
    return 1;
}

int bn_bits(const BigNum *a)
{
    int i;
    u32 v;
    if (!a->n)
        return 0;
    v = a->d[a->n - 1];
    for (i = 31; i >= 0; i--)
        if (v & (1u << i))
            return a->n * 32 - (31 - i) - 1 + 1;
    return 0;
}

int bn_bit(const BigNum *a, int i)
{
    int limb = i / 32;
    if (limb >= a->n || limb < 0)
        return 0;
    return (a->d[limb] >> (i % 32)) & 1;
}

static void bn_trim(BigNum *a)
{
    while (a->n > 0 && a->d[a->n - 1] == 0)
        a->n--;
}

void bn_add(BigNum *r, const BigNum *a, const BigNum *b)
{
    int i, max = a->n > b->n ? a->n : b->n;
    u64 carry = 0;
    for (i = 0; i < max; i++) {
        u64 s = carry;
        if (i < a->n)
            s += a->d[i];
        if (i < b->n)
            s += b->d[i];
        r->d[i] = (u32)s;
        carry = s >> 32;
    }
    if (max < AC_BN_LIMBS)
        r->d[max] = (u32)carry;
    r->n = max + (carry ? 1 : 0);
    bn_trim(r);
}

void bn_sub(BigNum *r, const BigNum *a, const BigNum *b)
{
    int i;
    i64 borrow = 0;
    for (i = 0; i < a->n; i++) {
        i64 s = (i64)a->d[i] - borrow - (i < b->n ? (i64)b->d[i] : 0);
        if (s < 0) {
            s += ((i64)1 << 32);
            borrow = 1;
        } else {
            borrow = 0;
        }
        r->d[i] = (u32)s;
    }
    r->n = a->n;
    if (r->n > 0)
        while (r->n > 0 && r->d[r->n - 1] == 0)
            r->n--;
}

void bn_mul(BigNum *r, const BigNum *a, const BigNum *b)
{
    BigNum t;
    int i, k;
    bn_zero(&t);
    for (i = 0; i < a->n; i++) {
        u64 carry = 0;
        for (k = 0; k < b->n || carry; k++) {
            u64 cur;
            if (i + k >= AC_BN_LIMBS)
                break;
            cur = (u64)t.d[i + k] + carry;
            if (k < b->n)
                cur += (u64)a->d[i] * b->d[k];
            t.d[i + k] = (u32)cur;
            carry = cur >> 32;
        }
        t.n = i + k;
        if (t.n > AC_BN_LIMBS)
            t.n = AC_BN_LIMBS;
    }
    bn_trim(&t);
    *r = t;
}

static int bn_shl(BigNum *a, int bits)
{
    int limbs = bits / 32, sh = bits % 32, i;
    if (a->n + limbs + 1 >= AC_BN_LIMBS)
        return -1;
    if (limbs) {
        for (i = a->n - 1; i >= 0; i--)
            a->d[i + limbs] = a->d[i];
        for (i = 0; i < limbs; i++)
            a->d[i] = 0;
        a->n += limbs;
    }
    if (sh) {
        u32 carry = 0;
        for (i = 0; i < a->n; i++) {
            u32 v = a->d[i];
            a->d[i] = (v << sh) | carry;
            carry = v >> (32 - sh);
        }
        if (carry) {
            a->d[a->n] = carry;
            a->n++;
        }
    }
    return 0;
}

static void bn_shr1(BigNum *a)
{
    int i;
    u32 carry = 0;
    for (i = a->n - 1; i >= 0; i--) {
        u32 v = a->d[i];
        a->d[i] = (v >> 1) | (carry << 31);
        carry = v & 1;
    }
    bn_trim(a);
}

static void bn_mod_shrink(BigNum *a, const BigNum *m)
{
    while (bn_cmp(a, m) >= 0)
        bn_sub(a, a, m);
    {
        BigNum zero;
        bn_zero(&zero);
        if (bn_cmp(a, &zero) < 0)
            *a = zero;
    }
}

void bn_mod(BigNum *r, const BigNum *a, const BigNum *m)
{
    BigNum res, tmp;
    int i, bits;
    bn_zero(&res);
    bits = bn_bits(a);
    for (i = bits - 1; i >= 0; i--) {
        int carry;
        bn_shl(&res, 1);
        if (bn_bit(a, i)) {
            res.d[0] |= 1;
            if (res.n == 0)
                res.n = 1;
        }
        if (bn_cmp(&res, m) >= 0)
            bn_sub(&res, &res, m);
        carry = 0;
        (void)carry;
    }
    bn_mod_shrink(&res, m);
    *r = res;
    (void)tmp;
}

void bn_modmul(BigNum *r, const BigNum *a, const BigNum *b, const BigNum *m)
{
    BigNum p;
    bn_mul(&p, a, b);
    bn_mod(r, &p, m);
}

typedef struct {
    BigNum n;
    u32 n0;
    int k;
} Mont;

static u32 mont_n0inv(const BigNum *n)
{
    u32 inv = 1, i;
    for (i = 0; i < 5; i++)
        inv *= 2 - n->d[0] * inv;
    return (u32)(0u - inv);
}

static void mont_init(Mont *m, const BigNum *n)
{
    m->n = *n;
    m->k = n->n;
    m->n0 = mont_n0inv(n);
}

static void mont_mul(BigNum *r, const BigNum *a, const BigNum *b, const Mont *m)
{
    u32 t[AC_BN_LIMBS + 2];
    int i, j, k = m->k;
    memset(t, 0, sizeof(u32) * (size_t)(k + 2));
    for (i = 0; i < k; i++) {
        u64 c = 0;
        u32 ai = (i < a->n) ? a->d[i] : 0;
        u32 q;
        for (j = 0; j < k; j++) {
            u64 s = (u64)t[j] + (u64)ai * ((j < b->n) ? b->d[j] : 0) + c;
            t[j] = (u32)s;
            c = s >> 32;
        }
        {
            u64 s = (u64)t[k] + c;
            t[k] = (u32)s;
            t[k + 1] = (u32)(s >> 32);
        }
        q = t[0] * m->n0;
        {
            u64 s = (u64)t[0] + (u64)q * m->n.d[0];
            c = s >> 32;
        }
        for (j = 1; j < k; j++) {
            u64 s = (u64)t[j] + (u64)q * ((j < m->n.n) ? m->n.d[j] : 0) + c;
            t[j - 1] = (u32)s;
            c = s >> 32;
        }
        {
            u64 s = (u64)t[k] + c;
            t[k - 1] = (u32)s;
            t[k] = t[k + 1] + (u32)(s >> 32);
        }
        t[k + 1] = 0;
    }
    bn_zero(r);
    r->n = k + 1;
    for (i = 0; i <= k; i++)
        r->d[i] = t[i];
    while (r->n > 0 && r->d[r->n - 1] == 0)
        r->n--;
    if (bn_cmp(r, &m->n) >= 0)
        bn_sub(r, r, &m->n);
}

static void mont_pow(BigNum *r, const BigNum *b, const BigNum *e, const BigNum *n)
{
    Mont m;
    BigNum base, res, rmod, r2;
    int i, bits_e;
    mont_init(&m, n);
    bn_set_small(&rmod, 1);
    for (i = 0; i < 32 * m.k; i++) {
        bn_add(&rmod, &rmod, &rmod);
        if (bn_cmp(&rmod, n) >= 0)
            bn_sub(&rmod, &rmod, n);
    }
    r2 = rmod;
    for (i = 0; i < 32 * m.k; i++) {
        bn_add(&r2, &r2, &r2);
        if (bn_cmp(&r2, n) >= 0)
            bn_sub(&r2, &r2, n);
    }
    bn_mod(&base, b, n);
    mont_mul(&base, &base, &r2, &m);
    bn_set_small(&res, 1);
    mont_mul(&res, &res, &r2, &m);
    bits_e = bn_bits(e);
    for (i = bits_e - 1; i >= 0; i--) {
        mont_mul(&res, &res, &res, &m);
        if (bn_bit(e, i))
            mont_mul(&res, &res, &base, &m);
    }
    bn_set_small(&rmod, 1);
    mont_mul(&res, &res, &rmod, &m);
    *r = res;
}

void bn_modpow(BigNum *r, const BigNum *b, const BigNum *e, const BigNum *m)
{
    if (m->n > 0 && (m->d[0] & 1)) {
        mont_pow(r, b, e, m);
        return;
    }
    {
        BigNum result, base;
        int i;
        bn_set_small(&result, 1);
        bn_mod(&base, b, m);
        for (i = bn_bits(e) - 1; i >= 0; i--) {
            bn_modmul(&result, &result, &result, m);
            if (bn_bit(e, i))
                bn_modmul(&result, &result, &base, m);
        }
        *r = result;
    }
}

static int is_even(const BigNum *a)
{
    return a->n == 0 || (a->d[0] & 1) == 0;
}

static void bn_sub_small(BigNum *a, u32 v)
{
    BigNum t;
    bn_zero(&t);
    t.d[0] = v;
    t.n = 1;
    bn_sub(a, a, &t);
}

static void bn_dec(BigNum *a)
{
    bn_sub_small(a, 1);
}

void bn_set_small_impl(BigNum *a, u32 v)
{
    bn_zero(a);
    a->d[0] = v;
    a->n = v ? 1 : 0;
}

static void bn_set_small(BigNum *a, u32 v)
{
    bn_set_small_impl(a, v);
}

static int miller_rabin(const BigNum *n, int rounds)
{
    BigNum nm1, d, a, x, one, two;
    int s = 0, i, k;
    bn_set_small(&one, 1);
    bn_set_small(&two, 2);
    nm1 = *n;
    bn_dec(&nm1);
    if (bn_cmp(n, &two) <= 0)
        return bn_cmp(n, &two) == 0;
    d = nm1;
    while (is_even(&d)) {
        bn_shr1(&d);
        s++;
    }
    for (k = 0; k < rounds; k++) {
        int pass = 0;
        u8 rnd[64];
        ac_random(rnd, sizeof(rnd));
        bn_from_bytes(&a, rnd, sizeof(rnd));
        bn_mod(&a, &a, &nm1);
        if (bn_cmp(&a, &two) < 0)
            bn_set_small(&a, 2);
        bn_modpow(&x, &a, &d, n);
        if (bn_cmp(&x, &one) == 0 || bn_cmp(&x, &nm1) == 0)
            pass = 1;
        else {
            for (i = 1; i < s; i++) {
                bn_modmul(&x, &x, &x, n);
                if (bn_cmp(&x, &nm1) == 0) {
                    pass = 1;
                    break;
                }
            }
        }
        if (!pass)
            return 0;
    }
    return 1;
}

static void rand_bn(BigNum *a, int bits)
{
    u8 buf[AC_BN_LIMBS * 4];
    int need = (bits + 7) / 8;
    int top = bits % 8;
    ac_random(buf, sizeof(buf));
    if (top)
        buf[0] = (u8)((buf[0] & ((1u << top) - 1)) | (1u << (top - 1)));
    else
        buf[0] |= 0x80;
    buf[need - 1] |= 1;
    bn_from_bytes(a, buf, (size_t)need);
}

static void bn_set_small(BigNum *a, u32 v);
static u32 bn_mod_small(const BigNum *a, u32 m);

static int small_prime_ok(const BigNum *a)
{
    static const u32 sp[] = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
                             53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103,
                             107, 109, 113, 127, 131, 137, 139, 149, 151, 157};
    int i;
    for (i = 0; i < (int)(sizeof(sp) / sizeof(sp[0])); i++)
        if (bn_mod_small(a, sp[i]) == 0)
            return bn_cmp(a, &(BigNum){.d = {sp[i]}, .n = 1}) == 0;
    return 1;
}

static int bn_is_probable_prime(BigNum *a, int rounds)
{
    if (is_even(a))
        return 0;
    if (!small_prime_ok(a))
        return 0;
    return miller_rabin(a, rounds);
}

static u32 bn_mod_small(const BigNum *a, u32 m)
{
    u64 r = 0;
    int i;
    for (i = a->n - 1; i >= 0; i--)
        r = ((r << 32) | a->d[i]) % m;
    return (u32)r;
}

static void bn_div_exact(BigNum *q, const BigNum *a, const BigNum *b)
{
    BigNum cur = *a, bs = *b;
    int shift = bn_bits(a) - bn_bits(b);
    bn_zero(q);
    if (shift < 0)
        return;
    if (bn_shl(&bs, shift) < 0)
        return;
    while (shift >= 0) {
        if (bn_cmp(&cur, &bs) >= 0) {
            bn_sub(&cur, &cur, &bs);
            {
                int li = shift / 32;
                if (li < AC_BN_LIMBS) {
                    q->d[li] |= 1u << (shift % 32);
                    if (li + 1 > q->n)
                        q->n = li + 1;
                }
            }
        }
        bn_shr1(&bs);
        shift--;
    }
}

static void bn_divmod(BigNum *q, BigNum *rem, const BigNum *a, const BigNum *b)
{
    BigNum cur, bs;
    int shift;
    bn_zero(q);
    *rem = *a;
    if (bn_is_zero(b))
        return;
    shift = bn_bits(a) - bn_bits(b);
    if (shift < 0)
        return;
    bs = *b;
    if (bn_shl(&bs, shift) < 0)
        return;
    cur = *a;
    while (shift >= 0) {
        if (bn_cmp(&cur, &bs) >= 0) {
            int li = shift / 32;
            bn_sub(&cur, &cur, &bs);
            if (li < AC_BN_LIMBS) {
                q->d[li] |= 1u << (shift % 32);
                if (li + 1 > q->n)
                    q->n = li + 1;
            }
        }
        bn_shr1(&bs);
        shift--;
    }
    *rem = cur;
}

static void bn_modinv(BigNum *r, const BigNum *a, const BigNum *m)
{
    BigNum old_r, rr, old_s, ss, q, rem, prod, tmp;
    old_r = *m;
    bn_mod(&rr, a, m);
    bn_zero(&old_s);
    bn_set_small(&ss, 1);
    while (!bn_is_zero(&rr)) {
        bn_divmod(&q, &rem, &old_r, &rr);
        bn_mod(&q, &q, m);
        bn_modmul(&prod, &q, &ss, m);
        if (bn_cmp(&old_s, &prod) >= 0)
            bn_sub(&tmp, &old_s, &prod);
        else {
            BigNum d2;
            bn_sub(&d2, &prod, &old_s);
            bn_sub(&tmp, m, &d2);
        }
        old_s = ss;
        ss = tmp;
        old_r = rr;
        rr = rem;
    }
    bn_mod(&old_s, &old_s, m);
    *r = old_s;
}

int rsa_generate(RsaKey *k, int bits)
{
    BigNum p, q, n, phi, e, d, pm1, qm1, t;
    int half = bits / 2;
    int tries = 0;
    bn_set_small(&e, 65537);
    for (;;) {
        if (++tries > 4000)
            return -1;
        rand_bn(&p, half);
        if (!bn_is_probable_prime(&p, 16))
            continue;
        if (bn_mod_small(&p, 65537) == 1)
            continue;
        break;
    }
    for (;;) {
        if (++tries > 8000)
            return -1;
        rand_bn(&q, bits - half);
        if (bn_cmp(&p, &q) == 0)
            continue;
        if (!bn_is_probable_prime(&q, 16))
            continue;
        if (bn_mod_small(&q, 65537) == 1)
            continue;
        break;
    }
    bn_mul(&n, &p, &q);
    if (bn_bits(&n) < bits) {
        bn_zero(&n);
        return rsa_generate(k, bits);
    }
    pm1 = p;
    qm1 = q;
    bn_dec(&pm1);
    bn_dec(&qm1);
    bn_mul(&phi, &pm1, &qm1);
    bn_modinv(&d, &e, &phi);
    if (bn_is_zero(&d))
        return rsa_generate(k, bits);
    k->n = n;
    k->e = e;
    k->d = d;
    k->p = p;
    k->q = q;
    {
        BigNum dp, dq, qinv, p1;
        bn_mod(&dp, &d, &pm1);
        bn_mod(&dq, &d, &qm1);
        bn_modinv(&qinv, &q, &p);
        k->dp = dp;
        k->dq = dq;
        k->qinv = qinv;
        (void)p1;
    }
    k->bits = bn_bits(&n);
    (void)t;
    return 0;
}

static int pkcs1_pad(int sha256, const u8 *hash, size_t hlen, u8 *em, size_t emlen)
{
    static const u8 di_sha1[] = {0x30, 0x21, 0x30, 0x09, 0x06, 0x05, 0x2b, 0x0e,
                                  0x03, 0x02, 0x1a, 0x05, 0x00, 0x04, 0x14};
    static const u8 di_sha256[] = {0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86,
                                   0x48, 0x01, 0x65, 0x03, 0x04, 0x02, 0x01, 0x05,
                                   0x00, 0x04, 0x20};
    const u8 *di = sha256 ? di_sha256 : di_sha1;
    size_t dlen = sha256 ? sizeof(di_sha256) : sizeof(di_sha1);
    size_t tlen = dlen + hlen;
    size_t ps;
    if (tlen + 11 > emlen)
        return -1;
    em[0] = 0x00;
    em[1] = 0x01;
    ps = emlen - tlen - 3;
    memset(em + 2, 0xff, ps);
    em[2 + ps] = 0x00;
    memcpy(em + 3 + ps, di, dlen);
    memcpy(em + 3 + ps + dlen, hash, hlen);
    return 0;
}

int rsa_sign_pkcs1(const RsaKey *k, int sha256, const u8 *hash, size_t hlen, u8 *sig, size_t *siglen)
{
    u8 em[AC_BN_LIMBS * 4];
    BigNum m, s;
    size_t nlen = (size_t)((k->bits + 7) / 8);
    if (nlen > sizeof(em))
        return -1;
    if (pkcs1_pad(sha256, hash, hlen, em, nlen) != 0)
        return -1;
    bn_from_bytes(&m, em, nlen);
    bn_modpow(&s, &m, &k->d, &k->n);
    bn_to_bytes(&s, sig, nlen);
    *siglen = nlen;
    return 0;
}

int rsa_verify_pkcs1(const BigNum *n, const BigNum *e, int sha256, const u8 *hash, size_t hlen, const u8 *sig, size_t siglen)
{
    u8 em[AC_BN_LIMBS * 4], want[AC_BN_LIMBS * 4];
    BigNum s, m;
    size_t nlen = (size_t)((bn_bits(n) + 7) / 8);
    if (siglen != nlen || nlen > sizeof(em))
        return 0;
    bn_from_bytes(&s, sig, siglen);
    bn_modpow(&m, &s, e, n);
    bn_to_bytes(&m, em, nlen);
    if (pkcs1_pad(sha256, hash, hlen, want, nlen) != 0)
        return 0;
    return memcmp(em, want, nlen) == 0;
}
