/* ************************************************************************
 * FILENAME: EMSInformationElement.inl
 * *********************************************************************** */
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.

/**@file EMSInformationElement.inl 
   @publishedAll 
   @released
*/

inline CEmsInformationElement::CEmsInformationElement(TSmsId aId, TBool aStartPosEncoded)
	: CSmsInformationElement(aId), iStartPosition(0), 
	  iEncodedBodyLength(0), iStartPosEncoded(aStartPosEncoded)
	{
	}
		
