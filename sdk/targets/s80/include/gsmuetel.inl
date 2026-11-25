// GSMUETEL.INL
//
// Copyright (c) 2001 Symbian Ltd.  All rights reserved.
//

/** @file GSMUETEL.INL 
    @publishedAll */

inline TGsmSms::TGsmSms()
/** Constructor. */
	{
	}

inline const TDesC8& TGsmSms::Pdu() const
/** Gets a descriptor containing the PDU.

@return Descriptor containing the PDU */
	{
	return iPdu;
	}

inline void TGsmSms::SetPdu(const TDesC8& aPdu)
/** Sets the PDU.

@param aPdu Descriptor containing the PDU */
	{
	iPdu = aPdu;
	}

inline const TGsmSmsTelNumber& TGsmSms::Sca() const
/** Gets the Service Centre Address.

@return Service Centre Address */
	{
	return iSca;
	}

inline void TGsmSms::SetSca(const TGsmSmsTelNumber& aSca)
/** Sets the Service Centre Address.

@param aSca Service Centre Address */
	{
	iSca = aSca;
	}
