/*
 * =========================================================================
 *  Name     : SenBaseAttribute.h
 *  Part of  : SenXml
 *  Created  : 2004-06-14 by Nokia
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenBaseAttribute.h,v $
 *   $Date: 2004/10/20 20:14:15 $
 *   $Revision: 1.3 $
 *   $Author: marmink $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_BASE_ATTRIBUTE_H
#define SEN_BASE_ATTRIBUTE_H

#include <e32base.h>
#include <s32strm.h>

/**
 *  A name-value pair. Both name and value may contain a namespace prefix
 *  but this is not handled specially in any way.
 */
class CSenBaseAttribute : public CBase
    {
public:
    IMPORT_C static CSenBaseAttribute* NewL(const TDesC& aName, 
											const TDesC& aValue);

    IMPORT_C static CSenBaseAttribute* NewL(const TDesC& aQName, 
											const TDesC& aName, 
											const TDesC& aValue);
    IMPORT_C virtual ~CSenBaseAttribute();

protected:
    IMPORT_C CSenBaseAttribute();
    IMPORT_C void BaseConstructL(const TDesC& aName, 
								const TDesC& aValue);
    IMPORT_C void BaseConstructL(const TDesC& aName, 
								 const TDesC& aQName,	
								 const TDesC& aValue);

public:
    virtual const TDesC& Name() const;
    virtual const TDesC& Value() const;

    virtual const TDesC& SetValueL(const TDesC& aValue);

private:
    HBufC* ipName;
    HBufC* ipValue;
    };

#endif // SEN_BASE_ATTRIBUTE_H
