/**
 * @file INSTENG.H
 *
 * Copyright (c) 1997-2002 Symbian Ltd. All rights reserved.
 *
 * Installer engine, (handles installation & removal of SIS files)
 */

#if !defined(__INSTENG_H__)
#define __INSTENG_H__

// ===========================================================================
// INCLUDES
// ===========================================================================

#include <e32base.h>
#include <e32std.h>
#include <badesca.h>
#include <apfrec.h>
#include <apmstd.h>
#include <instenum.h>
#include <instform.h>
#include <jarfile.h>
#include <jadfile.h>

class CPKIXValidationResult;
class CPKIXCertChain;
class TOCSPOutcome;
class TResourceReader;
class CInstCapResult;
class MInstallCondVariableSupplier;
class CInstUninstHandler;
class CInstallationFile;
class CInstVarSupplier;
class CSISInstaller;
class TInstallPrefs;
class CAlgorithmIdentifier;
class CInstallEngineProxy;
class CSISRegistry;
class CSISSignatureInfoReader;
class MSecurityWarningDlgHandler;

// ===========================================================================
// CONSTANTS
// ===========================================================================

// location of SIS stub files
_LIT(KInstallSystemPath,"c:\\system\\install\\");
_LIT(KWildcards,"*.*");

// UID of install engine
const TUid KInstengUid = { 0x100042AB };

// ===========================================================================
// INTERFACES
// ===========================================================================

class MInstUIHandler
// This represents the User Interface handler for the install engine
// The higher code should provide one of these interfaces for the engine
// to use for a UI
	{
	public:
		virtual TBool DisplayInstallDialogL(const TDesC& aAppName, 
			const TDesC* aAppVendor,
			TSISType aType,
			TInt aMajor,TInt aMinor,TInt build,
			TBool aValidationProblem, 
			const CSISSignatureInfoReader* aSigReader,
			const TDesC& aPolicyOid, const TDesC& aSuggestedPolicyText,
			const TDesC* aDescription, const CArrayPtr<TDesC>* aNames)=0;
		/**
		 * Requests preferred language and dialect information from the UI.
		 * @param aAppName Application name
		 * @param aLanguages Array of languages supported by the SIS file. 
		 *     No duplicates. The order is backwards compared to the PKG 
		 *     file order, so the strings have to be displayed in the reverse 
		 *     order.
		 * @param aDialect Preferred dialect. Vendor/operator/region-specific.
		 *     Does not change, should be stored in a resource file. If not used,
		 *     set the parameter to zero. The dialect is stored in the high 6 
		 *     bits of the word and must be returned this way (unshifted).
		 * @return Must return index in the passed array that corresponds to the
		 *     user's selected preferred language. If out-of-bounds value is 
		 *     returned, the engine will abort installation. There is no 
		 *     "default" choice.
		 * @internalComponent
		 */
		virtual TInt DisplayLanguageDialogL(const TDesC& aAppName,
			const CArrayFix<TLanguage>& aLanguages,
			TInt16& aDialect)=0;
		virtual TChar DisplayDriveDialogL(const TDesC& aAppName,TInt aSize,
										  const CArrayFix<TChar>& aDriveLetters,
										  const CArrayFix<TInt>& aDriveSpaces)=0;
		virtual TInstFileTextOption DisplayTextDialogL(
			TInstFileTextOption aOption,
			const TDesC& aAppName,TPtr& aText)=0;
		virtual TBool DisplayQuestionDialogL(TInstQuestionDialogType aType,
											 const TDesC& aAppName,
											 TInt aMajor=0,
											 TInt aMinor=0,
											 TInt aExistMajor=0,
											 TInt aExistMinor=0)=0;
		virtual TBool DisplayOptionsDialogL(const TDesC& aAppName,
			const CDesCArray& aOptions,
			CArrayFix<TBool>& aSelections)=0;
		virtual void DisplayErrorDialogL(TInstErrorDialogType aMsgType,
			const TDesC& aAppName=_L(""),
			TInt aMajor=0,TInt aMinor=0,
			TInt aReqMajor=0,TInt aReqMinor=0)=0;
		virtual void HandleInstallEventL(TInstallEngineEvent aEvent, TInt aValue=0)=0;
		virtual TBool DisplaySecurityWarningDialogL(MSecurityWarningDlgHandler& aHandler, 
			TSignatureValidationResult aSigValidationResult,
			TBool aInstallAnyway) = 0;
		virtual TInstAbortRetrySkip DisplayAbortRetrySkipDialogL(const TDesC& aAppName,
											 TInt error) = 0;
		virtual TBool DisplayInUseDialogL(const TDesC& aAppName,
			const CDesCArray& aComponents) = 0;

		// Warn user that revocation checking is off, asking if they want to do it
		// Return whether to continue (True) or cancel (false), placing true
		// in aDoRevocationCheck if checking is required.
		virtual TBool DisplayRevocationQueryL(TBool& aDoRevocationCheck) = 0;

		// Warning/error dialog, resulting when something goes kafluey in the revocation check
		virtual TBool DisplayRevocationDialogL(
			const TInstRevocationDialogMessage aMessage, 
			const TOCSPOutcome* aOutcome,
			const TBool aWarningOnly) = 0;

		// Display a username/password dialog when the server uses the http basic
		// authentication protocol
		virtual TBool DisplayUsernamePasswordDialogL(TDesC*& aUsername,
			TDesC*& aPassword) = 0;

		/**
		 * Displays dialog telling the user that the online certificate check 
		 * is in progress, and offers her a chance to cancel it.
		 * @return ETrue on success, EFalse on error.
		 */
		virtual TBool DisplayRevocationCheckProgressDialogL() = 0;

		/**
		 * Dismisses revocation check progress dialog.
		 * @return ETrue on success, EFalse on error.
		 */
		virtual TBool DismissRevocationCheckProgressDialog() = 0;

		/**
		 * Displays "This application cannot be trusted" dialog and asks user 
		 * to install it anyway or to cancel installation.
		 * @param aAppName Application name
		 * @return ETrue to install anyway, EFalse to cancel installation.
		 */
		virtual TBool DisplayUntrustedQueryDialogL(const TDesC& aAppName) = 0;

		/**
		 * Informs user that the applications are in use. Return ETrue if the 
		 * user wishes to continue the removal process and close the
		 * applications anyway
		 * @param aAppNames The names of the applications in use
		 * @return ETrue if the user wishes to continue with removal
		 */
		virtual TBool ApplicationInUseL(const RPointerArray<HBufC>& aAppNames) = 0;

		/**
		 * Informs user that a file is in use and so therefore cannot be 
		 * deleted. Return ETrue if the user wishes to continue anyway
		 * @param aAppName The application name
		 * @param aFileName The file in use
		 * @return ETrue if the user wishes to continue
		 */
		virtual TBool FileInUseL(const TDesC& aAppName, const TDesC& aFileName) = 0;

		/**
		 * Displays dialog that asks the user to confirm closure of all running 
		 * applications. This is called when removal fails after calling 
		 * DisplayRunningAppsDialogL().
		 * @return True to close all applications, false to abort uninstallation.
		 */
		virtual TBool DisplayCloseAllAppsDialogL() = 0;
	};

