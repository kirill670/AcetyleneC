// BAMATCH.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

//	Started by Brendan, January 1996
// 	Descended from HCIMATCH.H
//	Incremental matcher class
//

#if !defined (__BAMATCH_H__)
#define __BAMATCH_H__

#if !defined(__E32STD_H__)
#include <e32std.h>
#endif

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif


/**
 *
 * A simple class that encapsulates a text string.
 *
 * As with the descriptor classes, the class sets a maximum length for
 * the encapsulated string, which cannot be exceeded. The class might be
 * preferred to a descriptor in some circumstances as its maximum length
 * can be increased (unlike a <code>TBuf</code>), and it can be created
 * on the stack (unlike an <code>HBufC</code>) .
 *
 * @since 5.0
 * @lib "bafl.lib"
 */
class RTextBuf
	{
public:
	IMPORT_C RTextBuf();
	IMPORT_C ~RTextBuf();
public:
	inline TPtr& Text();
	inline const TPtr& Text() const;
	inline TInt MaxLength() const;
	inline void SetText(const TDesC &aDes);
	IMPORT_C void SetMaxLengthL(TInt aMaxLength);
private:
	TPtr iPtr;
	TText* iText;
	};


/**
 *
 * Base class for incremental matcher classes.
 *
 * An incremental matcher compares two text buffers from left-to-right.
 * For example, the match between "garage" and "gander" is "ga".The class
 * provides the interface for getting and setting the text to be matched
 * against, and for performing match tests. Each type of match test is
 * available in three versions, one using binary comparison, one using
 * locale collation rules (comparison of strings to produce a
 * dictionary-like ('lexicographic') ordering, e.g. ignoring
 * punctuation), and one using locale folding rules (e.g. ignoring case).
 *
 * @since 5.0
 * @lib "bafl.lib"
 */
class RIncrMatcherBase
	{
public:
    IMPORT_C virtual ~RIncrMatcherBase();
protected:
	inline RIncrMatcherBase() {}
protected:
	virtual TDes& MatchDes()=0;
	virtual const TDes& MatchDes() const=0; 
public:
	inline TInt MaxLength() const;
	inline TInt MatchLength() const;
	inline TPtrC MatchText() const;
//
	inline void Clear();
	IMPORT_C void DeleteLastChar();
	IMPORT_C void AppendChar(TChar aLetter);
	inline void SetMatchText(const TDesC& aText);
//
	IMPORT_C void SetBestMatch(const TDesC& aBuf);
	IMPORT_C void SetBestMatchC(const TDesC& aBuf);
	IMPORT_C void SetBestMatchF(const TDesC& aBuf);
	IMPORT_C TBool IsMatch(const TDesC& aBuf) const;
	IMPORT_C TBool IsMatchC(const TDesC& aBuf) const;
	IMPORT_C TBool IsMatchF(const TDesC& aBuf) const;
	IMPORT_C TInt FirstMatchingIndex(TInt& aResult,const MDesCArray& aDesArray,TInt aStartIndex=0) const;
	IMPORT_C TInt FirstMatchingIndexC(TInt& aResult,const MDesCArray& aDesArray,TInt aStartIndex=0) const;
	IMPORT_C TInt FirstMatchingIndexF(TInt& aResult,const MDesCArray& aDesArray,TInt aStartIndex=0) const;
private:
	typedef TInt (*TCompareFunc)(const TText*,TInt,const TText*,TInt);
	TBool DoIsMatch(const TDesC& aQuery,TCompareFunc aCompare) const;
	TInt DoFirstMatchingIndex(TInt& aIndex,const MDesCArray& aDesArray,TCompareFunc aCompare) const;
	void DoSetBestMatch(const TDesC& aBuf,TCompareFunc aCompare);
	};


/**
 *
 * Incrementally matches text against a descriptor, accessed via a
 * pointer.
 *
 * The class does not take a copy of the text to match against, but only
 * stores the pointer.
 *
 * @since 5.0
 * @lib "bafl.lib"
 */
