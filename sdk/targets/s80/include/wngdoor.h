/*
* ==============================================================================
*  Name        : wngdoor.h
*  Part of     : Word Engine
*  Interface   : 
*  Description : Glass door support
*  Version     : 
*
*  Copyright (c) 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/


#if !defined(__WNGDOOR_H__)
#define __WNGDOOR_H__

//  INCLUDES
#include <e32std.h>
#include <e32base.h>
#include <apamdr.h>

// CONSTANTS
const TUid KUidWordApp = {0x10003A64};

// MACROS
// DATA TYPES
// FUNCTION PROTOTYPES

// FORWARD DECLARATIONS
// Classes defined
class CWordModelHeader;
class TWordModelHeaderFactory;
class CWordModelHeaderV2;
class TWordModelHeaderFactoryV2;
//
// Class referenced
class CWordModel;
class TWordModelStoreResolver;

// CLASS DECLARATION




/* \class CWordModelHeader
*    \brief Wrapper for the word processor application engine.
*    
*    The class provides the knowledge for internalising and externalising an application model's data. It enables word processor documents to be embedded within Rich Text objects
*
*  @lib WPeng
*  @since ?Series90_version
*/
class CWordModelHeader : public CApaModelHeader
	{
    public:  // Constructors and destructor

        /**
        * C++ constructor.
        */
		IMPORT_C CWordModelHeader(CWordModel* aModel);
        
        /**
        * Two-phased constructor.
        */
        
        /**
        * Destructor.
        */
		IMPORT_C virtual ~CWordModelHeader();

    public: // New functions
        
		IMPORT_C virtual void StoreL(CStreamStore& aStore,CStreamDictionary& aDict)const;
		IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
		IMPORT_C virtual TApaAppIdentifier AppId()const;
		IMPORT_C void DetachFromStoreL(CPicture::TDetach aDegree);
		IMPORT_C CWordModel* Model();

    public: // Functions from base classes

        
    protected:  // New functions
        

    protected:  // Functions from base classes
        

    private:

        /**
        * C++ default constructor.
        */

        /**
        * By default Symbian 2nd phase constructor is private.
        */

        // Prohibit copy constructor if not deriving from CBase.
        // Prohibit assigment operator if not deriving from CBase.

    public:     // Data
    
    protected:  // Data
		CWordModel*	iModel;

    private:    // Data
         
        // Reserved pointer for future extension
        //TAny* iReserved;

    public:     // Friend classes
    protected:  // Friend classes
    private:    // Friend classes

	};


//
//

/* \class TWordModelHeaderFactory
*    \brief Factory to construct CWordModelHeader application wrapper objects
*
*  @lib WPeng
*  @since ?Series90_version
*/
class TWordModelHeaderFactory : public MApaModelHeaderFactory
	{
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        
        /**
        * Destructor.
        */

    public: // New functions
        
		IMPORT_C TWordModelHeaderFactory(const TFileName& aPrintDriverPath);
		IMPORT_C CApaModelHeader* NewHeaderL(const CStreamStore& aStore,const CStreamDictionary& aDict,
											const TApaAppIdentifier& aAppId)const;

    public: // Functions from base classes

        
    protected:  // New functions
        

    protected:  // Functions from base classes
        

    private:

        /**
        * C++ default constructor.
        */

        /**
        * By default Symbian 2nd phase constructor is private.
        */

        // Prohibit copy constructor if not deriving from CBase.
        // Prohibit assigment operator if not deriving from CBase.

    public:     // Data
    
    protected:  // Data

    private:    // Data
		TFileName iPrintDriverPath;

    public:     // Friend classes
    protected:  // Friend classes
    private:    // Friend classes

	};

/* \class CWordModelHeaderV2
*    \brief Wrapper for the word processor application engine.
*    
*    The class provides the knowledge for internalising and 
*    externalising an application model's data. It enables 
*    word processor documents to be embedded within Rich Text objects.
*    
*    Compared to CWordModelHeader, it also provides restoration support for objects embedded within embedded word documents
*
*
*  @lib WPeng
*  @since ?Series90_version
*/
class CWordModelHeaderV2 : public CApaModelHeader
	{
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        
        /**
        * Destructor.
        */
		IMPORT_C ~CWordModelHeaderV2();

    public: // Functions from base classes

	public:	// from CApaModelHeader

		IMPORT_C void StoreL(CStreamStore& aStore,CStreamDictionary& aDict)const;
		IMPORT_C TApaAppIdentifier AppId()const;
		IMPORT_C void DetachFromStoreL(CPicture::TDetach aDegree);
        
    public: // New functions
        
		IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
		IMPORT_C CWordModel* Model();
		void SetFactory(MApaModelHeaderFactory* aFactory); // takes ownership

    protected:  // New functions
        

    protected:  // Functions from base classes
        

    private:

        /**
        * C++ constructor.
        */
		CWordModelHeaderV2(CWordModel* aModel);

        /**
        * By default Symbian 2nd phase constructor is private.
        */

        // Prohibit copy constructor if not deriving from CBase.
        // Prohibit assigment operator if not deriving from CBase.

    public:     // Data
    
    protected:  // Data

    private:    // Data
		CWordModel*	iModel;
		TWordModelStoreResolver* iResolver; // created during restore
		MApaModelHeaderFactory* iHeaderFactory;

    public:     // Friend classes
    protected:  // Friend classes
		friend class TWordModelHeaderFactoryV2;	// Only TWordModelHeaderFactoryV2 is allowed to construct objects
    private:    // Friend classes


	};


