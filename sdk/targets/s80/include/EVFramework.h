// ===========================================================================
//
// Copyright        :   Nokia 2004
//
// Program          :   External View Framework
//
// Identification   :   Driving Application API
//
// ===========================================================================

#if !defined (__EVFRAMEWORK_H__)
#define __EVFRAMEWORK_H__

#include <e32base.h>
#include <eikdialg.h>
#include "EVCommon.h"

// Priorities for connections
enum TEVPriority
{
    EEVPriorityLow,      // Screen Exporter should use this
    EEVPriorityMedium,   // Most Apps should use this
    EEVPriorityHigh      // Only special case applications should use this
};

enum TEVDrawType
{
    EEVDrawSync,
    EEVDrawAsync
};

class TPageMetaData;
class TDocumentMetaData;

/*********************************************************************
 * Observer Mixin Class
 *********************************************************************
 */

class MExternalViewObserver 
{
public:
    virtual void OperationComplete (TInt aResult) = 0;
};

class MExternalViewDrawObserver 
{
public:
    virtual TPageMetaData *DrawToExternalView(CBitmapContext &aDisplay) = 0;
    virtual TPageMetaData *DrawToExternalView(TRequestStatus *aStatus, CBitmapContext &aDisplay) = 0;
};


class MExternalViewConnection
{
public:
    virtual TInt    ConnectPlugIn(const TDesC8 &aMatch) = 0;
    virtual TInt    DisconnectPlugIn() = 0;
    virtual TBool   IsConfigured() = 0;
    virtual TBool   IsPlugInConnected(const TDesC8 &aMatch) = 0;
};

/*********************************************************************
 * RExternalView Class
 *********************************************************************
 */

class CExternalViewRequester : public CActive
{
public:
    CExternalViewRequester();
    ~CExternalViewRequester() {};

    TRequestStatus *Start(TRequestStatus *aStatus);
    void DoCancel();
    void RunL();

private:
    TRequestStatus *iEVStatus;
};

class RExternalView : public RSessionBase
{
public:
    RExternalView();
    ~RExternalView();

    TBool   IsConnected();
    TInt    Connect(TEVPriority aPriority);
    void    Close();

    TBool   IsConfigured();
    TBool   IsPlugInConnected(const TDesC8 &aMatch);
    TInt    ConnectPlugIn(TRequestStatus *aStatus, const TDesC8 &aMatch);
    TInt    DisconnectPlugIn(TRequestStatus *aStatus);

    TBool   IsCached(TPageMetaData &aPageInfo);
    TInt    DisplayCachedPageA(TRequestStatus *aStatus, TPageMetaData &aPageInfo);
    TInt    PurgeDisplayCache(TDocumentMetaData &aDocInfo);
    void    CachingCapabilities(TInt &aNumPages, TBool &aPreCaching);

    TInt    ReserveDisplayContext(TInt &aHandle);
    TInt    UnreserveDisplayContext();
    TInt    ReleaseDisplayContextA(TRequestStatus *aStatus, 
                                   TPageMetaData *aPageInfo);
    TInt    Cancel();
    inline TBool   IsActive();

private:
    TVersion Version();

    TInt     SetPriority(TEVPriority aPriority);

private:
    TBool                  iConnected; // Operational state for Client
    TPtr8                  iTransferPtr;
    CExternalViewRequester iRequester;
};

inline TBool RExternalView::IsActive() { return iRequester.IsActive(); };


/*********************************************************************
 * CExternalView Class
 *********************************************************************
 */

class CPlugInSelectionDialog;
class CExtViewInstalledPlugIns;
class CExternalView : public CActive, public MExternalViewConnection
{
private:
    enum TExternalViewRequest
    {
        ENoRequest,
        EDraw,
        EDrawEnd,
        EDrawRelease,
        EDisplayCachedPage,
        EConnecting,
        EDisconnecting,
    };

public:

    // Public construction & destructor
    IMPORT_C static CExternalView* NewL(MExternalViewObserver &aObserver, 
                                        MExternalViewDrawObserver &aDrawObserver, 
                                        TEVDrawType aDrawType = EEVDrawSync);
    IMPORT_C ~CExternalView();

    IMPORT_C void    DoCancel();
    void             RunL();

    IMPORT_C TBool   IsConnected();
    IMPORT_C TInt    Connect(TEVPriority aPriority);
    IMPORT_C void    Close();

    IMPORT_C TBool   PlugInsAvailable();
    IMPORT_C TBool   IsConfigured();
    IMPORT_C TBool   IsPlugInConnected(const TDesC8 &aMatch);
    IMPORT_C TBool   RunDialogL();
    IMPORT_C void    CachingCapabilities(TInt &aNumPages, TBool &aPreCaching);

    IMPORT_C TInt    DrawRequest(TPageMetaData *aPageInfo);
    IMPORT_C TInt    PurgeCache(TDocumentMetaData &aDocInfo);


    IMPORT_C const TDesC &PlugInNameL();

             TInt    ConnectPlugIn(const TDesC8 &aMatch);
             TInt    DisconnectPlugIn();


protected:
    // Protected construction
    CExternalView(MExternalViewObserver &aObserver, 
                  MExternalViewDrawObserver &aDrawObserver, 
                  TEVDrawType aDrawType);
    void ConstructL();

    // Observer notification
    inline void OperationComplete (TInt aResult) const;

private:
    void EndRequest(TInt aError);

private:
    RExternalView              iEVClient; // EV Framework client
    MExternalViewObserver     *iDialogObserver; // Dialog Observer (NULL if there isn't one)
    MExternalViewObserver     &iObserver; // Observer
    MExternalViewDrawObserver &iDrawObserver; // Draw Observer
    CFbsBitmap                 iFbsBitmap;
    CBitmapContext            *iContext;
    CBitmapDevice             *iDevice;
    TPageMetaData             *iPageInfo;
    TEVDrawType                iDrawType;
    TExternalViewRequest       iRequest;
    CExtViewInstalledPlugIns  *iUtility;
    TBool                      iRequestedByDialog;
};

inline void CExternalView::OperationComplete (TInt aResult) const
{
    iObserver.OperationComplete(aResult);
}       

#endif // __EVFRAMEWORK_H__
