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
* This class offers methods to
*  - query whether a feature is supported in the current environment
*
*
*  Using the class:
*
*  #include <FeatureDiscovery.h>
*  #include <featureinfo.h> // feature IDs
*  ...
*
*  // Static way of using the class:
*  TBool isSupported = CFeatureDiscovery::IsFeatureSupportedL(KFeatureIdUsb);
*  
*  // Dynamic way of using the class using NewL():
*  CFeatureDiscovery* testA = CFeatureDiscovery::NewL();
*  TBool usbSupported = testA->IsSupported(KFeatureIdUsb);
*  TBool mmcSupported = testA->IsSupported(KFeatureIdMmc);
*
*  delete testA;
*  
*  // Dynamic way of using the class using NewLC():
*  CFeatureDiscovery* testB = CFeatureDiscovery::NewLC();
*  TBool wcdmaSupported = testB->IsSupported(KFeatureIdProtocolWcdma);
*  TBool gsmSupported = testB->IsSupported(KFeatureIdProtocolGsm);
*  CleanupStack::PopAndDestroy();
*
*  delete testB;
*
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
