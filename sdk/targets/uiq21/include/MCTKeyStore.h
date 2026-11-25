// Copyright (c) Symbian Ltd 2001

#ifndef __MCTKEYSTORE_H__
#define __MCTKEYSTORE_H__

#include <securitydefs.h>
#include <mkeystore.h>

///@file

class MCTAuthenticationObject;

/** The UID of a key store interface */
const TInt KInterfaceKeyStore = 0x101F501D;
/** The type ID of CCTKeyInfo objects */
const TUid KKeyInfoUID = {0x101F5152};

/** @ingroup interfaces */
/** @{ */

/** A representation of a key store on a token. This lets the client
	query the keys.
	@see MKeyStore
*/
class MCTKeyStore : public MCTTokenInterface, public MKeyStore
	{
	};
///@}
/** @ingroup interfaces */
/** @{ */

/** A filter to specify which keys should be returned from the store by
	MCTKeyStore::List */
struct TCTKeyAttributeFilter
	{
	/** Constructor */
	IMPORT_C TCTKeyAttributeFilter();
	/** The hash of the key we're looking for. A zero-length
		descriptor means 'don't care */
	TKeyIdentifier iKeyId;
	/** The required usage of the key. A key must match any of the
		usages specified. Use EAllKeyUsages to return all usages. */
	TKeyUsage iUsage;
	};
///@}
/** @ingroup interfaces */
/** @{ */


/** Information about a key, as returned by MCTKeyStore::List */
class CCTKeyInfo : protected CBase, public MCTTokenObject
	{
 public:
	/** Creates a CCTKeyInfo.
		@param aID The SHA1 hash of the key
		@param aUsage The usage of the key
		@param aSize The size of the key in bytes
		@param aProtector A protector object if the key is protected by a PIN.
		This may be NULL if the protector is not known.
		Ownership of this object is taken by the key info
		@param aLabel The label of the key
		@param aToken The token the key is in
		@param aHandle The object ID part of the object handle; an
		integer that is unique amongst keys in this token.
	*/
	IMPORT_C static CCTKeyInfo* NewL(TKeyIdentifier aID, TKeyUsage aUsage, 
							  TUint aSize, MCTAuthenticationObject* aProtector,
							  HBufC* aLabel, MCTToken& aToken, TInt aHandle);
	/** Destructor */
	~CCTKeyInfo();

	/** The ID (SHA-1 hash) of the key */
	inline TKeyIdentifier ID() const;
	/** The key usage */
	inline TKeyUsage Usage() const;
	/** The size of the key */
	inline TUint Size() const;
	/** The PIN (or other authentication object) that protects the key.
		NULL if not known */
	inline MCTAuthenticationObject* Protector() const;
 public:	///@name from MCTTokenObject
	///@{
	/** The label of the key */
 	virtual const TDesC& Label() const;
	/** The token the key is in */
	virtual MCTToken& Token() const;
	/** Returns KKeyInfoUID to indicate this is a key info object */
	virtual TUid Type() const;
	/** A handle for the key. This can be used to identify a key to
	 * another process */
	virtual TCTTokenObjectHandle Handle() const;
	///@}
 private:
	CCTKeyInfo(TKeyIdentifier aID, TKeyUsage aUsage, TUint aSize, 
			   MCTAuthenticationObject* aProtector, HBufC* aLabel,
			   MCTToken& aToken, TInt aHandle);

	/** The ID of the key */
	TKeyIdentifier iID;
	/** The usage of the key */
	TKeyUsage iUsage;
	/** The size of the key */
	TUint iSize;
	/** The protector object of the key. This pointer is not owned by 
		the class */
	MCTAuthenticationObject* iProtector;
	HBufC* iLabel;
	MCTToken& iToken;
	/** The handle of the key*/
	TInt iHandle;
	
	};

inline TKeyIdentifier CCTKeyInfo::ID() const
	{
	return iID;
	}

inline TKeyUsage CCTKeyInfo::Usage() const
	{
	return iUsage;
	}

inline TUint CCTKeyInfo::Size() const
	{
	return iSize;
	}

inline MCTAuthenticationObject* CCTKeyInfo::Protector() const
	{
	return iProtector;
	}

///@}
#endif // __MCTKEYSTORE_H__
