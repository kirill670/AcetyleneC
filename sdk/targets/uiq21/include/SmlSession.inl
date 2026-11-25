//
// SMLSession.INL
//

#include <ecom.h>

inline CSmlSession* CSmlSession::NewL(const TUid& aImplementationUid)
	{

	TUid tempKey;
	TAny* any = REComSession::CreateImplementationL(aImplementationUid, tempKey);
	CSmlSession* object = REINTERPRET_CAST(CSmlSession*, any);
	object->iDtorKey = tempKey;
	return object;
	}

inline CSmlSession::~CSmlSession()
	{
	REComSession::DestroyedImplementation(iDtorKey);
	}

inline CSmlSession::CSmlSession() : CActive(0)
	{}

inline void CSmlSession::RunL()
	{}

inline void CSmlSession::DoCancel()
	{}