class RIncrMatcherPtr : public RIncrMatcherBase
	{
public:
	IMPORT_C RIncrMatcherPtr();
	IMPORT_C RIncrMatcherPtr(TDes& aDes);
    IMPORT_C virtual ~RIncrMatcherPtr();
public:
	inline void SetMatcherPtr(TDes& aDes);
protected:
	IMPORT_C TDes& MatchDes();
	IMPORT_C const TDes& MatchDes() const;
private:
	TDes* iDesPtr;
	};


/**
 *
 * Incrementally matches text against a text buffer with variable maximum
 * length.
 * @since 5.0
 * @lib "bafl.lib"
 */
class RIncrMatcherTextBuf : public RIncrMatcherBase
	{
public:
    IMPORT_C RIncrMatcherTextBuf();
    IMPORT_C virtual ~RIncrMatcherTextBuf();
	inline void SetMatcherLengthL(TInt aMaxLength);
protected:
	IMPORT_C TDes& MatchDes();
	IMPORT_C const TDes& MatchDes() const;
private:
	RTextBuf iTextBuf;
	};

template <TInt aMaximumSize>

/**
 *
 * Incrementally matches text against a modifiable descriptor buffer.
 *
 * Set <code>aMaximumSize</code> to be the maximum size of this buffer.
 *
 * @since 5.0
 * @lib "bafl.lib"
 */
class RIncrMatcherBuf : public RIncrMatcherBase
	{
public:
	/**
	 * Default constructor.
	 */
	RIncrMatcherBuf() {}
protected:
	/**
	 * Gets the match text.
	 *
	 * @returns   "TDes&"
	 *            Match text
	 */
	inline TDes& MatchDes() {return(iMatchBuf);}

	/**
	 * Gets the match text.
	 *
	 * @returns   "const TDes&"
	 *            Match text
	 */
	inline const TDes& MatchDes() const {return(iMatchBuf);}
	inline RIncrMatcherBuf(const RIncrMatcherBuf& aMatcher) {iMatchBuf=aMatcher.iMatchBuf;}
private:
	TBuf<aMaximumSize> iMatchBuf;
    };


inline TPtr& RTextBuf::Text()
	{return(iPtr);}

/**
 * Gets the text as a descriptor.
 */
inline const TPtr& RTextBuf::Text() const
	{return(iPtr);}

/**
 * Gets the maximum length of the text.
 */
inline TInt RTextBuf::MaxLength() const
	{return(iPtr.MaxLength());}

/**
 *
 * Sets the text.
 *
 * You must have set the maximum length appropriately first with
 * <code>SetMaxLengthL()</code>.
 *
 */
inline void RTextBuf::SetText(const TDesC &aDes)
	{iPtr.Copy(aDes);}


inline TInt RIncrMatcherBase::MaxLength() const
	{return(MatchDes().MaxLength());}
inline TInt RIncrMatcherBase::MatchLength() const
	{return(MatchDes().Length());}
inline TPtrC RIncrMatcherBase::MatchText() const
	{return(TPtrC(MatchDes()));}
inline void RIncrMatcherBase::SetMatchText(const TDesC& aText)
	{MatchDes()=aText;}

/**
 * Clears the match text.
 */
inline void RIncrMatcherBase::Clear()
	{MatchDes().Zero();}

/**
 *
 * Sets the text to be matched against.
 *
 * @param     "TDes& aDes"
 *            Text to be matched against
 */
inline void RIncrMatcherPtr::SetMatcherPtr(TDes& aDes)
	{iDesPtr=&aDes;}


/**
 *
 * Sets the maximum length of text that can be stored through
 * <code>SetMatchText()</code> etc.
 *
 * @param     "TInt aMaxLength"
 *            Maximum length of text that can be stored
 */
inline void RIncrMatcherTextBuf::SetMatcherLengthL(TInt aMaxLength)
	{iTextBuf.SetMaxLengthL(aMaxLength);}


#endif
