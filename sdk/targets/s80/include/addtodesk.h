#ifndef __ADDTODESK_H__
#define __ADDTODESK_H__

#include <e32std.h>
#include <f32file.h>

class AddToDesk 
{
public:
/*! \brief Displays "Add to Desk" dialog and adds a File or Folder to Desk. If aLinkName==NULL then name is determined from content */
	IMPORT_C static void AddDocToDeskL(RFs& aFs,const TDesC& aDocName,const TDesC* aLinkName=NULL);
/*! \brief Displays "Add to Desk" dialog and adds existing shortcut */
	IMPORT_C static void AddSheetOrChartToDeskL(RFs& aFs,const TDesC& aDocName,TInt aSheetOrChartIndex,TBool aIsChart,const TDesC* aLinkName=NULL);
/*! \brief Displays "Add to Desk" dialog and adds an application to Desk. If aLinkName==NULL then name is determined from content */
	IMPORT_C static void AddAppToDeskL(RFs& aFs,TUid aApp,const TDesC* aLinkName=NULL);
/*! \brief Displays "Add to Desk" dialog and adds an application to Desk. If aLinkName==NULL then name is determined from content */
	IMPORT_C static void AddAppToDeskL(RFs& aFs,TUid aApp,const TDesC* aLinkName,const TDesC& aDefaultNewFolderName);
/*! \brief Displays "Add to Desk" dialog and adds a URL to Desk. If aLinkName==NULL then name is determined from content */
	IMPORT_C static void AddUrlToDeskL(RFs& aFs,const TDesC& aUrl,const TDesC* aLinkName=NULL);
/*! \brief Displays "Add to Desk" dialog and adds a DocManFolder to Desk. If aLinkName==NULL then name is determined from content */
	IMPORT_C static void AddFolderToDeskL(RFs& aFs,const TDesC& aFolderName,const TDesC* aLinkName=NULL);
};

#endif