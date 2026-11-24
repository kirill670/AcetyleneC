/*
* ============================================================================
*  Name        : CMessageAddress.h
*  Part of     : SendUi
*  Description : Encapsulates message real address and alias.
*  Version     : 1.0
*
*  Copyright © 2002-2004 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  Information which may not be disclosed to others without the 
*  prior written consent of Nokia.
*
* ============================================================================
*/

#ifndef CMESSAGEADDRESS_H
#define CMESSAGEADDRESS_H

// INCLUDES
#include <e32Base.h>

// FORWARD DECLARATIONS
class CMessageAddressImpl;

// CLASS DECLARATION

/**
 * Encapsulates message recipient real address and alias.
 *
 * @lib SendUi
 * @since Series 60 3.0
 */ 
class CMessageAddress : public CBase
    {
    public:  // Constructors and destructor
 
        /**
        * Two-phased constructor.
        */
        IMPORT_C static CMessageAddress* NewL();
        
        /**
        * Two-phased constructor. Leaves object to cleanup stack.
        */
        IMPORT_C static CMessageAddress* NewLC();
        
        /**
        * Destructor.
        */
        IMPORT_C virtual ~CMessageAddress();

    public: // New functions

        /**
        * Sets real address.
        * @since Series 60 3.0
        * @param aAddress Real address.
        * @return None.
        */
        IMPORT_C void SetAddressL( const TDesC& aAddress );

        /**
        * Returns real address.
        * @since Series 60 3.0
        * @return Real address.
        */
        IMPORT_C const TPtrC Address() const;

        /**
        * Sets alias for the real address.
        * @since Series 60 3.0
        * @param aAlias Alias for the real address.
        * @return None.
        */
        IMPORT_C void SetAliasL( const TDesC& aAlias );

        /**
        * Returns alias for the address.
        * @since Series 60 3.0
        * @return Alias for the real address.
        */
        IMPORT_C const TPtrC Alias() const;

    private:
    
        /**
        * C++ default constructor.
        */
        CMessageAddress();
        
        /**
        * Symbian 2nd phase constructor.
        */
        void ConstructL();

    private:  // Data

        // Message address implementation.
        CMessageAddressImpl*                   iMessageAddressImpl;
    };

typedef CArrayPtrFlat<CMessageAddress> CMessageAddressArray;

#endif      // CMESSAGEADDRESS_H

// End of File
