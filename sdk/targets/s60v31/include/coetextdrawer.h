// COETEXTDRAWER.H
//
// Copyright (c) 1997-2005 Symbian Software Ltd.  All rights reserved.
//

#ifndef __COETEXTDRAWER_H__
#define __COETEXTDRAWER_H__

#include <gulutil.h>	 
#include <gulalign.h>	 
#include <biditext.h>
#include <coemop.h>

//
// TEXT DRAWER CODE
//

// forward declarations
class CCoeTextDrawerBase;
class TCoeTextTypeAdaptor;

/**
XCoeTextDrawer: This class serves as a handle to the class CCoeTextDrawerBase. Specifically 
it enables access to the CCoeTextDrawerBase's private DrawText() method. 
The class also manages the life of the heap allocated CCoeTextDrawerBase (deleting it or resetting 
it depending on whether the object is reusable or not).
XCoeTextDrawer shall be allocated on the stack in the control's Draw() method and initialized 
with a heap allocated CCoeTextDrawerBase object fetched from the control's own skin, or from its 
parent or background through the CCoeControl::TextDrawer() method. 

Note that an overload of the '->' operator is implemented in this class.
Invoking -> on an XCoeTextDrawer object will return the iTextDrawer data member which is a pointer
to a CCoeTextDrawerBase object. Using this the accessor and set methods in CCoeTextDrawerBase can be
invoked. For example issuing xCoeTextDrawerObject -> Margins(); will invoke
(iTextDrawer*).Margins();

@publishedAll
@released
*/
class XCoeTextDrawer
	{
public:
	IMPORT_C XCoeTextDrawer(CCoeTextDrawerBase& aTextDrawer);
	IMPORT_C ~XCoeTextDrawer();
	
	IMPORT_C void operator=(CCoeTextDrawerBase& aTextDrawer);
	IMPORT_C CCoeTextDrawerBase *operator ->();
	
	IMPORT_C void DrawText(CGraphicsContext& aGc, const TBidiText& aText, const TRect& aTextRect, const CFont& aFont) const;
	IMPORT_C void DrawDisplayOrderedText(CGraphicsContext& aGc, const TDesC& aText, const TRect& aTextRect, const CFont& aFont) const;
	
	IMPORT_C TRect ClipRect() const;
	IMPORT_C void SetClipRect(const TRect& aClipRect);
private:
	XCoeTextDrawer(XCoeTextDrawer& aTextDrawer);  
private:	
	CCoeTextDrawerBase* iTextDrawer;
	TRect iClipRect;
	};


// forward declaration
class CCoeTextDrawerBaseExt;

/**
CCoeTextDrawerBase: This is the base class for all text drawers implementing different text effects 
(for example shadow or glowing/outlined text). The object can be created and deleted each time 
it's used, or Reset() and reused if it IsReusable().

The pure virtual DrawText() method is private. This ensures that the object is used through 
the XCoeTextDrawer (that manages its life). 

Note also that the accessor and set methods should be used via the owning XCoeTextDrawer object. The
-> operator is overridden in XCoeTextDrawer for this purpose.
Invoking -> on an XCoeTextDrawer object will return the iTextDrawer data member which is a pointer
to a CCoeTextDrawerBase object. Using this the accessor and set methods in CCoeTextDrawerBase can be
invoked. For example issuing xCoeTextDrawerObject -> Margins(); will invoke
(iTextDrawer*).Margins();

@publishedAll
@released
*/
class CCoeTextDrawerBase : public CBase, public MObjectProvider
	{
	friend class XCoeTextDrawer;   
public:
	IMPORT_C ~CCoeTextDrawerBase();
	/**
	This method is intended to be called from the destructor of the corresponding
	XCoeTextDrawer handle. It is provided for the case where the text drawer object
	is to be left available for re-use rather than deleted.
	*/
	IMPORT_C virtual void Reset();
		
	/**
	This method returns the color used by the CCoeTextDrawer to draw text.
	@return The color used to draw text.
	*/
	virtual TRgb TextColor() const = 0;
	/**
	This method sets the color to use to draw text.
	@param aColor The color to use to draw text.
	*/
	virtual void SetTextColor(TRgb aColor) = 0;
 
	IMPORT_C TGulAlignment Alignment() const;
	IMPORT_C void SetAlignment(const TGulAlignment& aAlignment);
	
	IMPORT_C TMargins8 Margins() const;
	IMPORT_C void SetMargins(const TMargins8& aMargins);
	
	IMPORT_C TInt LineGapInPixels() const;
	IMPORT_C void SetLineGapInPixels(TInt aLineGapInPixels);
	
 	IMPORT_C TBool IsReusable() const;
	IMPORT_C void SetReusable(TBool aIsReusable);	
protected:
 	IMPORT_C CCoeTextDrawerBase();
	IMPORT_C TInt Construct();
private:  
	virtual void DrawText(CGraphicsContext& aGc, const TCoeTextTypeAdaptor& aText, const CFont& aFont, 
							const TRect& aTextRect, const TRect& aClipRect) const = 0;

public:
	IMPORT_C virtual TMargins8 EffectMargins();

private:
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved2();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved3();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved4();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved5();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved6();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved7();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved8();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved9();
	IMPORT_C virtual void CCoeTextDrawerBase_Reserved10();
 private:
	TBool iIsReusable;	 
	TGulAlignment iAlignment;
	TMargins8 iMargins;
	TInt iLineGap;
	CCoeTextDrawerBaseExt* iExtension;
	};


/**
TCoeTextTypeAdaptor: The purpose of this class is to allow the XCoeTextDrawer to
draw text that is in the form of a TBidiText object as well as pre-reordered 
text in plain descriptors. 
(The descriptor text is especially useful when using the XCoeTextDrawer together 
with the FORM component). This removes the need to implement two versions of the 
DrawText() method.

@publishedAll
@released
*/
class TCoeTextTypeAdaptor
	{
public:
	IMPORT_C TCoeTextTypeAdaptor(const TDesC& aText);		// text separated with '\n'
	IMPORT_C TCoeTextTypeAdaptor(const TBidiText& aText);		// TBidiText object
	IMPORT_C TInt NumberOfLines() const;
	IMPORT_C TPtrC LineOfText(TInt aLineNumber, TInt& aWidthInPixels, const CFont& aFont) const;	
	IMPORT_C TBool HasRightToLeftDirectionality() const;
private:
	enum TTextType
		{
		ENewlineSeparated,
		EBidiText
		};
	const TAny* iText;
	TTextType iTextType;
	};


/**	
CCoePlainTextDrawer: This class is the default text drawer that can be used 
if no other (device specific) text drawers has been added to the system. 

@publishedAll
@released
*/
class CCoePlainTextDrawer : public CCoeTextDrawerBase
	{
public:
	DECLARE_TYPE_ID(0x1020831A)
public:
	IMPORT_C static CCoePlainTextDrawer* New(TRgb aTextColor);
	IMPORT_C TRgb TextColor() const;
	IMPORT_C void SetTextColor(TRgb aTextColor);
protected: // from MObjectProvider
	IMPORT_C virtual TTypeUid::Ptr MopSupplyObject(TTypeUid aId);
private:  
	void DrawText(CGraphicsContext& aGc, const TCoeTextTypeAdaptor& aText, const CFont& aFont, 
					const TRect& aTextRect, const TRect& aClipRect) const;
	void Reset();	
	CCoePlainTextDrawer(TRgb aTextColor);
	IMPORT_C TInt Construct();	
private:
	TRgb iTextColor;
	};
		
		
// __COETEXTDRAWER_H__
#endif
