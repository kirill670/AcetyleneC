/*
* ============================================================================
*  Name     : CEikFileNameSelector, CEikFileSelectorListBox, CFileSelectorItemDrawer, CEikFileNameEditor, CEikFolderNameSelector, CEikFolderNameEditor, CEikDriveNameSelector from %name%
*  Part of  : CKON
*  Description:
*     File name selector
* ============================================================================
*/
// EIKFSEL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef EIKFSEL_H
#define EIKFSEL_H

// INCLUDES
#include <eikchlst.h>
#include <eikedwin.h>
#include <f32file.h>
#include <eiklbi.h>
#include <eiktxlbx.h>
#include <eikfso.h>

// DATA TYPES


typedef TBuf<KMaxFileName> TEikDriveName;
typedef TBuf<1> TEikDriveLetter;


// FORWARD DECLARATIONS
class CEikDirectoryTreeListBox;


// CLASS DECLARATIONS

/**
*  File Selector. This type of choice list allows a file or set of files from a specified folder to be chosen.
*  Files with the hidden attribute are not displayed. The control may be used in conjunction with folder and drive name selectors.
* 
*
*  Link against eikfile.lib
*/
class CEikFileNameSelector : public CEikChoiceList, public MEikFileSelectionObserver
    {
	public:  // Declarations
	enum TFlags
		{
		EMultiSelectionAllowed	= 0x0002,
		ESpecifiedFolderIsEmpty	= 0x0004
		};



	public:
	// Constructors and destructor
		/**
		* C++ default constructor.Empty default constructor. 
		* The constructor is present only to support virtual function table export.
		* This function should be used as the first stage in two stage construction, followed by a call to ConstructFromResourceL() to initialise the object from a resource file
		*/
		IMPORT_C CEikFileNameSelector();


		/**
		* Destructor.
		*/
		IMPORT_C ~CEikFileNameSelector();


	// New methods
        
		/**
		* Gets the full filename of the currently selected file.
		* @return The current filename. If the selected folder is empty, returns an empty string
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TFileName
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C TFileName FullName() const;

		/**
		* Sets the currently selected file or folder using the filename. 
		* If aFullName specifies a valid filename, that file is selected. If no file is specified, or the specified filename does not exist, the filename selected will be the first filename in the folder.
		* If the specified folder is empty, the function will display an appropriate info message and return.
		* @param aFullName A path indicating a folder, or a file
		*/
		IMPORT_C void SetFullNameL(const TDesC& aFullName);

		/**
		* Gets the filenames of all selected files.
		* The function is used, when multiple selection is allowed, to get an array containing the full paths all currently selected files. If multiple file selection is not allowed, use FullName() instead.
		* @param aFullNames On return, contains a pointer to an array containing the full path and file names of all currently selected files
		*/
		IMPORT_C void GetFullNamesOfSelectedFilesL(CDesCArray* aFullNames) const;

		/**
		* Sets a specified group of files as selected.
		* All filenames contained in the argument will be marked as selected inCEikFileNameSelector's pop-out listbox. If multiple file selection is not allowed, use SetFullNameL() to select a file.
		* @param aFileNames A pointer to the array of filenames which should be marked (and displayed) as selected
		*/
		IMPORT_C void SetSelectedFileNamesL(CDesCArray* aFileNames);

		/**
		* Tests whether multiple file selection is allowed.
		* The function returnsETrue if more than one file at a time can be selected within the control by default multiple selection is not allowed.
		* @return ETrue if multiple selections are allowed; otherwiseEFalse
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TBool
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C TBool MultipleSelectionAllowed() const;

		/**
		* Sets whether the selection of multiple files is allowed.
		* @param aMultipleSelectionAllowed ETrue to allow multiple file selection.EFalse to disable multiple file selection
		*/
		IMPORT_C void SetMultipleSelectionAllowed(TBool aMultipleSelectionAllowed);

		/**
		* Sets a file selection observer. When the file selection changes, the file selection observer updates itself accordingly.
		* @param aObserver Any control which implements the file selection observer interface
		*/
		IMPORT_C void SetFileSelectionObserver(MEikFileSelectionObserver* aObserver);

		/**
		* Validate selector state.
		* This function is used to ensure that a valid file has been specified in the file selector control
		* @return If the selected folder contains no files, or if the selector state is otherwise invalid , this function will leave and display an appropriate info message
		*/
		IMPORT_C void ValidateStateL();

		/**
		* From MEikFileSelectionObserver Handles a change in the full name of a specified file.
		* The framework calls this function on the specified file selection observer, which implements the MEikFileSelectionObserverinterface, when a file name changes.
		* In this case the observer is this class. The function simply sets the full name of the file usingSetFullNameL()
		* @param aFullName The name of the file which changed
		* @param aUpdateEvent The type of event to handle. By default this is an EFullNameChanged event.
		*/
		IMPORT_C virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged);

		/**
		* Second phase construction from a resource.
		* This function initialises the file selector from a FILENAMESELECTOR resource.
		* It reads the maximum number of characters which may be displayed in the filename selector, and uses this value to determine the width of the selector
		* @param aReader A resource file reader.
		*/
		IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* Sets which files to display, based on filename extension. Only filenames with this extension will be displayed in the filename selector and in its pop-out listbox. 
		* This function is intended to be used by applications which restrict selection to files with a particular extension
		* @param aExtension A filename extension, which is copied.
		*/
		IMPORT_C void SetExtensionL(const TDesC& aExtension);

		/**
		* Gets the selector's display filename extension. Only filenames with this extension are displayed in the filename selector and in its pop-out listbox.
		* @return The filename extension
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TDesC*
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		inline const TDesC* Extension() const {return(iExtension);}

		/**
		* Tests whether more than one file is selected. If multiple file selection is not allowed, this function will return false.
		* @return ETrue if multiple files are currently selected;EFalse otherwise
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TBool
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C TBool MultipleFilesSelected() const;

		/**
		* Sets which files to display, based on UID. Only files with this UID will be displayed in the filename selector and in its pop-out listbox.
		* @param aUidType The UID type of the files to display in the file selector
		*/
		IMPORT_C void SetUidType(const TUidType& aUidType);

        
    protected:  // Methods

	// New Methods
        
		/**
		* Set the file flags specified in TFlags
		* @param aMask Mask the file flags with those in TFlags
		*/
		void SetFlags(TInt aMask) {iFileSelectorFlags|=aMask;}

		/**
		* Clear the file flags as specified in TFlags
		* @param aMask ?description
		*/
		void ClearFlags(TInt aMask) {iFileSelectorFlags&=(~aMask);}

		/**
		* Gets the current file selection observer.
		* @return A pointer to the current file selection observer
		*/
		IMPORT_C MEikFileSelectionObserver* FileSelectionObserver() const;

		/**
		* Gets the file selector UID type. This UID is used for filtering the files to be displayed in the selector.
		* @return The current selector UID type
		*/
		IMPORT_C TUidType UidType() const;

		/**
		* Builds the file name array. The function uses the current UID type to filter the drive names in the array.
		* @param aParse Parser to ensure that the file names are within the allowed maximum length
		* @param aFileNames The file name array
		* @return KErrNone if successful, otherwise another of the system-wide error codes
		*/
		IMPORT_C TInt BuildFileNameArrayL(const TParse& aParse, MDesCArray* aFileNames);

		/**
		* Creates an Open file dialog when the selector popout is invoked.
		*/
		IMPORT_C virtual void DoCreatePopoutL();

		/**
		* Destroys the popout and all its associated memory.
		*/
		IMPORT_C virtual void DestroyPopout();

		/**
		* If the selection has changed, the item is redrawn, and the change event is reported to the item's observers.
		*/
		IMPORT_C virtual void HandleInteractionConfirmedL();

		/**
		* Draws the currently selected item
		*/
		IMPORT_C virtual void DrawContent() const;

		/**
		* Notifies the file selection observer that it needs to handle a change in the current file item.
		*/
		IMPORT_C virtual void CurrentItemChangedL();

    private: //Methods

		void TryFindCurrentItemL(const TDesC& aFullName);
		TInt TryBuildFileNameArrayL(const TDesC& aFullName);



	protected:     // Data
		/** Multiple filenames selection array. */
		CDesCArray* iSelectionArray;
		/** Temporary filename array */
		CDesCArray* iTempFileNameArray;
		/** The fullname. */
		TFileName iRef;
		/** The extension. */
		HBufC* iExtension;
		/** The file TFlags. */
		TInt iFileSelectorFlags;

	private:     // Data
		MEikFileSelectionObserver* iFileSelectionObserver;
		TUidType iUidType;
		TInt iSpare;

    };

