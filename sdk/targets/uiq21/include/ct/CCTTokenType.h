// Copyright (c) Symbian 2001


#ifndef __CCTTOKENTYPE_H__
#define __CCTTOKENTYPE_H__

#include <ct/MCTTokenType.h>

/**@ingroup ct */
/**@{ */

/** A token type. This abstract class is instantiated via ECom for a
	particular token type. This adds a delayed destruction behaviour
	to MCTTokenType, which defines the majority of the interface.
*/
class CCTTokenType : protected CBase, public MCTTokenType
	{
public:
	/** Returns a file server session */
	inline RFs& Fs();

protected:
	/** Increments the reference count. Must be called for every 
		token created from this interface */
	inline void IncReferenceCount();

	// From this point onwards, everything in this class is essentialy
	// internal and of no interest to dereived classes.
 public:
	/// @name Static constructor functions that use ECom to load the actual implementation.
	///@{
	/** Creates a CCTTokenType given it's CCTTokenTypeInfo */
	IMPORT_C static CCTTokenType* NewL(const CCTTokenTypeInfo& aInfo, RFs aFs);
	/** Creates a CCTTokenType given the UID of the token type. */
	IMPORT_C static CCTTokenType* NewL(TUid aUID, RFs aFs);
	///@}

	/** From MCTTokenType. Releases the token. */
	IMPORT_C virtual void Release();

	/** Returns the UID of the token type. */
	IMPORT_C virtual TUid Type() const;
	/** Returns the label of the token type. */
	IMPORT_C virtual const TDesC& Label() const;

 protected:
	IMPORT_C CCTTokenType();

	/** Destructor */
	IMPORT_C virtual ~CCTTokenType();

 private:
	/** For 2 phase construction */
	void ConstructL(TUid aUID, const TDesC& aLabel, RFs aFs);

 private:
	/// Needed for ECom
	TUid iDtor_ID_Key;

	/// A refedrence count
	TInt iCount;

	/// The UID of the token type.
	TUid iUID;

	/// The label of the token type
	HBufC* iLabel;

	RFs iFs;
	};

inline void CCTTokenType::IncReferenceCount()
	{
	++iCount;
	}

inline RFs& CCTTokenType::Fs()
	{
	return iFs;
	}

// These are defined here as they need to ahve both MCTTokenType and 
// CCTTokenType defined before they can be.
inline MCTTokenType* MCTTokenType::NewL(const CCTTokenTypeInfo& aInfo, RFs aFs)
	{
	return CCTTokenType::NewL(aInfo, aFs);
	}
inline MCTTokenType* MCTTokenType::NewL(TUid aUID, RFs aFs)
	{
	return CCTTokenType::NewL(aUID, aFs);
	}
///@}

#endif //__CCTTOKENTYPE_H__
