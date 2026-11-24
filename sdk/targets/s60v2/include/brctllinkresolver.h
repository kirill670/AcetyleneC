/*
* ==============================================================================
*  Name        : BrCtlLinkResolver.h
*  Part of     : Browser Engine
*  Interface   : Browser Control API
*  Description : Handle links and embedded content that are not fetched from the network
*  Version     : %Version%
*
*  Copyright (c) 2004 Nokia Corporation.
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


#ifndef BRCTLLINKRESOLVER_H
#define BRCTLLINKRESOLVER_H

//  INCLUDES
#include <e32std.h>
#include <e32base.h>


// DATA TYPES
enum TBrCtlLoadContentType
    {
    ELoadContentTypeAny,
    ELoadContentTypeMarkup,
    ELoadContentTypeImage,
    ELoadContentTypeCss,
    ELoadContentTypeJavascript,
    ELoadContentTypePlugin
    };


// FORWARD DECLARATIONS
class MBrCtlLinkContent;

// CLASS DECLARATION
/**
*  This observer is notified of need for embedded content or when the user requested new content
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlLinkResolver
    {
    public: // New functions
        
    	/**
    	* Browser plug-in calls this method when embedded link is found. Used with ECapabilityClientResolveEmbeddedURL
        * @since 2.8
    	* @param aEmbeddedUrl The url of the embedded content
    	* @param aCurrentUrl The url of the current page
    	* @param aLoadContentType The expected type of the embedded content
    	* @param aEmbeddedLinkContent a callback interface to return the embedded content
    	* @return EFalse, browser will resolve the link
    	*/
        virtual TBool ResolveEmbeddedLinkL(const TDesC& aEmbeddedUrl,
    		                               const TDesC& aCurrentUrl,
        	                               TBrCtlLoadContentType aLoadContentType, 
        	                               MBrCtlLinkContent& aEmbeddedLinkContent) = 0; 
		
    	/**
    	* Browser plug-in calls this method when the user requests to load content via selecting a link, or any other way. Used with ECapabilityClientNotifyURL 
        * @since 2.8
    	* @param aUrl The requested url
    	* @param aCurrentUrl The url of the current page
    	* @param aBrCtlLinkContent a callback interface to return the embedded content
    	* @return EFalse, browser will resolve the link
    	*/
        virtual TBool ResolveLinkL(const TDesC& aUrl, const TDesC& aCurrentUrl,
                                   MBrCtlLinkContent& aBrCtlLinkContent) = 0;

		/**
		* Cancel all outstanding resolving operations
        * @since 2.8
    	* @return void
    	*/
        virtual void CancelAll() = 0;
    };


/**
*  This interface returns the resolved content
*
*  @lib BrowserEngine.lib
*  @since 2.8
*/
class MBrCtlLinkContent
    {
    public: // New functions
        /**
    	* Resolver calls this method when content is resolved.
    	* @param aContentType The content type of the response
    	* @param aCharset The charset of the response. May be empty in case of image
    	* @param aContentBuf content data. Ownership is not transfered
    	* @return void
    	*/
        virtual void HandleResolveComplete(const TDesC& aContentType,
                                           const TDesC& aCharset,
                                           const HBufC8* aContentBuf) = 0;

		/**
    	* This method is called if there is some error while resolving the content
    	* @param aError system wide error code.
    	* @return void
    	*/
        virtual void HandleResolveError(TInt aError) = 0;
    };



#endif      // BRCTLLINKRESOLVER_H
            
// End of File
