/*
* ============================================================================
*  Name     : AknGlobalNote.h
*  Part of  : Avkon
*
*  Description:
*     
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
#ifndef __AKNGLOBALNOTENOTIFY_H__
#define __AKNGLOBALNOTENOTIFY_H__

#include <AknNotify.h>
#include <aknnotifystd.h>


class CAknGlobalNote : public CAknNotifyBase
  {
public:	
	IMPORT_C static CAknGlobalNote* NewL();
	IMPORT_C static CAknGlobalNote* NewLC();
	IMPORT_C ~CAknGlobalNote();

   /**
	* Enable or disable all text processing done by the dialog.
    * This includes text wrapping, text truncation
    * and reordering of bidirectional text.
    *
    * By default, it is enabled.
    *
    * If text processing is disabled, lines are broken only at explicit line end
    * characters and they are not truncated, but drawn as long as they fit.
    * Also, the dialog does not handle reordering of bidirectional text.
	*
    * @since 2.0
	* @param aEnabled Enable or disable all text processing.
	*/
	IMPORT_C void SetTextProcessing(TBool aEnabled);

	IMPORT_C TInt ShowNoteL(TAknGlobalNoteType aType,const TDesC& aNoteText);
	IMPORT_C TInt ShowNoteL(TRequestStatus& aStatus, TAknGlobalNoteType aType,const TDesC& aNoteText);
	IMPORT_C void CancelNoteL(TInt aNoteId);
	IMPORT_C void SetPriority(TInt aPriority);
	IMPORT_C void SetSoftkeys(TInt aId);
	IMPORT_C void SetGraphic(TInt aId, TInt aMaskId=-1);
	IMPORT_C void SetAnimation(TInt aResourceId);
	IMPORT_C void SetTone(TInt aTone);	// must be specified in avkon.hrh

private:
	CAknGlobalNote();
	void ConstructL();    
	void PrepareBufferL(TAknGlobalNoteType aType,const TDesC& aNoteText);

private:
	IMPORT_C void CAknNotifyBase_Reserved();
private:
	TInt iPriority;
	TInt iSoftkeys;
	TInt iGraphic;
	TInt iGraphicMask;
	TInt iAnimation;
	TInt iTone;
    TBool iTextProcessing;
	CBufFlat *iBuffer;
	TPtrC8 iBufferPtr;
  };


#endif
