// VOBSERV.H
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __VOBSERV_H__
#define __VOBSERV_H__

#ifndef __E32DEF_H__
#include <e32def.h>
#endif
#ifndef __E32STD_H__
#include <e32std.h>
#endif
#ifndef __E32DES16_H__
#include <e32des16.h>
#endif
#ifndef __S32STRM_H__
#include <s32strm.h>
#endif
#ifndef __VUTIL_H__
#include <vutil.h>
#endif

class CVersitParser;

/**
 * A versit parser observer.
 *
 * An implimentator of this class can find out when the version number of the object being parsed
 * and also when a new parsor object is created.
 *
 * @since 6.1
 */
class MVersitObserver
	{
public:
/**
 * The Parser has parsed the 'Version' keyword.
 *
 * This function will be called whenever the parser has determined the version of the object being parsed to inform the observer 
 * which version was specified.
 *
 * @param     "CVersitParser* aParser"
 *            A pointer to the parser object that detected the version.
 * @param     "const TDesC16& aVersion"
 *            A unicode string containing the version number detected.
 */
	virtual void VersionSet(CVersitParser* aParser,const TDesC16& aVersion)=0;
/**
 * A new parser for an embedded object has been created.
 *
 * This function will be called whenever a new parser is created to parser an embedded object such as a VEVENT or VTODO or an AGENT.
 *
 * @param     "CVersitParser* aParser"
 *            A pointer to the new parser object.
 */
	virtual void NewParser(CVersitParser* aParser)=0;
private:
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	};

/**
 * A versit parser plug-in.
 *
 * An implimentator of this class can overide some of the low level behaviour of a versit parser. When there is no plug-in
 * the parser object will follow the the vCal v1.0 and vCard v2.1 way of doing things. However vCard v3.0 has different rules
 * on things like line wrapping and unwrapping and the functions in this class will be called to allow the behaviour to be changed.
 *
 * @since 6.1
 */
class MVersitPlugIn
	{
public:
/**
 * Should a space be added when unwrapping lines.
 *
 * This function is called to find out if a space when be adding when merging two lines together while unwrapping. 
 * If there is not a plugin then versit will add a space.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if a space is to be added and <code>EFalse</code> if not.
 */
	virtual TBool AddSpace()=0;				//Unwrapping lines
/**
 * Should the white space at the start of a line form part of the data.
 *
 * This function is called to find out if the white space (tabs and spaces) at the start a wrapped line should form part of the data.
 * If there is not a plugin then it will not be part of the data.
 *
 * @returns   "TBool"
 *            <code>EFalse</code> if the spaces are to be part of the data and <code>ETrue</code> if not.
 */
	virtual TBool DeleteAllSpaces()=0;		//Unwrapping lines
/**
 * How should the end of Base64 data be detected.
 *
 * Should a blank line be looked for to determine the end of Base64 data or only a line without a space at the start.
 * If there is not a plugin then a blank line will be looked for.
 *
 * @returns   "TBool"
 *            <code>ETrue</code> if a blank line should be looked for and <code>EFalse</code> if a line with out a space at the start.
 */
	virtual TBool NeedsBlankLine()=0;		//Unwrapping Base64 data
/**
 * Allows removing of escaped characters during internalising.
 *
 * This function is called to allow escaped characters in the property value to be delt with.
 * versit itself will deal with the escaping of semi-colons and the escape character (Yen character for Shift-JIS, Backslash otherwise).
 * Other characters like commas or carriage returns should be delt with by the plugin.
 *
 * Note: Although the sting passed into the function can be changed, it much not be made longer.
 *
 * @param     "TPtr16& aText"
 *            The text to have it's escaping removed.
 */
	virtual void RemoveEscaping(TPtr16& aText)=0;
/**
 * Allows the adding of escape characters during externalising.
 *
 * This function is called to allow characters in the property value to be escaped. versit itself will deal with the escaping
 * of semi-colons and the escape character (Yen character for Shift-JIS, Backslash other character sets).
 * Other characters like commas or carriage returns should be delt with by the plugin.
 *
 * Note: If the string passed into this function needs to be made longer then it should be done so with the command following command,
 * otherwise the cleanup stack will eventually panic.
 * <code>aText=aText->ReAllocL(newSize);</code>
 *
 * @param     "HBufC16*& aText"
 *            The text to be escaped.
 */
	virtual void AddEscaping(HBufC16*& aText)=0;
/**
 * Wrap the property value during an externalise.
 *
 * This function is called to wrap the propery value. If there is no plugin or this function returns <code>EFalse</code>
 * then versit will wrap the line according the vCal v1.0 and vCard v2.1 wrapping rules.
 *
 * @param     "RWriteStream& aStream"
 *            The text should be written to this stream with any needed line break characters.
 * @param     "TInt& aCurrentLineLength"
 *            The number of characters already writting to the current line, should be updated before returning.
 * @param     "const TPtr8& aText"
 *            The text of the property value, in the correct character set and encoded as necessary.
 * @returns   "TBool"
 *            ###<code>ETrue</code> if a blank line should be looked for and <code>EFalse</code> if a line with out a space at the start.
 */
	virtual TBool WrapLine(RWriteStream& aStream,TInt& aCurrentLineLength,const TPtr8& aText)=0;
/**
 * What encoding should be used to output the property value.
 *
 * This function will be called for each property in turn
 * and can specify what encoding should be used for that property when it is externalised.
 *
 * @param     "Versit::TVersitEncoding& aEncoding"
 *            This parameter is used to specify the encoding type to be used.
 * @param     "TBool aRequiresEncoding"
 *            This is <code>ETrue</code> if either the default encoding is not <code>ENoEncoding</code> 
 *            or any of the character in the data cannot be written out directly (eg. "="," " or tab).
 * @param     "Versit::TVersitEncoding aDefaultEncoding"
 *            The default encoding specifed by the user of the parser.
 * @param     "TUid aPropertyUid"
 *            The property UID of the property being externalised.
 * @param     "TUint aPropertyCharsetId"
 *            The character set UID of the character set being used to output the property.
 * @returns   "TBool"
 *            <code>ETrue</code> to specify the type encoding type to be used and <code>EFalse</code> to let versit choose it.
 */
	virtual TBool EncodingType(Versit::TVersitEncoding& aEncoding,TBool aRequiresEncoding,Versit::TVersitEncoding aDefaultEncoding
																						,TUid aPropertyUid,TUint aPropertyCharsetId)=0;
/**
 * Returns the encoding name to be used for a particular encoding type.
 *
 * Return the encoding name if you want to overide the name versit would otherwise use ("BASE64", "QUOTED-PRINTABLE", "8-BIT").
 *
 * @param     "Versit::TVersitEncoding aEncoding"
 *            The encoding the name is required for.
 * @returns   "const TDesC8&"
 *            The name to use for the encoding type otherwise a zero length descriptor if the default name should be used.
 */
	virtual const TDesC8& EncodingName(Versit::TVersitEncoding aEncoding)=0;
private:
	IMPORT_C virtual void Reserved1();
	IMPORT_C virtual void Reserved2();
	};

#endif