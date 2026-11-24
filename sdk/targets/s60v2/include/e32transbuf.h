// E32TransBuf.h
//
// Copyright (c) Symbian Software Ltd 2000-2004.  All rights reserved.
//
/**
@file
@publishedAll
@released
*/

#ifndef __E32TRANSBUF_H__
#define __E32TRANSBUF_H__


#include <e32std.h>

enum TTransferBufferType
	{
	ETransferBufferFixedContiguous,
	ETransferBufferContiguous,
	ETransferBufferNonContiguous
	};

class RTransferWindow;

/**
	Resource handle to kernel memory object for use in conjunction with Transfer Windows handles.

	@lib euser.lib
	@since 6.2
 */
class RTransferBuffer : public RHandleBase
	{
	public:
		IMPORT_C TInt Create(TInt aBufferSize);
		IMPORT_C TInt GetBufferSize() const;
	};

/**
	Resource handle to kernel object facilitating zero-copy data exchange between processes.

	@lib euser.lib
	@since 6.2
 */
class RTransferWindow : public RHandleBase
	{
	public:
		IMPORT_C TInt Create(TInt aMaxBufferSize);
		IMPORT_C TInt Open(RTransferBuffer& aBuffer);
		IMPORT_C TInt MapInBuffer(const RTransferBuffer& aBuffer) const;
		IMPORT_C void WaitForBuffer() const;
		IMPORT_C void WaitForBuffer(TRequestStatus& aStatus) const;
		IMPORT_C void CancelWaitForBuffer() const;
		IMPORT_C void MapOutBuffer() const;
		IMPORT_C void WaitForBufferFree() const;
		IMPORT_C void WaitForBufferFree(TRequestStatus& aStatus) const;
		IMPORT_C void CancelWaitForBufferFree() const;
		IMPORT_C TUint8* GetBufferAddress() const;
		IMPORT_C TInt GetBufferSize() const;
	};


#endif