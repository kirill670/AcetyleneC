// HCIFrame.h
// HCI methods for formatting a HCI frame
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.

#ifndef HCIFRAME_H_
#define HCIFRAME_H_

#include <e32std.h>
#include <e32base.h>
#include <bttypes.h>

#include "hcibase.h"

static const TInt KHCTLMaxCommandFrameSize = 260;

class CHCICommandFrame : public CBase
	{
public:
	static CHCICommandFrame* NewL(TUint16 aOpcode);

public:
	void SetOpcode(TUint16 aOpcode);
	void SetParameterLength(TUint8 aLength);
	TUint16 Opcode();
	void PutByte(TUint8 aByte);
	void PutBytes16(TUint16 aVal);
	void PutBytes32(TUint aVal,TUint8 aNumOfBytes);
	void PutString(const TDesC8& aString);
	void PutDevAddr(const TBTDevAddr& aBdaddr);
    void PutLinkKey(TBTLinkKey& aLinkKey);
    void PutPINCode(TBTPinCode& aPIN);
	TUint8& UpdateByte(TInt aOffset);
	TUint8 ParameterLength() const;
	const TDesC8& HCTLPayload() const;
	const TDesC8& HCIPayload() const;

private:
	void ConstructL(TUint16 aOpcode);
	CHCICommandFrame();

private:
	TPtr8		iHCIPayload;
    TBuf8<KHCTLMaxCommandFrameSize>	iHCTLFrame;
	};


class CHCIACLDataFrame : public CBase
	{
public:
	static CHCIACLDataFrame* NewL(TUint16 aBufSize);
	~CHCIACLDataFrame();

	void SetDataLength(TUint16 aLength);
	void SetConnectionHandle(THCIConnHandle aConnectionHandle);
	void SetFlag(TUint8 aFlag);
	void SetDataPayload(const TDesC8& aData);
	const TPtrC8 HCTLPayload() const;
	THCIConnHandle ConnectionHandle() const;

private:
	void ConstructL(TUint16 aBufSize);
	void PutBytes16(TUint16 aVal, TUint8 aPayloadIndex);
	CHCIACLDataFrame();

private:
	TPtr8		iHCIPayload;
	HBufC8*		iHCTLFrame;					// entire HCTL frame, avec reserved header
	};

#endif