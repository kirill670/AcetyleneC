#include "ac_crypto.h"

static int g_cert_v1;
static int g_no_null;

void der_init(Der *d)
{
    d->data = NULL;
    d->len = 0;
    d->cap = 0;
}

void der_free(Der *d)
{
    free(d->data);
    der_init(d);
}

void der_raw(Der *d, const void *p, size_t n)
{
    if (d->len + n > d->cap) {
        size_t cap = d->cap ? d->cap : 256;
        while (cap < d->len + n)
            cap *= 2;
        d->data = ac_realloc(d->data, cap);
        d->cap = cap;
    }
    memcpy(d->data + d->len, p, n);
    d->len += n;
}

static void der_put_len(Buf *b, size_t len)
{
    if (len < 0x80) {
        buf_u8(b, (u8)len);
    } else if (len < 0x100) {
        buf_u8(b, 0x81);
        buf_u8(b, (u8)len);
    } else if (len < 0x10000) {
        buf_u8(b, 0x82);
        buf_u8(b, (u8)(len >> 8));
        buf_u8(b, (u8)len);
    } else {
        buf_u8(b, 0x83);
        buf_u8(b, (u8)(len >> 16));
        buf_u8(b, (u8)(len >> 8));
        buf_u8(b, (u8)len);
    }
}

void der_tlv(Der *d, u8 tag, const void *p, size_t n)
{
    Buf b;
    buf_init(&b);
    buf_u8(&b, tag);
    der_put_len(&b, n);
    der_raw(d, b.data, b.len);
    der_raw(d, p, n);
    buf_free(&b);
}

void der_len_prefix(Buf *b, u8 tag, size_t len)
{
    buf_u8(b, tag);
    der_put_len(b, len);
}

void der_small_int(Der *d, u32 v)
{
    u8 tmp[5];
    int n = 0;
    if (v == 0) {
        tmp[0] = 0;
        der_tlv(d, 0x02, tmp, 1);
        return;
    }
    while (v) {
        tmp[n++] = (u8)v;
        v >>= 8;
    }
    {
        u8 rev[5];
        int i;
        for (i = 0; i < n; i++)
            rev[i] = tmp[n - 1 - i];
        if (rev[0] & 0x80) {
            u8 padded[6];
            padded[0] = 0;
            memcpy(padded + 1, rev, (size_t)n);
            der_tlv(d, 0x02, padded, (size_t)n + 1);
        } else {
            der_tlv(d, 0x02, rev, (size_t)n);
        }
    }
}

void der_int(Der *d, const BigNum *v)
{
    u8 buf[AC_BN_LIMBS * 4];
    size_t i, n = 0;
    n = bn_to_bytes(v, buf, sizeof(buf));
    for (i = 0; i < n - 1; i++)
        if (buf[i] != 0)
            break;
    if (i > 0) {
        memmove(buf, buf + i, n - i);
        n -= i;
    }
    if (n == 0) {
        buf[0] = 0;
        n = 1;
    }
    if (buf[0] & 0x80) {
        u8 padded[AC_BN_LIMBS * 4 + 1];
        padded[0] = 0;
        memcpy(padded + 1, buf, n);
        der_tlv(d, 0x02, padded, n + 1);
    } else {
        der_tlv(d, 0x02, buf, n);
    }
}

void der_oid(Der *d, const char *oid)
{
    u8 out[64];
    int n = 0;
    u32 parts[16];
    int np = 0;
    const char *s = oid;
    while (*s && np < 16) {
        u32 v = 0;
        while (*s >= '0' && *s <= '9') {
            v = v * 10 + (u32)(*s - '0');
            s++;
        }
        parts[np++] = v;
        if (*s == '.')
            s++;
        else
            break;
    }
    if (np < 2)
        return;
    out[n++] = (u8)(parts[0] * 40 + parts[1]);
    {
        int i;
        for (i = 2; i < np; i++) {
            u32 v = parts[i];
            u8 tmp[5];
            int k = 0;
            tmp[k++] = (u8)(v & 0x7f);
            v >>= 7;
            while (v) {
                tmp[k++] = (u8)((v & 0x7f) | 0x80);
                v >>= 7;
            }
            while (k > 0)
                out[n++] = tmp[--k];
        }
    }
    der_tlv(d, 0x06, out, (size_t)n);
}

