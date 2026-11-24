#include "ac_crypto.h"

static void dsa_name(Der *d, const char *cn)
{
    Der cn_atv, o_atv, both;
    der_init(&cn_atv);
    der_init(&o_atv);
    der_init(&both);
    {
        Der o, v, a;
        der_init(&o);
        der_init(&v);
        der_init(&a);
        der_oid(&o, "2.5.4.3");
        der_printable(&v, cn);
        der_raw(&a, o.data, o.len);
        der_raw(&a, v.data, v.len);
        der_tlv(&cn_atv, 0x30, a.data, a.len);
        der_free(&o);
        der_free(&v);
        der_free(&a);
    }
    {
        Der o, v, a;
        der_init(&o);
        der_init(&v);
        der_init(&a);
        der_oid(&o, "2.5.4.10");
        der_printable(&v, "AcetyleneC SDK");
        der_raw(&a, o.data, o.len);
        der_raw(&a, v.data, v.len);
        der_tlv(&o_atv, 0x30, a.data, a.len);
        der_free(&o);
        der_free(&v);
        der_free(&a);
    }
    {
        Der set, seq, c_atv, cset;
        der_init(&set);
        der_init(&seq);
        der_init(&c_atv);
        der_init(&cset);
        {
            Der o, v, a;
            der_init(&o);
            der_init(&v);
            der_init(&a);
            der_oid(&o, "2.5.4.6");
            der_printable(&v, "RU");
            der_raw(&a, o.data, o.len);
            der_raw(&a, v.data, v.len);
            der_tlv(&c_atv, 0x30, a.data, a.len);
            der_free(&o);
            der_free(&v);
            der_free(&a);
        }
        der_tlv(&set, 0x31, cn_atv.data, cn_atv.len);
        der_tlv(&seq, 0x31, o_atv.data, o_atv.len);
        der_tlv(&cset, 0x31, c_atv.data, c_atv.len);
        der_raw(&both, cset.data, cset.len);
        der_raw(&both, set.data, set.len);
        der_raw(&both, seq.data, seq.len);
        der_tlv(d, 0x30, both.data, both.len);
        der_free(&c_atv);
        der_free(&cset);
        der_free(&set);
        der_free(&seq);
    }
    der_free(&cn_atv);
    der_free(&o_atv);
    der_free(&both);
}

static void dsa_alg(Der *d)
{
    static const u8 oid[] = {0x06, 0x07, 0x2a, 0x86, 0x48, 0xce, 0x38, 0x04, 0x03};
    der_raw(d, oid, sizeof(oid));
}

static void dsa_spki(Der *d, const DsaKey *k)
{
    Der inner, params, ybits, yint, seq;
    der_init(&inner);
    der_init(&params);
    der_init(&ybits);
    der_init(&yint);
    der_init(&seq);
    der_int(&inner, &k->p);
    der_int(&inner, &k->q);
    der_int(&inner, &k->g);
    der_tlv(&params, 0x30, inner.data, inner.len);
    der_int(&yint, &k->y);
    der_bits(&ybits, yint.data, yint.len, 0);
    {
        static const u8 oid[] = {0x06, 0x07, 0x2a, 0x86, 0x48, 0xce, 0x38, 0x04, 0x01};
        Der alg, body;
        der_init(&alg);
        der_init(&body);
        der_raw(&alg, oid, sizeof(oid));
        der_raw(&alg, params.data, params.len);
        der_tlv(&body, 0x30, alg.data, alg.len);
        der_raw(&body, ybits.data, ybits.len);
        der_tlv(&seq, 0x30, body.data, body.len);
        der_free(&alg);
        der_free(&body);
    }
    der_raw(d, seq.data, seq.len);
    der_free(&inner);
    der_free(&params);
    der_free(&ybits);
    der_free(&yint);
    der_free(&seq);
}