/**
*  File selector list box.
*This is a specialisation of CEikTextListBox used by objects of type CEikFileNameSelector.
*
*  Link against eikfile.lib
*/
class CEikFileSelectorListBox : public CEikTextListBox
    {


	private:  // Declarations



	public:
	// Constructors and destructor
		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikFileSelectorListBox();

        
    protected:  // Methods

	// New Methods
        
		/**
		* Creates the item drawer for this list box. The item drawer is an instance of a CFileSelectorItemDrawer.
		*/
		IMPORT_C virtual void CreateItemDrawerL();


    };

/**
*  Item drawer for file selector list boxes.
*  This class is used by CListBoxView to draw individual list box items for a CEikFileSelectorListBox
*
*  Link against eikfile.lib
*/
class CFileSelectorItemDrawer : public CTextListItemDrawer
    {

	public:
	// Constructors and destructor
		/**
        * C++ default constructor.
        * @param aTextListBoxModel A pointer to the creating CEikFileSelectorListBox's model
		* @param aFont Font to use
		*/
	IMPORT_C CFileSelectorItemDrawer(MTextListBoxModel* aTextListBoxModel, const CFont* aFont);
	

    protected:  // Methods

	// New Methods
        
		/**
		* Draws the item's text.
		* @param aItemIndex The index of the list item to draw
		* @param aItemTextRect The rectangle to draw in
		* @param aItemIsCurrent Whether the item is current
		* @param aViewIsEmphasized Whether the view is emphasised
		* @param aSelected Whether the item is currently selected
		*/
		IMPORT_C virtual void DrawItemText(TInt aItemIndex, const TRect& aItemTextRect, TBool aItemIsCurrent, TBool aViewIsEmphasized, TBool aSelected) const;  

    };

