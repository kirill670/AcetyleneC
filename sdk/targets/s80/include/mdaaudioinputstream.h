
// MdaAudioInputStream.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//



#ifndef __MDAAUDIOINPUTSTREAM_H
#define __MDAAUDIOINPUTSTREAM_H


#include <e32std.h>
#include <mmf\common\Mmfbase.h>
#include <mmf\common\mmfstandardcustomcommands.h>
#include <mda\common\base.h>      


/**
@publishedAll
@released

Class for audio output stream callback.
*/
class MMdaAudioInputStreamCallback 
	{
public:
/**
	Called when the open package comple 
	
	@param "aError"	"a an error value which indicate if open success or not"
*/
	virtual void MaiscOpenComplete(TInt aError) = 0;

/**
	Called when the buffer has been copied from the server 
	
	@param "aError"	"a an error value"
	@param "aError"	"a reference to the buffer that has been copied"
*/
	virtual void MaiscBufferCopied(TInt aError, const TDesC8& aBuffer) = 0;

/**
	Called when sound device has stopped recording sound 
	
	@param "aError"	"a an error value which indicate record success or not"
*/	
	virtual void MaiscRecordComplete(TInt aError) = 0;
	};


class CMMFMdaAudioInputStream;
/**
@publishedAll
@released

Base class for audio intput stream.
*/
class CMdaAudioInputStream : public CBase
	{
public:
/**
	To instantiate a new audio output stream using default priority preferences

	@param "aCallBack"	"a reference to an MMdaAudioInputStreamCallback object" 
	@return "A pointer to CMdaAudioInputStream"
	@leave	""	"This method can leave with any of the system-wide error codes."
*/
	
	IMPORT_C static CMdaAudioInputStream* NewL(MMdaAudioInputStreamCallback& aCallBack);
/**
	To instantiate a new audio output stream.

	@param "aCallBack"	"a reference to an MMdaAudioInputStreamCallback object" 
	@param "aPriority"	"the priority value" 
	@param "TMdaPriorityPreference"	"the TMdaPriorityPreference value"
	@return "A pointer to CMdaAudioInputStream"
	@leave	""	"This method can leave with any of the system-wide error codes."
*/
	
	IMPORT_C static CMdaAudioInputStream* NewL(MMdaAudioInputStreamCallback& aCallBack,
		TInt aPriority,	TMdaPriorityPreference aPref);

	~CMdaAudioInputStream();

/**
	To set audio proprties

	@param "aSampleRate"	"a sample rate" 
	@param "aChannels"		"a channel" 
*/
	IMPORT_C void SetAudioPropertiesL(TInt aSampleRate, TInt aChannels);

/**
	To open a stream package

	@param "aSettings"	"a pointer to an TMdaPackage object" 
*/
	IMPORT_C void Open(TMdaPackage* aSettings);

/**
	To set audio volume

	@param "aNewGain"	"a specified audio gain" 
*/
	IMPORT_C void SetGain(TInt aNewGain);
	
/**
	To return the current gain

	@return "a current gain value in integer"
*/	
	IMPORT_C TInt Gain() const;

/**
	To return the maximum gain level

	@return "the maximum gain value in integer, which supported by sound device"
*/
	IMPORT_C TInt MaxGain() const;	
	
/**
	To set audio balance

	@param "aBalance"	"a specified balance volume" 
*/
	IMPORT_C void SetBalanceL(TInt aBalance = KMMFBalanceCenter);
	
/**
	To return the current balance in integer

	@return "the current balance value in integer"
*/	
	IMPORT_C TInt GetBalanceL() const;

/**
	To set audio priority

	@param "aPriority"	"a specified priority volume" 
	@param "aPref"		"a specified preference volume" 
*/
	IMPORT_C void SetPriority(TInt aPriority, TMdaPriorityPreference aPref);
	
/**
	Read data from a stream.

	@param "aData"	"a reference to a buffer to be written into" 
*/
	IMPORT_C void ReadL(TDes8& aData);

/**
	To stop reading data from a stream
*/
	IMPORT_C void Stop();

/**
	To return the current position in the data stream

	@return "the current position in integer"
*/	
	IMPORT_C const TTimeIntervalMicroSeconds& Position();

/**
	To return the current number of bytes recorded by audio hardware

	@return "the current current number of bytes recorded by audio hardware in integer"
*/	
	IMPORT_C TInt GetBytes();

	
/**
    To set the data type.

	Leaves with KErrNotSupported with everything other than PCM16	
*/
	IMPORT_C void SetDataTypeL(TFourCC aAudioType);

/**
	Get the Data Type. 
	
	Always returns PCM16
*/
	IMPORT_C TFourCC DataType() const;
private:
	CMdaAudioInputStream();
private:
	CMMFMdaAudioInputStream* iProperties;
	};

#endif
