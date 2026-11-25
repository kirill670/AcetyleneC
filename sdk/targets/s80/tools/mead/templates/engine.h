// <mead:applicationname/>eng.h
//


#ifndef __<mead:constantname/>ENG_H
#define __<mead:constantname/>ENG_H

#include <e32base.h>
#include <e32std.h>


class C<mead:classname/>Eng : public CBase
	{
public:
	IMPORT_C TPoint Coords();
	IMPORT_C void SetCoords(TPoint);
	IMPORT_C void Reset();

private:
	TPoint iCoords;
	};

#endif