void der_printable(Der *d, const char *s)
{
    der_tlv(d, 0x13, s, strlen(s));
}

void der_utf8(Der *d, const char *s)
{
    der_tlv(d, 0x0c, s, strlen(s));
}

void der_utctime(Der *d, int year, int mon, int day, int hour, int min, int sec)
{
    char buf[32];
    snprintf(buf, sizeof(buf), "%02d%02d%02d%02d%02d%02dZ", year % 100, mon, day, hour, min, sec);
    der_tlv(d, 0x17, buf, 13);
}

void der_bits(Der *d, const u8 *p, size_t n, int unused)
{
    Buf b;
    buf_init(&b);
    buf_u8(&b, (u8)unused);
    buf_put(&b, p, n);
    der_tlv(d, 0x03, b.data, b.len);
    buf_free(&b);
}

static void mk_alg_sha1(Der *d)
{
    static const u8 oid_sha1[] = {0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02, 0x1a};
    static const u8 nullp[] = {0x05, 0x00};
    Buf b;
    buf_init(&b);
    buf_put(&b, oid_sha1, sizeof(oid_sha1));
    if (!g_no_null)
        buf_put(&b, nullp, sizeof(nullp));
    der_tlv(d, 0x30, b.data, b.len);
    buf_free(&b);
}

static void mk_alg_rsa(Der *d)
{
    static const u8 oid_rsa[] = {0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01};
    static const u8 nullp[] = {0x05, 0x00};
    Buf b;
    buf_init(&b);
    buf_put(&b, oid_rsa, sizeof(oid_rsa));
    if (!g_no_null)
        buf_put(&b, nullp, sizeof(nullp));
    der_tlv(d, 0x30, b.data, b.len);
    buf_free(&b);
}

static void mk_name(Der *d, const char *cn, const char *org)
{
    Der inner, atv;
    Der seq;
    der_init(&inner);
    der_init(&atv);
    der_init(&seq);
    der_init(&inner);
    {
        Der o, v;
        der_init(&o);
        der_init(&v);
        der_oid(&o, "2.5.4.3");
        der_printable(&v, cn);
        {
            Der a;
            der_init(&a);
            der_raw(&a, o.data, o.len);
            der_raw(&a, v.data, v.len);
            der_tlv(&atv, 0x30, a.data, a.len);
            der_free(&a);
        }
        der_free(&o);
        der_free(&v);
        der_init(&o);
        der_init(&v);
        der_oid(&o, "2.5.4.10");
        der_printable(&v, org);
        {
            Der a;
            der_init(&a);
            der_raw(&a, o.data, o.len);
            der_raw(&a, v.data, v.len);
            der_tlv(&seq, 0x31, a.data, a.len);
            der_free(&a);
        }
        der_free(&o);
        der_free(&v);
    }
    {
        Der both;
        der_init(&both);
        der_raw(&both, atv.data, atv.len);
        der_raw(&both, seq.data, seq.len);
        der_tlv(d, 0x30, both.data, both.len);
        der_free(&both);
    }
    der_free(&inner);
    der_free(&atv);
    der_free(&seq);
}

