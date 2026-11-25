// EIKHGDLG.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKHGDLG_H__)
#define __EIKHGDLG_H__

#if !defined(__EIKDIALG_H__)
#include <eikdialg.h>
#endif

#if !defined(__COECNTRL_H__)
#include <coecntrl.h>
#endif

#if !defined(__EIKENV_H__)
#include <eikenv.h>
#endif

//
//	class CEikDebugKeys
//

class CEikDebugKeys : public CCoeControl, public MEikDebugKeys
	{
private: // from MEikDebugKeys
	void ConstructL();
	void Release();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // framework
	virtual TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private:
	friend class CEikonEnv;
//	friend class CDebugKeysDlg;
//	friend class CDebugKeysAppUi;
	TInt iHeapFailRate;
	TInt iFailType;
	TInt iWservHeapFailRate;
	TInt iWservFailType;
	TInt iFileFailRate;
	TBool iFileFailChbx;
	TBool iVerbose;
	};


//
// class CEikHeapFailDialog
//

class CEikHeapFailDialog : public CEikDialog
	{
public:
	enum TFailType {EHeapFailOff,EFailRandom,EFailDeterministic,EFailFileError};
	inline CEikHeapFailDialog(TInt* aHeapFailRate,TInt* aFailType,TInt* aWservHeapFailRate,TInt* aWservFailType,TInt* aFileFailRate,TInt* aFileFailChbx) :iHeapFailRate(aHeapFailRate),iFailType(aFailType),iWservHeapFailRate(aWservHeapFailRate),iWservFailType(aWservFailType),iFileFailRate(aFileFailRate),iFileFailChbx(aFileFailChbx) {}
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private: // from CEikDialog
	void PreLayoutDynInitL();
	TBool OkToExitL(TInt aKeyCode);
private: // from CCoeControl
	IMPORT_C void Reserved_2();
private: // from CEikDialog
	IMPORT_C void CreateButtonGroupContainerL(TInt aResourceId);
	IMPORT_C void Reserved_4();
private:
	TInt* iHeapFailRate;
	TInt* iFailType;
	TInt* iWservHeapFailRate;
	TInt* iWservFailType;
	TInt* iFileFailRate;
	TInt* iFileFailChbx;
	};
//
//	class CEikDebugWin
//

class CEikDebugWin : public CCoeControl
    {
public:
    void ConstructL();
protected: //from CCoeControl
	IMPORT_C void WriteInternalStateL(RWriteStream& aWriteStream) const;
private:
	void Draw(const TRect& aRect) const;
private: // from CCoeControl
	IMPORT_C void Reserved_2();
    };


#endif
