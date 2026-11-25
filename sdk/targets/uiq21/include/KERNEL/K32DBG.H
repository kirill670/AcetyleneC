// K32DBG.H
//
// Copyright (c) 1998-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __K32DBG_H__
#define __K32DBG_H__
#include <k32std.h>

/**
 * Debugger class
 */
class DDebugger
	{
public:
	static DDebugger *New();
	virtual TInt Init3() =0;
	virtual ~DDebugger() {};
//
	virtual void Reschedule() =0;
	virtual void SwitchThread(const DThread *aThread) =0;
	virtual TInt AddProcess(const DProcess *aProcess) =0;
	virtual void RemoveProcess(const DProcess *aProcess) =0;
	virtual void UpdateProcess(const DProcess *aProcess) =0;
	virtual TInt AddLibrary(const DLibrary *aLibrary) =0;
	virtual void RemoveLibrary(const DLibrary *aLibrary) =0;
	virtual void UpdateLibrary(const DLibrary *aLibrary) =0;
	virtual TInt AddThread(const DThread *aThread) =0;
	virtual void RemoveThread(const DThread *aThread) =0;
	virtual void UpdateThread(const DThread *aThread) =0;
	virtual TInt AddChunk(const DProcess *aProcess, const DChunk *aChunk) =0;
	virtual void RemoveChunk(const DProcess *aProcess, const DChunk *aChunk) =0;
	virtual void UpdateChunk(const DProcess *aProcess, const DChunk *aChunk) =0;
public:
	TVersion iVersion;
	};
#endif
