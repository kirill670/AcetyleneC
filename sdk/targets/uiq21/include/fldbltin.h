// FLDBLTIN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __FLDBLTIN_H__
#define __FLDBLTIN_H__

#include <e32std.h>
#include <fldbase.h>


// Classes declared in this file
class MFieldPageNumInfo;
class MFieldNumPagesInfo;
class MFieldFileNameInfo;
// the built-in field types
class CDateTimeField;
class CPageNumField;
class CNumPagesField;
class CFileNameField;
class TRomanNumeral;
//
// Classes referenced
class RReadStream;
class RWriteStream;


/**
 *
 * Specifies the mixin protocol for evaluating a page number field (see
 * class <code>CPageNumField</code>).
 *
 * It declares a single pure virtual function,
 * <code>UpdateFieldPageNum()</code>. You should implement this function
 * in a concrete derived class, then pass an object of the derived class
 * to the page number field (using
 * <code>CPageNumField::SetPageNumInfo()</code>) before the field can be
 * evaluated.
 *
 * @since 5.0
 * @lib ""
 */

class MFieldPageNumInfo
	{
public:
	
	/**
	 *
	 * Implementations of this function should return the current page
	 * number.
	 *
	 * @returns   " TInt "
	 *            The page number.
	 */

	virtual TInt UpdateFieldPageNum()const=0;
	};


/**
 *
 * Specifies the mixin protocol for evaluating a number of pages field
 * (see class <code>CNumPagesField</code>).
 *
 * It declares a single pure virtual function,
 * <code>UpdateFieldNumPages()</code>. You should implement this function
 * in a concrete derived class, then pass an object of the derived class
 * to the number of pages field (using
 * <code>CNumPagesField::SetNumPagesInfo()</code>) before the field can
 * be evaluated.
 *
 * @since 5.0
 * @lib ""
 */

class MFieldNumPagesInfo
	{
public:
	
	/**
	 *
	 * Implementations of this function should return the number of pages in
	 * the current document.
	 *
	 * @returns   " TInt "
	 *            The total number of pages.
	 */

	virtual TInt UpdateFieldNumPages()const=0;
	};


/**
 *
 * Specifies the mixin protocol for evaluating a filename field.
 *
 * It defines a single pure virtual function,
 * <code>UpdateFieldFileName()</code>. You should implement this function
 * in a concrete derived class, then pass an object of the derived class
 * to the filename field (using
 * <code>CFileNameField::SetFileNameInfo()</code>) before the field can
 * be evaluated.
 *
 * @since 5.0
 * @lib ""
 */

class MFieldFileNameInfo
	{
public:
	
	/**
	 *
	 * Implementations of this function should set <code>aValueText</code> to
	 * the current document's filename, if the buffer is large enough.
	 *
	 * If not, the function should return the length which is required to
	 * hold the filename.
	 *
	 * @param     " TPtr& aValueText "
	 *            Descriptor which on return contains the document's
	 *            filename.
	 * @returns   " TInt "
	 *            Zero if <code>aValueText</code> is long enough to hold
	 *            the filename. Otherwise, the length of the buffer
	 *            which is required to hold the filename.
	 */

	virtual TInt UpdateFieldFileName(TPtr& aValueText)const=0;
	};


/**
 *
 * A date/time field.
 *
 * This is a field which may contain any or all components of the date
 * and time, and can be formatted in a variety of ways. The class stores
 * a format string, which is used by the <code>Value()</code> function to
 * format the current date/time. For information on date/time formatting,
 * see the documentation of <code>TTime::FormatL()</code>.
 *
 * @since 5.0
 * @lib " field.lib "
 */

class CDateTimeField : public CTextField
	{
public:
	IMPORT_C CDateTimeField();
	IMPORT_C void SetFormat(const TDesC& aFormat);
	// from TTextField
	IMPORT_C virtual TInt Value(TPtr& aValueText);
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream)const;
	//
	// Getters
	IMPORT_C const TDesC& FormatString()const;
	IMPORT_C TUid Type()const;
protected:
	TBuf<64> iFormatString;
	};


/**
 *
 * Stores a style for displaying the value of numeric fields.
 *
 * This style is used when converting the integer value of numeric fields
 * into a descriptor for display in another format, e.g. Arabic, Roman,
 * alphabetic. This is the base class for the numeric fields,
 * <code>CPageNumField</code> and <code>CNumPagesField</code>.
 *
 * @since 5.0
 * @lib " field.lib "
 */

