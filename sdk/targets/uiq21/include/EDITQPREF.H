// EDITQPREF.H
// Created by the Marrakech Team

/** @author SSELAPE */
/** @version $Header: /Marrakech/QMsgeik/EditQINC/EditQPref.h 2     11/11/99 12:02p Sselape $ */
/** $History: EditQPref.h $ */
/**/
/******************  Version 2  ******************/
/*User: Sselape      Date: 11/11/99   Time: 12:02p*/
/*Updated in $/Marrakech/QMsgeik/EditQINC*/
/**/
/******************  Version 1  ******************/
/*User: Sselape      Date: 11/09/99   Time: 11:43a*/
/*Created in $/Marrakech/QMsgeik/EditQINC*/
/**/


// EDITQPREF.H
//
// Copyright (c) 1998/99 Symbian Ltd.  All rights reserved. 
//

// MODULE - Message Editor preferences base


#if !defined(__EDITQPREF_H__)
#define __EDITQPREF_H__

#if !defined(__S32STOR_H__)
#include <S32STOR.H>
#endif

#include <qikon.hrh>

#include "CQMsgEditGlobals.h"
/** Stores generic prefernces for any kind of mail editor*/
class TMailEditorPreferences
	{
public:

	/** Three different zoom levels for viewers */
	enum TZoomLevels{
		EZoom1=EQikCmdZoomLevel1,
		EZoom2=EQikCmdZoomLevel2,
		EZoom3=EQikCmdZoomLevel3
	};
	enum TSearchDirection
	{
		ESearchUp,
		ESearchDown
	};
	/** Constructor */
	 IMPORT_C TMailEditorPreferences();

	 /** Destructor */
	 IMPORT_C virtual ~TMailEditorPreferences();

	 /**  --- Persistence out --- */
	 void ExternalizeL(CDictionaryStore& aStore) const;

 	 /**  --- Persistence in --- */
	 void InternalizeL(const CDictionaryStore& aStore);
protected:
	virtual TUid PreferencesUid() const = 0;
	 virtual void DoExternalizeL(RDictionaryWriteStream& aStore) const;
	 virtual void DoInternalizeL(RDictionaryReadStream& aStore);

	TBool operator!=(const TMailEditorPreferences& aRHS) const;
public:
	/** Has preferences changed!? */
	TBool		iChanged;

	/** Current zoom level */
	TZoomLevels		iZoom;

	/** Current search direction used in editors*/
	TSearchDirection iSearchDirection;

	/** Last find item */
	TBuf<ENameMaxLength> iLastSearchString;
	
	/** Version of prefs stored*/
	TUint8		iPrefsVersion;
	
	TBool iSmiliesEnabled;
	};

#endif // __EDITQPREF_H__
