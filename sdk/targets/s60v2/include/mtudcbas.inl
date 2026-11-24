// MTUDCBAS.INL
//
// Copyright (C) Symbian Ltd 1998
//

inline TUid CBaseMtmUiData::Type() const
/** Gets the Type UID of the message type associated with the UI Data MTM.

@return UID of the message type associated with the MTM */
	{ 
	return iRegisteredMtmDll.MtmTypeUid();
	}

inline const CArrayFix<CBaseMtmUiData::TMtmUiFunction>& CBaseMtmUiData::MtmSpecificFunctions() const
/** Gets an array of MTM-specific operations that can be carried out through the 
associated User Interface MTM's CBaseMtmUi::InvokeSyncFunctionL()/InvokeAsyncFunctionL() 
functions.

It is intended that message client applications will use this function to 
add dynamically user interface features, such as menu items, dependent on 
the MTM type of the entry currently selected within the application. Message 
client applications can also use OperationSupportedL() to check dynamically 
if a particular operation is appropriate to a particular entry.

Implementers should note that this function returns a pointer to the iMtmSpecificFunctions 
data member.

@return Array of operations relevant to the MTM and context. */
	{ 
	return *iMtmSpecificFunctions; 
	}

