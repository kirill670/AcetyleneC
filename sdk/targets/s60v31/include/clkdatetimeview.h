/*
* ==============================================================================
*  Name        : ClkDateTimeView.h
*  Part of     : ClkDateTimeView / ClkDateTimeView.dll
*  Interface   : 
*  Description : This class implements the function of
*                common "Date & Time" settings view.
*  Version     : 
*
*  Copyright © 2002 Nokia Corporation.
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

#ifndef CLKDATETIMEVIEW_H
#define CLKDATETIMEVIEW_H

//  INCLUDES
#include <coecntrl.h>
#include <aknview.h>
#include <aknlists.h>
#include <tzlocalizationdatatypes.h>

#include <ClkMdlObserver.h>



// CONSTANTS
const TInt KMaxItemLength=128;
const TInt KMaxValueLength=64;
const TUid KMainViewId = {1};
const TUid KClkDateTimeViewId = {10};
const TInt KNotiferPriority = CActive::EPriorityIdle;

_LIT(KRESOURCE, "Z:\\Resource\\Apps\\clockapp.rsc");
_LIT(KHardCodedAlarmTone, "z:\\Resource\\Sounds\\Simple\\clock.rng");

// DATA TYPES
class TClkDateTimeInfo
    {
    public:
        TTime           iTime;
        TDateFormat     iDateFormat;
        TInt            iDateSepar;
        TTimeFormat     iTimeFormat;
        TInt            iTimeSepar;
        TBool           iNITZ;
        TClockFormat    iClockFormat;
		TTimeIntervalSeconds   iGMTOffset;
    };

enum TClkDateTimeViewPanic
    {
    EClkDateTimeViewBadLocale,
    EClkDateTimeViewBadCommandId,
    EClkDateTimeViewBadItemIndex
    };

#ifdef _DEBUG
// FUNCTION PROTOTYPES
GLREF_C void Panic(TClkDateTimeViewPanic aPanic);
// _DEBUG
#endif

//  FORWARD DECLARATION
class CClkDateTimeViewContainer;
class CClkNitzModel;
class CClkIntermediateObserver;
class CEnvironmentChangeNotifier;
class CDRMHelper;
class CClkDateTimeViewExtension;
class RConeResourceLoader;
// CLASS DECLARATION

/**
*  Common "Date & Time" settings view.
*
*/