static void tbs_bytes(Der *out, const RsaKey *key, const char *cn, const char *org, int serial)
{
    Der ver, serial_d, name, validity, spki, ext, alg, rsa_inner;
    u8 nb[AC_BN_LIMBS * 4];
    size_t nlen = (size_t)((key->bits + 7) / 8);
    der_init(&ver);
    der_init(&serial_d);
    der_init(&name);
    der_init(&validity);
    der_init(&spki);
    der_init(&ext);
    der_init(&alg);
    der_init(&rsa_inner);

    der_small_int(&ver, 2);
    der_small_int(&serial_d, (u32)serial);
    mk_name(&name, cn, org);
    {
        Der t1, t2;
        der_init(&t1);
        der_init(&t2);
        der_utctime(&t1, 2020, 1, 1, 0, 0, 0);
        der_utctime(&t2, 2040, 1, 1, 0, 0, 0);
        {
            Der v;
            der_init(&v);
            der_raw(&v, t1.data, t1.len);
            der_raw(&v, t2.data, t2.len);
            der_tlv(&validity, 0x30, v.data, v.len);
            der_free(&v);
        }
        der_free(&t1);
        der_free(&t2);
    }
    bn_to_bytes(&key->n, nb, nlen);
    {
        Der n_int, e_int;
        BigNum tmp;
        der_init(&n_int);
        der_init(&e_int);
        bn_from_bytes(&tmp, nb, nlen);
        der_int(&n_int, &tmp);
        der_int(&e_int, &key->e);
        {
            Der both;
            der_init(&both);
            der_raw(&both, n_int.data, n_int.len);
            der_raw(&both, e_int.data, e_int.len);
            der_tlv(&rsa_inner, 0x30, both.data, both.len);
            der_free(&both);
        }
        der_free(&n_int);
        der_free(&e_int);
    }
    mk_alg_rsa(&alg);
    {
        Der bitsv, spki_seq;
        der_init(&bitsv);
        der_init(&spki_seq);
        der_bits(&bitsv, rsa_inner.data, rsa_inner.len, 0);
        {
            Der a;
            der_init(&a);
            der_raw(&a, alg.data, alg.len);
            der_raw(&a, bitsv.data, bitsv.len);
            der_tlv(&spki_seq, 0x30, a.data, a.len);
            der_free(&a);
        }
        der_raw(&spki, spki_seq.data, spki_seq.len);
        der_free(&bitsv);
        der_free(&spki_seq);
    }
    {
        static const u8 oid_bc[] = {0x06, 0x03, 0x55, 0x1d, 0x13};
        static const u8 oid_ku[] = {0x06, 0x03, 0x55, 0x1d, 0x0f};
        Der e1, e2, crit, v1, v2, bcval, kuseq, exts, ku;
        der_init(&e1);
        der_init(&e2);
        der_init(&crit);
        der_init(&v1);
        der_init(&v2);
        der_init(&bcval);
        der_init(&kuseq);
        der_init(&exts);
        der_init(&ku);
        der_tlv(&crit, 0x01, (const u8[]){0xff}, 1);
        der_tlv(&bcval, 0x04, (const u8[]){0x30, 0x03, 0x01, 0x01, 0xff}, 5);
        der_tlv(&v1, 0x04, bcval.data, bcval.len);
        {
            Der a;
            der_init(&a);
            der_raw(&a, oid_bc, sizeof(oid_bc));
            der_raw(&a, crit.data, crit.len);
            der_raw(&a, v1.data, v1.len);
            der_tlv(&e1, 0x30, a.data, a.len);
            der_free(&a);
        }
        der_tlv(&ku, 0x03, (const u8[]){0x01, 0x06}, 2);
        der_tlv(&v2, 0x04, ku.data, ku.len);
        {
            Der a;
            der_init(&a);
            der_raw(&a, oid_ku, sizeof(oid_ku));
            der_raw(&a, v2.data, v2.len);
            der_tlv(&e2, 0x30, a.data, a.len);
            der_free(&a);
        }
        {
            Der a;
            der_init(&a);
            der_raw(&a, e1.data, e1.len);
            der_raw(&a, e2.data, e2.len);
            der_tlv(&exts, 0x30, a.data, a.len);
            der_free(&a);
        }
        der_tlv(&ext, 0xa3, exts.data, exts.len);
        der_free(&e1);
        der_free(&e2);
        der_free(&crit);
        der_free(&v1);
        der_free(&v2);
        der_free(&bcval);
        der_free(&kuseq);
        der_free(&exts);
        der_free(&ku);
    }
    {
        Der body;
        der_init(&body);
        if (!g_cert_v1)
            der_tlv(&body, 0xa0, ver.data, ver.len);
        der_raw(&body, serial_d.data, serial_d.len);
        {
            Der a;
            der_init(&a);
            mk_alg_sha1(&a);
            der_raw(&body, a.data, a.len);
            der_free(&a);
        }
        der_raw(&body, name.data, name.len);
        der_raw(&body, validity.data, validity.len);
        der_raw(&body, name.data, name.len);
        der_raw(&body, spki.data, spki.len);
        if (!g_cert_v1)
            der_raw(&body, ext.data, ext.len);
        der_tlv(out, 0x30, body.data, body.len);
        der_free(&body);
    }
    der_free(&ver);
    der_free(&serial_d);
    der_free(&name);
    der_free(&validity);
    der_free(&spki);
    der_free(&ext);
    der_free(&alg);
    der_free(&rsa_inner);
}

void devcert_set_nonull(int v)
{
    g_no_null = v ? 1 : 0;
}

void devcert_set_v1(int v)
{
    g_cert_v1 = v ? 1 : 0;
}