/* \class TWordModelHeaderFactoryV2
*    \brief Factory to construct CWordModelHeaderV2 application wrapper objects.
*
*  @lib WPeng
*  @since ?Series90_version
*/
class TWordModelHeaderFactoryV2 : public MApaModelHeaderFactory
	{
    public:  // Constructors and destructor

        /**
        * C++ constructor.
        */
		IMPORT_C TWordModelHeaderFactoryV2(const TFileName& aPrintDriverPath);
        
        /**
        * Two-phased constructor.
        */
        
        /**
        * Destructor.
        */

    public: // New functions
        
		IMPORT_C CApaModelHeader* NewHeaderL(const CStreamStore& aStore,const CStreamDictionary& aDict,
											const TApaAppIdentifier& aAppId)const;

    public: // Functions from base classes

        
    protected:  // New functions
        

    protected:  // Functions from base classes
        

    private:

        /**
        * C++ default constructor.
        */

        /**
        * By default Symbian 2nd phase constructor is private.
        */

        // Prohibit copy constructor if not deriving from CBase.
        // Prohibit assigment operator if not deriving from CBase.

    public:     // Data
    
    protected:  // Data

    private:    // Data
		TFileName iPrintDriverPath;

    public:     // Friend classes
    protected:  // Friend classes
    private:    // Friend classes
	};




/* \class CWordModelHeaderV3
*    \brief Wrapper for the word processor application engine.
*    
*    The class provides the knowledge for internalising and 
*    externalising an application model's data. It enables 
*    word processor documents to be embedded within Rich Text objects.
*    
*    Like CWordModelHeaderV2, it provides restoration support for 
*    objects embedded within embedded word documents. 
*    Unlike that class, however, it does not restore printer setup 
*    information, or process header and footer information.
*
*  @lib WPeng
*  @since ?Series90_version
*/
class CWordModelHeaderV3 : public CApaModelHeader
	{
    public:  // Constructors and destructor
        
        /**
        * Two-phased constructor.
        */
        
        /**
        * Destructor.
        */
		IMPORT_C ~CWordModelHeaderV3();


    public: // Functions from base classes

		// from CApaModelHeader
		IMPORT_C void StoreL(CStreamStore& aStore,CStreamDictionary& aDict)const;
		IMPORT_C TApaAppIdentifier AppId()const;
		IMPORT_C void DetachFromStoreL(CPicture::TDetach aDegree);

    public: // New functions
        
		IMPORT_C void RestoreL(const CStreamStore& aStore,const CStreamDictionary& aDict);
		IMPORT_C CWordModel* Model();
		void SetFactory(MApaModelHeaderFactory* aFactory); // takes ownership

    protected:  // New functions
        

    protected:  // Functions from base classes
        

    private:

        /**
        * C++ constructor.
        */
		CWordModelHeaderV3(CWordModel* aModel);

        /**
        * By default Symbian 2nd phase constructor is private.
        */

        // Prohibit copy constructor if not deriving from CBase.
        // Prohibit assigment operator if not deriving from CBase.

    public:     // Data
    
    protected:  // Data

    private:    // Data
		CWordModel*	iModel;
		TWordModelStoreResolver* iResolver; // created during restore
		MApaModelHeaderFactory* iHeaderFactory;

    public:     // Friend classes
    protected:  // Friend classes
		friend class TWordModelHeaderFactoryV3;	// Only TWordModelHeaderFactoryV2 is allowed to construct objects
    private:    // Friend classes

	};


/* \class TWordModelHeaderFactoryV3
*    \brief Factory to construct CWordModelHeaderV3 application wrapper objects
*
*		Mimimal header factory for efficiency
*		Does not restore header or footer information from the document
*
*  @lib WPeng
*  @since ?Series90_version
*/
class TWordModelHeaderFactoryV3 : public MApaModelHeaderFactory
	{
    public:  // Constructors and destructor

        /**
        * C++ default constructor.
        */
		IMPORT_C TWordModelHeaderFactoryV3();
        
        /**
        * Two-phased constructor.
        */
        
        /**
        * Destructor.
        */

    public: // New functions
        
		IMPORT_C CApaModelHeader* NewHeaderL(const CStreamStore& aStore,const CStreamDictionary& aDict,
											const TApaAppIdentifier& aAppId) const;

    public: // Functions from base classes

        
    protected:  // New functions
        

    protected:  // Functions from base classes
        

    private:

        /**
        * By default Symbian 2nd phase constructor is private.
        */

        // Prohibit copy constructor if not deriving from CBase.
        // Prohibit assigment operator if not deriving from CBase.

    public:     // Data
    
    protected:  // Data

    private:    // Data
         
        // Reserved pointer for future extension
        //TAny* iReserved;

    public:     // Friend classes
    protected:  // Friend classes
    private:    // Friend classes
	};


#endif      // __WNGDOOR_H__
            
// End of File
