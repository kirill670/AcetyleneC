/*
* ==============================================================================
*  Name        : cknlocationcontrol.h
*  Part of     : CKon
*  Interface   : CCknLocationControl
*  Description : Class that contributes to the Folder Dialog widget
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


#ifndef CKNLOCATIONCONTROL_H
#define CKNLOCATIONCONTROL_H

// INCLUDES
#include <CknIconWithText.h>

/**
 * This class is used to display an icon and folder name.
 * If the control is selected, it runs a change folder dialog
 * allowing the user to change the folder referenced by the control
 * @since Series90 1.0
 * @Lib CKNCTL.lib
 */

class CCknLocationControl : public CCknIconWithText
	{
	public:

	/**
	 * Returns a pointer to a new CCknLocationControl
	 *
	 * @param     "TInt aBitmapIndex"
	 *            Index used to determine which icon to display in the control
	 * @param     "TUid aMbmUid"
	 *            The MbmUid used to locate the icon bitmap
	 * @param     "const TPath& aPath"
	 *            Reference to the full path of the current location
	 * @param     "TInt aMaximumWidth"
	 *            The maximum width in pixels for the control
	 * @param     "TBool aAllowNewFolder"
	 *			  If ETrue any Change Folder dialog launched from this control
	 *            is allowed to create new folders. If EFalse then no new folders
	 *            can be created.
	 *
	 * @returns   "CCknLocationControl*"
	 *            Pointer to the newly instantiated object
	 */
	IMPORT_C static CCknLocationControl* NewL(TInt aBitmapIndex,
											  TUid aMbmUid,
								              const TPath& aPath, 
								              TInt aMaximumWidth,
											  TBool aAllowNewFolder=ETrue);
	/**
	 * Returns a pointer to a new CCknLocationControl
	 * 
	 * @returns   "CCknLocationControl*"
	 *            Pointer to the newly instantiated object
	 */

	IMPORT_C static CCknLocationControl* NewL();


	/**
	* Returns a reference to the control's iFolderPath
	* @return pointer to a full folder path
	* <BR><B>Type of return value:</B> TPtrC 
	* <BR><B>Contents of return value:</B> pointer to a full folder path
	*/
	IMPORT_C TPtrC FolderPath();


	/**
	* Method to set the control's folder path, changes the text displayed by the control
	* @param aFolderPath - reference to a text string containing a full folder path
	* @return void
	*/
	IMPORT_C void SetFolderPathL(const TPath& aFolderPath);

	/**
	* Sets the location control to display a dummy text if the path is empty
	* @param aTextRid - the id of the text resource to display
	*/
	IMPORT_C void SetDummyTextL(TInt aTextRid);

	/**
	 * Method to set the icon and text displayed by the control
	 *
	 * @param     "TInt aBitmapIndex"
	 *            Index used to determine which icon to display in the control
	 * @param     "TUid aMbmUid"
	 *            The MbmUid used to locate the icon bitmap
	 * @param     "const TPath& aPath"
	 *            Reference to a full folder path, the folder name is displayed
	 *			  by the control
	 * @return void
	 */
	IMPORT_C void AddContentsL(TInt aBitmapIndex, 
					  TUid aMbmUid,
					  const TPath& aPath);


	/**
	* Method to set the iAllowNewFolder data member
	* @param aAllow - If ETrue, a change folder dialog launched from the location control
	*					 will have a 'New Folder' button. If EFalse it will not.
	* @return void
	*/
	IMPORT_C void AllowNewFolder(TBool aAllow);
	/**
	* Function that runs the Change Folder dialog and resets iFolderPath if necessary
	* Updates the control text and reports state changed to its iObserver
	*/
	IMPORT_C void RunChangeFolderDialogL();

	public:
		~CCknLocationControl();

//from CoeControl

	/**
	* See CCoeControl
	*/
	void ConstructFromResourceL(TResourceReader& aReader);

	private:

	/**
	* Constructor
	*/
	void ConstructL(TInt aBitmapIndex,
					TUid aMbmUid,
					const TPath& aPath, 
					TInt aMaximumWidth,
					TBool aAllowNewFolder);

	//from CoeControl
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

	private:

	enum TLocationControlInternalFlags
		{
		ELocLeftDownInViewRect =0x00000001
		};

	private:
	/**
	* The full path of the folder referred to by the control
	*/
	TPath iFolderPath;

	/**
	* A text string displayed if the path is empty
	*/
	HBufC* iDummyText;

	/**
	* Determines whether new folder creation is allowed in Change Folder
	* dialogs launched by the control
	*/
	TBool iAllowNewFolder;

	TUint iInternalFlags;
	};


#endif	// CKNLOCATIONCONTROL_H

// End of File
