// commschan.inl
//
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.
//

#ifndef __COMMSCHAN_INL__
#define __COMMSCHAN_INL__

/** 
@file commschan.inl
Implementation of the Comms Channels. The Channels are an abstraction in the SymbianOS kernel queues.

@publishedPartner
@released
*/

template<TInt aMaxParamBlockSize>
void TCFMessageBase<aMaxParamBlockSize>::ParamBlock(TInt aParamBlockSize, TAny* aParamBlock)
/** Copy a piece of memory to the message parameter block.
@param aParamBlockSize Size, in octets, of memory area to copy.
@param aParamblock Pointer to memory area to copy.
@panic ECFChanMsgTooBig
*/
	{
	__ASSERT_DEBUG(aParamBlockSize <= aMaxParamBlockSize, User::Panic(KCFChannelPanic, ECFChanMsgTooBig));
	Mem::Copy(iParamBlock, aParamBlock, aParamBlockSize);
	}

template<TInt aMaxParamBlockSize>
TUint8* TCFMessageBase<aMaxParamBlockSize>::ParamBlock() 
/**
@return A pointer to the parameter block.
*/
	{
	return iParamBlock;
	}

template<TInt aMaxParamBlockSize>
const TUint8* TCFMessageBase<aMaxParamBlockSize>::ParamBlock() const
/**
@return A const pointer to the parameter block.
*/
	{
	return iParamBlock;
	}

template<TInt aMaxParamBlockSize>
typename TCFMessageBase<aMaxParamBlockSize>::TCode TCFMessageBase<aMaxParamBlockSize>::Code() const
/**
@return Message code parameter.
*/
	{
	return iCode;
	}

template<TInt aMaxParamBlockSize>
void TCFMessageBase<aMaxParamBlockSize>::Code(TCode aCode)
/**
@param aCode Code to to set in the message code.
@see TCode
*/
	{
	iCode = aCode;
	}

template<TInt aMaxParamBlockSize>
TCFMessageBase<aMaxParamBlockSize>::TCFMessageBase(TCode aCode, TInt aParamBlockSize, TAny* aParamBlock)
/** Copy a piece of memory to the message parameter block and set the message code.
@param aCode Code to to set in the message code.
@param aParamBlockSize Size, in octets, of memory area to copy.
@param aParamblock Pointer to memory area to copy.
@panic ECFChanMsgTooBig
*/
	{
	__ASSERT_DEBUG(aParamBlockSize <= aMaxParamBlockSize, User::Panic(KCFChannelPanic, ECFChanMsgTooBig));
	iCode = aCode;
	Mem::Copy(iParamBlock, aParamBlock, aParamBlockSize);
	}

template<TInt aMaxParamBlockSize>
TCFMessageBase<aMaxParamBlockSize>::TCFMessageBase()
/** C'tor. Sets the message code to an invalid value, ensuring that the message cannot be sent on a channel
unless the message code is set to a valid code, e.g. by a deriving class.
*/
	{
	iCode=0; // Make sure this is an illegal message
	}

template<TInt aMaxParamBlockSize>
void TCFMessageBase<aMaxParamBlockSize>::SetPIGCode()
/**
Sets the code of the message to type EPIG. This is the message type used for closing channels. 
It is guaranteed that no messages can be sent on a channel after a PIG message has been sent, thus
this is ideal for controlled closing of channels using, avoiding data loss,  e.g. using the 
CloseGracefully() member.
*/
	{
	Code(EPIG);
	}

template<TInt aMaxParamBlockSize>
TBool TCFMessageBase<aMaxParamBlockSize>::IsPIGCode() const
/**
@return ETrue if this is a PIG message.
*/
	{ 
	return EPIG == Code();
	}

TCFMessage::TCFMessage(TCode aCode, TInt aParamBlockSize, TAny* aParamBlock)
	: TCFMessageBase<KCFMessageParamBlockSize>(aCode, aParamBlockSize, aParamBlock)
/** Copy a piece of memory to the message parameter block and set the message code.
@param aCode Code to to set in the message code.
@param aParamBlockSize Size, in octets, of memory area to copy.
@param aParamblock Pointer to memory area to copy.
@panic ECFChanMsgTooBig
*/
	{}

TCFMessage::TCFMessage() 
	: TCFMessageBase<KCFMessageParamBlockSize>()
/** C'tor. Initialises the derived TCFMessageBase with the default message block size
of a TCFMessage.
@see KCFMessageParamBlockSize
@see TCFMessageBase
*/
	{}






#endif // __COMMSCHAN_INL__
