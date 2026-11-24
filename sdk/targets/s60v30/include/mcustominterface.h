#ifndef __MCUSTOMINTERFACE_H
#define __MCUSTOMINTERFACE_H

#include <e32std.h>

class MCustomInterface 
	{
public:
	virtual TAny* CustomInterface(TUid aInterfaceId) = 0;

	};

#endif
