// <mead:applicationname/>eng.cpp
//


#include "<mead:applicationname/>eng.h"


EXPORT_C TPoint C<mead:classname/>Eng::Coords()
	{
	return iCoords;
	}

EXPORT_C void C<mead:classname/>Eng::SetCoords(TPoint aCoords)
	{
	iCoords=aCoords;
	}

EXPORT_C void C<mead:classname/>Eng::Reset()
	{
	iCoords.SetXY(50,50);
	}

// requirement for E32 DLLs
EXPORT_C TInt E32Dll(TDllReason)
	{
	return 0;
	}
