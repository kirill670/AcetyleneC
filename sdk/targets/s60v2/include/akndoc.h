/*
* ============================================================================
*  Name     : AknDoc.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
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
#ifndef __AKNDOC_H__
#define __AKNDOC_H__

#include <eikdoc.h>

class CAknDocument : public CEikDocument
	{
public:	// from CEikDocument
	IMPORT_C CFileStore* OpenFileL(TBool aDoOpen,const TDesC& aFilename,RFs& aFs);
protected:
	IMPORT_C CAknDocument(CEikApplication& aApp);
	};

#endif