// ===========================================================================
// CLASS DEFINITIONS
// ===========================================================================

class CInstallEngine : public CBase
// The main install engine class for installing & removing SIS files
	{
		// Construction/destruction
	public:	// public methods available at DLL interface
		IMPORT_C static CInstallEngine* NewForInstallL(const TDesC& aFileName,
			MInstUIHandler& aUIHandler, const TInstallPrefs& aPrefs);
		IMPORT_C static CInstallEngine* NewForUnInstallL(
			const TDesC& aFileName,	MInstUIHandler& aUIHandler);

		virtual ~CInstallEngine();

		// Engine control
	public:	// public methods available at DLL interface
		IMPORT_C void Start();
		IMPORT_C void Halt();
		IMPORT_C void Restart();
		IMPORT_C void CancelL();

		IMPORT_C TBool InstallationInProgress() const;
		IMPORT_C CInstallationFile& InstallationFile() const;

		IMPORT_C TBool CancelRequestNoConfirm() const;

		IMPORT_C static CInstCapResult* GetCapLC(TInt aAppUID, TInt aCapID);
		IMPORT_C static CInstCapResult* GetCapL(TInt aAppUID, TInt aCapID);
		IMPORT_C static TLanguage GetPreferredLanguage();
		IMPORT_C static TBool IsMIDPJar(const TFileName& jarFileName);	
	
		/** Lists applications signed with a particular certificate.
			@param aCertSerialNumber Certificate serial number
			@param aHashAlgorithm Hash algorithm used to hash 
				certificate issuer distinguished name; supported 
				algorithms are MD2, MD5, and SHA1.
			@param aIssuerNameHash Hash of the certificate issuer's 
				distinguished name, including type and length fields 
				(the entire DER-encoded DN)
			@param aAppList Dynamic array of descriptors to put the 
				names of relevant SIS files into
		*/
		IMPORT_C static void GetAppListL(const TDesC8& aCertSerialNumber, 
			const CAlgorithmIdentifier& aHashAlgorithm,
			const TDesC8& aIssuerNameHash, 
			CDesCArrayFlat& aAppList);
		
	private:
		// Proxy class which kicks off the thread which runs the engine
		CInstallEngineProxy* iProxy;
	};

#include <instread.h>

#endif
