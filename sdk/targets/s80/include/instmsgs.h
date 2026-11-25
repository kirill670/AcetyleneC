/**
@file INSTMSGS.CPP

Copyright (c) 1997-2003 Symbian Ltd. All rights reserved.

Messages sent between EPOC InstSrv class and PC based installer (EPOCInstall)

@publishedPartner
*/

#if !defined(__INSTMSGS_H__)
#define __INSTMSGS_H__

/**
Messages sent by instsrv
@publishedPartner
@released
*/
enum TInstEPOCMsg 
	{
	EInstEPOCMsgHello,
	EInstEPOCMsgGetSISFile,
	EInstEPOCMsgInstallDialog,
	EInstEPOCMsgLanguageDialog,
	EInstEPOCMsgDriveDialog,
	EInstEPOCMsgQuestionDialog,
	EInstEPOCMsgTextDialog,
	EInstEPOCMsgOptionsDialog,
	EInstEPOCMsgErrorDialog,
	EInstEPOCMsgAbortRetrySkipDialog,
	EInstEPOCMsgInUseDialog,
	EInstEPOCMsgSecWarningDialog,
	EInstEPOCMsgEvent,
	EInstEPOCMsgExiting,
	EInstEPOCMsgRevocationQueryDialog,
	EInstEPOCMsgRevocationDialog,
	EInstEPOCMsgUsernamePasswordDialog,
	EInstEPOCMsgRevocationCheckProgressDialogOn,
	EInstEPOCMsgRevocationCheckProgressDialogOff,
	EInstEPOCMsgUntrustedDialog,
	EInstEPOCMsgGetJarFile,
	EInstEPOCMsgAppInUseDialog,
	EInstEPOCMsgCloseAllAppsDialog
	};

#define EInstEPOCMsgInstallSigned				(1<<0)
#define EInstEPOCMsgInstallValidationProblem	(1<<1)

/**
Messages sent by epocinst
@publishedPartner
@released
*/
enum TInstPCMsg 
	{
	EInstPCMsgHello,
	EInstPCMsgStart,
	EInstPCMsgReady,
	EInstPCMsgSelectDrive,
	EInstPCMsgSelectLanguage,
	EInstPCMsgSelectQuestion,
	EInstPCMsgSelectOptions,
	EInstPCMsgSelectDelDepend,
	EInstPCMsgSelectText,
	EInstPCMsgSelectAbortRetrySkip,
	EInstPCMsgSelectInUse,
	EInstPCMsgSelectSecWarning,
	EInstPCMsgSISData,
	EInstPCMsgGoodBye,
	EInstPCMsgSelectRevocationQueryDialog,
	EInstPCMsgSelectRevocationDialog,
	EInstPCMsgSelectUsernamePassword,
	EInstPCMsgUntrustedQueryDialog,
	EInstPCMsgJarData,
	EInstPCMsgSelectAppInUse,
	EInstPCMsgSelectCloseAllApps
	};

#endif
