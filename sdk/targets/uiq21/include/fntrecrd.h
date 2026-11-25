// Header FNTRECRD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__FNTRECRD_H__)
#define __FNTRECRD_H__

#include "lexical.h"
#include "lst.h"
#include "record.h"
#include "strng.h"
#include "uid.h"

const boolean PostureUpright=0;
const boolean PostureItalic=1;

const boolean StrokeWeightNormal=0;
const boolean StrokeWeightBold=1;

class CharacterMetrics					 
	{
public:
	CharacterMetrics();
	void Externalize(ostream& out);
public:
	uint16 iBitmapOffset;  // restricts bitmap to 64k
	chardim iAscentInPixels;
	chardim iHeightInPixels;
	chardim iLeftAdjustInPixels;
	chardim iMoveInPixels;
	chardim iRightAdjustInPixels;
	chardim iSpare;
	};

class Characters
	{
public:
	void Externalize(ostream& out);
	ObjectList<CharacterMetrics*> iCharacterMetricsList;
	~Characters();
public:
	streampos iStreamId;
	};

class ByteList
	{
public:
	ByteList();
	void AddBit(char aBit);
	void NewByte();
	int Length() const;
	void Externalize(ostream& out);
private:
	String iString;
	char iOffset;
	};

class CharactersBitmap : public Record
	{
public:
	void Externalize(ostream& out);
public:
	ByteList iByteList;
	streampos iStreamId;
	};

class BitmapCodeSection
	{
public:
	void Externalize(ostream& out);
	void ExternalizeComponents(ostream& out);
public:
	uint16 iStart;
	uint16 iEnd;
	Characters iCharacters;
	CharactersBitmap iCharactersBitmap;
	};	

class FontBitmap : public Record
	{
public:
	FontBitmap();
	void Externalize(ostream& out);
	void ExternalizeComponents(ostream& out);
	~FontBitmap();	
public:
	uid iUid;
	boolean iPosture;
	boolean iStrokeWeight;
	boolean iIsProportional;
	chardim iCellHeightInPixels;
	chardim iAscentInPixels;
	chardim iMaxCharWidthInPixels;
	chardim iMaxNormalCharWidthInPixels;
	int32 iBitmapEncoding;
	ObjectList<BitmapCodeSection*> iCodeSectionList;
	};
 
class TypefaceFontBitmap
	{
public:
	TypefaceFontBitmap(FontBitmap* aFontBitmap);
	TypefaceFontBitmap(uid aFontBitmapUid);
	void Externalize(ostream& out);	
public:
	FontBitmap* iFontBitmap;
	uid iFontBitmapUid;
	char iWidthFactor;
	char iHeightFactor;
	};

class FntTypeface : public Record, public Typeface
	{
public:
	void Externalize(ostream& out);	
public:
	ObjectList<TypefaceFontBitmap*> iTypefaceFontBitmapList;
	};

class FontStoreFile : public Record
	{
public:
	FontStoreFile();
	void AddTypeface(FntTypeface* aTypeface);
	void AddFontBitmap(FontBitmap* aFontBitmap);
	void Externalize(ostream& out);
private:
	void ExternalizeHeader(ostream& out);
	void ExternalizeComponents(ostream& out);
public:
	uid iCollectionUid;
	int32 iKPixelAspectRatio;
	ObjectList<String*> iCopyrightInfo;
private:
	streampos iDataStreamId;
	RecordList iFontBitmapList;
	RecordList iTypefaceList;
	};

class FontStore
	{
public:
	boolean Store(const String& aFilename);
	void AddFontStoreFile(FontStoreFile* aFontStoreFile);
	void AddFontBitmap(FontBitmap* aFontBitmap);
	Record* FindFontBitmap(String& aLabel);
	void AddTypeface(FntTypeface* aTypeface);
	Record* FindTypeface(String& aLabel);
	FontStore();
	~FontStore();
private:
	FontStoreFile* iFontStoreFile;
	RecordList iFontBitmapList;
	RecordList iTypefaceList;
	};

#endif
	 
