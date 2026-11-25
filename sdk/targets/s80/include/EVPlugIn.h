// ===========================================================================
//
// Copyright        :   Nokia 2004
//
// Program          :   External View Framework
//
// Identification   :   Plug In interface
//
// ===========================================================================

#if !defined (__EVPLUGIN_H__)
#define __EVPLUGIN_H__

#include <e32base.h>
#include <ecom/ecom.h>
#include <gdi.h>

#include "EVCommon.h"

class CExternalViewPlugIn : public CActive
{
public:
    static inline CExternalViewPlugIn *NewL(const TDesC8& aMatch); // aMatch is default data
    virtual ~CExternalViewPlugIn();

    virtual void  ScreenDimensions (TSize &aSize, TDisplayMode &aDisplayMode) = 0;
    virtual void  UpdateDisplay(const CFbsBitmap &aDisplay, TRequestStatus *aStatus, TPageMetaData *aPageInfo) = 0;
    virtual void  Connect(TRequestStatus *aStatus) = 0;
    virtual void  Disconnect(TRequestStatus *aStatus) = 0;
    virtual TBool PageIsCached(TPageMetaData *aPageInfo) = 0;
    virtual void  DisplayCachedPage(TRequestStatus *aStatus, TPageMetaData *aPageInfo) = 0;
    virtual void  PurgeCache(TDocumentMetaData *aDocInfo) = 0;
    virtual void  CachingCapabilities(TInt &aNumPages, TBool &aPreCaching) = 0;

protected:
    inline CExternalViewPlugIn ();

private:
	/** iDtor_ID_Key Instance identifier key. When instance of an
	 *               implementation is created by ECOM framework, the
	 *               framework will assign UID for it. The UID is used in
	 *               destructor to notify framework that this instance is
	 *               being destroyed and resources can be released.
     */
	TUid iDtor_ID_Key;
};

inline CExternalViewPlugIn::CExternalViewPlugIn() : CActive(CActive::EPriorityLow) {}

// Interface's (abstract base class's) static factory method implementation.
// Asks ECOM plugin framework to instantiate appropriate concrete plugin
// implementation. Uses default resolver so aMatch is the default data.
inline CExternalViewPlugIn* CExternalViewPlugIn::NewL(const TDesC8& aMatch)
{

	TEComResolverParams resolverParams;
	resolverParams.SetDataType (aMatch);
	resolverParams.SetWildcardMatch (ETrue);

	// Find implementation for our interface.
	// - KCExternalViewPlugInInterfaceUid is the UID of our custom ECOM
	//   interface. It is defined in EComInterfaceDefinition.h
	// - This call will leave, if the plugin architecture cannot find
	//   implementation.
	// - The returned pointer points to one of our interface implementation
    //   instances.
	TAny* interface = REComSession::CreateImplementationL (KCExternalViewPlugInInterfaceUid,
		_FOFF (CExternalViewPlugIn, iDtor_ID_Key), resolverParams);

	return reinterpret_cast <CExternalViewPlugIn*> (interface);
	}


// Interface's (abstract base class's) destructor
inline CExternalViewPlugIn::~CExternalViewPlugIn()
	{
	// If in the NewL some memory is reserved for member data, it must be
	// released here. This interface does not have any instance variables so
	// no need to delete anything.

	// Inform the ECOM framework that this specific instance of the
    // interface has been destroyed.
	REComSession::DestroyedImplementation (iDtor_ID_Key);
	}
#endif // __EVPLUGIN_H__
