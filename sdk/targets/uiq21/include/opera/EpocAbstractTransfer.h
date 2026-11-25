/* -*- Mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
**
** Copyright (C) 2000-2002 Opera Software AS.  All rights reserved.
**
** This file is part of the Opera web browser.  It may not be distributed
** under any circumstances.
**
** Keith Hollis, Rob Gregson
*/

#ifndef __EPOCABSTRACTTRANSFER_H
#define __EPOCABSTRACTTRANSFER_H

class MOperaDownload;
class MOperaTransferAdapter;

/*********************************************************************************************

	class MOperaTransferFactory - to be implemented on the platform side

	This class is responsible for created and destroying platform-side downloads
*/

class MOperaTransferFactory
	{
public:
	virtual MOperaDownload* NewDownloadL(const TDesC& aName,const TDesC& aUrl,MOperaTransferAdapter* aTransferAdapter)=0;
	virtual void RemoveL(MOperaDownload* aDownload)=0;
	};

/*********************************************************************************************

	class MOperaDownload - to be implemented on the platform side
*/

class MOperaDownload
	{
public:
	virtual void UpdateL(int aSize,int aTotal,int aSeconds)=0;
	virtual void CompleteL()=0;
	virtual void DownloadErrorL(TInt aError)=0;
	};

/*********************************************************************************************

	class MOperaTransferAdapter	- to be implemented on the engine side
*/

class MOperaTransferAdapter
	{
public:
	virtual void DestroyDownload()=0;
	virtual void StopDownload()=0;
	virtual void ResumeDownload()=0;
	};

#endif // __EPOCABSTRACTTRANSFER_H
