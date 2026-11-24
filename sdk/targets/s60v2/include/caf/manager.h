// manager.h
// Copyright (c) 2003 Symbian Ltd.  All rights reserved.

#ifndef __MANAGER_H__
#define __MANAGER_H__

#include <e32base.h>


namespace ContentAccess
{
	/** 
	* Manages the Content Access Framework. 
	*
	* @publishedPartner
	* @prototype
	*/
	class CManager 
		{
	public:
		/**
		* Delete a file.
		* 
		* @param aFileName	The file to delete.
		*/
		IMPORT_C static void DeleteFileL(const TDesC& aFileName);
		};

} // namespace ContentAccess
#endif /* __MANAGER_H__ */

