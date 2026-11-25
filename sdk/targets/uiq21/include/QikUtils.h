// QikUtils.h
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#ifndef __QIKUTILS_H__
#define __QIKUTILS_H__

#include <e32svr.h>
#include <e32std.h> // For the descriptors
#include <apgcli.h> // For the AppArc related classes
#include <eikenv.h>

class TBaSystemSoundType;

// moved from QuikProfileUtils.h

// This macro can be used to print out messages to the debug channel,
// which will be accomponied with the current tick count of the processor.
// Applications wanting to use this macro only have to include the file
// QikProfileUtils.h and can then call the macro anywhere within their code.
// Example:  __PROFILE_PRINT("AppLauncher: Started agenda").

#ifdef __QUARTZPROFILING__
#define __PROFILE_PRINT(aText) \
	{ \
	TUint currentTickCount = User::TickCount(); \
	RDebug::Print(_L("QUARTZPROFILING: %d - %s"), currentTickCount, _S(aText)); \
	}
#else // __QUARTZPROFILING__
#define __PROFILE_PRINT(aText)
#endif


/**
 * Utility class to reserve in a palette the n most common colors in 
 * currently used colorscheme
 */
class QikPaletteUtils
	{
public:
	IMPORT_C static TInt FindCommonlyUsedColors(const CEikonEnv* aEnv, CPalette& aPalette, TInt n = 256);
	IMPORT_C static void Colorize(CFbsBitmap& aBitmap, TRgb aTargetColor);
	IMPORT_C static void Colorize(CFbsBitmap& aBitmap, TRgb aBaseColor, TRgb aTargetColor);
private:
	QikPaletteUtils();
	};


const TUid KUidViewerMessageChangeSaveBehaviour = { 0x101F617A };

/**
 * Utility class to give a central spot to retrieve the path and name of the
 * document file. All methods are static and the class should never be
 * instantiated.
 *
 * Background:
 * Applications should not hardcode or use resource to locate the path and name
 * of the document for an application.This utility class is introduced to give
 * applications a common way of finding the name for the document.
 *
 * @since 6.2
 */
class QikFileUtils
	{
public:
	enum 
		{	
		EFileUtilsPanicWrongResourceFormat
		};

	enum TQikViewerBehaviour
		{
		EQikViewerAlwaysDelete,
		EQikViewerDeleteOnSave,
		EQikViewerNeverDelete
		};

	IMPORT_C static void MakeAppDocumentFileNameL(TFileName& aDocFile, const TUid& aAppUid);
	IMPORT_C static void MakeAppDocumentFileNameL(TFileName&aDocFile, TApaAppInfo& aInfo, const TUid& aAppUid);
	IMPORT_C static void MakeAppDocumentFileNameL(TFileName& aDocFile, const TApaAppInfo& aInfo);
	IMPORT_C static TBool TempFile(const TFileName& aTempFile);
	IMPORT_C static void StartAppL(const TFileName& aDocFile, TQikViewerBehaviour aBehaviour = EQikViewerNeverDelete );
	IMPORT_C static void StartDefaultViewerAppL(const TFileName& aDocFile,RApaLsSession& aLsSession, TQikViewerBehaviour aBehaviour = EQikViewerNeverDelete);
	IMPORT_C static TQikViewerBehaviour GetViewerBehaviourFromTail(const TDesC8& aTailEnd);
	IMPORT_C static void GetTempPathL(TPath& aPath);
	IMPORT_C static TInt FileNameToSoundType(const TFileName& aFileName, TBaSystemSoundType& aSoundType);
	IMPORT_C static void SoundTypeToFileName(const TBaSystemSoundType& aSoundType, TFileName& aFileName);
private:
	QikFileUtils(); // shouldn't instantiate this class
	};


/** 
 *
 * @since 7.0
 */
class CQikDynamicPaletteBitmap : public CBase, public MCoeResourceChangeObserver
	{
public:
	IMPORT_C static CQikDynamicPaletteBitmap* NewL(CEikonEnv& aEikEnv, TInt aResourceId);
	IMPORT_C void AddBitmapsL(TInt aResourceId);
	~CQikDynamicPaletteBitmap();
private:	// from MCoeResourceChangeObserver
	void HandleResourceChange();
private:
	CQikDynamicPaletteBitmap(CEikonEnv& aEikEnv);
	TInt MapColorsL(TInt aResourceId, TInt aBitmapArrayOffset);
private:
	CEikonEnv& iEikEnv;
	RArray<TInt> iResourceIds;
	RPointerArray<CFbsBitmap> iBitmaps;
	};




#endif __QIKUTILS_H__