int devcert_generate(DevCert *dc, int bits, const char *common_name)
{
    Der tbs, cert, sigalg, sigbit;
    u8 hash[20], sig[AC_BN_LIMBS * 4];
    size_t siglen = 0;
    BigNum n;
    if (rsa_generate(&dc->key, bits) != 0)
        return -1;
    bn_from_bytes(&n, (const u8 *)"", 0);
    der_init(&tbs);
    der_init(&cert);
    der_init(&sigalg);
    der_init(&sigbit);
    tbs_bytes(&tbs, &dc->key, common_name, "AcetyleneC SDK", 1);
    sha1(tbs.data, tbs.len, hash);
    if (rsa_sign_pkcs1(&dc->key, 0, hash, 20, sig, &siglen) != 0)
        return -1;
    {
        Der a, body;
        der_init(&a);
        der_init(&body);
        mk_alg_sha1(&a);
        der_raw(&sigalg, a.data, a.len);
        der_free(&a);
        der_bits(&sigbit, sig, siglen, 0);
        der_raw(&body, tbs.data, tbs.len);
        der_raw(&body, sigalg.data, sigalg.len);
        der_raw(&body, sigbit.data, sigbit.len);
        der_tlv(&cert, 0x30, body.data, body.len);
        der_free(&body);
    }
    if (cert.len > sizeof(dc->cert))
        return -1;
    memcpy(dc->cert, cert.data, cert.len);
    dc->cert_len = cert.len;
    der_free(&tbs);
    der_free(&cert);
    der_free(&sigalg);
    der_free(&sigbit);
    return 0;
}

