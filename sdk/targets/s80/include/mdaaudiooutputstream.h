// MdaAudioOutputStream.h
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//

#ifndef __MDAAUDIOOUTPUTSTREAM_H
#define __MDAAUDIOOUTPUTSTREAM_H


#include <e32std.h>
#include <mmf\common\Mmfbase.h>
#include <mmf\common\mmfstandardcustomcommands.h>
#include <mda\common\base.h>      
#include <mda\client\utility.h>


/**
@publishedAll
@released

Class for audio output stream callback.
*/
class MMdaAudioOutputStreamCallback 
	{
public:
/**
	Called when the open package comple 
	
	@param "aError"	"a an error value which indicate if open success or not"
*/
	virtual void MaoscOpenComplete(TInt aError) = 0;

/**
	Called when the buffer has been copied to the server 
	
	@param "aError"	"a an error value"
	@param "aError"	"a reference to the buffer that has been copied"
*/
	virtual void MaoscBufferCopied(TInt aError, const TDesC8& aBuffer) = 0;

/**
	Called when sound device has stopped playing sound 
	
	@param "aError"	"a an error value which indicate play success or not"
*/	
	virtual void MaoscPlayComplete(TInt aError) = 0;
	};


class CMMFMdaAudioOutputStream;
/**
@publishedAll
@released

Base class for audio output stream.
Note all the virtual functions that need to retained for BC with 6.1

*/
class CMdaAudioOutputStream : public CBase
	{
public:
/**
	To instantiate a new audio output stream.

	@param "aCallBack"	"a reference to an MMdaAudioOutputStreamCallback object" 
	@param "aServer"  "a pointer to a CMdaServer"
	@return "A pointer to CMdaAudioOutputStream"
	@leave	""	"This method can leave with any of the system-wide error codes."
*/

	IMPORT_C static CMdaAudioOutputStream* NewL(MMdaAudioOutputStreamCallback& aCallBack,
												CMdaServer* aServer = NULL);

/**
	To instantiate a new audio output stream.

	@param "aCallBack"	"a reference to an MMdaAudioOutputStreamCallback object" 
	@param "aPriority"	"the priority value" 
	@param "TMdaPriorityPreference"	"the TMdaPriorityPreference value"
	@return "A pointer to CMdaAudioOutputStream"
	@leave	""	"This method can leave with any of the system-wide error codes."
*/
	
	IMPORT_C static CMdaAudioOutputStream* NewL(MMdaAudioOutputStreamCallback& aCallBack,
												TInt aPriority,
												TMdaPriorityPreference aPref = EMdaPriorityPreferenceTimeAndQuality);


	~CMdaAudioOutputStream();

/**
	To set audio proprties

	@param "aSampleRate"	"a sample rate" 
	@param "aChannels"		"a channel" 
*/
	virtual void SetAudioPropertiesL(TInt aSampleRate, TInt aChannels);

/**
	To open a stream package

	@param "aSettings"	"a pointer to an TMdaPackage object" 
*/
	virtual void Open(TMdaPackage* aSettings);

/**
	To return the maximum volume level

	@return "the maximum volume value in integer, which supported by sound device"
*/
	virtual TInt MaxVolume();

/**
	To return the current volume

	@return "a current volume value in integer"
*/	
	virtual TInt Volume();

/**
	To set audio volume

	@param "aNewVolume"	"a specified audio volume" 
*/
	virtual void SetVolume(const TInt aNewVolume);

/**
	To set audio priority

	@param "aPriority"	"a specified priority volume" 
	@param "aPref"		"a specified preference volume" 
*/
	virtual void SetPriority(TInt aPriority, TMdaPriorityPreference aPref);
	
/**
	To write data to stream

	@param "aData"	"a reference to the stream data" 
*/
	virtual void WriteL(const TDesC8& aData);

/**
	To stop write data to stream
*/
	virtual void Stop();

/**
	To return the current position in the data stream

	@return "the current position in integer"
*/	
	virtual const TTimeIntervalMicroSeconds& Position();

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
	To return the current number of bytes rendered by audio hardware

	@return "the current current number of bytes rendered by audio hardware in integer"
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
	CMdaAudioOutputStream();
private:
	CMMFMdaAudioOutputStream* iProperties;
	};

#endif
