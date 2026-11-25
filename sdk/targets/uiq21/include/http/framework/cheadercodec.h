// CHeaderCodec.h
//
// Copyright (C) 2001 Symbian Ltd

/** 
	@file CHeaderCodec.h
	@public
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __CHEADERCODEC_H__
#define __CHEADERCODEC_H__

// System includes
#include <e32base.h>
#include <http/framework/rheaderfield.h>

// Forward declarations
class CHeaderWriter;
class CHeaderReader;

/**
	@public
	@class			CHeaderCodec
	@since			7.0
	An abstract HTTP header codec.  

	Each instance of a concrete subclass of CHeaderCodec is associated with, and owned
	by, a specific	CProtocolHandler.  It provides on-demand encoding/decoding of
	HTTP header data, between the generic format used by clients/filters to formulate
	requests and interpret responses, and the raw format used by
	the transport handlers (and origin servers/gateways/etc.)

	The CHeaderCodec has an associated instance of a sub-class of each of
	CHeaderReader and CHeaderWriter.  It delegates the actual encoding and
	decoding function to these instances.

	Header codecs provide a mechanism for extensibility whereby if one codec can't
	decode (or encode) a given header, it locates a codec that can, and then delegates
	the task to that codec instead.
*/
//##ModelId=3C4C18850126
class CHeaderCodec : public CBase
	{
public: // methods

/** @fn				~CHeaderCodec()
	Intended Usage:	Destructor - cleans up and releases resources to the system.
	@since			7.0
*/
	//##ModelId=3C4C18850194
	IMPORT_C virtual ~CHeaderCodec();

/**
	@fn				EncodeHeaderL(RHeaderField& aHeader) const
	Intended Usage:	Encode the supplied header field.  This method uses the associated
					concrete CHeaderWriter object to do a conversion of the field into
					raw form from the generic internal representation.
	@since			7.0
	@param			aHeader		(in) A proxy for the header field to be encoded
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory;  additional
					error codes that occur during the encode are defined in <httperr.h>
 */
	//##ModelId=3C4C1885018C
	IMPORT_C void EncodeHeaderL(RHeaderField& aHeader) const;

/**
	@fn				EncodeHeaderL(RHeaderField& aHeader) const
	Intended Usage:	Decode the supplied header field.  This method uses the associated
					concrete CHeaderReader object to do a conversion of the field into
					the generic internal representation from the raw form.
	@since			7.0
	@param			aHeader		(in) A proxy for the header field to be decoded
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory;  additional
					error codes that occur during the decode are defined in <httperr.h>
 */
	//##ModelId=3C4C1885018A
	IMPORT_C void DecodeHeaderL(RHeaderField& aHeader) const;

/**
	@fn				CanEncode(RStringF aHeaderField) const = 0
	Intended Usage:	Concrete header codec classes must implement this method to
					indicate to the framework whether their concrete CHeaderWriter is
					capable of encoding the named header field.
	@since			7.0
	@param			aHeader		(in) A proxy for the header field to be encoded
	@return			A flag indicating ETrue if the field can be encoded.
 */
	//##ModelId=3C4C18850181
	virtual TBool CanEncode(RStringF aHeaderField) const = 0;

/**
	@fn				CanDecode(RStringF aHeaderField) const = 0
	Intended Usage:	Concrete header codec classes must implement this method to
					indicate to the framework whether their concrete CHeaderReader is
					capable of decoding the named header field.
	@since			7.0
	@param			aHeader		(in) A proxy for the header field to be encoded
	@return			A flag indicating ETrue if the field can be decoded.
 */
	//##ModelId=3C4C18850178
	virtual TBool CanDecode(RStringF aHeaderField) const = 0;

/**
	@fn				FindDelegateCodecL(RStringF aHeaderField) const = 0
	Intended Usage:	Concrete header codecs must be implement this method if they wish to
					delegate the encoding/decoding of particular header fields to a
					different codec.  
					This would be done if the codec doesn't have the ability itself to
					do the encode/decode but can locate an alternative that does.
					
					The caller takes ownership of the returned codec.
	@since			7.0
	@param			aHeader		(in) A proxy for the header field to be encoded
	@return			A pointer to the new CHeaderCodec, or NULL if one couldn't be found.
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
	*/
	//##ModelId=3C4C18850176
	virtual CHeaderCodec* FindDelegateCodecL(RStringF aHeaderField) const = 0;

protected: // methods

/**
	@fn				CHeaderCodec()
	Intended Usage:	Default constructor.
	@since			7.0
 */
	//##ModelId=3A914DF20273
	IMPORT_C CHeaderCodec();

/**
	@fn				ConstructL()
	Intended Usage:	Second phase construction in which any necessary allocation is done
	@since			7.0
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
 */
	//##ModelId=3C4C1885016E
	IMPORT_C void ConstructL();

protected: // attributes

	/** The owned header writer object that does actual encoding of header fields.
	*/
	//##ModelId=3C4C18850164
	CHeaderWriter* iWriter;

	/** The owned header reader object that does actual decoding of header fields.
	*/
	//##ModelId=3C4C1885015A
	CHeaderReader* iReader;

private: // methods

/**	@fn				Reserved1()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C1885016D
	inline virtual void Reserved1();

/**	@fn				Reserved2()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C1885016C
	inline virtual void Reserved2();

private: // attributes

	/** The most recently-obtained delegate codec
	*/
	//##ModelId=3C4C18850150
	mutable CHeaderCodec* iDelegateCodec;
	};


