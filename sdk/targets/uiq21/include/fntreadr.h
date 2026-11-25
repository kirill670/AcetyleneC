// Header FNTREADR.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__FNTREADR_H__)
#define __FNTREADR_H__

#include "fntrecrd.h"
#include "lst.h"
#include "reader.h"

const uint16 KMaxSizeCodeSectionBitmap=0xFFFF;
const int KMaxBitmapWidth=0x7f;
const int KMaxBitmapHeight=0x7f;
const int KNumberOfBitsInByte=8; 

const int KLowestPermittedCharacterEncoding=0x0000;
const int KHighestPermittedCharacterEncoding=0xffff;

const int KMaxNumberRepeatedLines=15;  // maximum number of repeated lines in font compiler

// Resource identifiers
const String IdentFontBitmap("FontBitmap");
const String IdentSTARTFONT("STARTFONT");
const String IdentTypeface("Typeface");
const String IdentFontStoreFile("FontStoreFile");

// Char identifiers
const String IdentAdjust("Adjust");
const String IdentEndChar("EndChar");

// Codesection identifiers
const String IdentEndCodeSection("EndCodeSection");
const String IdentChar("Char");

// Fontbitmap identifiers
const String IdentEndFontBitmap("EndFontBitmap");
const String IdentUid("Uid");
const String IdentBold("Bold");
const String IdentItalic("Italic");
const String IdentFontBitmapProportional("Proportional");
const String IdentCellHeight("CellHeight");
const String IdentAscent("Ascent");
const String IdentMaxNormalCharWidth("MaxNormalCharWidth");
const String IdentBitmapEncoding("BitmapEncoding");
const String IdentCodeSection("CodeSection");
const String IdentMaxConsecutiveFillChars("MaxConsecutiveFillChars"); 

// BDF CHAR identifiers
const String IdentBDFFileHeader("STARTFONT");
const String IdentBDFComment("COMMENT");
const String IdentBDFContentVersion("CONTENTVERSION");
const String IdentBDFFontBitmap("FONT"); 
const String IdentBDFPointSize("SIZE");
const String IdentBDFFontDesignBox("FONTBOUNDINGBOX");
const String IdentBDFWritingDirection("METRICSSET");
const String IdentBDFStartProperties("STARTPROPERTIES");	
const String IdentBDFPropertyUid("UID");
const String IdentBDFPropertyBold("BOLD");
const String IdentBDFPropertyItalic("ITALIC");
const String IdentBDFPropertyFontAscent("FONTASCENT");
const String IdentBDFPropertyFontDescent("FONTDESCENT");
const String IdentBDFPropertyMaxNormalCharWidth("MAXNORMALCHARWIDTH");
const String IdentBDFPropertyMaxConsecutiveFillChars("MAXCONSECUTIVEFILLCHARS");
const String IdentBDFEndProperties("ENDPROPERTIES");	
const String IdentBDFNumChars("CHARS"); // To be used as sanity check on BDF files
const String IdentBDFCharLabel("STARTCHAR");
const String IdentBDFChar("ENCODING");
const String IdentBDFCursorMove("DWIDTH");
const String IdentBDFBitmapSizeAndDisplacement("BBX");
const String IdentBDFStartBitmap("BITMAP");
const String IdentBDFEndChar("ENDCHAR");
const String IdentBDFEndFontBitmap("ENDFONT");


// Typeface identifiers
const String IdentEndTypeface("EndTypeface");
const String IdentName("Name");
const String IdentTypefaceProportional("Proportional");
const String IdentSerif("Serif");
const String IdentSymbol("Symbol");
const String IdentFontBitmaps("FontBitmaps");
const String IdentWidthFactor("WidthFactor");
const String IdentHeightFactor("HeightFactor");
const String IdentEndFontBitmaps("EndFontBitmaps");

// Fontstorefile identifiers
const String IdentEndFontStoreFile("EndFontStoreFile");
const String IdentFilename("Filename");
const String IdentCollectionUid("CollectionUid");
const String IdentKPixelAspectRatio("KPixelAspectRatio");
const String IdentTypefaces("Typefaces");
const String IdentEndTypefaces("EndTypefaces");
const String IdentExtraFontBitmaps("FontBitmaps");
const String IdentEndExtraFontBitmaps("EndFontBitmaps");
const String IdentCopyrightInfo("CopyrightInfo");
const String IdentEndCopyrightInfo("EndCopyrightInfo");

class FontReader : public Reader
	{
public:
	enum TReadFileFormat
		{
		EPsionGDFFormat,
		EBDFFormat
		};
public:
	FontReader();
	boolean Read(const String& aFilename);
	boolean ReadCharacter(int aCode);
	boolean ReadBDFCharacter(int aCode);
	boolean ReadCodeSection(int aCode);
	boolean ReadBDFChars(int aNumberCharsInFile,int aMaxConsecutiveFillChars);
	boolean ReadFontBitmap();
	boolean ReadBDFFontBitmap();
	boolean ReadTypeface();
	boolean ReadFontStoreFile();
	int Store(const String& aFilename);
    boolean CharLine(String& aCharLine);
private:
	void ErrorIdentifierExpected(const String& aIdentifier);
	boolean CompareBitmapLines(int aLine1,int aLine2);
	boolean BitmapLineEmpty(int aLine);
	boolean BitmapColumnEmpty(int aColumn);
	void WriteFillCharacter(int aCode);
private:
	FontStore iFontStore;
	FontStoreFile* iFontStoreFile;
	CharacterMetrics* iCharacterMetrics;
	BitmapCodeSection* iCodeSection;
	FontBitmap* iFontBitmap;
	FntTypeface* iTypeface;
	TReadFileFormat iReadFileFormat;
	int iBitArray[KMaxBitmapWidth][KMaxBitmapHeight];
	int iBitmapWidth;
	int iBitmapHeight;
	int iDefaultXMoveInPixels;
	int iDefaultYMoveInPixels;
	};

#endif
