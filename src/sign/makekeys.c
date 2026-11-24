#include "ac_crypto.h"

void devcert_set_v1(int v);
void devcert_set_nonull(int v);

int main(int argc, char **argv)
{
    int bits = 1024;
    int use_dsa = 1;
    const char *name = "AcetyleneC Developer";
    const char *cer = NULL;
    const char *key = NULL;
    int i;
    DevCert dc;

    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-bits") == 0 && i + 1 < argc) {
            bits = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-name") == 0 && i + 1 < argc) {
            name = argv[++i];
        } else if (strcmp(argv[i], "-dsa") == 0) {
            use_dsa = 1;
        } else if (strcmp(argv[i], "-rsa") == 0) {
            use_dsa = 0;
        } else if (strcmp(argv[i], "-v1") == 0) {
            devcert_set_v1(1);
        } else if (strcmp(argv[i], "-nonull") == 0) {
            devcert_set_nonull(1);
        } else if (strcmp(argv[i], "--selftest") == 0) {
            u8 h1[20], h2[32], sig[512];
            size_t siglen = 0;
            BigNum n, e;
            sha1("abc", 3, h1);
            sha256("abc", 3, h2);
            printf("sha1(abc)=%02x%02x%02x%02x%02x%02x\n", h1[0], h1[1], h1[2], h1[3], h1[4], h1[5]);
            printf("sha256(abc)=%02x%02x%02x%02x%02x\n", h2[0], h2[1], h2[2], h2[3], h2[4]);
            if (devcert_generate_dsa(&dc, "Test") != 0) {
                printf("dsa keygen FAILED\n");
                return 1;
            }
            {
                u8 r[20], s[20], hash[20];
                sha1("hello world", 11, hash);
                if (dsa_sign(&dc.dsa, hash, r, s) != 0) {
                    printf("dsa sign FAILED\n");
                    return 1;
                }
                printf("dsa cert=%u bytes sig r=%02x%02x.. s=%02x%02x..\n", (unsigned)dc.cert_len, r[0], r[1], s[0], s[1]);
            }
            if (devcert_generate(&dc, 1024, "Test") != 0) {
                printf("rsa keygen FAILED\n");
                return 1;
            }
            if (devcert_sign(&dc, 0, (const u8 *)"hello world", 11, sig, &siglen) != 0) {
                printf("rsa sign FAILED\n");
                return 1;
            }
            {
                u8 hash[20];
                sha1("hello world", 11, hash);
                printf("rsa cert=%u sig=%u verify=%s\n", (unsigned)dc.cert_len, (unsigned)siglen,
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
            if (!cer)
                cer = argv[i];
            else if (!key)
                key = argv[i];
        }
    }
    if (!cer || !key) {
        fprintf(stderr, "usage: acetylene-makekeys [-dsa|-rsa] [-bits N] [-name CN] [-v1] [-nonull] out.cer out.key\n");
        return 1;
    }
    memset(&dc, 0, sizeof(dc));
    if (use_dsa) {
        printf("generating DSA key...\n");
        if (devcert_generate_dsa(&dc, name) != 0) {
            fprintf(stderr, "key generation failed\n");
            return 1;
        }
        if (devcert_save_dsa(&dc, cer, key) != 0) {
            fprintf(stderr, "cannot write %s / %s\n", cer, key);
            return 1;
        }
    } else {
        printf("generating %d-bit RSA key...\n", bits);
        if (devcert_generate(&dc, bits, name) != 0) {
            fprintf(stderr, "key generation failed\n");
            return 1;
        }
        if (devcert_save(&dc, cer, key) != 0) {
            fprintf(stderr, "cannot write %s / %s\n", cer, key);
            return 1;
        }
    }
    printf("wrote %s (%u bytes) and %s\n", cer, (unsigned)dc.cert_len, key);
    return 0;
}
