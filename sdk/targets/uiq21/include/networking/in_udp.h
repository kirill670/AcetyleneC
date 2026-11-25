// IN_UDP.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __IN_UDP_H__
#define __IN_UDP_H__

#include <nifmbuf.h>
#include <in_ip.h>

const TUint KUDPHeaderSize = 8;

class ThdrUDP
{
public:
	static ThdrUDP *GetHeader(RMBufChain &aChain);
	void SwapOrder();
	inline static ThdrUDP* Ptr(RMBufPacketBase& aPacket);
	inline static ThdrUDP* Ptr(ThdrIP* aHdr);
	inline static ThdrUDP* NetPtr(ThdrIP* aHdr);
	inline TUint GetLength();
	inline TUint NetGetLength();
	inline TUint NetGetLengthInNetOrder();
	inline TUint GetSrcPort();
	inline TUint GetDstPort();
	inline TUint NetGetSrcPort();
	inline TUint NetGetDstPort();
	inline TUint GetChecksum();
	inline TUint NetGetChecksum();
	inline void SetLength(TUint aLen);
	inline void SetSrcPort(TUint aPort);
	inline void SetDstPort(TUint aPort);
	inline void SetChecksum(TUint aSum);
	inline void NetSetChecksum(TUint aSum);
private:
// UDP Protocol Header
	union
		{
		TUint16	iData16[4];
		TUint32	iData32[2];
		} u;
};

#include "in_udp.inl"

#endif
