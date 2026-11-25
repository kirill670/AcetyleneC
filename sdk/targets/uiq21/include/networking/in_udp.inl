// IN_UDP.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __IN_UDP_INL__
#define __IN_UDP_INL__

inline ThdrUDP* ThdrUDP::Ptr(RMBufPacketBase& aPacket)
	{ return (ThdrUDP*)aPacket.First()->Ptr(); }

inline ThdrUDP* ThdrUDP::Ptr(ThdrIP* aHdr)
	{ return (ThdrUDP*)aHdr->EndPtr(); }

inline ThdrUDP* ThdrUDP::NetPtr(ThdrIP* aHdr)
	{ return (ThdrUDP*)aHdr->NetEndPtr(); }

inline TUint ThdrUDP::NetGetSrcPort()
	{ return ByteOrder::Swap16(u.iData16[0]); }

inline TUint ThdrUDP::GetSrcPort()
	{ return u.iData16[1]; }

inline void ThdrUDP::SetSrcPort(TUint aPort)
	{ u.iData16[1] = (TUint16)aPort; }

inline TUint ThdrUDP::GetDstPort()
	{ return u.iData16[0]; }

inline TUint ThdrUDP::NetGetDstPort()
	{ return ByteOrder::Swap16(u.iData16[1]); }

inline void ThdrUDP::SetDstPort(TUint aPort)
	{ u.iData16[0] = (TUint16)aPort; }

inline TUint ThdrUDP::GetLength()
	{ return u.iData16[3]; }

inline TUint ThdrUDP::NetGetLength()
	{ return ByteOrder::Swap16(u.iData16[2]); }

inline TUint ThdrUDP::NetGetLengthInNetOrder()
	{ return u.iData16[2]; }

inline void ThdrUDP::SetLength(TUint aLen)
	{ u.iData16[3] = (TUint16)aLen; }

inline TUint ThdrUDP::GetChecksum()
	{ return u.iData16[2]; }

inline void ThdrUDP::SetChecksum(TUint aSum)
	{ u.iData16[2] = (TUint16)aSum; }

inline TUint ThdrUDP::NetGetChecksum()
	{ return u.iData16[3]; }

inline void ThdrUDP::NetSetChecksum(TUint aSum)
	{ u.iData16[3] = (TUint16)aSum; }

#endif
