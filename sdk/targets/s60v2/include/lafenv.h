// LAFENV.H
//
// Copyright (c) 1997-2004 Symbian Ltd.  All rights reserved.
//

#ifndef __LAFENV_H__
#define __LAFENV_H__

#include <e32std.h>
#include <e32base.h>
#include <gulbordr.h>
#include <gulalign.h>
#include <lafmain.h>
#include <apgcli.h>

#include <fontids.hrh>
#include <gulfont.h>

class MParser;
class CCoeEnv;
class CFont;
class TLogicalFont;


class CAknDynamicFont;

//Avkon specific class that enables matching of font by Uid
class TAknSystemFont
	{
public:
	IMPORT_C TAknSystemFont(TUid aUid, CFont* aFont);
	IMPORT_C CFont* Font() const;
	IMPORT_C TUid Uid() const;
	enum TDisambiguationParam {KConstructWithResId = 1234};
	TAknSystemFont(TUid aUid, TInt aResId, TDisambiguationParam /*aDisambiguationParam*/);
	void LoadIfNecessaryL() const;
private:
	TUid iUid;
	union
		{
		// in this union, iId is valid if it is in the range 
		// R_EIK_FONTS_START to R_EIK_FONTS_END, otherwise iFont is valid.
		mutable CFont* iFont;
		TInt iId;
		};
public:
	TBool iIsDynamic; // Only put the non-dynamic font here if there is a dynamic font in iFont
	};


/**
 * @internal
 * Do not use
 */
