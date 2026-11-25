//
// SmlReportingCallback.h
//

#ifndef __SMLREPORTINGCALLBACK_H__
#define __SMLREPORTINGCALLBACK_H__

/**

The MSmlReportingCallback  callback is used by the SmlEngine to report progress & errors during the syncronisation process
	The "Error" function is used to report any errors
	The "Progress" function is used to report the percentage complete to the UI
	The "Notify" function reports notification message to the UI, such as "Connecting", "Sending data..." etc.

*/
class MSmlReportingCallback
	{
	public:
		
		enum TSmlReportingStatus	// Reporting current status
			{
			ESmlStartSync,
			ESmlConnecting,
			ESmlConnected,
			ESmlDisconnected,
			ESmlCompleted,
			ESmlSendingData,
			ESmlReceivingData,
			ESmlSlowSync,
			ESmlStoppedSync,
			};
		
		enum TSmlErrorLevel			// Error levels
			{
			ESmlWarning,
			ESmlFatalError,
			};
		
		enum TSmlError				// Error codes
			{
			ESmlConnectionError					=-8050,
			ESmlCannotCommunicateWithServer		=-8051,
			ESmlDatabaseAdapterIndexError		=-8052,
			ESmlParseCallbackError				=-8053,
			ESmlCommandInvalid					=-8054,
			
			ESmlSessionIdNotValid				=-8055,
			ESmlVerDTDMissing					=-8056,
			ESmlProtoMissing					=-8057,
			ESmlSyncHdrMissing					=-8058,
			ESmlTargetLocUriMissing				=-8059,
			ESmlSourceLocUriMissing				=-8060,
			ESmlTargetLocNameMissing			=-8061,
			ESmlSourceLocNameMissing			=-8062,
			ESmlMappingInfoMissing				=-8063,
			ESmlMappingInfoNotAcked				=-8064,

			ESmlVersionDTDNotSupported			=-8065,
			ESmlProtoNotSupported				=-8066,
			
			ESmlStatusCommandForCommandNotSent	=-8067,	// A status was received for a cmdId, but this cmdId was not sent
			ESmlStatusCommandNotTheSame			=-8068,	// A status was received but the command string does not matched the received one
			ESmlMissingStatusCommands			=-8069,	// Status command(s) weere expected but are missing			
			ESmlFailedToAddRecord				=-8070,	// Failed to add record in database
			ESmlFailedToReplaceRecord			=-8071,	// Failed to replace record in database
			ESmlFailedToDeleteRecord			=-8072,	// Failed to delete record in database

			ESmlXmlParsingError					=-8073,	// XML parsing error
			ESmlReferenceToolkitError			=-8074,	// There was an error reported in the reference toolkit
			};

		virtual void Error(TSmlErrorLevel aErrorLevel, TInt aError, TInt aInfo1, TInt aInfo2) = 0;
		virtual void Progress(TInt aPercentComplete) = 0;
		virtual void Notify(TSmlReportingStatus aStatus, TUint aUid) = 0;		
	};

#endif //__SMLREPORTINGCALLBACK_H__