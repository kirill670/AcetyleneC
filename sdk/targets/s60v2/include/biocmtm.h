// BIOCMTM.H
//
// Copyright (c) Symbian Software Ltd 1998-2004.  All rights reserved.
//

#if !defined(__CIOCMTM_H__)
#define __BIOCMTM_H__
#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif
#if !defined(__MTCLBASE_H__)
#include <mtclbase.h>
#endif


#ifdef __REMOVE_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#define __HIDE_MESSAGING_API_V1__
#undef __SUPPORT_MESSAGING_API_V1__
#endif	//  __REMOVE_MESSAGING_API_V1__

#ifdef __SUPPORT_MESSAGING_API_V1__
#undef __HIDE_MESSAGING_API_V1__
#endif	// __SUPPORT_MESSAGING_API_V1__


#ifdef __MESSAGING_API_V2__	
// forward declarations
class CBIODatabase;
#endif // __MESSAGING_API_V2__


class CBIOClientMtm : public CBaseMtm
/** BIO client MTM interface.

The BIO client MTM is simply responsible for requesting BIO message parser 
operations to the BIO Server MTM through InvokeAsyncFunctionL(). Many of the 
other base class functions are implemented to do nothing. 
@publishedPartner
@released
*/
	{
public:
	IMPORT_C static CBIOClientMtm* NewL(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aSession);
	~CBIOClientMtm();
	// from MMsvEntryObserver
	void HandleEntryEvent(TMsvEntryEvent aEvent, TAny* aArg1, TAny* aArg2, TAny* aArg3);
	//
	// from CBaseMtm
	void SaveMessageL(); 
	void LoadMessageL();
	CMsvOperation* ReplyL  (TMsvId aDestination, TMsvPartList aPartlist, TRequestStatus& aCompletionStatus);
	CMsvOperation* ForwardL(TMsvId aDestination, TMsvPartList aPartList, TRequestStatus& aCompletionStatus);
	TMsvPartList ValidateMessage(TMsvPartList aPartList);
	TMsvPartList Find(const TDesC& aTextToFind, TMsvPartList aPartList);
	void AddAddresseeL(const TDesC& aRealAddress);
	void AddAddresseeL(const TDesC& aRealAddress, const TDesC& aAlias);
	void RemoveAddressee(TInt aIndex);
	// --- RTTI functions ---
	TInt QueryCapability(TUid aCapability, TInt& aResponse);
	void InvokeSyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter);
	CMsvOperation*  InvokeAsyncFunctionL(TInt aFunctionId,const CMsvEntrySelection& aSelection, TDes8& aParameter, TRequestStatus& aCompletionStatus);
protected:
	//
	// from CBaseMtm
	void ContextEntrySwitched();
	//
private:
	CBIOClientMtm(CRegisteredMtmDll& aRegisteredMtmDll, CMsvSession& aSession);
#ifdef __MESSAGING_API_V2__	
	void ConstructL();
#endif // __MESSAGING_API_V2__
	//
	void FindInDescriptionL(const TDesC& aTextToFind, TMsvPartList aPartList,TMsvPartList& aFoundList);
	void FindInOriginatorL(const TDesC& aTextToFind, TMsvPartList aPartList,TMsvPartList& aFoundList);
	void FindInBodyL(const TDesC& aTextToFind, TMsvPartList aPartList,TMsvPartList& aFoundList);
#ifdef __MESSAGING_API_V2__	
private:
	RFs					iFs;
	CBIODatabase*		iBioDatabase;
#endif // __MESSAGING_API_V2__
	};


#endif