static void b64_line(Buf *out, const u8 *data, size_t len)
{
    static const char tbl[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    size_t i;
    int col = 0;
    for (i = 0; i < len; i += 3) {
        u32 v = (u32)data[i] << 16;
        int n = 1;
        if (i + 1 < len) {
            v |= (u32)data[i + 1] << 8;
            n = 2;
        }
        if (i + 2 < len) {
            v |= data[i + 2];
            n = 3;
        }
        buf_u8(out, tbl[(v >> 18) & 0x3f]);
        buf_u8(out, tbl[(v >> 12) & 0x3f]);
        buf_u8(out, n > 1 ? tbl[(v >> 6) & 0x3f] : '=');
        buf_u8(out, n > 2 ? tbl[v & 0x3f] : '=');
        col += 4;
        if (col >= 64) {
            buf_u8(out, 0x0a);
            col = 0;
        }
    }
    if (col)
        buf_u8(out, 0x0a);
}

void ac_pem_write(const char *path, const char *label, const u8 *der, size_t len)
{
    Buf b;
    char hdr[64];
    char ftr[64];
    buf_init(&b);
    snprintf(hdr, sizeof(hdr), "-----BEGIN %s-----", label);
    snprintf(ftr, sizeof(ftr), "-----END %s-----", label);
    buf_put(&b, hdr, strlen(hdr));
    buf_u8(&b, 0x0a);
    b64_line(&b, der, len);
    buf_put(&b, ftr, strlen(ftr));
    buf_u8(&b, 0x0a);
    ac_write_file(path, b.data, b.len);
    buf_free(&b);
}

int devcert_save(const DevCert *dc, const char *cer_path, const char *key_path)
{
    Der priv;
    u8 nb[AC_BN_LIMBS * 4];
    size_t nlen = (size_t)((dc->key.bits + 7) / 8);
    der_init(&priv);
    {
        Der body;
        der_init(&body);
        der_small_int(&body, 0);
        bn_to_bytes(&dc->key.n, nb, nlen);
        {
            BigNum t;
            bn_from_bytes(&t, nb, nlen);
            der_int(&body, &t);
            bn_to_bytes(&dc->key.e, nb, 4);
            bn_from_bytes(&t, nb, 4);
            der_int(&body, &t);
            bn_to_bytes(&dc->key.d, nb, nlen);
            bn_from_bytes(&t, nb, nlen);
            der_int(&body, &t);
            bn_to_bytes(&dc->key.p, nb, nlen / 2);
            bn_from_bytes(&t, nb, nlen / 2);
            der_int(&body, &t);
            bn_to_bytes(&dc->key.q, nb, nlen / 2);
            bn_from_bytes(&t, nb, nlen / 2);
            der_int(&body, &t);
            bn_to_bytes(&dc->key.dp, nb, nlen / 2);
            bn_from_bytes(&t, nb, nlen / 2);
            der_int(&body, &t);
            bn_to_bytes(&dc->key.dq, nb, nlen / 2);
            bn_from_bytes(&t, nb, nlen / 2);
            der_int(&body, &t);
            bn_to_bytes(&dc->key.qinv, nb, nlen / 2);
            bn_from_bytes(&t, nb, nlen / 2);
            der_int(&body, &t);
        }
        der_tlv(&priv, 0x30, body.data, body.len);
        der_free(&body);
    }
    if (ac_has_ext(cer_path, ".der") || ac_has_ext(cer_path, ".bin"))
        ac_write_file(cer_path, dc->cert, dc->cert_len);
    else
        ac_pem_write(cer_path, "CERTIFICATE", dc->cert, dc->cert_len);
    if (ac_has_ext(key_path, ".der") || ac_has_ext(key_path, ".bin"))
        ac_write_file(key_path, priv.data, priv.len);
    else
        ac_pem_write(key_path, "RSA PRIVATE KEY", priv.data, priv.len);
    der_free(&priv);
    return 0;
}

static size_t der_len_at(const u8 *p, size_t left, size_t *hdr)
{
    size_t len;
    if (left < 2)
        return (size_t)-1;
    if (!(p[1] & 0x80)) {
        *hdr = 2;
        return p[1];
    }
    {
        int nb = p[1] & 0x7f;
        int i;
        size_t v = 0;
        if (nb > 3 || left < (size_t)(2 + nb))
            return (size_t)-1;
        for (i = 0; i < nb; i++)
            v = (v << 8) | p[2 + i];
        *hdr = (size_t)(2 + nb);
        len = v;
    }
    return len;
}

int devcert_load_cert(const char *cer_path, BigNum *n, BigNum *e, u8 *raw, size_t *rawlen)
{
    Buf b;
    static const u8 rsa_oid[] = {0x06, 0x09, 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01};
    size_t i;
    int ok = 0;
    if (ac_read_file(cer_path, &b) != 0)
        return -1;
    if (raw && rawlen) {
        size_t c = b.len < *rawlen ? b.len : *rawlen;
        memcpy(raw, b.data, c);
        *rawlen = c;
    }
    for (i = 0; i + sizeof(rsa_oid) < b.len; i++) {
        if (memcmp(b.data + i, rsa_oid, sizeof(rsa_oid)) != 0)
            continue;
        {
            size_t p = i + sizeof(rsa_oid);
            size_t hdr, len;
            if (p + 2 <= b.len && b.data[p] == 0x05 && b.data[p + 1] == 0x00)
                p += 2;
            if (p >= b.len || b.data[p] != 0x03)
                continue;
            len = der_len_at(b.data + p, b.len - p, &hdr);
            if (len == (size_t)-1)
                continue;
            p += hdr;
            if (p >= b.len)
                continue;
            p++;
            if (p >= b.len || b.data[p] != 0x30)
                continue;
            len = der_len_at(b.data + p, b.len - p, &hdr);
            if (len == (size_t)-1)
                continue;
            p += hdr;
            if (p >= b.len || b.data[p] != 0x02)
                continue;
            len = der_len_at(b.data + p, b.len - p, &hdr);
            if (len == (size_t)-1)
                continue;
            p += hdr;
            if (p + len > b.len)
                continue;
            bn_from_bytes(n, b.data + p, len);
            p += len;
            if (p >= b.len || b.data[p] != 0x02)
                continue;
            len = der_len_at(b.data + p, b.len - p, &hdr);
            if (len == (size_t)-1)
                continue;
            p += hdr;
            if (p + len > b.len)
                continue;
            bn_from_bytes(e, b.data + p, len);
            ok = 1;
            break;
        }
    }
    buf_free(&b);
    return ok ? 0 : -1;
}

int devcert_sign(const DevCert *dc, int use_sha256, const u8 *data, size_t len, u8 *sig, size_t *siglen)
{
    u8 hash[32];
    size_t hlen;
    if (use_sha256) {
        sha256(data, len, hash);
        hlen = 32;
    } else {
        sha1(data, len, hash);
        hlen = 20;
    }
    return rsa_sign_pkcs1(&dc->key, use_sha256, hash, hlen, sig, siglen);
}