/**
*  This editor may be used in conjunction with folder and drive name selectors/editors.
*  The control has an associated resource struct FILENAMEEDITOR and control factory identifier EEikCtFileNameEd
*
*  Link against eikfile.lib
*/
class CEikFileNameEditor : public CEikEdwin, public MEikFileSelectionObserver
	{

	public:
	// Constructors and destructor
		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikFileNameEditor();


		/**
		* Destructor.
		*/
		IMPORT_C ~CEikFileNameEditor();


	// New methods
        
		/**
		* Second phase construction from resource file.
		* The width of the filename editor is read from the FILENAMEEDITOR resource, the editor is set to contain a single line and the base class constructor is called (CEikEdwin::BaseConstructL()).
		* @param aReader A resource file reader
		*/
		IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* Gets and validates the full name of a file, given the full path or filename.
		* Will leave if the following are not true:-A file is specified,and may not be of zero length.
		* The filename specified is syntactically correct
		* @param aFileName The full path of a file, or just the filename. On return, contains the fully parsed file specification
		*/
		IMPORT_C void GetFullNameL(TFileName& aFileName);

		/**
		* Sets the named file to be the current file.
		* @param aFullName Specifies either the full path, or just the filename, of the file which is to become the current file
		*/
		IMPORT_C void SetFullNameL(const TDesC& aFullName);

		/**
		* From MEikFileSelectionObserver Handles a change in the full name of a specified file.
		* The framework calls this function on the specified file selection observer when a file name changes. In this case the observer is this class. The function simply sets the full name of the file using SetFullNameL()
		* @param aFullName The name of the file which changed
		* @param aUpdateEvent The type of event to handle. By default this is an EFullNameChanged event
		*/
		IMPORT_C virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged);

		/**
		* Sets the editor to automatically append filename extensions. By default, file extensions are not automatically appended.
		* The extension is appended only if the file in the editor has no extension. The extension which is appended is the extension of the previously selected filename
		* @param aAppendExtension ETrue to set append extension, EFalse to cancel append extension
		*/
		IMPORT_C void SetAppendExtension(TBool aAppendExtension);


    private: //Methods


		IMPORT_C void Dummy1();
		IMPORT_C void Dummy2();
		IMPORT_C void Dummy3();




	protected:     // Data
		/** The filename used. */
		TFileName iRef;
		/** The extension . */
		TBool iAppendExtension;

	private:     // Data
		TInt iSpare;

    };

