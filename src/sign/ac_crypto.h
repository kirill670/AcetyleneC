#ifndef AC_CRYPTO_H
#define AC_CRYPTO_H

#include "../common/ac.h"

typedef struct {
    u32 h[5];
    u64 len;
    u8 buf[64];
    u32 n;
} Sha1;

typedef struct {
    u32 h[8];
    u64 len;
    u8 buf[64];
    u32 n;
} Sha256;

void sha1_init(Sha1 *c);
void sha1_update(Sha1 *c, const void *data, size_t len);
void sha1_final(Sha1 *c, u8 out[20]);
void sha1(const void *data, size_t len, u8 out[20]);

void sha256_init(Sha256 *c);
void sha256_update(Sha256 *c, const void *data, size_t len);
void sha256_final(Sha256 *c, u8 out[32]);
void sha256(const void *data, size_t len, u8 out[32]);

#define AC_BN_LIMBS 128
typedef struct {
    u32 d[AC_BN_LIMBS];
    int n;
} BigNum;

typedef struct {
    BigNum n;
    BigNum e;
    BigNum d;
    BigNum p;
    BigNum q;
    BigNum dp;
    BigNum dq;
    BigNum qinv;
    int bits;
} RsaKey;

void bn_zero(BigNum *a);
void bn_from_bytes(BigNum *a, const u8 *data, size_t len);
size_t bn_to_bytes(const BigNum *a, u8 *out, size_t outlen);
int bn_cmp(const BigNum *a, const BigNum *b);
void bn_add(BigNum *r, const BigNum *a, const BigNum *b);
void bn_sub(BigNum *r, const BigNum *a, const BigNum *b);
void bn_mul(BigNum *r, const BigNum *a, const BigNum *b);
void bn_mod(BigNum *r, const BigNum *a, const BigNum *m);
void bn_modmul(BigNum *r, const BigNum *a, const BigNum *b, const BigNum *m);
void bn_modpow(BigNum *r, const BigNum *b, const BigNum *e, const BigNum *m);
void bn_modinv(BigNum *r, const BigNum *a, const BigNum *m);
int bn_is_zero(const BigNum *a);
int bn_bit(const BigNum *a, int i);
int bn_bits(const BigNum *a);

void ac_random(void *buf, size_t len);
int rsa_generate(RsaKey *k, int bits);
int rsa_sign_pkcs1(const RsaKey *k, int sha256, const u8 *hash, size_t hlen, u8 *sig, size_t *siglen);
int rsa_verify_pkcs1(const BigNum *n, const BigNum *e, int sha256, const u8 *hash, size_t hlen, const u8 *sig, size_t siglen);

typedef struct {
    u8 *data;
    size_t len;
    size_t cap;
} Der;

void der_init(Der *d);
void der_free(Der *d);
void der_raw(Der *d, const void *p, size_t n);
void der_tlv(Der *d, u8 tag, const void *p, size_t n);
void der_len_prefix(Buf *b, u8 tag, size_t len);
void der_int(Der *d, const BigNum *v);
void der_small_int(Der *d, u32 v);
void der_oid(Der *d, const char *oid);
void der_utf8(Der *d, const char *s);
void der_printable(Der *d, const char *s);
void der_utctime(Der *d, int year, int mon, int day, int hour, int min, int sec);
void der_bits(Der *d, const u8 *p, size_t n, int unused);

typedef struct {
    BigNum p;
    BigNum q;
    BigNum g;
    BigNum y;
    BigNum x;
} DsaKey;

int dsa_generate(DsaKey *k);
int dsa_sign(DsaKey *k, const u8 hash[20], u8 r_out[20], u8 s_out[20]);

typedef struct DevCert DevCert;

int devcert_generate_dsa(DevCert *dc, const char *common_name);
int devcert_save_dsa(const DevCert *dc, const char *cer_path, const char *key_path);

struct DevCert {
    RsaKey key;
    DsaKey dsa;
    int is_dsa;
    int bits;
    u8 cert[4096];
    size_t cert_len;
};

int devcert_generate(DevCert *dc, int bits, const char *common_name);
int devcert_save(const DevCert *dc, const char *cer_path, const char *key_path);
int devcert_load_cert(const char *cer_path, BigNum *n, BigNum *e, u8 *raw, size_t *rawlen);
int devcert_sign(const DevCert *dc, int sha256, const u8 *data, size_t len, u8 *sig, size_t *siglen);
u32 crc32_ieee(const void *data, size_t len);
void ac_pem_write(const char *path, const char *label, const u8 *der, size_t len);

#endif
