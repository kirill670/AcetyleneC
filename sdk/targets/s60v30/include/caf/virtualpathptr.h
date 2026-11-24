// virtualpathptr.h
// Copyright (c) Symbian Software Ltd 2004.  All rights reserved.

/** 
@file

@publishedPartner
@released
*/


#ifndef __CAFVIRTUALPATHPTR_H__
#define __CAFVIRTUALPATHPTR_H__

#include <e32base.h>

namespace ContentAccess
	{
	class CVirtualPath;

	/** 
	The character used to separate the URI from the UniqueId 
	when the two are concatenated into a single descriptor 
	*/
	_LIT(KCafVirtualPathSeparator, "!");

	/**	Identifies the location of a file and a particular content object inside it.

	TVirtualPathPtr points to the two descriptors (the URI and UniqueId) used 
	to initialise it. These descriptors must not be modified or destroyed while 
	the TVirtualPathPtr object is in use.

	The UniqueId will be created by the Agent. Content is only ever
	accessed by one agent so it is the agents responsibility to ensure the 
	UniqueId is truly unique within the file.

	It is also possible to flatten a virtual path into a single descriptor. The
	ContentAccess::CVirtualPath class concatenates the URI, a separator 
	and the UniqueId to form a single URI. TVirtualPathPtr can be used to 
	decode this single URI into the file URI and the content object UniqueId.
	
	@code
	// Create a CVirtualPath object to point to OBJECT1 inside file.dcf
	CVirtualPath *path = CVirtualPath::NewL(_L("C:\\directory\file.dcf"), _L("OBJECT1");

	// convert the URI and unique ID into a single URI
	TPtrC singleURI = *path;

	// convert the single URI back to file URI and content ID
	TVirtualPathPtr aPath = singleURI;
	@endcode

	@publishedPartner
	@released
	*/
	class TVirtualPathPtr
		{
	public:
		/** Constructor used when the URI and UniqueId fields are separate 
		@param aUri The location of the file
		@param aUniqueId The location of the content within the file
		*/
		IMPORT_C TVirtualPathPtr(const TDesC& aUri, const TDesC& aUniqueId);

		/** Constructor used for a concatenated URI and UniqueId.
		
		Note that the descriptor here may be just a URI or it could be a URI
		concatenated with the file's uniqueId.

		@param aCombinedUriUniqueId The location of the content object
		*/
		IMPORT_C TVirtualPathPtr(const TDesC& aCombinedUriUniqueId);

		/** Copy constructor */
		IMPORT_C TVirtualPathPtr(const TVirtualPathPtr& aPtr);

		/** The location of the file containing the content object 
		@return The location of the file
		*/
		IMPORT_C const TDesC& URI() const;

		/** UniqueId supplied by a CAF Agent to identify the object within the 
		file.  
		@return The location of the content within the file
		*/
		IMPORT_C const TDesC& UniqueId() const;

		/** Assignment operator */
		IMPORT_C TVirtualPathPtr& operator = (const TVirtualPathPtr& aVirtualPath);
	
		/** Assignment operator converts a single descriptor to a TVirtualPath
		If the descriptor is just a URI, the TVirtualPath will point to the KDefaultContentObject() within that file.
		If the descriptor is the URI and the UniqueId concatenated together they will be separated during the assignment
		URI and UniqueId to a TVirtualPath 
		*/
		IMPORT_C TVirtualPathPtr& operator = (const TDesC& aCombinedUriUniqueId);


	private:
		// The Set() function is only used by CVirtualPath
		friend class CVirtualPath;

		/** Used to redirect the TVirtualPathPtr to point at a different set of descriptors */
		void Set(const TDesC& aUri, const TDesC& aUniqueId);

	private:
		TPtrC iUri;
		TPtrC iUniqueId;
		};
	}

#endif
