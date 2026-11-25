/*
 * =========================================================================
 *  Name     : SenDateUtils.h
 *  Part of  : SenUtils
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Utils/inc/SenDateUtils.h,v $
 *   $Date: 2004/08/06 13:54:18 $
 *   $Revision: 1.2 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */
 


#ifndef SEN_DATE_UTILS_H
#define SEN_DATE_UTILS_H

#include <e32base.h>


class SenDateUtils
    {
public:
    enum { KXmlDateTimeMaxLength = 25 };

    /**
     *  Convert dateTime (from XML schema) to Symbian TTime. The returned
     *  time will be in UTC.
     */
    IMPORT_C static TTime FromXmlDateTimeL(const TDesC& aXmlDateTime);

    /**
     *  Convert Symbian TTime to dateTime (from XML schema).
     *  @param aDest result will be written here. It must be at least
     *      KXmlDateTimeMaxLength long.
     *  @param TTime in UTC.
     */
    IMPORT_C static void ToXmlDateTimeL(TDes& aDest, const TTime& aSrc);

    /**
     *  Convert Symbian TTime to dateTime (from XML schema).
     *  @param aDest (UTF8) result will be written here. It must be at least
     *      KXmlDateTimeMaxLength long.
     *  @param TTime in UTC.
     */
	IMPORT_C static void ToXmlDateTimeUtf8L(TDes8& aDest, const TTime& aSrc);

private:
    SenDateUtils() { }
    };

#endif // SEN_DATE_UTILS_H
