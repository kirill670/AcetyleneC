/*
* ==============================================================================
*  Name        : ckninfo.h
*  Part of     : CKON
*  Interface   : Misc Dialog API
*  Description : The CCknInfoDialog class implements a dialog to display an 
*                Information Note.
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef CKNINFO_H
#define CKNINFO_H

//** INCLUDES */
#include <eikdialg.h>
#include <barsread.h>
#include <gulicon.h>
#include <eikenv.h>

/**
 * The <code>CCknInfoDialog</code> class implements an Information Note.
 * There are different overloaded ways in which the Information Note methods
 * can be called, depending on whether a custom icon is used and if the message
 * text is passed in via descriptor or resource ID.
 *
 * @lib ckndlg.lib
 * @since Series90 1.0
 */
class CCknInfoDialog : public CEikDialog, public MEikInfoDialog
    {
public:
    /**
    * Starts the two-phase object construction.
    *
    * @return a pointer to the newly constructed <code>CCknInfoDialog</code> object
    * @remarks
    * @see
    */
    static CCknInfoDialog* NewL();

    /**
    * Launches an Information Note with a custom icon.
    * The message to be displayed is passed in via a descriptor.
    * 
    * @param aMsg A reference to the descriptor to be used as the message 
    *             text in the Information Note
    * @param aIcon A pointer to the icon to be shown in the Information 
    *              Note
    * @param aButtonTextRid The ID of a resource giving the string of text 
    *                       to display on the button
    * @return the ID of the button used to dismiss the dialog, 
    *         <code>EEikBidOk</code>
    * @remark If <code>aIcon=NULL</code>, no icon is displayed.
    *         If <code>aButtonTextRid=0</code>, the default text is displayed
    * @see EEikBidOk in uikon.hrh
    */
    static IMPORT_C TBool RunDlgLD(const TDesC& aMsg, CGulIcon* aIcon, TInt aButtonTextRid);

    /**
    * Launches an Information Note with a custom icon.
    * The message to be displayed is passed in via a resource ID.
    *
    * @param aMsgRid The message ID from the resource file
    * @param aIcon A pointer to the icon to be displayed in the 
    *              Information Note
    * @param aButtonTextRid The ID of a resource giving the string of text 
    *                       to display on the button
    * @return the ID of the button used to dismiss the dialog, <code>EEikBidOk</code>
    * @remark If <code>aIcon=NULL</code>, no icon is displayed.
    *         If <code>aButtonTextRid=0</code>, the default text is displayed
    * @see EEikBidOk in uikon.hrh
    */
    static IMPORT_C TBool RunDlgLD(TInt aMsgRid, CGulIcon* aIcon, TInt aButtonTextRid);

    /**
    * Launches an Information Note with the default icon.
    * The message to be displayed is passed in via a descriptor.
    * 
    * @param aMsg A reference to the descriptor to be used as the message 
    *             text in the Information Note
    * @param aButtonTextRid The ID of a resource giving the string of text 
    *                       to display on the button
    * @remark If <code>aButtonTextRid=0</code>, the default text is displayed
    * @return the ID of the button used to dismiss the dialog, <code>EEikBidOk</code>
    * @see EEikBidOk in uikon.hrh
    */
    static IMPORT_C TBool RunDlgDefaultIconLD(const TDesC& aMsg, TInt aButtonTextRid);

    /**
    * Launches an Information Note with the default icon.
    * The message to be displayed is passed in via a resource ID
    *
    * @param aMsgRid The message ID from a resource file
    * @param aButtonTextRid The ID of a resource giving the string of text 
    *                       to display on the button
    * @remark If <code>aButtonTextRid=0</code>, the default text is displayed
    * @return the ID of the button used to dismiss the dialog, <code>EEikBidOk</code>
    * @see EEikBidOk in uikon.hrh
    */
    static IMPORT_C TBool RunDlgDefaultIconLD(TInt aMsgRid, TInt aButtonTextRid);

private:
    CCknInfoDialog();
    ~CCknInfoDialog();
    CCknInfoDialog(const TDesC& aTitle, const TDesC& aMsg, CGulIcon* aIcon);
    TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

private: //** from MEikInfoDialog */
    TBool RunDlgLD(TInt aResource, const TDesC& aTitle, const TDesC& aMsg);

private:
    void PreLayoutDynInitL();
    TBool OkToExitL(TInt aButtonId);

private:
    const TDesC* iTitle;
    const TDesC* iMessage;
    const CGulIcon* iIcon;
    TBool iUnused;
    HBufC* iButtonText;

public:
    /**
    * Kept for binary compatibility.
    * @deprecated 
    * @see
    */
    static IMPORT_C TBool RunDlgLD(const TDesC& aTitle, const TDesC& aMsg, CGulIcon* aIcon=NULL);
    };


#endif  // CKNINFO_H

// End of File
