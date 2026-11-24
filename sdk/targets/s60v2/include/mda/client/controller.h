// Mda\Client\Controller.h 
//
// Copyright (c) 1997-2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MDA_CLIENT_CONTROLLER_H__
#define __MDA_CLIENT_CONTROLLER_H__

// Standard EPOC32 includes
#include <e32base.h>

// Public Media Server includes
#include <Mda\Client\Base.h>
#include <Mda\Client\Port.h>
#include <Mda\Client\Utility.h>
#include <Mda\Common\Controller.h>


/**
 * @publishedAll
 * @removed
 *
 * Dummy class for BC
 */
class CDummyMdaController : public CActive, public MMdaObjectEventListener
	{
public:

	IMPORT_C static CDummyMdaController* NewL(CMdaServer* aServer, MMdaObjectStateChangeObserver& aObserver);
	IMPORT_C virtual ~CDummyMdaController();
	//
	IMPORT_C void SetPriorityL(TInt aPriority, TMdaPriorityPreference aPref);
	//
	IMPORT_C void ConnectL(MDummyMdaSrcPort* aSrcPort, MDummyMdaDstPort* aDstPort, TUid aType);
	IMPORT_C void Prepare();
	IMPORT_C void Prime();
	IMPORT_C void Play();
	IMPORT_C void Pause();
	IMPORT_C void Stop();
	IMPORT_C void Unprepare();
	IMPORT_C void Reset();
private:
	CDummyMdaController(CMdaServer* aServer, MMdaObjectStateChangeObserver& aObserver);
	void ConstructL();
	// From CActive
	virtual void RunL();
	virtual void DoCancel();
	// From MMdaObjectEventListener
	virtual const RDummyMdaObject& MoelObject() const;
	virtual void MoelEvent(const TMdaEvent& aEvent);
	virtual void MoelEventMissed();
private:
	RDummyMdaObject iDummyObject;
	};

#endif
