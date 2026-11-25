// GSMUETEL.INL
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

inline TGsmSms::TGsmSms()
/**
 * Constructor
 */ 
	{
	}

inline const TDesC8& TGsmSms::Pdu() const
/**
 *
 * @return Descriptor containing PDU
 */
	{
	return iPdu;
	}

inline void TGsmSms::SetPdu(const TDesC8& aPdu)
/**
 *
 * @param aPdu Sets the PDU
 */
	{
	iPdu = aPdu;
	}

inline const TGsmSmsTelNumber& TGsmSms::Sca() const
/**
 *
 * @return Descriptor containing SCA
 */
	{
	return iSca;
	}

inline void TGsmSms::SetSca(const TGsmSmsTelNumber& aSca)
/**
 *
 * @param aPdu Sets the SCA
 */
	{
	iSca = aSca;
	}