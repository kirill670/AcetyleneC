/*
* ============================================================================
*  Name     : AknQueryValueText.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
// AknQueryValueText.h
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

#if !defined(__AKNQUERYVALUETEXT_H__)
#define __AKNQUERYVALUETEXT_H__

#include <bamdesca.h>
#include <eikdialg.h>
#include "AknQueryValue.h"

class CAknQueryValueTextArray;

/**
 * Encapsulates a string. Provides an interface to create a dialog
 * containing a text query control, which will edit the value. Optionally 
 * allows the value to be changed by selecting from a list of values. 
 *
 */
NONSHARABLE_CLASS(CAknQueryValueText) : public CAknQueryValue
    {
public:
	IMPORT_C static CAknQueryValueText* NewL();
	IMPORT_C static CAknQueryValueText* NewLC();
    IMPORT_C virtual ~CAknQueryValueText();
	IMPORT_C void SetArrayL(const CAknQueryValueTextArray* aArray);
	IMPORT_C void SetQueryCaption(TInt aResourceId);
	IMPORT_C HBufC* Value() const;
public: // from MAknQueryValue
    IMPORT_C virtual const MDesCArray* MdcArray() const;
    IMPORT_C virtual HBufC* CurrentValueTextLC();
    IMPORT_C virtual TInt CurrentValueIndex() const;
    IMPORT_C virtual void SetCurrentValueIndex(const TInt aIndex);
    IMPORT_C virtual TBool CreateEditorL();
protected:
	CAknQueryValueText();
	void ConstructL();
	void CalculateCurrentIndex();
	virtual void AppendValueIfNewL();
private: // from MAknQueryValue
	IMPORT_C void Reserved_MAknQueryValue();

private:
	// the following are member variables
	TInt iQueryCaptionId;
	HBufC* iText;
	TInt iCurrentIndex;
	// the following are not owned
	const CAknQueryValueTextArray* iArray;
    };


/**
 * Wraps a descriptor array.
 *
 */
NONSHARABLE_CLASS(CAknQueryValueTextArray) : public CBase, public MDesCArray
	{
public:
	typedef CDesCArray TextArray;
	enum {KSafeSizeOfDescriptorForTextFormat = 32};
public:
	IMPORT_C static CAknQueryValueTextArray* NewL();
	IMPORT_C static CAknQueryValueTextArray* NewLC();
	IMPORT_C ~CAknQueryValueTextArray();
	IMPORT_C void SetArray(TextArray& aArray);
	IMPORT_C TextArray* Array() const;
#ifdef __WINS__
	IMPORT_C const TInt FormattedStringSize() const;
#else
	IMPORT_C TInt FormattedStringSize() const;
#endif // __WINS__

public:
	// from MDesCArray
    IMPORT_C virtual TInt MdcaCount() const;
    IMPORT_C virtual TPtrC MdcaPoint(TInt aIndex) const;
protected:
	CAknQueryValueTextArray();
	void ConstructL();
private:
	// the following members are not owned
	TextArray* iArray;
	TInt iFormattedStringSize;
	};

#endif // __AKNQUERYVALUETEXT_H__

