/*
* ============================================================================
*  Name        : CSendingServiceInfo.h
*  Part of     : SendUi
*  Description : Encapsulates the ECom plugged sending service data.
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

#ifndef CSENDINGSERVICEINFO_H
#define CSENDINGSERVICEINFO_H

// INCLUDES
#include <e32Base.h>
//#include <SendUi.h>     // TSendingCapabilities

// FORWARD DECLARATIONS
class TSendingCapabilities;
class CSendingServiceInfoImpl;

// CLASS DECLARATION

/**
 * Encapsulates the ECom plugged sending service data.
 *
 * 
 * 
 */ 
class CSendingServiceInfo : public CBase
    {
    public:
    
    enum TServiceFeatures
        {
        EServiceInValid = 1,
        EServiceHidden = 2,
        EServiceCanSendDirectly = 4,
        ENotUsed3 = 8
        };
        
    public:  // Constructors and destructor
    
        /**
        * Two-phased constructor.
        * @return Pointer to object of CSendingServiceInfo.
        */
        IMPORT_C static CSendingServiceInfo* NewL();
        
        /**
        * Two-phased constructor.
        * @return Pointer to object of CSendingServiceInfo.
        */
        IMPORT_C static CSendingServiceInfo* NewLC();

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CSendingServiceInfo();

    public: // New functions

        /**
        * Creates a copy of CSendingServiceInfo object.
        * 
        * @return A pointer to the new copy of the CSendingServiceInfo object.
        */
        IMPORT_C CSendingServiceInfo* CopyLC() const;

        /**
        * Set service human readable name.
        * Service name is used in editors "To"-field.
        * 
        * @param aServiceName Service human readable name.
        * @return None.
        */
        IMPORT_C void SetServiceNameL( const TDesC& aServiceName );

        /**
        * Returns service human readable name.
        * Service name is used in editors "To"-field.
        * 
        * @return Service human readable name.
        */
        IMPORT_C const TPtrC ServiceName() const;

        /**
        * Set service human readable name for the "Send"-menu.
        * 
        * @param aServiceMenuName Service human readable name for the
        *        "Send"-menu.
        * @return None.
        */
        IMPORT_C void SetServiceMenuNameL( const TDesC& aServiceMenuName );

        /**
        * Returns service human readable name for the "Send"-menu.
        * 
        * @return Service human readable name for the "Send"-menu.
        */
        IMPORT_C const TPtrC ServiceMenuName() const;

        /**
        * Set service address.
        * 
        * @param aServiceAddress Service address.
        * @return None.
        */
        IMPORT_C void SetServiceAddressL( const TDesC& aServiceAddress );

        /**
        * Returns service address. 
        * 
        * @return Service address.
        */
        IMPORT_C const TPtrC ServiceAddress() const;

        /**
        * Set sending service id.
        * 
        * @param aServiceId Service id.
        * @return None.
        */
        IMPORT_C void SetServiceId( TUid aServiceId );

        /**
        * Returns sending service id.
        * 
        * @return Service id.
        */
        IMPORT_C TUid ServiceId() const;

        /**
        * Set sending service provider id.
        * 
        * @param aServiceProviderId Service provider id.
        * @return None.
        */
        IMPORT_C void SetServiceProviderId( TUid aServiceProviderId );

        /**
        * Returns sending service provider id.
        * 
        * @return Service provider id.
        */
        IMPORT_C TUid ServiceProviderId() const;

        
          /**
        * Returns sending service technology type id.
        * 
        * @return Service id.
        */
        IMPORT_C void SetTechnologyTypeId( TUid aTechnologyType );
        /**
        * Returns sending service technology type id.
        * 
        * @return Service id.
        */
        IMPORT_C TUid TechnologyTypeId() const;


        /**
        * Set service sending capabilities.
        * 
        * @param aServiceCapabilities Service sending capabilities.
        * @return None.
        */
        IMPORT_C void SetServiceCapabilities(
            TSendingCapabilities aServiceCapabilities );

        /**
        * Returns service sending capabilities.
        * 
        * @return Service sending capabilities.
        */
        IMPORT_C TSendingCapabilities ServiceCapabilities() const;

       /**
        * Set sending service features
        * 
        * @param aServiceCapabilities Sending service features.
        * @return None.
        */
        IMPORT_C void SetServiceFeatures(
            TInt aServiceFeatures );

        /**
        * Returns service features.
        * 
        * @return Sending service features.
        */
        IMPORT_C TInt ServiceFeatures() const;
        

    private:


        /**
        * C++ default constructor.
        */
        CSendingServiceInfo();

        /**
        * By default Symbian 2nd phase constructor is private.
        */
        void ConstructL();

    private:  // Data

        CSendingServiceInfoImpl*            iServiceInfoImpl;
    };

// CSENDINGSERVICEINFO_H
#endif

// End of File