/**
*  Folder name selector.
*  This is a choice list control which allows users to select a folder beneath a specified root. It may be used in conjunction with file and drive name selectors/editors
*
*  Link against eikfile.lib
*/
class CEikFolderNameSelector : public CEikChoiceList, public MEikFileSelectionObserver
    {
	public:  // Declarations
	enum TFlags
		{
		EFullNameUpdate	= 0x0001,
		EShowSystem		= 0x0002
		};

	public:
	// Constructors and destructor
		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikFolderNameSelector();


		/**
		* Destructor.
		*/
		IMPORT_C ~CEikFolderNameSelector();


	// New methods
        
		/**
		* Gets the full name of the currently selected folder. The full name includes the path to the folder and the file name.
		* @return The full name of the currently selected folder
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TFileName
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C TFileName FullName() const;

		/**
		* Sets the current folder to be the named folder. 
		* The function is called when the user confirms the selection of a new folder name, or, if the folder selector is an observer of the drive selector, when the drive letter is changed in the drive selector.
		* If the folder specified does not exist, a panic will occur
		* @param aFullName The path containing the name of the folder that is to be the new current folder
		*/
		IMPORT_C void SetFullNameL(const TDesC& aFullName);

		/**
		* Sets the folder name selector's root folder.
		* This folder will be set to be at the top of the folder hierarchy displayed in the folder name selector.
		* Normally, you should not need to call this function. By default, the root folder is set to be the top level folder on the current drive
		* @param aRoot A root folder
		*/
		IMPORT_C void SetRootL(const TDesC& aRoot);

		/**
		* Creates the list of folders to display in the folder name selector.
		* All folders contained in the hierarchy below the root folder are added to the list.
		* This function is called whenever the root folder changes, for example though using SetRootL()
		*/
		IMPORT_C void CreateFlattenedHierarchyL();

		/**
		* Sets the folder selector's file selection observer. This will normally be a file selection editor or selector.
		* When the folder selection changes, the file selection observer updates itself accordingly.
		* @param aObserver A control which implements the file selection observer interface
		*/
		IMPORT_C void SetFileSelectionObserver(MEikFileSelectionObserver* aObserver);

		/**
		* From MEikFileSelectionObserver Handles a change in the full name of a specified folder. See MEikFileSelectionObserver::HandleFullNameChangedEventL().
		* The framework calls this function on the specified file selection observer,
		* which implements the MEikFileSelectionObserver interface, when a file name changes. In this case the observer is this class.
		* The function simply sets the full name of the file using SetFullNameL()
		* @param aFullName The name of the file which changed
		* @param aUpdateEvent The type of event to handle. By default this is an EFullNameChanged event
		*/
		IMPORT_C virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged);

		/**
		* Gets a pointer to the folder selector's pop-out list box.
		* @return A pointer to the folder selector's pop-out list box
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> CEikDirectoryTreeListBox*
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C CEikDirectoryTreeListBox* PopoutDirTreeListBox() const;

		/**
		* Sets whether the system folder and its contents should be shown. This setting applies to the folder selector and to its pop-out list box.
		* @param aShowSystem ETrue to show the system folder, EFalse to hide it
		*/
		IMPORT_C void SetShowSystem(TBool aShowSystem);

	public: // framework
		/**
		* From CEikChoiceList Second stage construction from a resource.
		* This function reads the maximum width of the folder name selector from a FOLDERNAMESELECTOR resource, and uses it to initialise the selector
		* @param aReader A resource file reader
		*/
		IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

        
