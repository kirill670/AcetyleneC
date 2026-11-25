// RHeaderField.h
//
// Copyright (C) 2001 Symbian Ltd.

/** 
	@file RHeaderField.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __RHEADERFIELD_H__
#define __RHEADERFIELD_H__

// System includes
#include <e32base.h>
#include <http/thttphdrval.h>
#include <http/rhttppropertyset.h>
#include <http/rhttpheaders.h>

// Forward declarations
class CHeaderField;
class THeaderFieldPartIter;

// The default chunk size for Raw data should be set to the average length of a header field when encoded in
// plaintext
const TInt KDefaultRawChunkSize= 32;

/**
	@public
	@class			RHeaderField
	@since			7.0
	An proxy object for a single field in an HTTP header.  The class is used by
	implementations of CHeaderCodec in order to manipulate the header at the part and
	parameter level, or to obtain raw data, during a header encode/decode operation.
 */

//##ModelId=3B1E52A50396
class RHeaderField
	{
public: // methods

/** @fn				RHeaderField(CHeaderField& aHeaderField)
	Intended Usage:	Normal constructor.  Creates a header field proxy
					based on the internal representation.
	@since			7.0
	@param aHeaderField		(in) The internal representation of a header field
*/
	//##ModelId=3BA6004002BC
	RHeaderField(CHeaderField& aHeaderField);

/** @fn				Name()
	Intended Usage:	Obtain the name of the header field, e.g. Accept
	@since			7.0
	@return			The header field name as a string
*/
	IMPORT_C
	//##ModelId=3B1E52A503C0
	RStringF Name() const;

/** @fn				PartsL()
	Intended Usage:	Access the header value parts via an iterator
	@since			7.0
	@return			An iterator constructed to point at the first part
	@leave KErrNoMemory - insufficient free memory for object creation when decoding parts
	@leave KErrNotSupported - if decoding when counting parts fails
*/
	IMPORT_C
	//##ModelId=3B1E52A503BF
	THeaderFieldPartIter PartsL();

/** @fn				RawDataL(TPtrC8& aRawData)
	Intended Usage:	Get the header field's raw data representation.  This will flip the
					internal state of the header, if it's not already in Raw form.
					Requires a Codec to be set.
	@since			7.0
	@param			aRawData	(inout) An 8-bit pointer descriptor that is set during
										the call to point at the data buffer
										representing the header in its raw form.
	@post			The header field is in either its 'raw' state (following a
					successful conversion) or in a 'corrupt' state if decoding failed.
	@leave KErrNoMemory - insufficient free memory for object creation when decoding parts
	@leave KErrNotSupported - if decoding when counting parts fails
	@leave Various error codes from <httperr.h> indicating a decode failure
*/
	IMPORT_C
	//##ModelId=3B1E52A503B9
	void RawDataL(TPtrC8& aRawData);

/** @fn				Collection()
	Intended Usage:	Get a handle to the headers collection that this field belongs to
	@since			7.0
	@return			The header collection handle.
*/
	IMPORT_C
	//##ModelId=3BA6004002B2
	RHTTPHeaders Collection();

/** @fn				Collection()
	Intended Usage:	Set a part in the header. It replaces any existing part at the
					specified index.  Note this is for use only by the header codec,
					when converting Raw data into parsed header parts.
	@since			7.0
	@param			aPart	(in) The part to be added.  The header takes ownership of
								 the new part.
	@param			aIndex	(in) The index within the header of field of the part.
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
*/
	IMPORT_C
	//##ModelId=3B1E52A503B6
	void SetPartL(CHeaderFieldPart* aPart, TInt aIndex);

/** @fn				BeginRawDataL(TInt aChunkSize)
	Intended Usage:	When the header codec starts converting parsed header data into the
					raw form, it must first call this method to indicate that the raw
					data is being generated.  Memory allocations are done in chunks set
					at the specified size.
					Note this method is for use only by the header codec. 
	@since			7.0
	@param			aChunkSize	(in) (optional) The size to be used for raw data chunk
												allocation.
	@pre			The header field is in the 'parsed' state
	@post			The header field is still in the 'parsed' state
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
*/
	IMPORT_C
	//##ModelId=3B1E52A503B4
	void BeginRawDataL(TInt aChunkSize = KDefaultRawChunkSize);

/** @fn				WriteRawDataL(const TDesC8& aData)
	Intended Usage:	Add more Raw data, supplied as a descriptor.  The data is appended
					to the existing contents of the field's internal raw data buffer,
					which is extended as necessary.
					Note this method is for use only by the header codec. 
	@since			7.0
	@param			aData		(in) The data to append to the buffer.
	@pre			The header field is in the 'parsed' state
	@post			The header field is still in the 'parsed' state
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
*/
	IMPORT_C
	//##ModelId=3B1E52A503AB
	void WriteRawDataL(const TDesC8& aData);

/** @fn				WriteRawDataL(const TDesC8& aData)
	Intended Usage:	Add more Raw data, supplied as a single character.  The data is
					appended to the existing contents of the field's internal raw data
					buffer, which is extended as necessary.
					Note this method is for use only by the header codec. 
	@since			7.0
	@param			aData		(in) The character data to append to the buffer.
	@pre			The header field is in the 'parsed' state
	@post			The header field is still in the 'parsed' state
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
*/
	IMPORT_C
	//##ModelId=3B1E52A503AD
	void WriteRawDataL(TChar aData);

/** @fn				CommitRawData()
	Intended Usage:	Commits the Raw data.  The parsed header parts and parameters are
					removed, leaving the field in a the raw data form.
					Note this method is for use only by the header codec.
	@since			7.0
	@pre			The header field is in the 'parsed' state
	@post			The header field is in the 'raw' state
*/
	IMPORT_C
	//##ModelId=3B1E52A503AA
	void CommitRawData();

private: // attributes

	/** The internal representation of this header field
	*/
	//##ModelId=3B1E52A503A2
	CHeaderField& iHeaderField;
};

inline RHeaderField::RHeaderField(CHeaderField& aHeaderField)
	: iHeaderField(aHeaderField)
	{
	}

#endif // __CHEADERFIELD_H__
