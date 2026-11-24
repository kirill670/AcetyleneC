// GSMUPDU.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

/** @file gsmupdu.inl 
contains inline method implementations from classes defined in gsmupdu.h
*/

inline CSmsPDU::TSmsPDUType CSmsPDU::Type() const
/** Gets the PDU type.

Once a PDU has been constructed it cannot change its type as the SMS 
elements present differ. Hence there is no function to set the type.

@return PDU type */
	{
	return iSmsPDUType;
	}

inline TBool CSmsDeliverReport::IsRPError() const
/** Gets the Reply Path Error flag.

@return True for Reply Path Error */
	{
	return iIsRPError;
	}

inline void CSmsDeliverReport::SetIsRPError(TBool aIsRPError)
/** Sets the Reply Path Error flag.

@param aIsRPError Set to True for Reply Path Error */
	{
	iIsRPError=(TUint8) aIsRPError;
	}
	
inline TBool CSmsSubmitReport::IsRPError() const
/** Gets the Reply Path Error flag.

@return True for Reply Path Error */
	{
	return iIsRPError;
	}

inline void CSmsSubmitReport::SetIsRPError(TBool aIsRPError)
/** Sets the Reply Path Error flag.

@param aIsRPError Set to True for Reply Path Error */
	{
	iIsRPError=(TUint8) aIsRPError;
	}

inline TBool CSmsStatusReport::ParameterIndicatorPresent() const
/** Gets Paramater Indicator.

@return True if Paramater Indicator is present */
	{
	return iParameterIndicatorPresent;
	}

inline void CSmsStatusReport::SetParameterIndicatorPresent(TBool aPresent)
/** Sets Paramater Indicator.

@param aPresent Set to True to set Parameter Indicator Present */
	{
	iParameterIndicatorPresent=(TUint8) aPresent;
	}