protected: // framework

        
		/**
		* Sets the item in the list which matches an entered character as current.
		* @param aCode The key code of the entered character
		*/
		IMPORT_C virtual void MatchTypedChar(TUint aCode);

		/**
		* If the selection has changed, the item is redrawn, and the change event is reported to the item's observers
		*/
		IMPORT_C virtual void HandleInteractionConfirmedL();

		/**
		* Notifies the folder name selection observer that it needs to handle a change in the current item.
		*/
		IMPORT_C virtual void CurrentItemChangedL();

		/**
		* Draws the currently selected item.
		*/
		IMPORT_C virtual void DrawContent() const;

		/**
		* Creates a pop out directory tree list box.
		*/
		IMPORT_C virtual void CreateListBoxL();

		/**
		* Completes construction of the popout directory tree list box.
		*/
		IMPORT_C virtual void InitializeListBoxL();

		/**
		* Deprecated. Sets the currently selected item in the popout listbox and activates it
		*/
		IMPORT_C virtual void ActivateListBoxL();

		/**
		* Deprecated.Calculates and sets the size of the popout listbox
		*/
		IMPORT_C virtual void SetListBoxExtentL();

		/**
		* Creates a browse dialog popout.
		*/
		IMPORT_C virtual void DoCreatePopoutL();

		/**
		* Destroys the popout and all its associated memory.
		*/
		IMPORT_C virtual void DestroyPopout();

protected:  // new functions
		/**
		* Expand the folder.
		* @param aPath The path of the folder to expa
		* @param aPositionToInsertSubFolders The position at which to insert subfolders
		*/
		IMPORT_C void ExpandFolderL(TDes* aPath, TInt aPositionToInsertSubFolders);

		/**
		* Fully expand the folder.
		* @param aIndexOfFolderToFullyExpand The index of the folder to expand
		* @param aAutoExpandAllFolders ETrue to show the directories contained in the specified folder's subdirectories
		*/
		IMPORT_C void FullyExpandFolderL(TInt aIndexOfFolderToFullyExpand, TBool aAutoExpandAllFolders);


    private: //Methods

		void SetRootFromReferenceL();




	protected:     // Data
		/** Any control which implements the file selection observer interface. */
		MEikFileSelectionObserver* iFileSelectionObserver;
		/** The root filename, as specified in SetRoot*/
		TFileName iRoot;
		/** The filename. */
		TFileName iRef;
		/** The current path. */
		TFileName iCurrentPath;
		/** The folder flags as defined in TFlags. */
		TInt iFolderSelectorFlags;

	private:     // Data
		TAny* iReserved;

    };

/**
*  Folder name editor. It is usually used in conjunction with a drive name selector.
*
*  Link against eikfile.lib 
*/
class CEikFolderNameEditor : public CEikEdwin, public MEikFileSelectionObserver
    {

	public:
	// Constructors and destructor
		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikFolderNameEditor();


		/**
		* Destructor.
		*/
		IMPORT_C ~CEikFolderNameEditor();


	// New methods
        
		/**
		* Gets the full name of the current folder. 
		* It does not validate the folder name, so call ValidateStateL() before calling this function.
		* @return The current folder name. Returned with a trailing backslash
		* <BR><B>Name of return value:</B> (Write name here)
		* <BR><B>Type of return value:</B> TFileName
		* <BR><B>Range of return value:</B> (Write range here, e.g. Valid range for Integers, Strings, Object References etc.)
		* <BR><B>Contents of return value:</B> (Write content here, e.g. Fields in structures)
		*/
		IMPORT_C TFileName FullName() const;

		/**
		* Sets the named folder to be the current folder.
		* @param aFullName Either the full path or just the folder name of the folder which is to be set as the current folder
		*/
		IMPORT_C void SetFullNameL(const TDesC& aFullName);

		/**
		* Validates the folder name of the current folder.
		* If the folder name isn't set (using SetFullNameL() or the folder name isn't syntactically correct the function will leave
		*/
		IMPORT_C void ValidateStateL();

		/**
		* Second phase construction from resource file.
		* The function reads the width of the folder name editor from a FOLDERNAMEEDITOR resource, sets the editor to contain a single line, and calls CEikEdwin::BaseConstructL()
		* CEikEdwin::ConstructL() may be used instead to complete second phase construction without a resource file
		* @param aReader A resource file reader
		*/
		IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* From MEikFileSelectionObserver Handles a change in the full name of a specified folder. See MEikFileSelectionObserver::HandleFullNameChangedEventL().
		* The framework calls this function on the specified file selection observer when a file name changes. In this case the observer is this class.
		* The function simply sets the full name of the file using SetFullNameL()
		* @param aFullName The name of the file which changed
		* @param aUpdateEvent TThe type of event to handle. By default this is an EFullNameChanged event
		*/
		IMPORT_C virtual void HandleFullNameChangedEventL(const TFileName& aFullName, TUpdateEvent aUpdateEvent = EFullNameChanged);

        
    protected:  // Methods

    private: //Methods




	protected:     // Data
		/** The fullname */
		TFileName iRef;

	private:     // Data
		TInt iSpare;

    };

