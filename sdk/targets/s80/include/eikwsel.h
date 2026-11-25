/*
* ==============================================================================
*  Name        : eikwsel.h
*  Part of     : CKON
*  Interface   : World selector API
*  Description : World selector
*  Version     : 1.0
*
*  Copyright (c) 2003 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#ifndef EIKWSEL_H
#define EIKWSEL_H

// INCLUDES
#include <eikdef.h>
#include <eikbctrl.h>
#include <t32wld.h>
#include <bamatch.h>

// FORWARD DECLARATIONS
class TResourceReader;
class CEikWorldController;
class CEikWorldModel;
class CCoeEnv;



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


/**
*  display a world map and allow selection using cross-hairs
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikWorldSelector : public CEikBorderedControl
	{
	public:	

		/**
		* C++ default constructor.
		*/
		IMPORT_C CEikWorldSelector();

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikWorldSelector();

		/**
		* Sets container window
		* @since Series90 1.0
		* @param aParent A parent control
		*/
		IMPORT_C virtual void SetContainerWindowL(const CCoeControl& aParent);

		/**
		* Construct from resource.
		* @since Series90 1.0
		* @param aReader A resource reader.
		*/
		IMPORT_C virtual void ConstructFromResourceL(TResourceReader& aReader);

		/**
		* Sets neighbor.
		* @since Series90 1.0
		* @param aNeighbor A control.
		*/
		IMPORT_C virtual void SetNeighbor(CCoeControl* aNeighbor);

		/**
		* Gets control's minimum size in pixels.
		* @since Series90 1.0
		* @return The control's minimum size.
		*/
		IMPORT_C virtual TSize MinimumSize();

		/**
		* Handles key events.
		* @since Series90 1.0
		* @param aKeyEvent A key event.
		* @param aType A event type.
		* @return Key response.
		* <BR><B>Type of return value:</B> TKeyResponse
		*/
		IMPORT_C virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

		/**
		* Handles the state change.
		* @since Series90 1.0
		*/
		IMPORT_C void HandleStateChangeL();

		/**
		* Calls report event.
		* @since Series90 1.0
		* @param anEvent A event.
		*/
		inline void CallReportEventL(MCoeControlObserver::TCoeEvent anEvent);

		/**
		* Gets the controler.
		* @since Series90 1.0
		* @return A pointer to the controller object.
		* <BR><B>Type of return value:</B> CEikWorldController*
		*/
		inline CEikWorldController* Controller() const;

		/**
		* Gets the type.
		* @since Series90 1.0
		* @return World selector type
		* <BR><B>Type of return value:</B> TWorldSelectorType
		*/
		inline TWorldSelectorType Type() const;
	public: //If control built outside a dialog...

		/**
		* The second phase construction.
		* @since Series90 1.0
		* @param aParent A parent control.
		* @param aWithBorder Width Border.
		* @param aSelectorType Selector type.
		*/
		IMPORT_C void ConstructL(CCoeControl& aParent,TBool aWithBorder=ETrue,TWorldSelectorType aSelectorType=EWorldSelectorTypeCity);

		/**
		* Constructs selector pair.
		* @since Series90 1.0
		* @param aFirstSelector The first selector.
		*/
		IMPORT_C void ConstructSelectorPairL(CEikWorldSelector& aFirstSelector);

		/**
		* Set the search state text.
		* @since Series90 1.0
		* @param aSearchExtent The search extent.
		* @param aDes Text.
		*/
		inline void SetSearchStateTextL(TWldSelect aSearchExtent,const TDesC& aDes);
	public:	// from CCoeControl

		/**
		* Gets the color list.
		* @since Series90 1.0
		* @param aColorUseList Color list.
		*/
		IMPORT_C virtual void GetColorUseListL(CArrayFix<TCoeColorUse>& aColorUseList) const; // not available before Release 005u

		/**
		* Handles the resource change.
		* @since Series90 1.0
		* @param aType A message uid.
		*/
		IMPORT_C virtual void HandleResourceChange(TInt aType);			// not available before Release 005u

		/**
		* Gets the control's input capailities.
		* @since Series90 1.0
		* @return The control's input capabilities.
		* <BR><B>Type of return value:</B> TCoeInputCapabilities
		*/
		IMPORT_C virtual TCoeInputCapabilities InputCapabilities() const;
	private: 
		IMPORT_C virtual void FocusChanged(TDrawNow aDrawNow);
		IMPORT_C virtual void Draw(const TRect& aRect) const;
		void DrawSelector() const;
		void DrawSearchStateText() const;
		void DrawTextInRect(TDesC& aText,TRect aRect,CGraphicsContext::TTextAlign aHoriz) const;
		void DisplayCursor() const;
	private:
		TWorldSelectorType iSelectorType;
		CEikWorldController* iController;
		const CCoeControl* iParent;
		CCoeControl* iPrevious;
		TBool iOwnsController;
	};



