/*
*	Name : AknDialog.h
*	Part of : Avkon
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
*/

#ifndef __AKNDIALOG_H__
#define __AKNDIALOG_H__


#include <eikdialg.h>
#include <eikmobs.h>


class CAknDialogAttributes;

class CAknDialog : public CEikDialog, public MEikMenuObserver
	{
	public :
		// Construction.  Owns a menu so needs ConstructL()  
		IMPORT_C CAknDialog() ;
		IMPORT_C void ConstructL( TInt aMenuTitleResourceId ) ;
		IMPORT_C ~CAknDialog() ;

		// From CEikDialog
		IMPORT_C TInt ExecuteLD( TInt aResourceId ) ;
		IMPORT_C  void PrepareLC(TInt aResourceId);
		IMPORT_C TInt RunLD();

		// From MEikMenuObserver
		IMPORT_C virtual void SetEmphasis( CCoeControl* aMenuControl,TBool aEmphasis ) ;
		IMPORT_C virtual void DynInitMenuPaneL( TInt aResourceId, CEikMenuPane* aMenuPane ) ;
		// From MEikCommandObserver
		IMPORT_C virtual void ProcessCommandL( TInt aCommandId ) ;

		// From CCoeControl
		IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType) ;
		IMPORT_C void FocusChanged(TDrawNow aDrawNow); 

	private: // formerly from MTopSetMember<CEikMenuBar>, now reserved
		IMPORT_C virtual void Reserved_MtsmPosition();
		IMPORT_C virtual void Reserved_MtsmObject();

	protected:
		// From CEikDialog
		IMPORT_C virtual TBool OkToExitL( TInt aButtonId ) ;

		IMPORT_C void DisplayMenuL() ;
		IMPORT_C void HideMenu() ;
		IMPORT_C TBool MenuShowing() const ;
		
		IMPORT_C virtual void SizeChanged();
		IMPORT_C virtual void Draw(const TRect &aRect) const;

	protected: // from MObjectProvider
		IMPORT_C TTypeUid::Ptr MopSupplyObject(TTypeUid aId);

	private: 
		IMPORT_C virtual void CEikDialog_Reserved_1();
		IMPORT_C virtual void CEikDialog_Reserved_2();	
	private: // new function 
		IMPORT_C virtual void CAknDialog_Reserved();
	
	protected: // new function 
			void CreateMenuBarL(TInt aMenuTitleResourceId);

	protected:
		// Owned
		CEikMenuBar* iMenuBar ;
private:
	enum TAknDialogFlag
	    {
	    EAknDialogFlagDialogDeleted = 1,
        EAknDialogFlagDefaultSounds = 2,
		EAknDialogFlagNotConstructed = 4
	    };
	CAknDialogAttributes* iAttributes;  // Was TInt iSpare;

	CAknDialogAttributes* AttributesL();

	} ;

#endif 