/**
*  Drive name selector.
*  This class defines a choice list control from which a user 
*  can select one of the currently available drives. This control may be used in conjunction with folder and filename selectors/editors.
*
*  Link against eikfile.lib 
*/
class CEikDriveNameSelector : public CEikChoiceList
    {
	public:  // Declarations
	enum TFlags {EHideROM = 0x0001, EAllowCorruptDisk = 0x0002, EShowFullName = 0x0004};


	public:
	// Constructors and destructor
		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikDriveNameSelector();
		/**
		* C++ constructor with drive selector flags.
		* The selector flags specify whether the ROM drive and drives containing corrupt media should be displayed or hidden.
		* This function should be used as the first stage in two stage construction, followed by a call to ConstructFromResourceL() to initialise the object from a resource file
		* @param aFlags Flags setting the drive visibility. For details, see the TFlags enum
		*/
		IMPORT_C CEikDriveNameSelector(TInt aFlags);

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikDriveNameSelector();


	// New methods

		/**
		* Gets the full path of the currently selected file.
		* @return The path of the currently selected file
		*/
		IMPORT_C TFileName FullName() const;

		/**
		* Sets the full path of the file to mark as currently selected.
		* If the drive selector has a file selection observer, the observer's HandleFullNameChangedEventL() function is called.
		* @param aFullName The path of the selected file
		*/
		IMPORT_C void SetFullNameL(const TDesC& aFullName);

		/**
		* Sets the drive selector's file selection observer.
		* When the drive selection changes, the file selection observer updates itself accordingly.
		* @param aObserver A control which implements the file selection observer interface. This must be a CEikFolderNameSelector
		*/
		IMPORT_C void SetFileSelectionObserver(MEikFileSelectionObserver* aObserver);

		/**
		* Sets the selector to show drives with corrupt media.
		* @param aAllowCorruptDisk ETrue to show drives containing corrupt media, EFalse to hide such drives
		*/
		IMPORT_C void AllowCorruptDisk(TBool aAllowCorruptDisk);

		/**
		* Sets the selector to show the ROM drive. By default, the ROM drive is not displayed.
		* @param aShowRom ETrue to show the ROM drive. EFalse to hide it
		*/
		IMPORT_C void ShowRom(TBool aShowRom);

		/**
		* Tests whether the drive selector has been set up to show the full drive name.
		* @param aFullName ETrue if the drive selector has been set up to show the full drive name. EFalse if it has been set up to display a single letter
		*/
		IMPORT_C void ShowFullName(TBool aFullName);

	public: // framework
		/**
		* Second-phase construction from a resource. 
		* In fact, the DRIVENAMESELECTOR resource is empty, and the function is used to initialise the CEikDriveNameSelector.
		* The width of the selector is set to contain a single character or to display 15 characters if the full name display flag is set, 
		* the list of available drives is initialised, and the selected drive letter is initialised to c:.
		* @param aReader A resource file reader. This is not actually used the DRIVENAMESELECTOR resource is empty
		*/
		IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

    protected:  // Methods

	// New Methods
        
		/**
		* Builds the drive name array. The drive name array contains the names of all the drives on the file system.
		* This function is called by the framework when the drive name selector is constructed
		*/
		IMPORT_C void BuildDriveNameArrayL();

	protected: // framework
		/**
		* Notifies the file selection observer that it needs to handle a change in the current file item.
		*/
		IMPORT_C virtual void CurrentItemChangedL();

    private: //Methods


		TEikDriveLetter DriveNameFromFullName(const TDesC& aFullName) const;
		void UpdateDiskListL(const RFs& aFs,CDesCArray& aArray,TBool aIncludeRom,TDriveNumber aDriveNumber);




	protected:     // Data
		/** The file selection observer */
		MEikFileSelectionObserver* iFileSelectionObserver;
		/** The filename. */
		TFileName iRef;
		/** The frive selector flags as defined on TFlags */
		TInt iDriveSelectorFlags;

	private:     // Data
		CDesCArray* iDriveLetterArray;

    };


#endif      // EIKFSEL_H   
            
// End of File
