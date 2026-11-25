// <mead:applicationname/>.cpp
//


#include "<mead:applicationname/>.h"


//
// EXPORTed functions
//

EXPORT_C CApaApplication* NewApplication()
	{
	return new C<mead:classname/>Application;
	}

GLDEF_C TInt E32Dll(TDllReason)
	{
	return KErrNone;
	}


////////////////////////////////////////////////////////////////
//
// Application class, C<mead:classname/>Application
//
////////////////////////////////////////////////////////////////

TUid C<mead:classname/>Application::AppDllUid() const
	{
	return KUid<mead:variablename/>;
	}

CApaDocument* C<mead:classname/>Application::CreateDocumentL()
	{
	// Construct the document using its NewL() function, rather 
	// than using new(ELeave), because it requires two-phase
	// construction.
	return C<mead:classname/>Document::NewL(*this);
	}


////////////////////////////////////////////////////////////////
//
// Document class, C<mead:classname/>Document
//
////////////////////////////////////////////////////////////////

// C++ constructor
C<mead:classname/>Document::C<mead:classname/>Document(CEikApplication& aApp)
		: CEikDocument(aApp)
	{
	}

// The document requires two-phase construction because it
// owns the model (C<mead:classname/>Eng) and therefore has to allocate 
// memory for it.
C<mead:classname/>Document* C<mead:classname/>Document::NewL(CEikApplication& aApp)
	{
	C<mead:classname/>Document* self = new (ELeave) C<mead:classname/>Document(aApp);
	CleanupStack::PushL(self);
	self->ConstructL();
	self->ResetModelL();
	CleanupStack::Pop();
	return self;
	}

void C<mead:classname/>Document::ConstructL()
	{
	iModel = new (ELeave) C<mead:classname/>Eng;
	}

// All resources allocated in ConstructL() must be released in 
// the destructor.
C<mead:classname/>Document::~C<mead:classname/>Document()
	{
	delete iModel;
	}

void C<mead:classname/>Document::ResetModelL()
	{
	iModel->Reset();
	}

CEikAppUi* C<mead:classname/>Document::CreateAppUiL()
	{
    return new(ELeave) C<mead:classname/>AppUi;
	}


////////////////////////////////////////////////////////////////
//
// App UI class, C<mead:classname/>AppUi
//
////////////////////////////////////////////////////////////////

void C<mead:classname/>AppUi::ConstructL()
    {
    BaseConstructL();
	iModel = ((C<mead:classname/>Document*)iDocument)->Model();
    iAppView = new(ELeave) C<mead:classname/>AppView;
    iAppView->ConstructL(ClientRect(), iModel);
    }

C<mead:classname/>AppUi::~C<mead:classname/>AppUi()
	{
    delete iAppView;
	}

void C<mead:classname/>AppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
	case E<mead:variablename/>Cmd1:
		iEikonEnv->InfoMsg(R_<mead:constantname/>_CMD_1);
		break;
	case E<mead:variablename/>Cmd2:
		iEikonEnv->InfoMsg(R_<mead:constantname/>_CMD_2);
		break;
	case E<mead:variablename/>Cmd3:
		iEikonEnv->InfoMsg(R_<mead:constantname/>_CMD_3);
		break;
	case E<mead:variablename/>Cmd4:
		iEikonEnv->InfoMsg(R_<mead:constantname/>_CMD_4);
		break;
	case EEikCmdExit:
		Exit();
		break;
		}
	}


////////////////////////////////////////////////////////////////
//
// Application view class, C<mead:classname/>AppView
//
////////////////////////////////////////////////////////////////

void C<mead:classname/>AppView::ConstructL(const TRect& aRect, C<mead:classname/>Eng* aModel)
    {
	iModel = aModel;
    CreateWindowL();
    SetRect(aRect);
    ActivateL();
    }

void C<mead:classname/>AppView::Draw(const TRect& /*aRect*/) const
	{
	CWindowGc& gc = SystemGc();
	// Clear the application view
	gc.Clear();
	// Draw a rectangle round the edge of the application view.
	TRect drawRect=Rect();
	drawRect.Shrink(10,10);
	gc.DrawRect(drawRect);
	// Set the pen size large so the dot is drawn large.
	gc.SetPenSize(TSize(10,10));
	// Draw a dot on the screen at the co-ordinates stored in the model.
	gc.Plot(iModel->Coords());
	}

// This function is called when the user taps the screen in the application view.
void C<mead:classname/>AppView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
	{
	// Update the co-ordinates in the model to the position at which the
	// pointer event occurred.
	iModel->SetCoords(aPointerEvent.iPosition);
	// DrawNow() results in a call to Draw().
	DrawNow();
	}
