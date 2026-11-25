// Copyright (c) Symbian Ltd. 2001

#ifndef __STRINGPOOL_INL__
#define __STRINGPOOL_INL__


/** Default (uninitialised) constructor. */
inline RStringTokenBase::RStringTokenBase()
		: iVal(0)
	{
	}

/** Assignment operator; makes a string token from a string.
	@param aVal The string to copy in its compact format  */
inline RStringTokenBase RStringTokenBase::operator=(RStringBase aVal)
	{
	iVal = aVal.iVal;
	return *this;
	}

/** Returns true if the string is null */
inline TBool RStringTokenBase::IsNull() const
	{
	return (iVal == 0);
	}

/** Comparison operator
	@param aVal The string to compare in its compact format  */
inline TBool RStringToken::operator==(RStringToken aVal) const
	{
	return iVal == aVal.iVal;
	}

/** Comparison operator
	@param aVal The string to compare in its compact format. */
inline TBool RStringToken::operator!=(RStringToken aVal) const
	{
	return iVal != aVal.iVal;
	}

/** Assignment operator with unfolded (case-sensitive) rules; makes a string token from a string.
	@param aVal The string to copy */
inline RStringToken RStringToken::operator=(RString aVal)
	{
	iVal = aVal.iVal;
	return *this;
	}

/** Comparison operator
	@param aVal The string to compare.its compact format  */
inline TBool RStringTokenF::operator==(RStringTokenF aVal) const
	{
	return iVal == aVal.iVal;
	}

/** Comparison operator
	@param aVal The string to compare.in its compact format  */
inline TBool RStringTokenF::operator!=(RStringTokenF aVal) const
	{
	return iVal != aVal.iVal;
	}

/** Assignment operator with folded (case-insensitive) rules; makes a string token from a string .
	@param aVal The string to copy */
inline RStringTokenF RStringTokenF::operator=(RStringF aVal)
	{
	iVal = aVal.iVal;
	return *this;
	}

/** Default (non-initialised) Constructor. */
inline RStringBase::RStringBase()
		: iVal(0)
	{
	}

/** Returns a compact string equivalent to the string  */
inline RStringBase::operator RStringTokenBase() const
	{
	RStringTokenBase s;
	s.iVal = iVal;
	return s;
	}

/** Copies a string. Both the original and the copy must be
	separately closed 
*/
inline RString RString::Copy()
	{
	RStringBase::Copy();
	return *this;
	}

/** Returns a compact string equivalent to the string (for case-sensitive strings)  */
inline RString::operator RStringToken() const
	{
	RStringToken s;
	s.iVal = iVal;
	return s;
	}

/** Copies a string. Both the original and the copy must be
	separately closed 
*/
inline RStringF RStringF::Copy()
	{
	RStringBase::Copy();
	return *this;
	}

/** Comparison operator for case-insensitive strings
	@param aVal The string to compare. */
inline TBool RStringF::operator==(const RStringF& aVal) const
	{
	__ASSERT_DEBUG(iPool.iImplementation==aVal.iPool.iImplementation || aVal.iVal==0 || iVal==0, StringPoolPanic::Panic(StringPoolPanic::EComparisonBetweenTwoStringPoolsNotAllowed));
	return (iVal == aVal.iVal);
	}

/** Comparison operator for case-insensitive strings
	@param aVal The string to compare. */
inline TBool RStringF::operator!=(const RStringF& aVal) const
	{
	__ASSERT_DEBUG(iPool.iImplementation==aVal.iPool.iImplementation || aVal.iVal==0 || iVal==0, StringPoolPanic::Panic(StringPoolPanic::EComparisonBetweenTwoStringPoolsNotAllowed));
	return (iVal != aVal.iVal);
	}

/** Returns a compact string equivalent to the string(for case-insensitive strings)  */
inline RStringF::operator RStringTokenF() const
	{
	RStringTokenF s;
	s.iVal = iVal;
	return s;
	}

/** Returns the string pool */
inline RStringPool RStringBase::Pool() const 
	{
	return iPool;
	}

/** Comparison operator for case-sensitive strings
	@param aVal The string to compare. */
inline TBool RString::operator==(const RString& aVal) const
	{
	__ASSERT_DEBUG(iPool.iImplementation==aVal.iPool.iImplementation || aVal.iVal==0 || iVal==0, StringPoolPanic::Panic(StringPoolPanic::EComparisonBetweenTwoStringPoolsNotAllowed));
	return (iVal == aVal.iVal);
	}

/** Comparison operator for case-sensitive strings
	@param aVal The string to compare. */
inline TBool RString::operator!=(const RString& aVal) const
	{
	__ASSERT_DEBUG(iPool.iImplementation==aVal.iPool.iImplementation || aVal.iVal==0 || iVal==0, StringPoolPanic::Panic(StringPoolPanic::EComparisonBetweenTwoStringPoolsNotAllowed));
	return (iVal != aVal.iVal);
	}

/** Default constructor. */
inline RStringPool::RStringPool()
		: iImplementation(0)
	{
	}


#endif // __STRINGPOOL_INL__
