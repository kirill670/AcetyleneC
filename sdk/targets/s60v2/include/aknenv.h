/*
* ============================================================================
*  Name     : AknEnv.h
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
#if !defined(__AVKON_ENV_H__)
#define __AVKON_ENV_H__

#include <eikenv.h>
#include <eiksbfrm.h>
#include <eikcba.h>
#include <eikmobs.h>
#include <eikmenub.h>
#include <eikappui.h>
#include <aknlayout2id.h> // for TAknLayoutId

class MAknEditingStateIndicator;
class MAknIntermediateState;
class CAknAppUi;
class CAknWaitDialog;
class CEikListBox;
class CAknSettingCache;
class CAknFontRegistry;


class CAknEnv : public CBase
	{
public:
	IMPORT_C static CAknEnv* Static();
	IMPORT_C ~CAknEnv();
public:
	// this one creates an empty dialog. for list queries and popup lists with "No Data" in it.
	IMPORT_C void ExecuteEmptyPopupListL(const TDesC *aEmptyText=0);
	IMPORT_C void ExecuteEmptyPopupListL(const TDesC *aEmptyText, const TDesC *aTitle, TInt aSoftkeyId=0);

public:
	IMPORT_C void SetFepMenuObserver(MEikMenuObserver* aObserver);
	IMPORT_C MEikMenuObserver* FepMenuObserver();
	IMPORT_C MAknEditingStateIndicator* EditingStateIndicator();
	IMPORT_C MAknEditingStateIndicator* SwapEditingStateIndicator(MAknEditingStateIndicator* aIndicator);
	IMPORT_C static void ExitForegroundAppL();

public: // Intermediate states support
	IMPORT_C void RegisterIntermediateStateL(MAknIntermediateState *aState);
	IMPORT_C void UnRegisterIntermediateState(MAknIntermediateState *aState);
	IMPORT_C void CloseAllIntermediateStates();

public:
	IMPORT_C static void RunAppShutter();
	IMPORT_C static CAknAppUi* AppWithShutterRunning();
	IMPORT_C static void StopSchedulerWaitWithBusyMessage(CActiveSchedulerWait& aWait);

public:
	IMPORT_C void CreateCbaObserverL(CEikButtonGroupContainer *aCba, CEikListBox *aListBox);
	IMPORT_C void RemoveCbaObserver();
	IMPORT_C void InformCbaDeletion(CEikButtonGroupContainer *aCba);

public:
	IMPORT_C void GetCurrentLayoutId(TAknLayoutId& aCurrentLayoutId) const;

public:
	IMPORT_C TInt StatusPaneResIdForCurrentLayout(TInt aResId) const;

public:
    /**
    * Requests Window Server client buffer used by the application to
    * be of at least the given size. All code that wants to increase the
    * buffer size should call this method instead of using WS interface
    * directly. A list of all requests is maintained and the highest
    * request is always effective.
    *
    * @since 2.0
    *
    * @param aRequestedBufferSize requested Window Server client buffer size
    *
    * @return Request ID. This is used when the request is canceled.
    *         In OOM situation, KErrNoMemory is returned. CancelWsBufferRequest
    *         ignores negative values as error codes so it is OK to pass any
    *         value returned by this method to CancelWsBufferRequest.
    */
    IMPORT_C TInt RequestWsBuffer( TInt aRequestedBufferSize );

    /**
    * Cancels a request made by call RequestWsBuffer. This should be
    * called in order to save RAM when higher than normal buffer size is
    * no longer required.
    *
    * @since 2.0
    *
    * @param aRequestID The request ID returned by the
    *        RequestWsBuffer call which is to be canceled.
    *        Negative values are treated as error codes and ignored.
    */
    IMPORT_C void CancelWsBufferRequest( TInt aRequestID );

