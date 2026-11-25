// GSMUPDU.INL
//
// Copyright (c) 1999 Symbian Ltd.  All rights reserved.
//

/**
 * @file gsmpudu.inl contains inline method implementations from classes defined in gsmupdu.h
 */

inline CSmsPDU::TSmsPDUType CSmsPDU::Type() const
/**
 * @return The type of CSmsPDU.
 * @note Once a PDU has been constructed it cannot change its type as the SMS elements present differ. Hence there is no function to set the type.
 */
	{
	return iSmsPDUType;
	}

inline TBool CSmsDeliverReport::IsRPError() const
/**
 *
 * @return True for Reply Path Error
 */
	{
	return iIsRPError;
	}

inline void CSmsDeliverReport::SetIsRPError(TBool aIsRPError)
/**
 *
 * @param aIsRPError set to True for Reply Path Error
 */
	{
	iIsRPError=(TUint8) aIsRPError;
	}
	
inline TBool CSmsSubmitReport::IsRPError() const
/**
 *
 * @return True for Reply Path Error
 */
	{
	return iIsRPError;
	}

inline void CSmsSubmitReport::SetIsRPError(TBool aIsRPError)
/**
 *
 * @param aIsRPError set to True for Reply Path Error
 */
	{
	iIsRPError=(TUint8) aIsRPError;
	}

inline TBool CSmsStatusReport::ParameterIndicatorPresent() const
/**
 *
 * @return True if Paramater Indicator is present
 */
	{
	return iParameterIndicatorPresent;
	}

inline void CSmsStatusReport::SetParameterIndicatorPresent(TBool aPresent)
/**
 *
 * @param Set to True to Set Parameter Indicator Present
 */
	{
	iParameterIndicatorPresent=(TUint8) aPresent;
	}
