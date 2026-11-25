// BARSREAD.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __BARSREAD_H__
#define __BARSREAD_H__

#include <e32std.h>
#include <badesca.h>

/**
 *
 * Interprets resource data read from a resource file.
 *
 * To use an instance of this class, pass the buffer containing the
 * resource data to it by calling <code>SetBuffer()</code>.The buffer
 * containing the resource data is created by <code>AllocReadLC()</code>
 * or <code>AllocReadL()</code> which reads the specified resource into
 * it.The current position within the buffer is always maintained and any
 * request for data is always supplied from the current position. The
 * current position is always updated .
 *
 * @since 5.0
 * @lib "bafl.lib"
 */
class TResourceReader
    {
public:
    IMPORT_C void SetBuffer(const TDesC8* aBuffer);
    IMPORT_C const TAny* Ptr();

    // Read counted strings into allocated buffer
    inline HBufC*   ReadHBufCL();
    IMPORT_C HBufC8*  ReadHBufC8L();
    IMPORT_C HBufC16* ReadHBufC16L();

    // Build pointer from a counted string
    inline TPtrC   ReadTPtrC();
    IMPORT_C TPtrC8  ReadTPtrC8();
    IMPORT_C TPtrC16 ReadTPtrC16();

    // Build pointer from a counted string in an array of counted strings,
    // also setting the buffer to be used.
    inline TPtrC ReadTPtrC(TInt aIndex,const TDesC8* aBuffer);
    IMPORT_C TPtrC8 ReadTPtrC8(TInt aIndex,const TDesC8* aBuffer);
    IMPORT_C TPtrC16 ReadTPtrC16(TInt aIndex,const TDesC8* aBuffer);

    // Build an array of strings from a resource array
    inline CDesCArrayFlat*   ReadDesCArrayL();
    IMPORT_C CDesC8ArrayFlat*  ReadDesC8ArrayL();
    IMPORT_C CDesC16ArrayFlat* ReadDesC16ArrayL();

    IMPORT_C TInt ReadInt8();
    IMPORT_C TUint ReadUint8();
    IMPORT_C TInt ReadInt16();
    IMPORT_C TUint ReadUint16();
    IMPORT_C TInt ReadInt32();
    IMPORT_C TUint ReadUint32();
    IMPORT_C TReal64 ReadReal64();

    IMPORT_C void Read(TAny* aPtr,TInt aLength);
    IMPORT_C void Rewind(TInt aLength);
    IMPORT_C void Advance(TInt aLength);
private:
    void MovePtr(const TUint8* aPtr);
private:
    const TDesC8* iBuffer;
    const TUint8* iCurrentPtr;
    const TUint8* iEndPtr;
    };

#if defined(_UNICODE)
/**
 *
 * Interprets the data at the current buffer position as leading byte
 * count data and constructs a build independent heap descriptor
 * containing a copy of this data.
 *
 * The data is interpreted as:a byte value defining the number of text
 * characters or the length of binary datafollowed by:the text characters
 * or binary data. This resource data is interpreted as either 8bit or
 * 16bit, depending on the build.If the value of the leading byte is
 * zero, the function assumes that no data follows the leading byte and
 * returns a <code>NULL</code> pointer.The current position within the
 * resource buffer is updated. If the resulting position lies beyond the
 * end of the resource buffer, then the function raises a BAFL 4
 * panic.Use this build independent variant when the resource contains
 * text. If the resource contains binary data, use the explicit 8bit
 * variant <code>ReadHBufC8L()</code>.
 *
 * @returns   "HBufC*"
 *            A pointer to the heap descriptor containing a copy of
 *            the data following the leading byte count at the
 *            current position within the resource buffer. The
 *            pointer can be <code>NULL</code>.
 */
inline HBufC* TResourceReader::ReadHBufCL()
    {return ReadHBufC16L();}

/**
 *
 * Interprets the data within the specified resource buffer as an array
 * of leading byte count data and constructs a non modifiable pointer
 * descriptor to represent an element within this array.
 *
 * The function sets the buffer containing the resource data and sets the
 * current position to the start of this buffer. Any buffer set by a
 * previous call to <code>SetBuffer()</code> etc, is lost.The buffer is
 * expected to contain an array of data elements preceded by a
 * <code>TInt16</code> value defining the number of elements within that
 * array.Each element of the array is interpreted as:a byte value
 * defining the number of text characters or the length of binary
 * datafollowed by:the text characters or binary data. This resource data
 * is interpreted as either 8bit or 16bit, depending on the build.If the
 * value of the leading byte is zero, calling <code>Length()</code> on
 * the returned <code>TPtrC</code> returns zero.The current position
 * within the resource buffer is updated. If the resulting position lies
 * beyond the end of the resource buffer, then the function raises a BAFL
 * 4 panic.Use this build independent variant when the elements contain
 * text. If the elements contain binary data, use the explicit 8bit
 * variant <code>ReadTPtrC8(TInt,constTDesC8*)</code>.
 *
 * @param     "TInt aIndex"
 *            The position of the element within the array. This
 *            value is relative to zero.
 * @param     "const TDesC8* aBuffer"
 *            The buffer containing the resource data.
 * @returns   "TPtrC"
 *            A non modifiable pointer descriptor representing the
 *            data following the leading byte count of the element
 *            at the specified position within the array.
 */
inline TPtrC TResourceReader::ReadTPtrC()
    {return ReadTPtrC16();}
inline TPtrC TResourceReader::ReadTPtrC(TInt aIndex,const TDesC8* aBuffer)
    {return ReadTPtrC16(aIndex, aBuffer);}

/**
 *
 * Interprets the data at the current buffer position as an array of
 * leading byte count data and constructs a build independent flat array
 * of descriptors.
 *
 * Each descriptor in the descriptor array corresponds to an element of
 * the resource array.At the current buffer position, the buffer is
 * expected to contain an array of data elements preceded by a
 * <code>TInt16</code> value defining the number of elements within that
 * array.Each element of the array is interpreted as:a byte value
 * defining the number of text characters or the length of binary
 * datafollowed by:the text characters or binary data. This resource data
 * is interpreted as either 8bit or 16bit, depending on the build.The
 * current position within the resource buffer is updated. If the
 * resulting position lies beyond the end of the resource buffer, then
 * the function raises a BAFL 4 panic.Use this build independent variant
 * when the elements contain text. If the elements contain binary data,
 * use the explicit 8bit variant <code>ReadDesC8ArrayL()</code>.
 *
 * @returns   "CDesCArrayFlat*"
 *            A pointer to a build independent flat descriptor
 *            array.
 */
inline CDesCArrayFlat* TResourceReader::ReadDesCArrayL()
    {return ReadDesC16ArrayL();}
#else
inline HBufC* TResourceReader::ReadHBufCL()
    {return ReadHBufC8L();}
inline TPtrC TResourceReader::ReadTPtrC()
    {return ReadTPtrC8();}
inline TPtrC TResourceReader::ReadTPtrC(TInt aIndex,const TDesC8* aBuffer)
    {return ReadTPtrC8(aIndex, aBuffer);}
inline CDesCArrayFlat* TResourceReader::ReadDesCArrayL()
    {return ReadDesC8ArrayL();}
#endif



#endif
