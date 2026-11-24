/* ************************************************************************
 * FILENAME: EMSInformationElement.inl
 * *********************************************************************** */
// Copyright (c) Symbian Software Ltd. 2003-2006.  All rights reserved.

/**@file
   @publishedAll
   @released
*/

inline CEmsInformationElement::CEmsInformationElement(TSmsId aId, TBool aStartPosEncoded)
	: CSmsInformationElement(aId), iStartPosition(0),
	  iEncodedBodyLength(0), iStartPosEncoded(aStartPosEncoded)
	{
	}