public:
    /**
    * @internal to Series 60
    */
	IMPORT_C CAknSettingCache& SettingCache() const;

    /**
    * Access to the registry of CAknLayoutFont pointers. Used for runtime checking of CFont pointers
    * 
    * @internal to Series 60
    * @since Series 60 2.8
    * 
    * @return   Reference to the registry
    */
    CAknFontRegistry& FontRegistry() const;

    /**
    * Access to the system font array that is owned by CEikonEnv. The member accessed by this
    * is set during CEikonEnv construction and may be null during application startup.
    * 
    * @internal to Series 60
    * @since Series 60 2.8
    * 
    * @return   Pointer to the system font array
    */
    CArrayFix<TAknSystemFont>* SystemFontArray() const;


    void UpdateSystemFontsL();

public: // layout
	IMPORT_C TBool LoadAknLayoutL();

private:

    void SetWsBufferSize();
    void SetWsBufferSize( TInt aRequestedBufferSize );

    // Only these can use run info array, so it cannot get messed up
    // by simultaneous use.
    friend class AknBidiTextUtils;
    friend class TAknTextWrapper;

    /**
    * Returns run info array owned by AknEnv.
    *
    * @param aLength Length of the array is returned here.
    *
    * @return Run info array owned by AknEnv.
    */
    TBidirectionalState::TRunInfo* RunInfoArray( TInt& aLength ) const;

    /**
    * Tests how big run info array the given text requires and
    * tries to increase the size of the array if required.
    *
    * @param aLogicalText Text in logical order.
    *
    * @return KErrNone or KErrNoMemory.
    */
    TInt PrepareRunInfoArray( const TDesC& aLogicalText );

    /**
    * Tries to increase the size of the run info array if
    * it is currently smaller than given length.
    *
    * @param aLength Length of the new run info array to be allocated.
    *
    * @return KErrNone or KErrNoMemory.
    */
    TInt SetRequiredRunInfoArraySize( TInt aLength );

	void SetLayoutRequirementsL();
	void AssertLayoutLoaded();
	TBool LoadAknLayoutL(TAknLayoutId aId, const TPixelsAndRotation& aSizeRot);

private:
	static TInt RealCloseIntermediateStates(TAny *aEnv);
	static TInt SchedulerStoppedCallBack(TAny* aWaitNote);
	void DoSchedulerStoppedCallBack();

private:
	friend class CEikonEnv;
    friend class LafEnv;
	IMPORT_C static void InstallAknEnvAsExtensionL(CEikonEnv* aEnv);
	IMPORT_C CAknEnv();
	IMPORT_C void ConstructL();

private:
    TInt SoftKeyLocationInLandscapeOrientationL() const;

private:
	MEikMenuObserver* iFepMenuObserver;
	MAknEditingStateIndicator* iEditStateIndicator;
private:
	CArrayPtr<MAknIntermediateState> *iStateArray;
	CArrayPtr<CBase> *iDeleteArray;
	CIdle *iIdle;
	CAknWaitDialog* iBusyMsgDialog;
	TInt iBusyMsgCount;
	MEikCommandObserver *iCbaCommandObserver;
    CAknSettingCache* iSettingCache;
    TBidirectionalState::TRunInfo* iRunInfoArray;
    TInt iRunInfoArrayLength;

    struct TWsBufferRequest
        {
        TInt iRequestID;
        TInt iRequestedSize;
        };

    RArray<TWsBufferRequest> iWsBufferRequestArray;
    TInt iRequestIdCounter;
    TInt iCurrentWsBufferRequest;

	// cache for layout parameters
	TAknLayoutId iLastLayoutId;
	TPixelsAndRotation iLastLayoutSizeRot;

	CEikonEnv* iCoeEnv;
    CAknFontRegistry* iFontRegistry;  // Owned register of CAknLayoutFont pointers
    CArrayFixFlat<TAknSystemFont>* iSystemFontArray; // Not owned. System Font array is owned by CEikonEnv
	};


#define iAvkonEnv (STATIC_CAST(CAknEnv*,iEikonEnv->Extension()))
#define AVKONENV (STATIC_CAST(CAknEnv*, CEikonEnv::Static()->Extension()))

#endif
