// EIKWSEL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKWSEL_H__)
#define __EIKWSEL_H__

#if !defined(__EIKDEF_H__)
#include <eikdef.h>
#endif

#if !defined(__EIKBCTRL_H__)
#include <eikbctrl.h>
#endif

#if !defined(__T32WLD_H__)
#include <t32wld.h>
#endif

#if !defined(__BAMATCH_H__)
#include <bamatch.h>
#endif

struct SWorldSelectorState
	{
	TCityName iCity;
	TCountryName iCountry;
	TWldSelect iSearch;
	};

enum TWorldSelectorType
	{
	EWorldSelectorTypeCity,
	EWorldSelectorTypeCountry
	};

class TResourceReader;
class CEikWorldController;
class CEikWorldModel;
class CCoeEnv;

class CEikWorldSelector : public CEikBorderedControl
	{
public:	
	IMPORT_C CEikWorldSelector();
	IMPORT_C ~CEikWorldSelector();
	IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aParent);
	IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);
	IMPORT_C virtual void SetNeighbor(CCoeControl* aNeighbor);
	IMPORT_C virtual TSize MinimumSize();
	IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	IMPORT_C void HandleStateChangeL();
	inline void CallReportEventL(MCoeControlObserver::TCoeEvent anEvent);
	inline CEikWorldController* Controller() const;
	inline TWorldSelectorType Type() const;
public: //If control built outside a dialog...
	IMPORT_C void ConstructL(CCoeControl& aParent,TBool aWithBorder=ETrue,TWorldSelectorType aSelectorType=EWorldSelectorTypeCity);
	IMPORT_C void ConstructSelectorPairL(CEikWorldSelector& aFirstSelector);
	inline void SetSearchStateTextL(TWldSelect aSearchExtent,const TDesC& aDes);
public:	// from CCoeControl
	IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const;
	IMPORT_C virtual void HandleResourceChange(TInt aType);
	IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: 
	IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
	IMPORT_C virtual void Draw(const TRect& aRect) const;
	void DrawSelector() const;
	void DrawSearchStateText() const;
	void DrawTextInRect(TDesC& aText,TRect aRect,CGraphicsContext::TTextAlign aHoriz) const;
	void DisplayCursor() const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	TWorldSelectorType iSelectorType;
	CEikWorldController* iController;
	const CCoeControl* iParent;
	CCoeControl* iPrevious;
	TBool iOwnsController;
	};



class CEikWorldController : public CBase
	{
public:
	IMPORT_C static CEikWorldController* NewL(const CCoeControl& aClient,CCoeEnv& aEnv,CEikWorldSelector& aSelector,TBool aWithBorder);
	IMPORT_C ~CEikWorldController();

    IMPORT_C void GetState(SWorldSelectorState& aState) const;
    IMPORT_C TInt SetStateL(const SWorldSelectorState& aState);
	IMPORT_C TPtrC CurrentItemText(TWorldSelectorType aSelectorType) const;

	IMPORT_C TWldSelect SearchExtent() const;
	IMPORT_C void SetSearchExtentL(TWldSelect aSearchExtent);
	IMPORT_C TPtrC SearchStateText(TWorldSelectorType aSelectorType) const;
	IMPORT_C void SetSearchStateTextL(TWorldSelectorType aSelectorType,TWldSelect aSearchExtent,const TDesC& aDes);

	inline const CCoeControl* Client() const;
	inline CEikWorldSelector* CitySelector() const;
	inline CEikWorldSelector* CountrySelector() const;
	IMPORT_C void SetSecondSelector(CEikWorldSelector& aSecondSelector);

	inline TBool Border() const;
	inline const CFont* Font() const;
	IMPORT_C void SetFontL(const CFont* aFont);
	inline TInt SelectorWidthInCharacters();
	IMPORT_C void SetSelectorWidthInCharacters(TInt aWidthInChars);
	
	IMPORT_C void ResetMatcher();
	IMPORT_C TInt CursorPos() const;
	
	inline CEikWorldModel* WorldModel() const;
	IMPORT_C TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,CEikWorldSelector& aSelector);
private:
	CEikWorldController();
	void ConstructL(const CCoeControl& aClient,CCoeEnv& aEnv,CEikWorldSelector& aSelector,TBool aWithBorder);

	TKeyResponse DoUnmodifiedKeys(const TKeyEvent& aKeyEvent,TWorldSelectorType aSelectorType);
	void HandleChangesL();
private:
	const CCoeControl* iClient;
	const CFont* iFont;
	CEikWorldSelector* iCitySelector;
	CEikWorldSelector* iCountrySelector;
	CEikWorldModel* iWorldModel;
	TInt iSelectorWidthInCharacters;
	TBool iWithBorder;
	CCoeEnv* iEnv;
	};

//
// CEikWorldSelector
//
inline void CEikWorldSelector::CallReportEventL(MCoeControlObserver::TCoeEvent anEvent)
	{
	ReportEventL(anEvent);
	}
inline CEikWorldController* CEikWorldSelector::Controller()	const
	{
	return iController;
	}
inline void CEikWorldSelector::SetSearchStateTextL(TWldSelect aSearchExtent,const TDesC& aDes)
	{
	iController->SetSearchStateTextL(Type(),aSearchExtent,aDes);
	}
inline TWorldSelectorType CEikWorldSelector::Type()	const
	{
	return iSelectorType;
	}

//
//	CEikWorldController
//
inline const CCoeControl* CEikWorldController::Client() const
	{
	return iClient;
	}
inline const CFont* CEikWorldController::Font() const
	{
	return iFont;
	}
inline TBool CEikWorldController::Border() const
	{
	return iWithBorder;
	}
inline TInt CEikWorldController::SelectorWidthInCharacters()
	{
	return iSelectorWidthInCharacters;
	}
inline CEikWorldSelector* CEikWorldController::CitySelector() const
	{
	return iCitySelector;
	}
inline CEikWorldSelector* CEikWorldController::CountrySelector() const
	{
	return iCountrySelector;
	}
inline CEikWorldModel* CEikWorldController::WorldModel() const
	{
	return(iWorldModel);
	}

#endif
