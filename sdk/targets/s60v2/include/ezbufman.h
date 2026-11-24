// EZLib: BUFMAN.H
// Copyright (C) Symbian LTD 1999-2003
//
// Defines Mixin class for a BufferManager
//

#ifndef __EZBUFFERMANAGER_H__
#define __EZBUFFERMANAGER_H__

class CEZZStream;

/**
 * @publishedAll 
 * @released
 */
class MEZBufferManager
	{
public:
	virtual void InitializeL(CEZZStream &aZStream) = 0;
	virtual void NeedInputL(CEZZStream &aZStream) = 0;
	virtual void NeedOutputL(CEZZStream &aZStream) = 0;
	virtual void FinalizeL(CEZZStream &aZStream) = 0;
	};

#endif

