/*
 * =========================================================================
 *  Name     : SenNameSpace.h
 *  Part of  : 
 *  Created  : 
 *  Descr.   :
 *
 *  Version :
 *   $Source: /projects/serene/sen/Xml/inc/SenNameSpace.h,v $
 *   $Date: 2004/10/14 12:29:03 $
 *   $Revision: 1.3 $
 *   $Author: matmatt $
 *
 *  Copyright (c) 2004 Nokia Corporation. All rights reserved.
 * =========================================================================
 */

#ifndef SEN_NAME_SPACE_H
#define SEN_NAME_SPACE_H

//  INCLUDES
#include <e32base.h>
#include <s32mem.h>

// CONSTANTS


// FORWARD DECLARATIONS 


// CONSTANTS

// CLASS DECLARATION
class CSenNameSpace :	public CBase
{
public: // Constructors and destructor
    IMPORT_C static CSenNameSpace* NewL(const TDesC& aPrefix, const TDesC& aUri);
    IMPORT_C static CSenNameSpace* NewLC(const TDesC& aPrefix, const TDesC& aUri);   
	IMPORT_C static CSenNameSpace* NewL(const TDesC& aUri);
	IMPORT_C static CSenNameSpace* NewLC(const TDesC& aUri);
    IMPORT_C virtual ~CSenNameSpace();    


public: // New methods
	IMPORT_C const TDesC& Uri() const;
	IMPORT_C void SetUriL(const TDesC& aUri);
	IMPORT_C const TDesC& Prefix() const;
	IMPORT_C void SetPrefixL(const TDesC& aPrefix);
	IMPORT_C TBool CompareL(const TDesC& aOtherPrefix, const TDesC& aOtherUri) const;
	IMPORT_C TBool CompareL(const CSenNameSpace& aOtherNameSpace) const;
	IMPORT_C TBool MatchesL(const CSenNameSpace& aOtherNameSpace) const;

	IMPORT_C void InsertL(RBufWriteStream& aWs);

public: // From parent class

private:
    CSenNameSpace();
    void ConstructL(const TDesC& aPrefix, const TDesC& aUri);  

protected:

private: // Data
	HBufC* ipPrefix;
	HBufC* ipUri;
};

#endif // SEN_NAME_SPACE_H

// End of File
