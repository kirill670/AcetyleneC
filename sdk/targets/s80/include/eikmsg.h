/*
* ==============================================================================
*  Name        : eikmsg.h
*  Part of     : UIKON
*  Interface   : Information Base API
*  Description : Message window classes.
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


#ifndef EIKMSG_H
#define EIKMSG_H

// INCLUDES
#include <clock.h>
#include <gulalign.h>

// FORWARD DECLARATIONS
class CCoeControl;
class CEikonEnv;
class RWindowGroup;
class CEikResourceChange;


class CEikMsgWin : public CBase
/** Base class providing functions to construct and display an information message. 

@publishedAll
@released */
	{
	protected:

/**
 *
 * Protected constructor.
 *
 * @param     " CEikonEnv& aEikonEnv "
 *            The Uikon environment for which the information
 *            message is constructed.
 */
		IMPORT_C CEikMsgWin(CEikonEnv& aEikonEnv);
	public:

/**
 *
 * Completes construction.
 *
 * @param     " RWindowGroup& aWindowGroup"
 *            The window group for which the information message is
 *            constructed.
 */
		IMPORT_C void ConstructL(RWindowGroup& aWindowGroup);

		/**
		* Destructor.
		*/
		IMPORT_C virtual ~CEikMsgWin();

/**
 *
 * Displays the message window with the specified text and alignment.
 *
 * @param     " const TDesC& aText"
 *            The text to display in the message.
 * @param     " TGulAlignment aCorner"
 *            The position in which the message window will appear.
 *            There are 9 options for this, each square of a 3 by 3
 *            matrix on the screen.
 */
		IMPORT_C void StartDisplay(const TDesC& aText, TGulAlignment aCorner);

/**
 * Stops displaying the message window.
 */
		IMPORT_C void CancelDisplay();

/**
 * Sets the MsgWin bitmap to the ID supplied.
 *
 * @param aBitmapCategory - The bitmap category to use e.g. KUidSkinGeneralBitmaps.
 * @param aBitmapId - The TMbmSkingeneral bitmap ID.
 */
		IMPORT_C void SetBitmapId(const TUid aBitmapCategory, TInt aBitmapId);
	protected:
		TDes& PrepareDisplay(TDes& aText, TGulAlignment aCorner);
	private:
		virtual void DoStartDisplay(const TDesC& aText)=0;
	protected:

/**
*  Data structure class for storing bitmap and resource data.
*
*  @since Series90 1.0
*/
	class CMsgWinExtraData : public CBase
		{
	public:
		TUid iBitmapCategory;
		TInt iBitmapId;
		CEikResourceChange* iResourceChange;
		};
	protected:
		CEikonEnv& iEikonEnv_; // the underscore is to prevent a name clash with the iEikonEnv #define
		CCoeControl* iDummy;
		RBlankWindow* iBlankWindow;
		RMessageWindow* iMessageWindow;
		CMsgWinExtraData *iExtra;
	};

/**
@publishedAll
@released
*/
const TInt KEikInfoMsgMaxLen=RMessageWindow::EMaxTextLength;

/**
 * Specifies the maximum length of the message buffer.
 */
typedef TBuf<KEikInfoMsgMaxLen> TEikInfoMsgBuf;


class CEikInfoMsgWin : public CEikMsgWin
/** Enables construction of an information message window. 

@publishedAll 
@released */
	{
	public:

/**
 *
 * Constructs an information message for the specified Uikon environment.
 *
 * @param     " CEikonEnv& aEikonEnv"
 *            The Uikon environment for which the information
 *            message is constructed.
 */
		IMPORT_C CEikInfoMsgWin(CEikonEnv& aEikonEnv);

/**
 *
 * Displays the information message window for a specified time period
 * with the specified text and alignment.
 *
 * @param     "const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aDuration"
 *            The text, alignment and specified time period for the
 *            information message.
 *
 * @since 6.1
 */
		IMPORT_C void StartDisplaySpecifyingDuration(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aDuration);
	private:
		virtual void DoStartDisplay(const TDesC& aText);
	};

//

/**
@publishedAll
@released
*/
const TInt KEikBusyMsgMaxLen=RMessageWindow::EMaxTextLength;

/**
@publishedAll
@released
*/
		typedef TBuf<KEikBusyMsgMaxLen> TEikBusyMsgBuf;

/**
 *
 * Enables construction of a 'busy message' window.
 * @since Series90 1.0
 * @lib "eikcore.lib"
 */
class CEikBusyMsgWin : public CEikMsgWin
	{
	public:

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikBusyMsgWin(CEikonEnv& aEikonEnv);
		
		/**
		*
		* Displays the busy message window for a specified time period
		* with the specified text and alignment.
		*
		* @param aText The message to display.
		* @param aCorner The position in which the message window will appear. There are 9 
		* options for this, each square of a 3 by 3 matrix on the screen.
		* @param aInitialDelay The delay before showing the busy message.
		* <BR><B>Type of return value:</B> void
		*/
		IMPORT_C void StartDisplaySpecifyingInitialDelay(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aInitialDelay);
	private:
		virtual void DoStartDisplay(const TDesC& aText);
	private:
		TTimeIntervalMicroSeconds32 iInitialDelay;
	};


#endif	// EIKMSG_H

// End of File
