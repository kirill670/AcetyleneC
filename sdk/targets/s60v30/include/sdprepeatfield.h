/*
* =============================================================================
*  Name          : SdpRepeatField.h
*  Part of       : SDP Codec
*  Interface     : SDK API, SDP Codec API
*  Description   : 
*  Version       : 1.0
*
*  Copyright (c) 2003 Nokia Corporation. 
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation. 
* =============================================================================
*/

#ifndef SDPREPEATFIELD_H
#define SDPREPEATFIELD_H

//  INCLUDES
#include <e32base.h>
#include <StringPool.h>
#include "_sdpdefs.h"
#include "sdptypedtime.h"

// FORWARD DECLARATIONS
class RReadStream;
class RWriteStream;

// CLASS DECLARATION
/**
 *  @publishedAll
 *
 *	This class encapsulates the repeat times field of the 
 *  Session Description Protocol.
 *
 *	The normative reference for correct formatting and values is
 *	draft-ietf-mmusic-sdp-new-14 unless specified otherwise in
 *  member documentation. The implementation supports this normative
 *  reference, but does not enforce it fully. 
 *
 *  @lib sdpcodec.lib
 */
class CSdpRepeatField : public CBase
	{
    public: // Constructors and destructor
        /**
         *	Constructs a new repeat times field.
		 *	
         *	@param  const TDesC8& aText: A string containing a correctly 
         *              formatted field value terminated by a CRLF.
         *	@return CSdpRepeatField*: The new instance.
		 *	@leave  In error case function leaves.
         */
		IMPORT_C static	CSdpRepeatField* DecodeL(const TDesC8& aText);

        /**
         *	Constructs a new repeat times field and adds the pointer to the 
         *  cleanup stack.
		 *	
         *	@param  const TDesC8& aText: A string containing a correctly 
         *              formatted field value terminated by a CRLF.
         *	@return CSdpRepeatField*: The new instance.
		 *	@leave  In error case function leaves.
         */
		IMPORT_C static	CSdpRepeatField* DecodeLC(const TDesC8& aText);

        /**
         *	Constructs a new repeat times field.
		 *	
         *	@param  const TSdpTypedTime aRepeatInterval: Repeat interval value 
         *              greater than zero.
         *	@param  const TSdpTypedTime aActiveDuration: Active duration.
         *	@param  const RArray<TSdpTypedTime>& aOffsets: At least one time 
         *              offset.
         *	@return CSdpRepeatField*: The new instance.
		 *	@leave  In error case function leaves.
         */
		IMPORT_C static	CSdpRepeatField* NewL(
                                        const TSdpTypedTime  aRepeatInterval,
										const TSdpTypedTime  aActiveDuration,
										const RArray<TSdpTypedTime>& aOffsets);

        /**
         *	Constructs a new repeat times field and adds the pointer to the 
         *  cleanup stack.
		 *	
         *	@param  const TSdpTypedTime aRepeatInterval: Repeat interval value 
         *              greated than zero.
         *	@param  const TSdpTypedTime aActiveDuration: Active duration.
         *	@param  const RArray<TSdpTypedTime>& aOffsets: At least one time 
         *              offset.
         *	@return CSdpRepeatField*: The new instance.
		 *	@leave  In error case function leaves.
         */
		IMPORT_C static	CSdpRepeatField* NewLC(
                                        const TSdpTypedTime  aRepeatInterval,
										const TSdpTypedTime aActiveDuration,
										const RArray<TSdpTypedTime>& aOffsets);

		/**
		 *	Deletes the resources held by the instance.
		 */
		IMPORT_C ~CSdpRepeatField();

    public: // New functions
		/**
		 *	Outputs the field formatted according to SDP syntax and including
		 *  the terminating CRLF.
		 * 
		 *	@param  RWriteStream& aStream: Stream used for output. On return 
         *              the stream includes correctly formatted repeat field.
		 *	@leave  In error case function leaves.
		 */
		IMPORT_C void EncodeL(RWriteStream& aStream) const;

		/**
		 *	Creates a new instance that is equal to the target.
		 *
		 *	@return CSdpRepeatField*: The new instance.
		 *	@leave  In error case function leaves.
		 */
		IMPORT_C CSdpRepeatField * CloneL() const;

		/**	
		 *	Compares this instance to another for equality.
		 *
		 *	@param const CSdpRepeatField& aObj: The instance to compare to.
		 *	@return TBool: ETrue if equal, EFalse if not.
		 */
		IMPORT_C TBool operator == (const CSdpRepeatField & aObj) const;

		/**
		 *	Gets the repeat interval.
		 *
		 *	@return const TSdpTypedTime: The repeat interval.
		 */
		IMPORT_C const TSdpTypedTime RepeatInterval() const;

		/**
		 *	Sets the repeat interval.
		 *
         *	@param  const TSdpTypedTime aValue: Repeat interval value greater 
         *              than zero.
         *	@leave KErrSdpCodecRepeatField if aValue is not positive integer 
         *              value.
		 */
		IMPORT_C void SetRepeatIntervalL(const TSdpTypedTime  aValue);

		/**
		 *	Gets the active duration..
		 *
		 *	@return const TSdpTypedTime: The active duration.
		 */
		IMPORT_C const TSdpTypedTime ActiveDuration() const;

		/**
		 *	Sets the active duration.
		 *
         *	@param  const TSdpTypedTime aValue:	Active duration.
		 */
		IMPORT_C void SetActiveDuration(const TSdpTypedTime aValue);

		/**
		 *	Gets the array of time offsets.
		 *  This array is used directly for element insertion and removal.
		 *
		 *	@return const RArray<TSdpTypedTime>&: The offsets.
		 */
		IMPORT_C const RArray<TSdpTypedTime>& TimeOffsets() const;

		/**
		 *	Sets the time offsets.
		 *
         *	@param  const RArray<TSdpTypedTime>& aOffsets: At least one time 
         *              offset.
		 *	@leave  In error case function leaves.
		 */
		IMPORT_C void SetTimeOffsetsL(const RArray<TSdpTypedTime>& aValue);

    public:
		/**
         *  Externalizes the object to stream
         *
         *  @param aStream Stream where the object's state will be stored
         */
		void ExternalizeL(RWriteStream& aStream) const;
		
		/**
         *  Creates object from the stream data
         *
         *  @param aStream Stream where the object's state will be read	
         *  @return Initialized object
         */
		static CSdpRepeatField* InternalizeL(RReadStream& aStream);

	private:
		CSdpRepeatField(const TSdpTypedTime aRepeatInterval,
						const TSdpTypedTime aActiveDuration);
		CSdpRepeatField();
		void ConstructL(const TDesC8& aText);
		void ConstructL(const RArray<TSdpTypedTime>& aOffsets);
        

    private: // Data
        RStringPool iPool;
		TSdpTypedTime iRepeatInterval;
		TSdpTypedTime iActiveDuration;
		RArray<TSdpTypedTime> iTimeOffsets;

		__DECLARE_TEST;
	};

#endif
