// CONNECTIONSETTINGS.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// Header for Connection Settings used by CDialogProcessor
// and DBAccess Classes

#ifndef __CONNECTIONSETTINGS_H__
#define __CONNECTIONSETTINGS_H__

#include <d32comm.h>
#include <commdb.h>

const TUint KCharT='T';
const TUint KCharP='P';
const TUint KSlashChar='\\';

const TUint KDCDHandshakeMask=KConfigObeyDCD|KConfigFailDCD;
const TUint KDSRFailHandshakeMask=KConfigFailDSR;
const TUint KCTSHandshakeMask=KConfigObeyCTS|KConfigFailCTS;
const TUint KNoHandshakingMask=~(KConfigObeyXoff | KConfigSendXoff | KConfigObeyCTS | 
		KConfigFailCTS | KConfigObeyDSR | KConfigFailDSR | KConfigObeyDCD | KConfigFailDCD );

class TConnectionSettings
	{
public:
	IMPORT_C TConnectionSettings();
public:
	TUint32 iRank;
	TCommDbConnectionDirection iDirection;
	TCommDbDialogPref iDialogPref;
	TUint32 iBearerSet;
	TUint32 iIAPId;
	TUint32 iServiceId;
	TBuf<KCommsDbSvrMaxColumnNameLength> iServiceType;
	TUint32 iModemId;
	TUint32 iLocationId;
	TUint32 iChargeCardId;
	};

#endif