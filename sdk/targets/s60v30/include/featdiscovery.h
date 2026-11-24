/*
* ============================================================================
*  Name     : CFeatureDiscovery from FeatDiscovery.h
*  Part of  : CommonEngine.dll
*
*  Description:
*  - Feature Discovery API offers functionality for querying
*    whether a feature is supported in the current environment.
*
*  Version: 1.0
*
*  Copyright (C) 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/


#ifndef FEATUREDISCOVERY_H
#define FEATUREDISCOVERY_H

//  INCLUDES
#include <e32std.h>


/**
* Feature discovery.
*
* Feature discovery offers methods to
*  - query whether a feature is supported in the current environment
*
*  Usage:
*
* @code
*  #include <FeatDiscovery.h>
*  #include <featureinfo.h> // for feature definitions
*
*  // If querying only one feature, it is more efficient to use the class
*  // via the static method, IsFeatureSupportedL().
*  // When querying more than one feature, it is more efficient to use the 
*  // class by creating an instance and calling the IsSupported() method.
*
*  // Static way of using the class:
*  TBool isSupported = CFeatureDiscovery::IsFeatureSupportedL(KFeatureIdUsb);
*
*  // Dynamic way of using the class using NewL():
*  
*  // Call NewL() to create an instance of CFeatureDiscovery. 
*  CFeatureDiscovery* testA = CFeatureDiscovery::NewL();
* 
*  // Call the exported IsSupported() method to query whether features 
*  // are supported in the current environment or not.
*  TBool usbSupported = testA->IsSupported(KFeatureIdUsb);
*  TBool mmcSupported = testA->IsSupported(KFeatureIdMmc);
*
*  // Delete the created instance of CFeatureDiscovery.
*  delete testA;
*
*  // Dynamic way of using the class using NewLC():
* 
*  // Call NewLC() to create an instance of CFeatureDiscovery.
*  // The method leaves the instance of the object on the cleanup stack.
*  CFeatureDiscovery* testB = CFeatureDiscovery::NewLC();
*
*  // Call the exported IsSupported() method to query whether features 
*  // are supported in the current environment or not. 
*  TBool wcdmaSupported = testB->IsSupported(KFeatureIdProtocolWcdma);
*  TBool gsmSupported = testB->IsSupported(KFeatureIdProtocolGsm);
*
*  // Pop and delete the created instance of CFeatureDiscovery.
*  CleanupStack::PopAndDestroy();
* @endcode
*/

class CFeatureDiscovery : public CBase
    {
    public:

        /**
        * Two-phased constructors.
        */
		IMPORT_C static CFeatureDiscovery* NewL();
		IMPORT_C static CFeatureDiscovery* NewLC();

        /**
        * Destructor.
        */
		virtual ~CFeatureDiscovery();

		/**
        * Fetches information whether a certain feature is supported.
        *
        * @param aFeature feature ID
        * @return feature support status
        */
		IMPORT_C static TBool IsFeatureSupportedL(TInt aFeature);

		/**
        * Fetches information whether a certain feature is supported.
        *
        * @param aFeature feature ID
        * @return feature support status
        */
		IMPORT_C TBool IsSupported(TInt aFeature) const ;

    private:

        /**
        * C++ default constructor.
        */
		CFeatureDiscovery();

        /**
        * By default Symbian OS constructor is private.
        */
        void ConstructL();
    } ;


#endif  // FEATUREDISCOVERY_H

// EOF
