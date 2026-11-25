// securitydefs.inl
//
// (c) Copyright 2003 Symbian Ltd

inline TKeyUsagePKCS15 operator|(TKeyUsagePKCS15 aLeft, TKeyUsagePKCS15 aRight)
	{
	return static_cast<TKeyUsagePKCS15>(static_cast<TUint>(aLeft) | static_cast<TUint>(aRight));
	}

inline TKeyUsagePKCS15 operator&(TKeyUsagePKCS15 aLeft, TKeyUsagePKCS15 aRight)
	{
	return static_cast<TKeyUsagePKCS15>(static_cast<TUint>(aLeft) & static_cast<TUint>(aRight));
	}

inline const TKeyUsagePKCS15& operator|=(TKeyUsagePKCS15& aLeft, TKeyUsagePKCS15 aRight)
	{
	aLeft = aLeft | aRight;
	return aLeft;
	}

inline const TKeyUsagePKCS15& operator&=(TKeyUsagePKCS15& aLeft, TKeyUsagePKCS15 aRight)
	{
	aLeft = aLeft & aRight;
	return aLeft;
	}

inline TKeyUsageX509 operator|(TKeyUsageX509 aLeft, TKeyUsageX509 aRight)
	{
	return static_cast<TKeyUsageX509>(static_cast<TUint>(aLeft) | static_cast<TUint>(aRight));
	}

inline TKeyUsageX509 operator&(TKeyUsageX509 aLeft, TKeyUsageX509 aRight)
	{
	return static_cast<TKeyUsageX509>(static_cast<TUint>(aLeft) & static_cast<TUint>(aRight));
	}

inline const TKeyUsageX509& operator|=(TKeyUsageX509& aLeft, TKeyUsageX509 aRight)
	{
	aLeft = aLeft | aRight;
	return aLeft;
	}

inline const TKeyUsageX509& operator&=(TKeyUsageX509& aLeft, TKeyUsageX509 aRight)
	{
	aLeft = aLeft & aRight;
	return aLeft;
	}
