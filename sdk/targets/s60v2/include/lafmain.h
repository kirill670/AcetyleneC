// LAFMAIN.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __LAFMAIN_H__
#define __LAFMAIN_H__

#include <e32std.h>
#include <e32base.h>
#include <gulbordr.h>
#include <gulcolor.h>
#include <frmtlay.h>

class CCoeControl;
class CFont;
class TLogicalFont;
class MLafEnv;


class CLafEdwinCustomDrawBase : public CBase, public MFormCustomDraw
/** LAF support for custom drawing of Edwins.

This class is used by CEikEdwin to draw lines in plain text editors. It does 
not work in rich text editors, as it assumes the line spacing is constant.

The custom drawing interface is defined by the MFormCustomDraw class. 

@publishedPartner
@released */
	{
public:
	/** Allocates and constructs the custom drawer.
	
	@param aEnv LAF environment functions
	@param aControl The Edwin control
	@return New custom drawer */
	IMPORT_C static CLafEdwinCustomDrawBase* NewL(const MLafEnv& aEnv,const CCoeControl& aControl);
public: // from MFormCustomDraw
	/** Implements MFormCustomDraw::DrawBackground() to draw the Edwin background. 
	
	See that function for a full description.
	
	@param aParam Drawing parameters
	@param aBackground Default background colour
	@param aDrawn On return, the rectangle to which the function has drawn */
	IMPORT_C void DrawBackground(const TParam& aParam,const TRgb& aBackground,TRect& aDrawn) const;
	/** Gets the physical colour that maps to a specified logical colour.
	
	@param aColorIndex Logical colour
	@param aDefaultColor The default physical colour. This is the colour to be 
	used if no translation is performed. This allows translation to change certain 
	indices but not others ( by passing the default colour back unchanged).
	@return Physical colour */
	IMPORT_C TRgb SystemColor(TUint aColorIndex,TRgb aDefaultColor) const;
public:
	/** Notifies the drawer that a MEikEdwinObserver::EEventFormatChanged event has 
	occurred for the Edwin. */
	IMPORT_C virtual void LineSpacingChanged();
protected:
	/** Constructor that initialises data members.
	
	@param aEnv LAF environment functions
	@param aControl The Edwin control */
	IMPORT_C CLafEdwinCustomDrawBase(const MLafEnv& aEnv,const CCoeControl& aControl);
protected:
	/** LAF environment functions
	
	This is initialised by the constructor. */
	const MLafEnv& iEnv;
	/** The Edwin control. 
	
	This is initialised by the constructor. */
	const CCoeControl& iControl;
private:
	/** Unused. */
	TInt iSpare;
	};



class MLafEnv
/** LAF interface to access the current system environment settings.

It is implemented by the Uikon Core, and effectively allows the LAF 
limited access to the current thread's CEikonEnv.

@publishedPartner 
@released 
*/
//@publishedAll @deprecated
	{
public:
	/** Gets the environment's nearest match to the specified logical font.

	The return value is never NULL.

	@param aLogicalFont Logical font to match.
	@return The font that most closely matches aLogicalFont. */
	virtual const CFont* Font(const TLogicalFont& aLogicalFont) const=0;

	/** Gets an environment bitmap specified by UID. 

	@param aBmpUid The UID of the bitmap to retrieve.
	@return The bitmap. */
	virtual const CFbsBitmap* Bitmap(TUid aBmpUid) const=0;

	/** Gets the physical (TRgb) colour that corresponds to the specified 
	logical colour, for a specified control.

	@param aLogicalColor Logical colour.
	@param aControl Control for which to get the mapping. Note controls can override 
	the system mappings.
	@return Physical colour. */
	virtual TRgb ControlColor(TLogicalColor aLogicalColor, const CCoeControl& aControl) const=0;

	/** Gets the environment's physical (TRgb) colour that corresponds to 
	the specified logical colour.

	@param aLogicalColor Logical colour.
	@param aColorListUid UID of the colour list from which to get the mapping. The default 
	value is the environment's list.
	@return Physical colour. */
	virtual TRgb Color(TLogicalColor aLogicalColor, TUid aColorListUid=KNullUid) const=0;

	/** Gets the environment setting for the default display mode.

	@return Display mode. */
	virtual TDisplayMode DefaultDisplayMode() const=0; 
	};

class MLafClientRectResolver
/** Interface that works out how screen furniture reduces the available screen area 
for applications.

The interface is implemented by the UI and can be called by the LAF to get information 
on the areas of screen furniture.

@see LafAppUi::ClientRect() 
@publishedPartner
@released */
	{
public:
	/** Flags for types of screen furniture. */
	enum TScreenFurniture
		{ 
		/** Menu bar. */
		EMenuBar, 
		/** Button group. */
		EButtonGroup, 
		/** Tool band. */
		EToolBand, 
		/** Title band. */
		ETitleBand, 
		/** Status pane. */
		EStatusPane,
		/** Command Button Array **/
		ECba
		};
public:
	/** Calculates how a specified type of screen furniture reduces the application 
	area of a specified screen rectangle. 

	@param aScreenFurniture Type of screen furniture.
	@param aRect Screen rectangle from which to remove area of specified furniture. 
	On return, the modified rectangle. */
	virtual void ReduceRect(TScreenFurniture aScreenFurniture,TRect& aRect) const=0;
	};

#endif //__LAFMAIN_H__
