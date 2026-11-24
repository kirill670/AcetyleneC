// EIKEMBAL.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#if !defined(__EIKEMBAL_H__)
#define __EIKEMBAL_H__

#if !defined(__E32BASE_H__)
#include <e32base.h>
#endif

#if !defined(__F32FILE_H__)
#include <f32file.h>
#endif

#if !defined(__BAMDESCA_H__)
#include <bamdesca.h>
#endif

#if !defined(__APADEF_H__)
#include <apadef.h>
#endif

#if !defined(__APAID_H__)
#include <apaid.h>
#endif

class CEikDocument;
class CApaProcess;
class RApaLsSession;


class CEikEmbeddableAppList : public CArrayFixFlat<TApaAppInfo>, public MDesCArray
/** Provides a list of all embeddable applications on the phone. 

Hidden applications are omitted from the list. The list is sorted by UID.

@see TApaAppCapability::iAppIsHidden
@publishedAll 
*/
	{
public:
	IMPORT_C CEikEmbeddableAppList();
	IMPORT_C ~CEikEmbeddableAppList();
	IMPORT_C void ConstructL();
	IMPORT_C void ConstructL(const TApaEmbeddabilityFilter& aFilter);
	IMPORT_C CEikDocument* CreateEmbeddedDocumentL(TInt aIndex,CApaProcess* aProcess);
private: // from MDesCArray
	IMPORT_C TInt MdcaCount() const;
	IMPORT_C TPtrC MdcaPoint(TInt aIndex) const;
	// Reserved methods
	IMPORT_C virtual void CEikEmbeddableAppList_Reserved1();
	IMPORT_C virtual void CEikEmbeddableAppList_Reserved2();

private: // utility methods
	TInt GetAppListL(const TApaEmbeddabilityFilter& aFilter);
	TInt DoGetAppListL(RApaLsSession& aLs, const TApaEmbeddabilityFilter& aFilter);
	void SortAppListL();
	
private:
	TInt iCEikEmbeddableAppList_Reserved1;
	};

#endif