class CClkDateTimeView : public CAknView,  
    					 public MEikListBoxObserver, 
    					 public MClkModelObserver
    {
    public:  // Constructors and destructor

        /**
        * Two-phased constructor.
        * @param aClockUse  ETrue means Clock application uses this.
        *                   EFalse means any application
        *                   except Clock uses this.
        * @param aViewId    Id of a view which is changed to,
        *                   when Back softkey is pressed.
        *                   It is ignored when aClockUse is ETrue.
        * @return CClkDateTimeView*
        */
        IMPORT_C static CClkDateTimeView*
            NewLC(TUid aViewId, TBool aClockUse = EFalse);

        /**
        * Destructor.
        */
        IMPORT_C ~CClkDateTimeView();

    public: // Functions from base classes

        /**
        * From CAknView Returns this view Id.
        */
        TUid Id() const;

        /**
        * From MEikCommandObserver Handles commands.
        */
        void HandleCommandL(TInt aCommandId);

        /**
        * From MClkModelObserver
        * Called when the model is changed.
        * @param aNotification The cause of the notification.
        */
        void HandleUpdateL(TInt aNotification);

    public: // New functions

        /**
        * Moves the current item to the top of the list items.
        */
        IMPORT_C void InitCurrentItem();

        /**
        * Handle options changed by system
        * @param aChange It indicates a cause of the change.
        */
        void HandleSettingsChangeL(const TInt aChange);

        /**
        * Increments the current list item to handle the task swapping event.
        */
        void IncCurrentItem();

        /**
        * Decrements the current list item to handle the task swapping event.
        */
        void DecCurrentItem();

        /**
        * Gets a flag meaning that Clock application is using.
        * @return ETrue means the ClockApp uses this object.
        *         EFalse means the ClockApp doesn't use this object.
        */
        TBool IsClockInUse() const;

        /**
        * Gets a previous view id.
        * @return TVwsViewId
        */
        TVwsViewId PrevViewId() const;

        /**
        * Handles a softkey event "Change".
        * @param aItemId The current item id of the settings list box.
        */
        void HandleChangeCmdL(const TInt aItemId);

        /**
        * From MEikMenuObserver
        */
        void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

    protected:  // Functions from base classes

        /**
        * From CAknView Activates this view.
        */
        void DoActivateL(const TVwsViewId& aPrevViewId,
            TUid aCustomMessageId, const TDesC8& aCustomMessage);

        /**
        * From CAknView Deactivates this view.
        */
        void DoDeactivate();


        /**
        * From MEikListBoxObserver Handles an event happend in aListBox.
        */
        void HandleListBoxEventL(
            CEikListBox* aListBox, TListBoxEvent aEventType);


	protected:
        /**
        * @param aClockUse  ETrue means Clock application uses.
        *                   EFalse means any application except Clock uses.
        * @param aViewId    Id of a view which is changed to,
        *                   when Back softkey is pressed.
        *                   It is ignored when aClockUse is ETrue.
        */
        void ConstructL(TUid aViewId, TBool aClockUse);

    private:    // New functions

		/**
		Returns the index of the country 
		in the list box for a given group id.
		*/
    	TInt IndexOfCountry(TInt aGroupId, CTzLocalizedCityGroupArray* aCountryList);

        /**
        * Reads the resources for settings list.
        * @param aResourceID Resource id for settings list.
        */
        void GetResourcesL();

        /**
        * Makes the list box items.
        */
        void PopulateListBoxL();

        /**
        * Updates the list box items.
        * @param aItemId An item id of the listbox.
        */
        void UpdateListBoxL(TInt aItemId);

        /**
        * Updates all items.
        */
        void UpdateAllL();


        /**
        * Updates the date and the time.
        * @param aTime The new time.
        * @return error code
        */
        TInt SetDateTimeL(TTime& aTime);

        /**
        * Updates the Workdays values.
        */
		void SetWorkDays();
        
        /**
        * Updates the date format.
        */
        void SetDateFormat();

        /**
        * Updates the date separator.
        */
        void SetDateSeparator();

        /**
        * Updates the time format.
        */
        void SetTimeFormat();

        /**
        * Updates the time format.
        */
        void SetTimeSeparator();

        /**
        * Updates the clock type.
        */
        void SetClockType();

        /**
        * Gets the NITZ state.
        */
        void NitzL();

        /**
        * Updates the NITZ state.
        */
        void SetNITZL();

        /**
        * Gets the device's setting values.
        */
        void SettingsL();

        /**
        * Makes the date item in the list box.
        */
        void MakeDateItemL();
        
        /**
        * Makes the time zone item in the list box.
        */
		void MakeZoneItemL();

        /**
        * Makes the date format item in the list box.
        */
        void MakeDateFormatItem();

        /**
        * Makes the date separator item in the list box.
        */
        void MakeDateSeparItem();

        /**
        * Makes the time item in the list box.
        */
        void MakeTimeItemL();

        /**
        * Makes the time format item in the list box.
        */
        void MakeTimeFormatItem();

        /**
        * Makes the time separator item in the list box.
        */
        void MakeTimeSeparItem();

        /**
        * Makes the NITZ item in the list box.
        */
        void MakeNITZItem();
        
        /**
        * Makes the Workdays item in the list box.
        */
		void MakeWorkDaysItem();
		
        /**
        * Makes the clock control type item in the list box.
        */
        void MakeClockTypeItem();

        /**
        * Makes the clock alarm tone item in the list box.
        */
        void MakeClockAlarmToneItem();


		/**
        * Makes the clock snooze time item in the list box.
        */

		void MakeClockSnoozeTimeItem();

        /**
        * Deletes the buffers used for the list box resources.
        */
        void DeleteResourceBuf();

        /**
        * Gets the date format of the device.
        */
        TInt DateFmt();

        /**
        * Handles a back softkey command.
        */
        void HandleBackCmdL();

        /**
        * Handles a Workdays command.
        */        
		void HandleWorkDaysCmdL();
        
        /**
        * Handles a date command.
        */
        void HandleDateCmdL();

        /**
        * Handles a date format command.
        */
        void HandleDateFrmtCmdL();

        /**
        * Handles a date separator command.
        */
        void HandleDateSeparCmdL();

        /**
        * Handles a time command.
        */
        void HandleTimeCmdL();
        
        /**
        * Handles a zone command.
        */
        void HandleZoneCmdL();

        /**
        * Handles a time format command.
        */
        void HandleTimeFrmtCmdL();

        /**
        * Handles a time separator command.
        */
        void HandleTimeSeparCmdL();

        /**
        * Handles a NITZ command.
        * @param aDraw ETrue means this redraws the NITZ item.
        *              EFalse means this doesn't redraw the NITZ item.
        */
        void HandleNitzCmdL(TBool aDraw = ETrue);

        /**
        * Handles a clock type command.
        */
        void HandleClockTypeCmdL();

        /**
        * opens file list resource reader.
        */
		void OpenFileListResourceLC( RConeResourceLoader& aResourceLoader );
        /**
        * Handles a clock alarm tone command.
        */
        void HandleClockAlarmToneCmdL();


        /**
        /**
        * Handles a clock alarm snooze command.
        */
		void HandleClockSnoozeTimeCmdL();


        /**
        * Shows a popup setting page.
        * @param aItemArray containing setting items.
        * @param aIndex an index of initial item.
        * @param aLabel a text of label.
        * @return an index of selected item.
        */
        TInt QueryPopupSettingPageL(
            CDesCArray& aItemArray, TInt aIndex, const TDesC& aLabel);

        /**
        * Callback when enviroment changed.
        * @param aThis This class.
        * @return TInt ETRUE or EFALSE
        */
        static TInt DoNotiferCallbackL(TAny* aThis);

        /**
        * Shows an confirmation note of nits setting off.
        */
        void ShowNitzSetOffConfNoteL();

        /**
        * Callback every interval time.
        * @param aThis This class.
        * @return TInt ETRUE or EFALSE
        */
        static TInt TimerCallback(TAny* aThis);

        /**
        * Deletes ProfileApp's resource file.
        * @param aThis This class.
        */
        static void DeleteResFile(TAny* aThis);

       /**
        * Removes registration of protected (automated) content.
        * This means that unless some other application uses same
        * media, no expiration notes are shown
        * @param aFile Full filename of the media.
        */
		void UnRegisterSound(const TFileName& aFile);

       
       
        void AppendToItem(const TDesC& aDes);
        void InsertToItem(const TDesC& aDes);

		
		/**
		*	Unregister and reregister the phone to network when NITZ turned ON.
		*/
		void UnregisterAndReregisterL();
		
		/**
		*	Make the GMT String to be displayed in DateTimeView.
		*/
		void MakeGmtOffsetStringL(TInt aUtcOffset);
	
		/**
		*	Displays the list of zones and selects.
		*/	
		void SelectZoneL(TBool nitz);

		/**
		*	Constructs the GMT string to be displayed in
		*	DateTimeView list.
		*/	
		void ConstructGmtStringL();

		/**
		*	Tells whether DST is in effect for the time zone.
		*/	
		TBool IsDstOnL(TInt aTimeZoneId);

		/**
		*	Shows information note if alarms exists
		*/	
		void ShowAlarmExistNote();
public:		
		/**
        * When an alarm tone / snooze time is changed 
        * through general settings, it gets updated
        * in the clock settings
        */
	
		void UpdateDTView(TUint32 aId, const TDesC16& aNewValue);
		
    private:    // Data
        CClkDateTimeViewContainer*  iContainer; // Owned
        MDesCArray*                 iItemList;
        CDesCArray*                 iItemArray;
        TClkDateTimeInfo            iDateTimeInfo;
        TVwsViewId                  iPrevViewId;
        TUid                        iViewId;
        TInt                        iOffset;
        CDesCArrayFlat*             iDateFrmtItemLists;  // Owned
        CDesCArrayFlat*             iDateSeparItemLists;  // Owned
        CDesCArrayFlat*             iTimeSeparItemLists;  // Owned
        CEnvironmentChangeNotifier* iNotifier;      // Owned
        CClkNitzModel*              iNitzModel;     // Owned
        CClkIntermediateObserver*   iModelObserver; // Owned
        CPeriodic*                  iTimer; // Owned
        // used to control key event
        TBool                       iIsClockInUse;
        TInt                        iCurrentItem;
        TInt                        iTopItem;
        TInt                        iNumOfItemsInView;

        // used to control menu event
        TBool                       iMenuChange;

        // Used in setting list item.
        HBufC*                      iItem; // Owned
        TBuf<KMaxValueLength>       iValue;

        // From resource. All owned.
        HBufC*      iDate;
        HBufC*      iDateFrmt;
        HBufC*      iDateSepar;
        HBufC*      iTime;
        HBufC*		iZone;
        HBufC*      iTimeFrmt;
        HBufC*      iTimeSepar;
        HBufC*      iNITZ;
        HBufC*      iClockType;
        HBufC*      iAbbrev24H;
        HBufC*      iAbbrev12H;
        HBufC*		iLocalTime;
        HBufC*      iNitzOn;
        HBufC*      iNitzOff;
        HBufC*      iAnalog;
        HBufC*      iDigital;
        HBufC*      iTone;
        HBufC*      iTimeZone;
		HBufC*		iDST;
        HBufC*      iDstOn;
        HBufC*      iDstOff;
        HBufC*      iGMTString;       
		HBufC* 		iGMTPrefixTxt;
		HBufC*		iZoneString;
        
		HBufC*		iSoundOffTxt;		// Owned
		HBufC*		iDefaultToneTxt;	// Owned
		HBufC*		iToneListHeader;	// Owned
        CClkDateTimeViewExtension*  iExtension;
        TInt        iResourceOffset;    // for working
		TInt		iListItemCount;		// How many items in the list
        TFileName   iAlarmToneName;     // Tone name
		TFileName	iDefaultAlarmToneName; // Default alarm tone
        CDRMHelper* iDRMHelper; // owned
        //Not used any more but kept to preserve BC
        TAny* iDummy; 
    };
// CLKDATETIMEVIEW_H
#endif

// End of File
