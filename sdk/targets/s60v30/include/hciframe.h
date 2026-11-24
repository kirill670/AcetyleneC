//Copyright (c) 2001 Symbian Software Ltd.  All rights reserved.

#ifndef HCIFRAME_H_
#define HCIFRAME_H_

#include <e32std.h>
#include <e32base.h>
#include <bttypes.h>

#include "hcibase.h"

static const TUint KHCTLMaxCommandFrameSize = 260; /*!<Maximum command frame size*/
static const TUint KHCTLMaxACLDataSize = KMaxTUint16; /*!<Maximum ACL frame size*/
static const TUint KHCTLMaxSCODataSize = KMaxTUint8;/*!<Maximum SCO frame size*/

/**
Class representing a HCI Command Frame as specified in the Bluetooth Core Specification, HCI Section
@publishedPartner
@released
*/
NONSHARABLE_CLASS(CHCICommandFrame) : public CBase
	{
public:
	static CHCICommandFrame* NewL(TUint16 aOpcode);
public:
	void SetOpcode(TUint16 aOpcode);
	void SetParameterLength(TUint8 aLength);
	TUint16 Opcode() const;
	void PutByte(TUint8 aByte);
	void PutBytes16(TUint16 aVal);
	void PutBytes32(TUint aVal,TUint8 aNumOfBytes);
	void PutString(const TDesC8& aString);
	void PutDevAddr(const TBTDevAddr& aBdaddr);
	void PutAFHHostChannelClassification(const TDesC8& aClassification);
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

/**
Class representing a HCI Data Frame as specified in the Bluetooth Core Specification, HCI Section
This is abstract and the different data types (ACL, SCO etc) derive from it
@publishedPartner
@released
*/
NONSHARABLE_CLASS(CHCIDataFrameBase) : public CBase
	{
public:
	void SetConnectionHandle(THCIConnHandle aConnectionHandle);
	virtual void SetDataPayload(const TDesC8& aData)=0;
	~CHCIDataFrameBase();
	virtual const TPtrC8 HCTLPayload() const=0;
protected:
	CHCIDataFrameBase();
	void ConstructL(TInt aPayloadSize);
	void PutBytes16(TUint16 aVal, TUint8 aPayloadIndex);
	
protected:
	TPtr8		iHCIPayload;
	HBufC8*		iHCTLFrame;
	};


/**
Class representing a HCI ACL Data Frame as specified in the Bluetooth Core Specification, HCI Section
@publishedPartner
@released
*/
NONSHARABLE_CLASS(CHCIACLDataFrame) : public CHCIDataFrameBase
	{
public:
	static CHCIACLDataFrame* NewL(TUint16 aBufSize);

	void SetFlag(TUint8 aFlag);
	virtual void SetDataPayload(const TDesC8& aData);
	THCIConnHandle ConnectionHandle() const;
	virtual const TPtrC8 HCTLPayload() const;
private:
	void ConstructL(TUint16 aPayloadSize);
	void SetDataLength(TUint16 aLength);

	};

/**
Class representing a HCI SCO Data Frame as specified in the Bluetooth Core Specification, HCI Section
@publishedPartner
@released
*/
NONSHARABLE_CLASS(CHCISCODataFrame) : public CHCIDataFrameBase
	{
public:
	static CHCISCODataFrame* NewL(TUint8 aBufSize);
	virtual void SetDataPayload(const TDesC8& aData);
	virtual const TPtrC8 HCTLPayload() const;
private:
	void ConstructL(TUint8 aPayloadSize);
	void SetDataLength(TUint8 aLength);
	};


#endif
