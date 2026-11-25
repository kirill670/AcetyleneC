/*
 * NOKIA MOBILE PHONES
 * DIGITAL CONVERGENCE
 * LINDA SW
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 *           vCard Control 
 *           -------------------------
 * 
 *           SW Include Document - C++
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * Module name:    vCardControl
 * 
 * $Archive: /Linda_PDA_SW/vCardBioControl/Inc/VCardControl.h $
 * 
 * $Revision: 11 $
 * 
 * 
 * Copyright (c) 1998. Nokia Mobile Phones
 * 
 * 
 * Change History:
 * 
 * History: VCardControl.h $
 * 
 *
 *---------------------------------------------------------------------------
 */

/*
-----------------------------------------------------------------------------

    DESCRIPTION

    Defines vCard Control.

-----------------------------------------------------------------------------
*/

#if !defined(__VCARDCONTROL_H__)
#define __VCARDCONTROL_H__

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>           // for CEikBorderedControl
#include <eikrted.h>            // for CEikRichTextEditors    
#endif

#include <MdaImageConverter.h>  // for CMdaImageFileToBitmapUtility, MMdaImageUtilObserver


// FORWARD DECLARATIONS

class CEikButtonGroupContainer;
class MMsgBioControlObserver;
class CVersitObject;
class CVersitProperty;
class RFileReadStream;

class CVCardControl : public CEikBorderedControl, public MMdaImageUtilObserver
{
public:
	enum TStatus
		{
		EStatusNone = 0,
		EStatusLoading
		};
    
	CVCardControl();
	~CVCardControl();
	void ConstructL(CCoeControl* aParent,TFileName aFileName);	//suskoe
	void ParseCardL(TFileName aFilename);
	TRect CurrentLineRect() const;
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);	
	TInt NeededHeight() const; //suskoe

public: 
	// From MMdaImageUtilObserver
	void MiuoCreateComplete(TInt aError);
	void MiuoOpenComplete(TInt aError);
	void MiuoConvertComplete(TInt aError);
	
protected:// from CCoeControl
	CCoeControl* ComponentControl(TInt aIndex) const;
	TInt CountComponentControls() const;
	
private:

	void Draw(const TRect& aRect) const; //suskoe
	TBool WrapString(TPtrC& aStringToWrap, TPtrC& aRemainingString, 
					TInt aWidthInPixels, const CFont* aFont) const;
	

	TBool PropertyToBeShown(const CVersitProperty& aProperty) const;	
	void FormNameAndParams(TDes& aNameAndParams, const CVersitProperty *aProperty) const;

	CVersitObject*					iVCard;
	TFileName						iFileName;
	CFbsBitmap*						iBitmap;
    CMdaImageDescToBitmapUtility*   iDescLoadUtil;
	TStatus							iStatus;
	TInt							iCurrentYPos;
	const TInt						iNeededHeight;
	TBool							iPhoto;
	HBufC8*							iPhotoBuf;
	TBool							iHasSound;

};

#endif // __VCARDCONTROL_H__

