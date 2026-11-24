//  random.h
// (c) 1999-2003 Symbian Ltd
//

/**
 * @file
 *
 * @publishedAll
 * @released
 */

#ifndef __RANDOM_H__
#define __RANDOM_H__

#include <e32base.h>

class CRandom : public CBase
/**
 * @publishedAll
 * @released
 */
	{
public:
	virtual void GenerateBytesL(TDes8& aDest) = 0;
protected:
	IMPORT_C CRandom(void);
private:
	CRandom(const CRandom&);
	CRandom& operator=(const CRandom&);
	};

IMPORT_C void SetThreadRandomL(CRandom* aRNG);
IMPORT_C void SetThreadRandomLC(CRandom* aRNG);
/** @internalAll */
void DeleteThreadRandom(TAny* aPtr);
IMPORT_C void DestroyThreadRandom(void);
IMPORT_C void GenerateRandomBytesL(TDes8& aDest);

class CSystemRandom : public CRandom
/**
 * @publishedAll
 * @released
 */
	{
public:
	IMPORT_C static CSystemRandom* NewL(void);
	IMPORT_C static CSystemRandom* NewLC(void);
	virtual void GenerateBytesL(TDes8& aDest);
private:
	CSystemRandom(void);
	CSystemRandom(const CSystemRandom&);
	CSystemRandom& operator=(const CSystemRandom&);
	};

class TRandom
/**
 * @publishedAll
 * @released
 */
	{
public:
	IMPORT_C static void Random(TDes8& aDestination);
	};

class RRandomSession:public RSessionBase
/**
 * @publishedAll
 * @released
 */
	{
public:
	IMPORT_C RRandomSession(void);
	IMPORT_C TInt GetRandom(TDes8& aDestination);
	IMPORT_C void ConnectL(void);
	};

#endif // __RANDOM_H__
