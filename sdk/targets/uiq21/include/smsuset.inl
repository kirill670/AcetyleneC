/**
*@file contains the implementation of the inline function the TSmsSettings Class
*used to get and set the SMS settimngs
*/  
inline const TTimeIntervalMicroSeconds32& TSmsSettings::Timeout() const
/**
 * @return the time out value
 */
	{
	return iTimeoutMicroSeconds32;
	}

inline void TSmsSettings::SetTimeout(const TTimeIntervalMicroSeconds32& aTimeout)
/**
 * sets the time out value
 */
	{
	iTimeoutMicroSeconds32=aTimeout;
	}

inline TInt TSmsSettings::SendTryLimit() const
/**
 * @return the maximum number of attemps to send a SMS
 */
	{
	return iSendTryLimit;
	}

inline void TSmsSettings::SetSendTryLimit(TInt aLimit)
/**
 * sets the maximum number of attemps to send a SMS
 */
	{
	iSendTryLimit=aLimit;
	}

inline TBool TSmsSettings::DeletePDUsFromSIM() const
	
/**
 * @return if the PDU can be deleted from SIM
 */	{
	return iFlags&ESmsFlagDeletePDUsFromSIM;
	}

inline void TSmsSettings::SetDeletePDUsFromSIM(TBool aDelete)
/**
 * sets if the PDU can be deleted from SIM
 */
	{
	iFlags=aDelete? iFlags|ESmsFlagDeletePDUsFromSIM: iFlags&(~ESmsFlagDeletePDUsFromSIM);
	}

inline TBool TSmsSettings::DeletePDUsFromPhoneStores() const
/**
 * @return if the PDU can be deleted from the phone store
 */
	{
	return iFlags&ESmsFlagDeletePDUsFromPhoneStores;
	}

inline void TSmsSettings::SetDeletePDUsFromPhoneStores(TBool aDelete)
/**
 * sets if the PDU can be deleted from the phone store
 */
	{
	iFlags=aDelete? iFlags|ESmsFlagDeletePDUsFromPhoneStores: iFlags&(~ESmsFlagDeletePDUsFromPhoneStores);
	}

inline TBool TSmsSettings::DeletePDUsFromCombinedStores() const
/**
 * @return if the PDU can be deleted from the combined store
 */
	{
	return iFlags&ESmsFlagDeletePDUsFromCombinedStores;
	}

inline void TSmsSettings::SetDeletePDUsFromCombinedStores(TBool aDelete)
/**
 * sets if the PDU can be deleted from the combined store
 */
	{
	iFlags=aDelete? iFlags|ESmsFlagDeletePDUsFromCombinedStores: iFlags&(~ESmsFlagDeletePDUsFromCombinedStores);
	}

inline const TTimeIntervalMinutes& TSmsSettings::ReassemblyLifetime() const
/**
 * @return the value of the Reassembly store life time
 */
	{
	return iReassemblyLifetime;
	}

inline void TSmsSettings::SetReassemblyLifetime(const TTimeIntervalMinutes& aReassemblyLifetime)
/**
 * sets the value of the Reassembly store life time
 */
	{
	iReassemblyLifetime=aReassemblyLifetime;
	}

inline TInt TSmsSettings::KSegmentationLifetimeMultiplier() const
/**
 * @return the value of the segmentation store multiplier
 */
	{
	return iKSegmentationLifetimeMultiplier;
	}

inline void TSmsSettings::SetKSegmentationLifetimeMultiplier(TInt aKSegmentationLifetimeMultiplier)
/**
 * sets the value of the segmentation store multiplier
 */
	{
	iKSegmentationLifetimeMultiplier=aKSegmentationLifetimeMultiplier;
	}

inline const TTimeIntervalMicroSeconds32& TSmsSettings::ModemInitializationTimeout() const
/**
 * @return the value of the modem initialisation timeout duration
 */
	{
	return iModemInitializationTimeoutMicroSeconds32;
	}

inline void TSmsSettings::SetModemInitializationTimeout(const TTimeIntervalMicroSeconds32& aTimeout)
/**
 * sets the value of the modem initialisation timeout duration
 */
	{
	iModemInitializationTimeoutMicroSeconds32=aTimeout;
	}

