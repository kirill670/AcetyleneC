//
// SMLDBA.INL
//

#include <ECom.h>
inline CSmlDbAdapter* CSmlDbAdapter::NewL(const TUid& aImplementationUid, CSmlDataStore* aDataStore)
	{

	TAny* any = REComSession::CreateImplementationL(aImplementationUid, _FOFF(CSmlDbAdapter, iDtorKey), aDataStore);
	CSmlDbAdapter* object = REINTERPRET_CAST(CSmlDbAdapter*, any);
	return object;
	}

inline CSmlDbAdapter::~CSmlDbAdapter()
	{
	REComSession::DestroyedImplementation(iDtorKey);
	}