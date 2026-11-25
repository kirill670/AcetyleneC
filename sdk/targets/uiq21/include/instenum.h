// INSTENUM.H
// Copyright (c) 1997-1999 Symbian Ltd. All rights reserved.
//
// Installer engine enumeration values used throughout:
// - install engine
// - EPOC install application (AppInst.app)
// - PC based installer (EPOCInstall.exe)
//

#if !defined(__INSTENUM_H__)
#define __INSTENUM_H__

enum TInstQuestionDialogType
	{ 
	EInstUIReplaceExisting,
	EInstUIContinuePartial,
	EInstUIShuttingDownApps,
	EInstUIConfirmCancel,	// Note: the install engine doesn't actually use this
	EInstUIIncompatibleApp,	// Added for dependency check warning
	EInstUIUpgradeRMS       // preserve RMS store for midlet during upgrade?
	};

enum TInstErrorDialogType
	{
	EInstUIAlreadyInRom,
	EInstUIMissingDependency,
	EInstUIMsgRequireVer,
	EInstUIMsgRequireVerOrGreater,
	EInstUIMsgFileCorrupt,
	EInstUIMsgIncompatibleInstaller,
	EInstUIMsgFileUnicode,
	EInstUIMsgFileAscii,
	EInstUIMsgDiskNotPresent,
	EInstUIMsgCannotRead,
	EInstUIMsgCannotDelete,
	EInstUIMsgInvalidFileName,
	EInstUIMsgInvalidArchive,
	EInstUIMsgInvalidJavaVersion,
	EInstUIMsgFileNotFound,
	EInstUIMsgIconConversionError,
	EInstUIMsgInvalidJadFile,
	EInstUIMsgInvalidManifestFile,
	EInstUIMsgInsufficientSpaceOnDrive,
	EInstUIMsgDownloadError,
	EInstUIMsgInvalidDownloadLocation,
	EInstUIMsgMissingIcon,
	EInstUIMsgMIDletRunning,
	EInstUIMsgNoJavaAMSAuth,
	EInstUIMsgNoUnsignedUpgrade // unsigned midlet cannot upgrade signed one
	};

enum TInstallEngineEvent
	{
	EInstallEngineSetProgressBarFinalValue,
	EInstallEngineUpdateProgressBar,
	EInstallEngineSetDeletingFilesLabel,
	EInstallEngineRemovingFiles,
	EInstallEngineShuttingDownApps,
	EInstallEngineCopyingFiles,
	EInstallEngineAborted,
	EInstallEngineCompletedInstall,
	EInstallEngineCompletedUnInstall,
	EInstallEngineCompletedUnInstallButContainerRemovalFailed,
	EInstallEngineAbortedUnInstall,
	EInstallEngineCompletedNoMessage,
	EInstallEngineLeave,
	EInstallEngineConvertingIconsExtracting,
	EInstallEngineConvertingIconsLoading,
	EInstallEngineConvertingIconsConverting,
	EInstallEngineCreatingStubs,
	EInstallEngineDownloadingJar
	};

enum TSignatureValidationResult
	{
	EValidationSuceeded,
	ENoCertificate,
	ECertificateValidationException,
	ECertificateValidationError,
	ESignatureNotPresent,
	ESignatureCouldNotBeDecrypted,
	ESignatureCouldNotBeValidated,
	EPartialInstall,
	ENoCodeSigningExtension,
	ENoSupportedPolicyExtension
	};

enum TInstRevocationDialogMessage
	{
	EInvalidRevocationServerUrl,
	EUnableToObtainCertificateStatus,
	EResponseSignatureValidationFailure,
	EInvalidRevocationServerResponse,
	EInvalidCertificateStatusInformation,
	ECertificateStatusIsUnknown,
	ECertificateStatusIsRevoked
	};

enum TInstAbortRetrySkip
	{
	EInstAbort,
	EInstRetry,
	EInstSkip,
	};

#endif
