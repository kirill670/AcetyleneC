// SMSUSET.H
//
// Copyright (c) 1999-2003 Symbian Ltd.  All rights reserved.


/*

 * History: gsmuset.h $
 * 
 *---------------------------------------------------------------------------
 */


/**
 * @file smsuset.h 
 * contains header file of the SMS settings.
 */


#if !defined (__SMSUSET_H__)
#define __SMSUSET_H__

#if !defined (__E32STD_H__)
#include "e32std.h"
#endif 


class RReadStream;
class RWriteStream;


class TSmsSettings
/**
SMS settings.

@publishedAll
@released
*/
	{
public:
	IMPORT_C TSmsSettings();

	inline const TTimeIntervalMicroSeconds32& Timeout() const;
	inline void SetTimeout(const TTimeIntervalMicroSeconds32& aTimeout);
	inline TInt SendTryLimit() const;
	inline void SetSendTryLimit(TInt aLimit);
	inline TBool DeletePDUsFromSIM() const;
	inline void SetDeletePDUsFromSIM(TBool aDelete);
	inline TBool DeletePDUsFromPhoneStores() const;
	inline void SetDeletePDUsFromPhoneStores(TBool aDelete);
	inline TBool DeletePDUsFromCombinedStores() const;
	inline void SetDeletePDUsFromCombinedStores(TBool aDelete);
	inline const TTimeIntervalMinutes& ReassemblyLifetime() const;
	inline void SetReassemblyLifetime(const TTimeIntervalMinutes& aReassemblyLifetime);
	inline TInt KSegmentationLifetimeMultiplier() const;
	inline void SetKSegmentationLifetimeMultiplier(TInt aKSegmentationLifetimeMultiplier);
	inline const TTimeIntervalMicroSeconds32& ModemInitializationTimeout() const;
	inline void SetModemInitializationTimeout(const TTimeIntervalMicroSeconds32& aTimeout);

	IMPORT_C void InternalizeL(RReadStream& aStream);
	IMPORT_C void ExternalizeL(RWriteStream& aStream) const;

private:
	enum
		{
        //sak 05/08/2004
        //gives more time to SMS stack and TSY to report about SMS sending result
        //waiting for official ICF from Symbian to fix the SMS timer
		KDefaultTimeoutMicroSeconds32=185000000 ///<185 sec
		};
	enum
		{
		KDefaultSendTryLimit=4
		};
	enum
		{
		KDefaultReassemblyLifetime=2*1440 ///< two days
		};
	enum
		{
		KDefaultKSegmentationLifetimeMultiplier=1200  ///< 1.2
		};
	enum
		{
		KDefaultModemInitializationTimeoutMicroSeconds32=30000000 ///<30sec
		};
	enum TSmsSettingsFlags
		{
		ESmsFlagDeletePDUsFromSIM=0x01,
		ESmsFlagDeletePDUsFromPhoneStores=0x02,
		ESmsFlagDeletePDUsFromCombinedStores=0x04
		};
private:
	TTimeIntervalMicroSeconds32 iTimeoutMicroSeconds32;	///<TimeOut period in microseconds for sending a PDU
	/** Number of attempts for sending a PDU.
	@deprecated 7.0	*/
	TInt iSendTryLimit;				
	TInt iFlags;								///<Contains TSmsSettingsFlags
	TTimeIntervalMinutes iReassemblyLifetime;///< Maximum time PDUs making a concatenated message stay in the reassembly store before they have all arrived
	TInt iKSegmentationLifetimeMultiplier;  ///<  Validity period is multiplied by this fraction, 1000=1:1
	TTimeIntervalMicroSeconds32 iModemInitializationTimeoutMicroSeconds32;///<TimeOut period in microseconds for initialising the modem
	};	

#include "smsuset.inl"

#endif // !defined __SMSUSET_H__