class CPageFieldBase : public CTextField
	{
public:
	
/**
 *
 * Numeric style.
 * @since 
 */

	enum TNumberStyle {
		/** Arabic numeral, e.g. 1, 2, 3. */
		EArabic,			// 1,2,3
		/** Upper case Roman numeral, e.g. I, II, III. */
		ERomanUpper,		// I,II,III
		/** Lower case Roman numeral, e.g. i, ii, iii. */
		ERomanLower,		// i,ii,iii
		/** Upper case alphabetic. */
		EAlphabeticUpper,	// A,B,C
		/** Lower case alphabetic. */
		EAlphabeticLower	// a,b,c
		};
public:
	
/**
 *
 * Sets the numeric style.
 *
 * @param     " TNumberStyle aStyle "
 *            The numeric style.
 */

	inline void SetNumberStyle(TNumberStyle aStyle) { iStyle = aStyle; } 
	// from TTextField
	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream)const;
	//
	// Getters
	IMPORT_C TNumberStyle NumberStyle()const;
protected:
	TInt InsertValue(TPtr& aValueText,TInt aValue);
protected:
	TNumberStyle iStyle;
	};


/**
 *
 * A field which evaluates to the current page number in the document.
 *
 * Before the page number field can be evaluated, it must be passed a
 * pointer to an object which implements the
 * <code>UpdateFieldPageNum()</code> function.
 *
 * @since 5.0
 * @lib " field.lib "
 */

class CPageNumField : public CPageFieldBase
	{
public:
	
/**
 *
 * Sets the object which implements <code>UpdateFieldPageNum()</code>, to
 * get the current page number.
 *
 * <code>SetPageNumInfo()</code> must be called before the page number
 * field can be evaluated.
 *
 * @param     " MFieldPageNumInfo* aInfo "
 *            Pointer to an object which implements
 *            <code>UpdateFieldPageNum()</code>.
 */

	inline void SetPageNumInfo(MFieldPageNumInfo* aInfo) { iPageNumInfo=aInfo; }
	// from TTextField
	IMPORT_C TInt Value(TPtr& aValueText);
	IMPORT_C TUid Type()const;
protected:
	MFieldPageNumInfo* iPageNumInfo;
	};


/**
 *
 * A field which evaluates to the number of pages in the document.
 *
 * Before the number of pages field can be evaluated, it must be passed a
 * pointer to an object which implements the
 * <code>UpdateFieldNumPages()</code> function.
 *
 * @since 5.0
 * @lib " field.lib "
 */

class CNumPagesField : public CPageFieldBase
	{
public:
	
/**
 *
 * Sets the object which implements <code>UpdateFieldNumPages()</code>,
 * to get the number of pages in the document.
 *
 * <code>SetNumPagesInfo()</code> must be called before the number of
 * pages field can be evaluated.
 *
 * @param     " MFieldNumPagesInfo* aInfo "
 *            Pointer to an object which implements
 *            <code>UpdateFieldNumPages()</code>.
 */

	inline void SetNumPagesInfo(MFieldNumPagesInfo* aInfo) { iNumPagesInfo=aInfo; }
	// from TTextField
	IMPORT_C TInt Value(TPtr& aValueText);
	IMPORT_C TUid Type()const;
protected:
	MFieldNumPagesInfo* iNumPagesInfo;
	};


/**
 *
 * A filename field.
 *
 * This is a field which evaluates to the filename of the current
 * document. Before the filename field can be evaluated, it must be
 * passed a pointer to an object which implements the
 * <code>UpdateFieldFileName()</code> function.
 *
 * @since 5.0
 * @lib " field.lib "
 */

class CFileNameField : public CTextField
	{
public:
	
/**
 *
 * Sets the object which implements the
 * <code>UpdateFieldFileName()</code> function, to get the current
 * document's filename.
 *
 * <code>SetFileNameInfo()</code> must be called before the filename
 * field can be evaluated.
 *
 * @param     " MFieldFileNameInfo* aInfo "
 *            Pointer to an object which implements the
 *            <code>UpdateFieldFileName()</code> function.
 */

	inline void SetFileNameInfo(MFieldFileNameInfo* aInfo) { iFileNameInfo=aInfo; }
	// from TTextField
	IMPORT_C virtual TStreamId StoreL(CStreamStore& aStore)const;  // returns KNullStreamId
	IMPORT_C virtual void RestoreL(const CStreamStore& aStore,TStreamId aId); // does nothing.
	IMPORT_C virtual TInt Value(TPtr& aValueText);
	
/**
 *
 * Overrides the base class method to do nothing, because this class has
 * no persistent data.
 *
 */

	inline virtual void InternalizeL(RReadStream& /*aStream*/) {}; // stream the formatting
	IMPORT_C TUid Type()const;
protected:
	MFieldFileNameInfo* iFileNameInfo;
	};


#endif
