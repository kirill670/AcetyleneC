/*
* =============================================================================
*  Name          : SdpTypedTime.h
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

#ifndef SDPTYPEDTIME_H
#define SDPTYPEDTIME_H

//  INCLUDES
#include <e32std.h>
#include "_sdpdefs.h"

// FORWARD DECLARATIONS
class RReadStream;
class RWriteStream;

// CLASS DECLARATION
/**
 *  @publishedAll
 *
 *	This class implements the typed time element of the Session
 *	Description Protocol.
 *
 *	The normative reference for correct formatting and values is
 *	draft-ietf-mmusic-sdp-new-14 unless specified otherwise in
 *  member documentation. The implementation supports this normative
 *  reference, but does not enforce it fully. 
 *
 *  @lib sdpcodec.lib
 */
class TSdpTypedTime
	{
    public: // enums

        enum TUnit
            {
            ETimeUnitDays,      /** d */
            ETimeUnitHours,     /** h */
		    ETimeUnitMinutes,   /** m */
		    ETimeUnitSeconds,   /** s */
		    ETimeUnitNone,
            };

    public: // Constructors and destructor
		/**
		 *	Constructs a typed time equal to zero and with no time unit set.
		 */
		IMPORT_C TSdpTypedTime();

		/**
		 *	Constructs a typed time equal to specified value and time unit.
		 *
		 *	@param  TInt64 aValue: Time value.
		 *	@param  TUnit aUnit: Time unit.
		 */
		IMPORT_C TSdpTypedTime(TInt64 aValue, TUnit aUnit);

    public: // New functions
		/**	
		 *	Compares this instance to another for equality.
		 *
		 *	@param  const TSdpTypedTime& aObj: Another instance to compare with.
		 *	@return ETrue if equal, EFalse if not.
		 */
		IMPORT_C TBool operator == (const TSdpTypedTime& aObj) const;

		/**
		 *	Sets the typed time value.
		 *
		 *	@param  TInt64 aValue: Time value.
		 *	@param  TUnit aUnit: Time unit.
		 */
		IMPORT_C void SetValue(TInt64 aValue, TUnit aUnit);

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
		static TSdpTypedTime InternalizeL(RReadStream& aStream);
        
        /**
		 *	Output the field formatted according to SDP syntax and including
		 *  the terminating CRLF.
		 * 
		 *	@param aStream	Stream used for output.
		 */
        void EncodeL(RWriteStream& aStream) const;
        
        /**
         *	Construct a new origin field.
		 *		 
         *	@param aText A string containing a correctly formatted field value
		 *               terminated by a CRLF.
         *	@return The new instance.
         */
        static TSdpTypedTime DecodeL(const TDesC8& aText);

    public: // Data
		TInt64 iValue;
		TInt iUnit;

	};

#endif