class LafEnv
/** Application environment level LAF functions.

@publishedPartner 
@released */
	{
public:
	/** Creates an EText parser.
	
	@param aIndex Index of parser to retrieve. A LAF can supply multiple parsers, 
	indexed from 0.
	@return EText parser */
	IMPORT_C static MParser* CreateTextParserL(TInt aIndex);
	/** Draws a logical border.
	
	@param aBorder Border specification to draw
	@param aGc Graphics context to which to draw
	@param aRect Drawing rectangle
	@param aBorderColors Colours with which to draw */
	IMPORT_C static void DrawLogicalBorder(const TGulBorder& aBorder,CGraphicsContext& aGc,const TRect& aRect,const TGulBorder::TColors& aBorderColors);
	/** Gets the margins of a specified logical border.
	
	@param aBorder Border specification
	@return Border's margins */
	IMPORT_C static TMargins LogicalBorderMargins(const TGulBorder& aBorder);
	/** Populates an array with a set of system bitmaps.
	
	CEikonEnv calls this to get system bitmaps, and uses the array in subsequent 
	calls to MatchBitmap().
	
	@param aEnv Application's control environment
	@param aBitmaps On return, array of system bitmaps */
	IMPORT_C static void CreateSystemBitmapsL(CCoeEnv& aEnv, CArrayPtrFlat<CFbsBitmap>& aBitmaps);
	/** Populates an array with a set of system fonts.
	
	CEikonEnv calls this to get system fonts, and uses the array in subsequent 
	calls to MatchFont().
	
	A minimum of one font must be created. 
	
	@param aEnv Application's control environment
	@param aFonts On return, array of system fonts */
	IMPORT_C static void CreateSystemFontsL(CCoeEnv& aEnv,CArrayFixFlat<TAknSystemFont>& aFonts);
	/** Gets the nearest match in the specified fonts for a specified logical system 
	font.
	
	The return value must be non-NULL.
	
	@param aFonts Fonts from which to select the match
	@param aLogicalFont The logical font to match
	@return Font that is the best match to aLogicalFont */
	IMPORT_C static const CFont* MatchFont(CArrayFixFlat<TAknSystemFont>& aFonts,const TLogicalFont& aLogicalFont);
	/** Gets the nearest match in the specified bitmaps for a specified system bitmap 
	type.
	
	The desired bitmap is specified by the identifer aBmpUid: for possible UIDs, 
	see KLafUidEikonTexturedVal etc.
	
	The return value must be non-NULL.
	
	@param aSystemBmps Bitmaps from which to select the match
	@param aBmpUid The bitmap type to match
	@return Bitmap that is the best match to aBmpUid */
	IMPORT_C static CFbsBitmap* MatchBitmap(const CArrayPtrFlat<CFbsBitmap>& aSystemBmps, TUid aBmpUid);
	/** Gets the corner of the screen which the busy message should appear in by default 
	on the device. 
	
	@return Default corner
	@see CEikonEnv::BusyMsgL() */
	IMPORT_C static TGulAlignment DefaultBusyMsgCorner();
	/** Tests if the specified key corresponds to the hardware default key.
	
	@param aCharCode Key to test
	@return True if the key is the default */
	IMPORT_C static TBool IsDefaultKey(TUint aCharCode);
	/** Gets the default line spacing used to format text paragraphs.
	
	@return Default line spacing in twips */
	IMPORT_C static TInt DefaultLineSpacingInTwips();
	/** Gets the height of single-line edit control for the system normal font.
	
	@param aLafEnv Environment access
	@return Height of single-line edit control */
	IMPORT_C static TInt EditableControlStandardHeight(const MLafEnv& aLafEnv);
	/** Sets any device-specific font attributes to be applied to the system character 
	formatting layer.
	
	Applications can access the format layer through CEikonEnv::SystemCharFormatLayerL(). 
	This format layer is also used in Edwins.
	
	@param aCharFormat On return, the character formatting to apply
	@param aCharFormatMask On return, the character formatting mask to apply */
	IMPORT_C static void PrepareCharFormatAndMask(TCharFormat& aCharFormat,TCharFormatMask& aCharFormatMask);
	/** Specifies (and creates if necessary) a default directory for documents.
	
	The function is called on application startup. The parameters provided are 
	to allow an implementation to generate a document directory based on the application 
	being launched.
	
	@param aFilePath On return, the default / generated directory path
	@param aAppUid UID of application being launched
	@param aLs Application's session with the Application Architecture server
	@param aEnv Thread's control environment */
	IMPORT_C static void GetDefaultPath(TDes& aFilePath,TUid aAppUid,RApaLsSession& aLs,CCoeEnv& aEnv);
    IMPORT_C static void UpdateSystemFontsL( CArrayFixFlat<TAknSystemFont>& aSystemFonts );
    IMPORT_C static void ReleaseSystemFonts( CArrayFixFlat<TAknSystemFont>& aSystemFonts );

public:
	inline static TInt ShadowHeight();
private:
	/** Defines types of constant setting relevant to LAFs. */
	enum TConstantType
		{
		/** Window shadow height. */
		EShadowHeight
		};
private:
	/** Gets the value for a specified constant setting.
	
	@param aConstant Type of constant setting to get
	@return Value for the constant setting */
	IMPORT_C static TInt Constant(TConstantType aConstant);

	//this function should only ever be called from within MatchFont. Don' use it elsewhere
	//as a means of getting Fonts.
	static const CFont* GetRightFontFromCategory(const TLogicalFont::TFontCategory aCategory);
	
	static CFont* GetFontFromSystemArray(CArrayFixFlat<TAknSystemFont>& aSystemFonts, TInt aIdToBeMatched);
	};

// identifiers for legacy system fonts

/** UID for the system "normal" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidNormalFontVal		0x10005F02

/** UID for the system "title" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidTitleFontVal			0x10005F03

/** UID for the system "annotation" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidAnnotationFontVal	0x10005F04

/** UID for the system "legend" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidLegendFontVal		0x10005F05

/** UID for the system "symbol" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidSymbolFontVal		0x10005F06

/** UID for the system "dense" font.

@see TLogicalFont::iFontId 
@publishedPartner 
@released */
#define KLafUidDenseFontVal			0x10005F07

// identifiers for legacy system bitmaps
/** UID for a textured block system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonTexturedVal		0x100048F4

/** UID for a gray block system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonGrayVal			0x100048F5

/** UID for a horizontal option button system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonOptiVal			0x100048F6

/** UID for a highlighted horizontal option button system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonOptihVal		0x100048F7

/** UID for a horizontal option button mask system bitmap.

@see LafEnv::MatchBitmap() 
@publishedPartner 
@released */
#define KLafUidEikonOptimVal		0x100048F8

// Inlines

inline TInt LafEnv::ShadowHeight()
/** Gets the height of shadows to apply to windows. 

@return Shadow height. */
	{//static
	return Constant(EShadowHeight);
	}

#endif
