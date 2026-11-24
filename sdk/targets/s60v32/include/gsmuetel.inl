// GSMUETEL.INL
//
// Copyright (c) Symbian Software Ltd. 2001-2006.  All rights reserved.
//

/** @file
    @publishedAll
    */

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
