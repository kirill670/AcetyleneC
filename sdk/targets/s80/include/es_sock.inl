/**
@file ES_SOCK.INL

Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
*/

inline TSockIOBufC::TSockIOBufC()	: TPckgC<TSockIO>(iArgs)

	{}

inline TSockOpenBufC::TSockOpenBufC()	: TPckgC<TSockOpen>(iArgs)

	{}

inline SSockAddr *TSockAddr::BasePtr() const
/**
This function returns the end point to a connection.

@return socket address
*/
	{ return (SSockAddr*)iBuf; }


inline TUint8 *TSockAddr::UserPtr() const
/** Gets an offset to place data after the base class data. This function is mainly 
intended for use in derived classes.
@return Pointer to derived class intended data area */
	{ return (TUint8*)(BasePtr()+1); }

inline TUint16 ByteOrder::Swap16(TUint aVal)
/** 
Reverses the order of the bytes in a 16-bit value.
	
@param aVal The value to reverse. 
@return The reversed value. 
*/
	{ return ByteOrder::Swap16((TUint16)aVal); }

inline TNameRecord::TNameRecord()
	:iName(),iAddr(),iFlags(0)	
/** 
Trivial C++ constructor. This sets the fields in the 
class to suitable default values. 
*/
	{}

inline TNifProgress::TNifProgress()	:iStage(0), iError(KErrNone) 
/**
It sets the iStage data member to 0 and the iError data member to KErrNone.
*/
	{}
