// QIKSOUNDSELECTOR.H
//
// Copyright (c) 1997-2003 Symbian AB.  All rights reserved.
//

#ifndef __QIKSOUNDSELECTOR_H__
#define __QIKSOUNDSELECTOR_H__

#include <coecntrl.h>	// class CCoeControl
#include <bamdesca.h>	// class MDesCArray
#include <mda\common\controller.h>

class CEikImage;
class CEikChoiceList;
class CSoundPickerChoiceList;
class CSoundSelectorPlayerSingleton;
class CQikSoundSelectorExtension;
class TBaSystemSoundType;
class TBaSystemSoundInfo;

/**
 * This class provides a Sound selector control
 * A control that allows the user to choose a sound to play
 **/
class CQikSoundSelector : public CCoeControl
	{
public:
	enum TFlags
		{
		EIncludeSilentOption = 0x01,			// Include 'Silent' as an option
		EIncludeFindAudioFileOption = 0x02,		// Allow user to select files from Audio Media Files
		EExcludeFindAudioFileHistory = 0x04
		};

	enum TFixedSequenceSoundTypes
		{
		EIncludeTones = 1,		// Key-clicks, screen-clicks, etc
		EIncludeEventSounds,	// Error, warning, etc
		EIncludeAlarmSounds,	
		EIncludeRingSounds
		};

public:
	IMPORT_C CQikSoundSelector();
	IMPORT_C ~CQikSoundSelector();
	IMPORT_C void ConstructL();
	IMPORT_C void SetSoundOptionL(TInt aFlags);
	IMPORT_C void SetDefaultSoundL(TInt aSoundNameStrResourceId, const TBaSystemSoundType& aDefaultToneUid);
	IMPORT_C void AddCustomSoundL(const TFileName& aSoundFile);
	IMPORT_C void AddFixedSequenceSoundsL(TFixedSequenceSoundTypes aSoundType);
	IMPORT_C void SetAllowedMimeTypesL(const MDesCArray& aMimeTypes);
	IMPORT_C void SetSoundPriority(const TInt aPriority, const TMdaPriorityPreference aPriorityPreference);
	IMPORT_C void SetSoundVolume(const TInt aVolume);
	IMPORT_C void SetSound(const TDesC& aSound);
	IMPORT_C void SetSound(const TBaSystemSoundInfo& aSoundInfo);
	IMPORT_C void GetSound(TDes& aSound) const;
	IMPORT_C CEikChoiceList* GetChoiceList();
	IMPORT_C void SetFont(const CFont* aFont);
public: // from CCoeControl
	IMPORT_C void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C TSize MinimumSize();
	IMPORT_C void SetDimmed(TBool aDimmed);
	IMPORT_C void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C void HandleResourceChange(TInt aType);
public:
	void HandleControlEventL(CCoeControl* aControl, MCoeControlObserver::TCoeEvent aEventType);
	void SetCurrentItem(TInt aIndex);
protected: // from CCoeControl
	IMPORT_C TInt CountComponentControls() const;
	IMPORT_C CCoeControl* ComponentControl(TInt aIndex) const;
	IMPORT_C void SizeChanged();
	IMPORT_C void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	IMPORT_C TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // reserved virtual function space
	IMPORT_C virtual void QikReserved_1();
private:
	void BaseConstructL();
	void PlaySoundL();
private:
	enum 
		{
		EDefaultPos=0,
		EFindPos=1
		};
private:
	CSoundPickerChoiceList* iChoiceList;
	CEikImage* iImage;
	CQikSoundSelectorExtension* iExtra;
	TInt iOldSelectionIndex;
private:
	TInt iQikSpare[3];
	};

#endif	// __QIKSOUNDSELECTOR_H__