/**
	@public
	@class			CHeaderWriter
	@since			7.0
	An abstract HTTP header encoder.  CHeaderWriter provides an interface used by its
	owning codec to do conversion of header data from the generic internal header
	representation to the raw representation used for a particular protocol/transport.
	Specific sub-classes of CHeaderWriter are associated with specific protocol handlers.
 */

//##ModelId=3C4C188601D1
class CHeaderWriter : public CBase
	{
public: // methods

/** @fn				~CHeaderWriter()
	Intended Usage:	Destructor - cleans up and release resources to the system.
	@since			7.0
*/
	//##ModelId=3C4C188601FC
	IMPORT_C virtual ~CHeaderWriter();

/**
	@fn				EncodeHeaderL(RHeaderField& aHeader) const
	Intended Usage:	Encodes the supplied header field.  This method does a conversion
					of the field into raw form from the generic internal representation.

					Specific header writer sub-classes must implement this method.
	@since			7.0
	@param			aHeader		(in) A proxy for the header field to be encoded
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory;  additional
					error codes that occur during the encode are defined in <httperr.h>
 */
	//##ModelId=3C4C188601FA
	virtual void EncodeHeaderL(RHeaderField& aHeader) = 0;

protected: // methods

/**
	@fn				CHeaderWriter()
	Intended Usage:	Default constructor.
	@since			7.0
 */
	IMPORT_C CHeaderWriter();

/**
	@fn				ConstructL()
	Intended Usage:	Second phase construction in which any necessary allocation is done
	@since			7.0
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
 */
	//##ModelId=3C4C188601F9
	IMPORT_C void ConstructL();

private: // methods

/**	@fn				Reserved1()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C188601F1
	inline virtual void Reserved1();

/**	@fn				Reserved2()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C188601F0
	inline virtual void Reserved2();
	};


/**
	@public
	@class			CHeaderReader
	@since			7.0
	An abstract HTTP header decoder.  CHeaderReader provides an interface used by its
	owning codec to do conversion of header data from the raw representation used for
	a particular protocol/transport to the generic internal header representation.
	Specific sub-classes of CHeaderWriter are associated with specific protocol
	handlers.
 */

//##ModelId=3C4C188602FE
class CHeaderReader : public CBase
	{
public: // methods

/** @fn				~CHeaderReader()
	Intended Usage:	Destructor - cleans up and release resources to the system.
	@since			7.0
*/
	//##ModelId=3C4C1886031E
	IMPORT_C virtual ~CHeaderReader();

/**
	@fn				DecodeHeaderL(RHeaderField& aHeader) const
	Intended Usage:	Decodes the supplied header field.  This method does a conversion
					of the field from the generic internal representation into raw form.

					Specific header reader sub-classes must implement this method.
	@since			7.0
	@param			aHeader		(in) A proxy for the header field to be decoded
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory;  additional
					error codes that occur during the encode are defined in <httperr.h>
 */
	//##ModelId=3C4C1886031C
	virtual void DecodeHeaderL(RHeaderField& aHeader) = 0;

protected: // methods

/**
	@fn				CHeaderReader()
	Intended Usage:	Default constructor.
	@since			7.0
 */
	IMPORT_C CHeaderReader();

/**
	@fn				ConstructL()
	Intended Usage:	Second phase construction in which any necessary allocation is done
	@since			7.0
	@leaves			Standard Symbian OS error codes. e.g. KErrNoMemory.
 */
	//##ModelId=3C4C18860315
	IMPORT_C void ConstructL();

private: // methods

/**	@fn				Reserved1()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C18860314
	inline virtual void Reserved1();

/**	@fn				Reserved2()
	Intended Usage:	Reserve a slot in the v-table to preserve future BC
	@since			7.0
 */
	//##ModelId=3C4C18860313
	inline virtual void Reserved2();
	};


inline void CHeaderCodec::Reserved1()
	{}
inline void CHeaderCodec::Reserved2()
	{}
inline void CHeaderWriter::Reserved1()
	{}
inline void CHeaderWriter::Reserved2()
	{}
inline void CHeaderReader::Reserved1()
	{}
inline void CHeaderReader::Reserved2()
	{}

#endif /* __CHEADERCODEC_H__ */

