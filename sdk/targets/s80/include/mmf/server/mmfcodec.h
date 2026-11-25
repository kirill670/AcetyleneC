// include\mmf\common\mmfcodec.h
//
// Copyright  2002 Symbian Ltd. All rights reserved.
//
#ifndef __MMF_COMMON_CODEC_H__
#define __MMF_COMMON_CODEC_H__


#include <e32base.h>
#include <ecom\ECom.h>
#include <mmf\common\mmfutilities.h>
#include <mmfPluginInterfaceUIDs.hrh>

/*
 * This UID is the INTERFACE_UID for CMMFCodec.  It is used to search for codec plugins in plugin DLLs.
 * All codec plugin DLLs must include interface_uid = KMmfUidPluginInterfaceCodec in their .rss files.
 */

/**
 * @publishedAll
 * @released
 *
 * Indicates the result of processing data from the source buffer to a destination buffer
 * and provides functions to compare the result code.
 */
class TCodecProcessResult
	{
public:
	/**
	 * Flag to track the codec's processing status.
	 */
	enum TCodecProcessResultStatus
	{
	/** The codec successfully has completed its processing */
	EProcessComplete,
	/** Could not empty the source buffer becuase the destination buffer became full */
	EProcessIncomplete,
	/** Codec came across an end of data */
	EEndOfData,
	/** Could not fill the destination buffer because the source buffer has been emptied */
	EDstNotFilled,
	/** An error occured */
	EProcessError,
	/** 
	 * @deprecated 
	 * As 'EFrameIncomplete' but also requests a call to GetNewDataPosition 
	 */
	EProcessIncompleteRepositionRequest,
	/** 
	 * @deprecated
	 *As 'EFrameComplete' but also requests a call to GetNewDataPosition 
	 */
	EProcessCompleteRepositionRequest
	};

	/** Overloaded operator to test equality */
	TBool operator==(const TCodecProcessResultStatus aStatus) const {return (iStatus == aStatus);}
	/** Overloaded operator to test inequality */
	TBool operator!=(const TCodecProcessResultStatus aStatus) const {return (iStatus != aStatus);}

	/**
	 * @see enum TCodecProcessResultStatus
	 *
	 * The codec's processing status
	 */
	TCodecProcessResultStatus iStatus;
	/** The number of source bytes processed */
	TUint iSrcBytesProcessed;
	/** The number of bytes added to the destination buffer */
	TUint iDstBytesAdded;
public:
	/**
	 * Default constructor
	 */
	TCodecProcessResult() 
		:iStatus(EProcessError), iSrcBytesProcessed(0), iDstBytesAdded(0) {};
	};


class TFourCC; //forward reference
class CMMFBuffer; //forward reference

/**
 * @publishedAll
 * @released
 *
 *  CMMFCodec
 *	ECom plugin class for a codec that processes source data in a certain fourCC coding type and
 *  converts it to a destination buffer of another fourCC coding type.
 *  The function is synchronous as it is expected that the codec will be operating in its own thread
 *  of execution - usually via a CMMFDataPath or CMMFDataPathProxy
 *
 *  The codec can be instantiated in 3 different ways:
 *
 *  1.	NewL(const TFourCC& aSrcDatatype, const TFourCC& aDstDataType)
 *  This instantiate a codec that can convert the aSrcDatatype to a aDstDataType
 *  2.	NewL(const TFourCC& aSrcDatatype, const TFourCC& aDstDataType, const TDesC& aPreferredSupplier)
 *  This is similar to the above but is used where there may be multiple codecs that
 *  perform the same conversion - the idea is that a 3rd party deveoper may develop there own 
 *  controller and codecs and can ensure the controller uses their codecs by setting the preferredSupplier
 *  to themselves.
 *  3.	NewL(TUid aUid)	
 *  This is used to explicitly instantiated a codec where the uid is known.  This might be used by
 *  controlers that only support one codec type.
 *
 *  The processing of the data is handles by the codecs ProcessL() member
 *  The intention is that the source buffer for conversion is converted to the appropriate coding type
 *  in the destination buffer.  The buffers can be of any size.  Since the buffers can be of anysize there is no 
 *  guarantee that all the source buffer can be processed to fill the destination buffer or that the 
 *  all the source buffer may be processed before the destination is full.  Therefore the
 *  ProcessL needs to return a TCodecProcessResult returinmg the number of source bytes processed
 *  and the number of destination bytes processed along with a process result code defined thus:
 *	EProcessComplete - the codec processed all the source data into the sink buffer
 *	EProcessIncomplete - the codec filled sink buffer before all the source buffer was processed
 *	EDstNotFilled - the codec processed the source buffer but the sink buffer was not filled
 *	EEndOfData - the codec detected the end data - all source data in processed but sink may not be full
 *  EProcessError - the codec process error condition
 *  
 *  The ProcessL should start processing the source buffer from the iPosition data member of the source data 
 *	and start filling the destination buffer from its iPosition
 *	
 */
class CMMFCodec  : public CBase
{
public:
	//The function which instantiates an object of this type 
	// using the TFourCC codes as the resolver parameters.
	IMPORT_C static CMMFCodec* NewL(const TFourCC& aSrcDatatype, const TFourCC& aDstDataType);
	IMPORT_C static CMMFCodec* NewL(const TFourCC& aSrcDatatype, const TFourCC& aDstDataType, const TDesC& aPreferredSupplier);
	IMPORT_C static CMMFCodec* NewL(TUid aUid);
	static void SelectByPreference( RImplInfoPtrArray& aPlugInArray, const TDesC& aPreferredSupplier ) ;

	/**
	 * Sets codec configuration. This is a virtual function which does not need to be implemented 
	 * by a codec, but may be if required. This function provides additional configuration 
	 * information for the codec. The configuration is passed in as a descriptor.
	 * The default version leaves with KErrNotSupported.
	 *
	 * @param	"aConfigType"
	 *			The UID of the codec to configure.
	 * @param	"aConfigData"
	 *			Configuration information.
	 */
	virtual void ConfigureL(TUid /*aConfigType*/, const TDesC8& /*aConfigData*/) {User::Leave(KErrNotSupported);}

	/**
	 * Codec reset. Used to flush out status information when a reposition occurs. 
	 * This is a virtual function that is provided should the codec require resetting prior to use.
	 */
	virtual void ResetL() {}
	//Standardised destructor.
	inline virtual ~CMMFCodec();


	/**
	 * @see enum TCodecProcessResult
	 *
	 * Processes the data in the specified source buffer and writes the processed data to 
	 * the specified destination buffer.
	 * This function is synchronous, when the function returns the data has been processed. 
	 *
	 * This is a virtual function that each derived class must implement.
	 *
	 * @param	"aSource"
	 *			Source buffer containing data to encode or decode.
	 * @param	"aDestination"
	 *			Destination buffer to hold the data after encoding or decoding.
	 * @return  Result of the processing.
	 */
	virtual TCodecProcessResult ProcessL(const CMMFBuffer& aSource, CMMFBuffer& aDestination) = 0;
private:
	TUid iDtor_ID_Key;
};

/**
 * Destructor
 */
inline CMMFCodec::~CMMFCodec()
	{
	// Destroy any instance variables and then
	// inform ecom that this specific 
	// instance of the interface has been destroyed.
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}

#endif

