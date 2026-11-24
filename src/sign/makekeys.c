#include "ac_crypto.h"

int main(int argc, char **argv)
{
    int bits = 1024;
    const char *name = "AcetyleneC Developer";
    const char *cer = "dev.cer";
    const char *key = "dev.key";
    int i;
    DevCert dc;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-bits") == 0 && i + 1 < argc) {
            bits = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-name") == 0 && i + 1 < argc) {
            name = argv[++i];
        } else if (strcmp(argv[i], "--selftest") == 0) {
            u8 h1[20], h2[32];
            u8 sig[512];
            size_t siglen = 0;
            BigNum n, e;
            sha1("abc", 3, h1);
            sha256("abc", 3, h2);
            printf("sha1(abc)=%02x%02x%02x%02x%02x%02x...\n", h1[0], h1[1], h1[2], h1[3], h1[4], h1[5]);
            printf("sha256(abc)=%02x%02x%02x%02x%02x...\n", h2[0], h2[1], h2[2], h2[3], h2[4]);
            if (devcert_generate(&dc, 1024, "Test") != 0) {
                printf("keygen FAILED\n");
                return 1;
            }
            if (devcert_sign(&dc, 0, (const u8 *)"hello world", 11, sig, &siglen) != 0) {
                printf("sign FAILED\n");
                return 1;
            }
            rsa_verify_pkcs1(&dc.key.n, &dc.key.e, 0, h1, 20, sig, siglen);
            {
                u8 hash[20];
                sha1("hello world", 11, hash);
                printf("cert=%u bytes sig=%u bytes verify=%s\n", (unsigned)dc.cert_len, (unsigned)siglen,
                       rsa_verify_pkcs1(&dc.key.n, &dc.key.e, 0, hash, 20, sig, siglen) ? "OK" : "BAD");
            }
            if (devcert_save(&dc, "selftest.cer", "selftest.key") != 0)
                printf("save FAILED\n");
            if (devcert_load_cert("selftest.cer", &n, &e, NULL, NULL) == 0)
                printf("cert parse OK, e=%u\n", e.d[0]);
            else
                printf("cert parse FAILED\n");
            return 0;
        } else if (argv[i][0] != '-') {
            if (cer == NULL || strcmp(cer, "dev.cer") == 0)
                cer = argv[i];
            else
                key = argv[i];
        }
    }
    printf("generating %d-bit RSA key...\n", bits);
    if (devcert_generate(&dc, bits, name) != 0) {
        fprintf(stderr, "key generation failed\n");
        return 1;
    }
    if (devcert_save(&dc, cer, key) != 0) {
        fprintf(stderr, "cannot write %s / %s\n", cer, key);
        return 1;
    }
    printf("wrote %s (%u bytes) and %s\n", cer, (unsigned)dc.cert_len, key);
    return 0;
}
