// EIKMSG.H
//
// Copyright (c) 1997-2004 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKMSG_H__)
#define __EIKMSG_H__

#include <clock.h>
#include <gulalign.h>

class CCoeControl;
class CEikonEnv;
class RWindowGroup;

class CEikMsgWin : public CBase
/** Base class providing functions to construct and display an information message. 

@publishedAll
@released */
	{
protected:
	IMPORT_C CEikMsgWin(CEikonEnv& aEikonEnv);
public:
	IMPORT_C void ConstructL(RWindowGroup& aWindowGroup);
	IMPORT_C virtual ~CEikMsgWin();
	IMPORT_C void StartDisplay(const TDesC& aText, TGulAlignment aCorner);
	IMPORT_C void CancelDisplay();
protected:
	TDes& PrepareDisplay(TDes& aText, TGulAlignment aCorner);
private:
	virtual void DoStartDisplay(const TDesC& aText)=0;
protected:
	/** A CEikonEnv*, which all applications have. This is required for construction 
	of a CEikMsgWin as it provides access to services which the message window 
	needs, the window server session for example. */
	CEikonEnv& iEikonEnv_; // the underscore is to prevent a name clash with the iEikonEnv #define
	/** An empty control required for construction of a blank window. This defines 
	a handle back to the client side object, which is only required if you need 
	to later initiate client side drawing. */
	CCoeControl* iDummy;
	/** The window in which the message will be drawn. */
	RBlankWindow* iBlankWindow;
	/** An RAnim derived class, which is responsible for interacting with server side 
	classes to provide the message window's animation on the screen. It is constructed 
	by passing in the RWindowBase which it will use to draw its contents to, and 
	also a handle to an animation DLL, which provides the animation functionality. */
	RMessageWindow* iMessageWindow;
private:
	TInt iSpare;
	};

/**
@publishedAll
@released
*/
const TInt KEikInfoMsgMaxLen=RMessageWindow::EMaxTextLength;

/** Specifies the maximum length of the message buffer. 

@publishedAll
@released */
typedef TBuf<KEikInfoMsgMaxLen> TEikInfoMsgBuf;


class CEikInfoMsgWin : public CEikMsgWin
/** Enables construction of an information message window. 

@publishedAll 
@released */
	{
public:
	IMPORT_C CEikInfoMsgWin(CEikonEnv& aEikonEnv);
	IMPORT_C void StartDisplaySpecifyingDuration(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aDuration);
private:
	virtual void DoStartDisplay(const TDesC& aText);
	};

//

/**
@publishedAll
@released
*/
const TInt KEikBusyMsgMaxLen=RMessageWindow::EMaxTextLength;

/**
@publishedAll
@released
*/
typedef TBuf<KEikBusyMsgMaxLen> TEikBusyMsgBuf;


class CEikBusyMsgWin : public CEikMsgWin
/** 
@publishedAll 
@released
*/
	{
public:
	IMPORT_C CEikBusyMsgWin(CEikonEnv& aEikonEnv);
	IMPORT_C void StartDisplaySpecifyingInitialDelay(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aInitialDelay);
private:
	virtual void DoStartDisplay(const TDesC& aText);
private:
	TTimeIntervalMicroSeconds32 iInitialDelay;
	};

#endif

