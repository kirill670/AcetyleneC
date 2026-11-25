// <mead:applicationname/>.h
//


#ifndef __<mead:constantname/>_H
#define __<mead:constantname/>_H

#include <coeccntx.h>

#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#include <eikdoc.h>
#include <eikmenup.h>

#include <eikon.hrh>

#include <<mead:applicationname/>.rsg>
#include "<mead:applicationname/>.hrh"
#include "<mead:applicationname/>eng.h"


const TUid KUid<mead:variablename/> = { <mead:guiuid/> };


//
// class C<mead:classname/>AppView
//

class C<mead:classname/>AppView : public CCoeControl, public MCoeControlBrushContext
	{
  public:
	void ConstructL(const TRect& aRect, C<mead:classname/>Eng* aModel);
  private: // from CCoeControl
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	void Draw(const TRect& /*aRect*/) const;
  private:
	C<mead:classname/>Eng *iModel;
	};


//
// C<mead:classname/>AppUi
//

class C<mead:classname/>AppUi : public CEikAppUi
	{
  public:
	void ConstructL();
	~C<mead:classname/>AppUi();
  private: // from CEikAppUi
	void HandleCommandL(TInt aCommand);
  private:
	C<mead:classname/>AppView* iAppView;
	C<mead:classname/>Eng *iModel;
	};


//
// C<mead:classname/>Document
//

class C<mead:classname/>Document : public CEikDocument
	{
  public:
	// construct/destruct
	C<mead:classname/>Document(CEikApplication& aApp);
	~C<mead:classname/>Document();
	static C<mead:classname/>Document* NewL(CEikApplication& aApp);
	void ConstructL();
	void ResetModelL();
	C<mead:classname/>Eng* Model() {return iModel;}
  private: // from CEikDocument
	CEikAppUi* CreateAppUiL();
	C<mead:classname/>Eng* iModel;
	};


//
// C<mead:classname/>Application
//

class C<mead:classname/>Application : public CEikApplication
	{
  private: // from CApaApplication
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	};

#endif
