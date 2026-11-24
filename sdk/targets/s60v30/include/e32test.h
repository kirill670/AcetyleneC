// e32\include\e32test.h
//
// Copyright (c) 1994-2001 Symbian Ltd. All rights reserved.
//

/**	@file e32test.h
	@publishedAll
	@released
*/

#ifndef __E32TEST_H__
#define __E32TEST_H__
#include <e32std.h>
#include <e32base.h>
#include <e32cons.h>
#include <e32ver.h>
#include <e32kpan.h>



/**
Test console.

The class creates a console window to which test results can be logged
through the various overloads of the operator().
*/
class RTest
	{
public:
	IMPORT_C RTest(const TDesC &aTitle,TInt aThrowaway,const TText* anOtherThrowaway);
	IMPORT_C RTest(const TDesC &aTitle,TInt aThrowaway);
	IMPORT_C RTest(const TDesC &aTitle);
	IMPORT_C void Close();
	IMPORT_C void Title();
	IMPORT_C void Start(const TDesC &aHeading);
	IMPORT_C void Next(const TDesC &aHeading);
	IMPORT_C void End();
	IMPORT_C void operator()(TInt aResult,TInt aLineNum,const TText* aFileName);
	IMPORT_C void operator()(TInt aResult,TInt aLineNum);
	IMPORT_C void operator()(TInt aResult);
	IMPORT_C void Panic(TInt anError,TRefByValue<const TDesC> aFmt,...);
	IMPORT_C void Panic(TRefByValue<const TDesC> aFmt,...);
	IMPORT_C void Printf(TRefByValue<const TDesC> aFmt,...);
	IMPORT_C TKeyCode Getch();
	inline static const TAny* String(TInt aSel,const TText8 *aBuf1,const TText16 *aBuf2);
	inline CConsoleBase* Console() const;
	inline void SetConsole(CConsoleBase* aConsole);
	inline TBool Logged() const;
	inline void SetLogged(TBool aToLog);
protected:
	void CheckConsoleCreated();
	void DisplayLevel();
	inline void Push();
	inline void Pop();
private:
	enum {EMaxStack=0x100,EMaxBuffer=0x100};
private:
	TInt	iTest;
	TInt	iCheck;
	TInt	iLevel;
	TBool	iLogging;
	CConsoleBase *iConsole;
	TBuf<0x40> iTitle;
	TInt iStack[EMaxStack];
	TText iBuf[EMaxBuffer];
	};




/**
Gets the console.

@return A pointer to the console object.
*/
inline CConsoleBase* RTest::Console() const
	{ return(iConsole); }

	
	
	
/**
Utility function that returns a pointer to the specified TText8* argument
or the TText16* argument depending on the value of the aSel argument.

@param aSel  An integer containing the size of a TText8 type or TText16 type.
@param aBuf1 A pointer to 8-bit text.
@param aBuf2 A pointer to 16-bit text.

@return A pointer to aBuf1, if the value of aSel is the size of a TText8 type,
        otherwise a pointer to aBuf2.
*/	
inline const TAny *RTest::String(TInt aSel,const TText8 *aBuf1,const TText16 *aBuf2)
	{ return(aSel == sizeof(TText8) ? (TAny *)aBuf1 : (TAny *)aBuf2); }



/**
@internalComponent
*/
inline void RTest::Push()
	{ iStack[iLevel++] = iTest; iTest = 0; }



/**
@internalComponent
*/
inline void RTest::Pop()
	{ iTest = iStack[--iLevel]; }




/**
Sets the console.

@param aConsole A pointer to the console object to be used.
*/	
inline void RTest::SetConsole(CConsoleBase* aConsole)
    { iConsole = aConsole; }




/**
Tests whether the logging flag is set.

If the logging flag is set, console output is also written to
the debug output as represented by a RDebug object.

@return True, if the logging flag is set, false otherwise.
*/	
inline TBool RTest::Logged() const
	{ return(iLogging); }




/**
Sets the logging flag.

If the logging flag is set, console output is also written to
the debug output as represented by a RDebug object.

@param aToLog ETrue, if the logging flag is to be set, EFalse, otherwise.
*/	
inline void RTest::SetLogged(TBool aToLog)
	{ iLogging = aToLog; }




// test equivalent of _L
/**
@internalComponent
*/
#define _TL(a) (S*)RTest::String(sizeof(S),(TText8*)a,(TText16*)L ## a) 

// the next two, slightly confusing, macros are necessary in order
// to enable proper string merging with certain compilers.

/**
@internalComponent
*/
#define __test(x,l,f) test(x,l,_S(f))

/**
@internalComponent
*/
#define test(x) __test(x,__LINE__,__FILE__)

#endif

