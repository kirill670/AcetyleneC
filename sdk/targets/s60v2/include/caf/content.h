// content.h
//Copyright (c) Symbian Software Ltd 2003 - 2004 . All rights reserved.

#ifndef __CONTENT_H__
#define __CONTENT_H__

#include <e32base.h>
#include <f32file.h>
#include <caf/caf.h>

namespace ContentAccess
{
	class CAgentResolver;
	class CAgentInfo;
	class CData;
	class CAttribute;
	
/**
 * Encapsulates a piece of content. 
 *
 * CContent allows direct access to meta-data such as the attributes of 
 * the content, and indirect access to the plaintext data itself through 
 * the CData class.
 *
 * In order to be DRM-aware, clients will use an object of this type
 * rather than the traditional RFile mechanisms. They will, however, be
 * required to indicate <i>DRM Intent</i> - something that determines
 * whether (and how) access to the content should be evaluated by a
 * Content-Access agent.
 * 
 * On creation, this object implicitly instantiates the correct agent
 * implementation based on identification of the agent-owner of the
 * content. If the content is not recognised as restricted, then an F32
 * agent implementation will handle access through the CData
 * interface. In this way, non-restricted content can be accessed through
 * the CData object as well.
 */
	class CContent : public CBase
		{
	public:
		/**
		 * Constructs a new CContent object with a given URI.
		 *
	 	 * The returned pointer is put onto the cleanup stack.
		 *
		 * @param aURI	The target filename or URI.
		 * @return		A pointer to the new CContent object.
		 */
		IMPORT_C static CContent* NewLC(const TDesC& aURI);
		
		/**
		 * Constructs a new CContent object with a given URI.
		 *
		 * @param aURI	The target filename or URI.
		 * @return		A pointer to the new CContent object.
		 */
		IMPORT_C static CContent* NewL(const TDesC& aURI);
		
		/** Destructor */
		virtual ~CContent();

		/** 
		 Grants access to the content data based on evaluation of the
		 supplied intent information. 
		 
		 Note that the intent is simply @e evaluated and not @e executed. 
		 To force the intent to be executed, clients must use the call
		 ContentAccess::CData::ExecuteIntent(). 
		 
		 A CData object can be obtained as follows:
		 @code
		 CData *MyData = MyContent->OpenContentL(ChosenIntent);
		 ...
		 delete MyData; // when finished accessing plaintext content
		 @endcode
		 	
		 @param aIntent	The intent indicator.
		 @return			A CData instance. The caller gets ownership of this object.
		 
		 @leave KErrCANoPermission
		 @leave KErrCANoRights
		 @leave KErrCANotSupported
		 @leave KErrCANoAgent

		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		 */
		IMPORT_C CData* OpenContentL(TIntent aIntent);
		
		/** 
		 Grants access to the content data based on evaluation of the
		 supplied intent information. 
		 
		 Note that the intent is simply @e evaluated and not @e executed. 
		 To force the intent to be executed, clients must use the call
		 ContentAccess::CData::ExecuteIntent(). 
		 
		 A CData object can be obtained as follows:
		 @code
		 // open content with EContentReadWrite share mode (this is the default when only one parameter is supplied)
		 CData *MyData = MyContent->OpenContentL(ChosenIntent, EContentReadWrite);
		 ...
		 delete MyData; // when finished accessing plaintext content
		 @endcode
		 	
		 @param aIntent	The intent indicator.
		 @param aShareMode Share mode used for opening this content. This parameter has no effect unless the content is a local file on the device.
		 @return			A CData instance. The caller gets ownership of this object.
		 
		 @leave KErrCANoPermission
		 @leave KErrCANoRights
		 @leave KErrCANotSupported
		 @leave KErrCANoAgent

		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted

		 @internalAll
		 @prototype
		 */
		IMPORT_C CData* OpenContentL(TIntent aIntent, TContentShareMode aShareMode);

		/**
		 * Gets an attribute object associated with the target content.
		 * 
		 * A fresh attribute object can be obtained as follows:
		 * @code
		 * CAttribute *MyAttr = MyContent->NewAttributeL();
		 * ...
		 * delete MyAttr; // when no longer required.
		 * @endcode
		 * 
		 * @param aPreloaded	If set to ETrue, the newly constructed attribute
		 * 						object will contain all the available attributes. 
		 *						If EFalse, the client will need to query for the 
		 *						attributes manually.
		 * @return				A CAttribute instance. 
		 * 
		 * @leave KErrCANoPermission
		 * @leave KErrCANoRights
		 * @leave KErrCANotSupported. 
		 */
		IMPORT_C CAttribute* NewAttributeL(TBool aPreloaded);

		/**
		 * Gets an attribute object associated with the target content.
		 * 
		 * A fresh attribute object can be obtained as follows:
		 * @code
		 * CAttribute *MyAttr = MyContent->NewAttributeL();
		 * ...
		 * delete MyAttr; // when no longer required.
		 * @endcode
		 * 
		 * @param aPreloaded	If set to ETrue, the newly constructed attribute
		 * 						object will contain all the available attributes. 
		 *						If EFalse, the client will need to query for the 
		 *						attributes manually.
		 * @param aShareMode    Share mode used for retrieving attributes for this content. This parameter has no effect unless the content is a local file on the device.
		 * @return				A CAttribute instance. 
		 * 
		 * @leave KErrCANoPermission
		 * @leave KErrCANoRights
		 * @leave KErrCANotSupported. 
		 * 
		 * @internalAll
		 * @prototype
		 */
		IMPORT_C CAttribute* NewAttributeL(TBool aPreloaded, TContentShareMode aShareMode);

		

	private:
		void ConstructL(const TDesC& aURI); 
		CContent();

	private:
		/** 
		 * Object that points to the agent that supports this content.
		 * NOTE: NOT OWNED - reference counted object 
		 */
		CAgentInfo* iAgent;
		
		/** The target URI/pathname */
		HBufC *iURI;

#ifdef SYMBIAN_SECURITY_CAF_RFILE_HANDLE
	public:
		/**
		 Constructs a new CContent object with an open file handle.

  		 CContent will use a duplicate of this file handle, the client is still responsible for 
		 calling RFile::Close() after construction of the CContent. 

		 @param aFile The file handle. The file must already be open before calling NewLC.
		 */
		IMPORT_C static CContent* NewLC(RFile& aFile);
		
		/** 
		 Constructs a new CContent object with an open file handle.

  		 CContent will use a duplicate of this file handle, the client is still responsible for 
		 calling RFile::Close() after construction of the CContent. 

		 @param aFile The file handle. The file must already be open before calling NewLC
		*/
		IMPORT_C static CContent* NewL(RFile& aFile);

	private:
		void ConstructL(RFile& aFile);

	private:
		/** Reference to the file handle if the content was opened with a file handle */
		RFile iFile;

#endif
		};
	} // namespace ContentAccess
#endif /* __CONTENT_H__ */