/**
*  Display country and city	selectors.	
*
*  @lib eikctl.lib
*  @since Series90 1.0
*/
class CEikWorldController : public CBase
	{
	public:

		/**
		* Two-phased constructor.
		*/
		IMPORT_C static CEikWorldController* NewL(const CCoeControl& aClient,CCoeEnv& aEnv,CEikWorldSelector& aSelector,TBool aWithBorder);

		/**
		* Destructor.
		*/
		IMPORT_C ~CEikWorldController();


		/**
		* Gets the state.
		* @since Series90 1.0
		* @param aState Selector's state.
		*/
		IMPORT_C void GetState(SWorldSelectorState& aState) const;

		/**
		* Sets the selector's state.
		* @since Series90 1.0
		* @param aState Selector's state to be set.
		*/
		IMPORT_C TInt SetStateL(const SWorldSelectorState& aState);

		/**
		* Gets the current item text.
		* @since Series90 1.0
		* @param aSelectorType A selector type.
		* @return The current item's text.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC CurrentItemText(TWorldSelectorType aSelectorType) const;


		/**
		* Gets search extent.
		* @since Series90 1.0
		*/
		IMPORT_C TWldSelect SearchExtent() const;

		/**
		* Set the search extent.
		* @since Series90 1.0
		* @param aSearchExtent Search extent.
		*/
		IMPORT_C void SetSearchExtentL(TWldSelect aSearchExtent);

		/**
		* Gets the search state text.
		* @since Series90 1.0
		* @param aSelectorType A selector type.
		* @return Search state text.
		* <BR><B>Type of return value:</B> TPtrC
		*/
		IMPORT_C TPtrC SearchStateText(TWorldSelectorType aSelectorType) const;

		/**
		* Sets the search state text.
		* @since Series90 1.0
		* @param aSelectorType A selector type.
		* @param aSearchExtent Search extent.
		* @param aDes Text.
		*/
		IMPORT_C void SetSearchStateTextL(TWorldSelectorType aSelectorType,TWldSelect aSearchExtent,const TDesC& aDes);


		/**
		* Gets the clilent.
		* @since Series90 1.0
		* @return A pointer to the control.
		* <BR><B>Type of return value:</B> const CCoeControl*
		*/
		inline const CCoeControl* Client() const;

		/**
		* Gets the city selector.
		* @since Series90 1.0
		* @return A pointer to the selector.
		* <BR><B>Type of return value:</B> CEikWorldSelector*
		*/
		inline CEikWorldSelector* CitySelector() const;

		/**
		* Gets the country selector.
		* @since Series90 1,0
		* @return A pointer to the country selector.
		* <BR><B>Type of return value:</B> CEikWorldSelector*
		*/
		inline CEikWorldSelector* CountrySelector() const;

		/**
		* Sets the second selector.
		* @since Series90 1.0
		* @param aSecondSelector Second selector
		*/
		IMPORT_C void SetSecondSelector(CEikWorldSelector& aSecondSelector);


		/**
		* Border.
		* @since Series90 1.0
		*/
		inline TBool Border() const;

		/**
		* Gets the font.
		* @since Series90 1.0
		* @return A pointer to the CFont.
		* <BR><B>Type of return value:</B> const CFont*
		*/
		inline const CFont* Font() const;

		/**
		* Sets the font.
		* @since Series90 1.0
		* @param aFont Font
		*/
		IMPORT_C void SetFontL(const CFont* aFont);

		/**
		* Gets the number of characters which can fit in the selector.
		* @since Series90_version
		* @return The number of characters which cna fit in the selector.
		* <BR><B>Type of return value:</B> TInt
		*/
		inline TInt SelectorWidthInCharacters();

		/**
		* Sets the selector width.
		* @since Series90 1.0
		* @param aWidthInChars Number of characters.
		*/
		IMPORT_C void SetSelectorWidthInCharacters(TInt aWidthInChars);
	

		/**
		* Resets the matcher.
		* @since Series90 1.0
		*/
		IMPORT_C void ResetMatcher();

		/**
		* Gets the cursor position.
		* @since Series90 1.0
		* @return The cursor position.
		* <BR><B>Type of return value:</B> TInt
		*/
		IMPORT_C TInt CursorPos() const;
	

		/**
		* Gets the world model.
		* @since Series90 1.0
		* @return A pointer to the world model.
		* <BR><B>Type of return value:</B> CEikWorldModel*
		*/
		inline CEikWorldModel* WorldModel() const;

		/**
		* Handles the key events.
		* @since Series90 1.0
		* @param aKeyEvent A key event.
		* @param aSelector The selector.
		* @return The key response.
		* <BR><B>Type of return value:</B> TKeyResponse
		*/
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


#endif	// EIKWSEL_H

// End of File
