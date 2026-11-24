/*
* ============================================================================
*  Name     : aknmessagequerydialog.h
*  Part of  : AVKON
*
*  Description:
* 
*  Version:
*
*  Copyright © 2002, 2005 Nokia Corporation.
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

#if !defined(__AKNMESSAGEQUERYDIALOG_H__)
#define __AKNMESSAGEQUERYDIALOG_H__

#include <aknquerydialog.h>
class CEikImage;
class CAknMessageQueryDialogExtension;

/** 
 * Message query dialog. The dialog contains text that can be scroller page by page.
 */
class CAknMessageQueryDialog : public CAknQueryDialog
    {
public:
    IMPORT_C static CAknMessageQueryDialog* NewL(TDesC& aMessage, const TTone& aTone = ENoTone);

    /**
     * Destructor.
     */
    IMPORT_C ~CAknMessageQueryDialog();

    /**
     * @deprecated - will become protected
     * @param aTone Tone played with the dialog (not implemanted)
     */
    IMPORT_C CAknMessageQueryDialog(const TTone aTone);

public:
    /**
     * Set message text. If you have links in your message you can mark link texts between
     * tags <AknMessageQuery Link> and </AknMessageQuery Link> in the message text.
     *
     * @param aMessage Message text inside query. Insert '\n' to get new line. 
     */
    IMPORT_C void SetMessageTextL(const TDesC& aMessage);

    /**
     * Set header text.
     * @param aHeader Message query header text
     *
     * @deprecated - use Heading() + CAknPopupHeadingPane API instead
     */
    IMPORT_C void SetHeaderTextL(const TDesC& aHeader);  

    /**
     * 
     * Use SetLinkText function to change the first occurance of aLinkText to a link within the
     * Message. If you have many links with the same name, the method will set the links in the 
     * order you call them. Before you set a new link you have to bind the previous one with a 
     * callback by calling SetLink function. 
     *
     * Note that you don't have to call this function if you have already marked your links
     * between tags <AknMessageQuery Link> and </AknMessageQuery Link> in the Message. In that
     * case only SetLink method is used.
     *
     * @param aLinkText Link text inside message.
     * @since 2.8
     */
    IMPORT_C void SetLinkTextL(const TDesC& aLinkText);

    /**
     * SetLink binds a callback to your link so that the dialog knows which callback to call
     * when a link is activateed by the user.
     * @param aLink points to function which is executed when a link is activated by a user.
     * @since 2.8
     */
    IMPORT_C void SetLink(TCallBack& aCallBack);

public: // from CCoeControl
    IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent, TEventCode);

    /**
     * Handles pointer events
     */
    IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent); 

protected: // from CEikDialog
    IMPORT_C virtual void PreLayoutDynInitL();
    IMPORT_C virtual void SetSizeAndPosition(const TSize& aSize);
    IMPORT_C virtual void PostLayoutDynInitL();

private:
    /**
     * @since 2.8
     * With link extension introduced 
     */
    void CreateExtensionL();
    
    /**
     * @since 3.0
     * With multiple link support 
     */
    TInt CountLinks() const;         
    TBool SetNextLinkTextAndLocationL();     // for the specially marked links
    TBool SetNextLinkTextLocationL(const TDesC* aLinkText);     // for the non-marked links
      
private:
    /**
    * From CAknControl
    */
    IMPORT_C void* ExtensionInterface( TUid aInterface );
private: 
    IMPORT_C virtual void CEikDialog_Reserved_1();
    IMPORT_C virtual void CEikDialog_Reserved_2();  
private: 
    IMPORT_C virtual void CAknDialog_Reserved();
private:
    IMPORT_C virtual void CAknQueryDialog_Reserved();
private:
    TDesC* iMessage;
    TDesC* iHeader;
    CEikImage* iHeaderImage;
    // Moved to iMsgQueryExtension
    // TInt iAnimationId;
    CAknMessageQueryDialogExtension * iMsgQueryExtension;
    

public:

    // @Since 3.0
    // Responds to EAknSoftkeyView and EAknSoftkeyEmpty
    IMPORT_C virtual void ProcessCommandL( TInt aCommandId );

public:

    /**
     * FOLLOWING METHODS ARE DEPRECATED !!!
     * Will be removed, do not use
     */
    // @deprecated
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, TDesC* aHeader); 
    // @deprecated
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, TDesC* aHeader, CEikImage *aHeaderImage); 
    // @deprecated
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, TDesC* aHeader, const TTone aTone); 
    // @deprecated
    IMPORT_C CAknMessageQueryDialog(TDesC* aMessage, TDesC* aHeader, CEikImage *aHeaderImage, const TTone aTone); 
    
    // @deprecated
    IMPORT_C void SetMessageText(TDesC* aMessage); 
    
    // @deprecated
    IMPORT_C void SetMessageText(const TDesC& aMessage);

    // @deprecated
    IMPORT_C void SetHeaderText(TDesC* aHeader);  
    // @deprecated
    IMPORT_C void SetHeaderText(const TDesC& aHeader);  

    // @deprecated
    IMPORT_C CAknMessageQueryDialog();
        
    };


#endif // __AKNMESSAGEQUERYDIALOG_H__

//  End of File  