int devcert_generate_dsa(DevCert *dc, const char *common_name)
{
    Der tbs, body, ver, serial, name, validity, spki, sigalg, sigder, sigbits, cert, ext;
    u8 hash[20], r[20], s[20];
    if (dsa_generate(&dc->dsa) != 0)
        return -1;
    dc->is_dsa = 1;
    der_init(&tbs);
    der_init(&body);
    der_init(&ver);
    der_init(&serial);
    der_init(&name);
    der_init(&validity);
    der_init(&spki);
    der_init(&sigalg);
    der_init(&sigder);
    der_init(&sigbits);
    der_init(&cert);
    der_init(&ext);

    der_small_int(&ver, 2);
    der_small_int(&serial, 1);
    dsa_name(&name, common_name);
    {
        Der t1, t2, v;
        der_init(&t1);
        der_init(&t2);
        der_init(&v);
        der_utctime(&t1, 2020, 1, 1, 0, 0, 0);
        der_utctime(&t2, 2040, 1, 1, 0, 0, 0);
        der_raw(&v, t1.data, t1.len);
        der_raw(&v, t2.data, t2.len);
        der_tlv(&validity, 0x30, v.data, v.len);
        der_free(&t1);
        der_free(&t2);
        der_free(&v);
    }
    dsa_spki(&spki, &dc->dsa);
    {
        Der crit, bcval, v, e, exts;
        static const u8 oid_bc[] = {0x06, 0x03, 0x55, 0x1d, 0x13};
        der_init(&crit);
        der_init(&bcval);
        der_init(&v);
        der_init(&e);
        der_init(&exts);
        der_tlv(&crit, 0x01, (const u8 *)"\xff", 1);
        der_tlv(&bcval, 0x04, (const u8 *)"\x30\x03\x01\x01\xff", 5);
        der_tlv(&v, 0x04, bcval.data, bcval.len);
        {
            Der a;
            der_init(&a);
            der_raw(&a, oid_bc, sizeof(oid_bc));
            der_raw(&a, crit.data, crit.len);
            der_raw(&a, v.data, v.len);
            der_tlv(&e, 0x30, a.data, a.len);
            der_free(&a);
        }
        der_tlv(&exts, 0x30, e.data, e.len);
        der_tlv(&ext, 0xa3, exts.data, exts.len);
        der_free(&crit);
        der_free(&bcval);
        der_free(&v);
        der_free(&e);
        der_free(&exts);
    }
    {
        Der a;
        der_init(&a);
        der_tlv(&body, 0xa0, ver.data, ver.len);
        der_raw(&body, serial.data, serial.len);
        dsa_alg(&a);
        der_tlv(&body, 0x30, a.data, a.len);
        der_free(&a);
        der_raw(&body, name.data, name.len);
        der_raw(&body, validity.data, validity.len);
        der_raw(&body, name.data, name.len);
        der_raw(&body, spki.data, spki.len);
        der_tlv(&tbs, 0x30, body.data, body.len);
    }
    sha1(tbs.data, tbs.len, hash);
    if (dsa_sign(&dc->dsa, hash, r, s) != 0)
        return -1;
    {
        Der ri, si, both;
        der_init(&ri);
        der_init(&si);
        der_init(&both);
        {
            BigNum b;
            bn_from_bytes(&b, r, 20);
            der_int(&ri, &b);
            bn_from_bytes(&b, s, 20);
            der_int(&si, &b);
        }
        der_raw(&both, ri.data, ri.len);
        der_raw(&both, si.data, si.len);
        der_tlv(&sigder, 0x30, both.data, both.len);
        der_free(&ri);
        der_free(&si);
        der_free(&both);
    }
    der_bits(&sigbits, sigder.data, sigder.len, 0);
    {
        Der a, outer;
        der_init(&a);
        der_init(&outer);
        der_raw(&outer, tbs.data, tbs.len);
        dsa_alg(&a);
        der_tlv(&sigalg, 0x30, a.data, a.len);
        der_free(&a);
        der_raw(&outer, sigalg.data, sigalg.len);
        der_raw(&outer, sigbits.data, sigbits.len);
        der_tlv(&cert, 0x30, outer.data, outer.len);
        der_free(&outer);
    }
    if (cert.len > sizeof(dc->cert))
        return -1;
    memcpy(dc->cert, cert.data, cert.len);
    dc->cert_len = cert.len;
    der_free(&tbs);
    der_free(&body);
    der_free(&ver);
    der_free(&serial);
    der_free(&name);
    der_free(&validity);
    der_free(&spki);
    der_free(&sigalg);
    der_free(&sigder);
    der_free(&sigbits);
    der_free(&cert);
    der_free(&ext);
    return 0;
}

int devcert_save_dsa(const DevCert *dc, const char *cer_path, const char *key_path)
{
    Der priv, body;
    der_init(&priv);
    der_init(&body);
    der_small_int(&body, 0);
    der_int(&body, &dc->dsa.p);
    der_int(&body, &dc->dsa.q);
    der_int(&body, &dc->dsa.g);
    der_int(&body, &dc->dsa.y);
    der_int(&body, &dc->dsa.x);
    der_tlv(&priv, 0x30, body.data, body.len);
    ac_pem_write(cer_path, "CERTIFICATE", dc->cert, dc->cert_len);
    ac_pem_write(key_path, "DSA PRIVATE KEY", priv.data, priv.len);
    der_free(&priv);
    der_free(&body);
    return 0;
}
