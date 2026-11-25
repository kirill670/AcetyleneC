// INSTREAD.H
// Copyright (c) 1997-2003 Symbian Ltd. All rights reserved.
//
// Software installation SIS file reader classes
//

#ifndef __INSTREAD_H__
#define __INSTREAD_H__

// ===========================================================================
// INCLUDES
// ===========================================================================

#include <e32std.h>
#include <f32file.h>
#include <e32base.h>

#include <swi\SISFile.h>	// TODO : should be replaced by MSISFile only
#include <InstallationFile.h>
#include <insteng.h>

class CSubjectPublicKeyInfo;
class CJavaInstallFile;
class CSISFileInfoReader;
class CMIDletSuiteAttributes;
class CMIDPJarFile;
class CJadFile;
class CSISSignatureInfoReader;

// ===========================================================================
// CLASS DEFINITIONS
// ===========================================================================

/**
 * This class provides functions to access the contents of a SIS file.
 * This class is being deprecated. Clients should now use the CSISFile
 * class.
 * @internal
 * @deprecated
 */
class CSISInstallFile : public CInstallationFile
// CSISInstallFile - for reading SIS files (real & stub)
	{
	public:	// concrete implementation of CInstallationFile
		IMPORT_C virtual ~CSISInstallFile();
		IMPORT_C TInstallationFileType Type() const;
		IMPORT_C virtual TFileName FileName() const;
		// application name & vendor name
		IMPORT_C HBufC* AllocReadForApplicationNameLC() const;
		IMPORT_C HBufC* AllocReadForVendorNameLC() const;
		IMPORT_C TInt AppVersionMajor() const;
		IMPORT_C TInt AppVersionMinor() const;
		IMPORT_C TInt AppVersionBuild() const;
		IMPORT_C TInt MaximumSpaceToInstall() const;
		IMPORT_C TBool IsDigitallySigned() const;
	public:	// public exported interface
		// construction & initialization
		IMPORT_C static CSISInstallFile* NewL();
		// file related
		IMPORT_C void OpenL(RFs& aFs,const TDesC& aName,TFileMode aFileMode);
		IMPORT_C void Close();
		// *** THIS FUNCTION CAN LEAVE BUT CANNOT BE CHANGED BECAUSE OF BC ***
		IMPORT_C TBool IsPartialInstallation() const;
		IMPORT_C TBool FileIsCorruptedL() const;
		// SIS file header attributes
		IMPORT_C TInt Uid(TInt aUidNumber) const;
		IMPORT_C TUint16 Crc() const;
		IMPORT_C TUint16 Flags() const;
		IMPORT_C TInt InstallerVersion() const;	
		IMPORT_C TInt NumberOfLanguagesSupported() const;
		IMPORT_C TInt NumberOfPkgLines() const;
		// THIS 
		IMPORT_C TInt NumberOfPkgLinesDoneL() const;
		IMPORT_C TInt NumberOfDependencies() const;
		IMPORT_C TInt NumberOfCapabilities() const;
		IMPORT_C void ReadDriveAndLanguageL();
		IMPORT_C void InstallationDrive(TChar& aChar) const;
		IMPORT_C TLanguage LanguageL(TInt aIndex) const;
		IMPORT_C void GetLanguagesL(CArrayFix<TLanguage>& aLanguages) const;
		IMPORT_C void GetCapabilitiesL(CArrayFix<TInstCapability>& aCapabilites) const;
		// *** THIS FUNCTION CAN LEAVE BUT CANNOT BE CHANGED BECAUSE OF BC ***
		IMPORT_C TInt SpaceUsed();
		IMPORT_C TInstPackageLineType PkgLineTypeL(TInt aIndex) const;
		// SIS header allocation
		IMPORT_C HBufC8* AllocReadForFileSisStubLC();
		// to update header attributes during installation
		IMPORT_C void SetDrive(TChar aChar);
		IMPORT_C void SetLanguage(TLanguage aLanguage);
		IMPORT_C void SetSpaceUsedL(TInt aBytes);
		IMPORT_C void SetSystemFileL(RFile& aFile,TBool aIsPartial);
		IMPORT_C void UpdatePkgLinesDoneL(TInt aNumber);
		IMPORT_C CSISSignatureInfoReader* SignatureReaderL() const;
	public:	
		void SetTypeL(TInstallationFileType aType);
	public:	// public interface available within instread.dll only
		void GetContainerSISFileNameL(CSISFileInfoReader* aFileInfoReader,
			                          TFileName& containerSISName);
		void SetDialect(MSISFileExtended::TDialect aDialect);
		
	private:
		CSISInstallFile();
		void ConstructL();
		
	public:	// TODO : should be made private.		
		/**
		 * Due to updates in SIS file installation. This class is now
		 * a simple layer on top of SISFile. All functions of this class 
		 * simply call the function of this SISFile member.
		 */
		 MSISFileExtended* iSISFile;
		 mutable CSISSignatureInfoReader* iSignatureInfo;
	};
	
class CSISFileInfoReader : public CBase
// reads file info block within SIS file
	{
	public: // public exported interface
		IMPORT_C static CSISFileInfoReader* NewLC(
			CSISInstallFile& aInstallationFile, TInt aIndex);
		IMPORT_C ~CSISFileInfoReader();
		IMPORT_C TBool IsLanguageDependent() const;
		IMPORT_C TInstFileType FileType() const;
		IMPORT_C void FileOption(TInstFileOption& aOption) const;
		IMPORT_C HBufC* AllocReadForSourceLC() const;
		IMPORT_C HBufC* AllocReadForDestinationLC() const;
		IMPORT_C HBufC8* AllocReadForMimeTypeLC() const;
		IMPORT_C HBufC8* AllocReadForFileContentsLC() const;
		IMPORT_C TInt FileLength() const;
		IMPORT_C TInt FileLengthInSisFile() const;
		IMPORT_C void DeleteFileContentsFromInstallationFileL();
		
	private:
		void ConstructL(CSISInstallFile& aInstallationFile,TInt aIndex);
				
	public:	// TODO : should be private
		/**
		 * This class is now simply a compatibility layer on top of
		 * CSISFileInfoReader2.
		 */
		CSISFileInfoReader2* iSISFileInfoReader2;
	};

class CInstCapResult;

class CSISConditionInfoReader : public CBase
// reads condition info block within SIS
	{
	public: // public exported interface
		IMPORT_C static CSISConditionInfoReader* NewLC(
			CSISInstallFile& aInstallationFile, TInt aIndex,
			MInstallCondVariableSupplier& aVariableSupplier);
		IMPORT_C ~CSISConditionInfoReader();
		IMPORT_C TInstPackageLineType Type();
		IMPORT_C TBool EvaluateL();
	private:
		void ConstructL(CSISInstallFile& aInstallationFile,TInt aIndex,
			MInstallCondVariableSupplier& aVariableSupplier);
		CInstCapResult* EvaluateExprLC(TText8*& ptr);
		CInstCapResult* EvaluatePrimExprLC(TText8*& ptr);
	private:
		CSISInstallFile* iInstallationFile;
		MInstallCondVariableSupplier* iVariableSupplier;
		TInstPackageLineType iType;
		HBufC8* iConditionBuf;
	};

class CSISOptionsInfoReader : public CBase
// reads options info block within SIS
	{
	public: // public exported interface
		IMPORT_C static CSISOptionsInfoReader* NewLC(
			CSISInstallFile& aInstallationFile, TInt aIndex);
		IMPORT_C ~CSISOptionsInfoReader();
		IMPORT_C CDesCArray* AllocReadForOptionsNamesLC() const;
		IMPORT_C void SetOptionL(TInt aOptionIndex, TBool aValue);
		IMPORT_C TBool OptionL(TInt aOptionIndex) const;
		IMPORT_C TInt NumberOfOptions() const;
	private:
		void ConstructL(CSISInstallFile& aInstallationFile,TInt aIndex);
		void ReadInNameL(TInt aOptionIndex, TDes& aDes) const;
	private:
		CSISInstallFile* iInstallationFile;
		TInt iPkgLineOffset;
		HBufC8* iOptionsBuf;
	};

class CSISDependencyInfoReader : public CBase
// reads dependency info block within SIS
	{
	public: // public exported interface
		IMPORT_C static CSISDependencyInfoReader* NewLC(
			CSISInstallFile& aInstallationFile, TInt aIndex);
		IMPORT_C ~CSISDependencyInfoReader();
		IMPORT_C TInt Uid() const;
		IMPORT_C TInt MajorVersion() const; 
		IMPORT_C TInt MinorVersion() const;
		IMPORT_C TInt BuildVersion() const;
		IMPORT_C HBufC* AllocReadForDependencyNameLC() const;
	private:
		enum
			{
			EUid			=0,
			EVersion		=1,
			ENameLengths	=2,
			ENameStrings	=3,
			};
	private:
		void ConstructL(CSISInstallFile& aInstallationFile,TInt aIndex);
		void WorkOutOffsets();
		const TUint8* StartPtr() const;
		const TUint8* MovePtr(TInt aIndex) const;
		void ReadInNameL(TDes& aDes) const;
	private:
		CSISInstallFile* iInstallationFile;
		TInt iDependencyIndex;
		HBufC8* iDependencyBuf;
		TInt iOffset[4];
	};
	
/**
 * This class provides function to access the signature info of a SIS
 * file.
 * @internal
 */
class CSISSignatureInfoReader : public CBase
	{
	public: 
		IMPORT_C static CSISSignatureInfoReader* NewLC(
			const CSISInstallFile& aInstallationFile);
		IMPORT_C static CSISSignatureInfoReader* NewL(
			const CSISInstallFile& aInstallationFile);
		IMPORT_C ~CSISSignatureInfoReader();
		/**
		 * TODO : This function validates the signature. This should be
		 * moved as this class shouldn't have to worry about validating a 
		 * signature. It should only get the signature data.
		 * @internal
		 * @deprecated
		 */
		IMPORT_C TSignatureValidationResult SignatureIsValidL() const;
		IMPORT_C TDateTime SignatureDate() const;
		IMPORT_C CPKIXCertChain* CertChain() const;
		IMPORT_C void CertValidationL(CPKIXValidationResult& aResult, 
			TRequestStatus& aStatus);
	public:
		static CSISSignatureInfoReader* NewL(CSISSignatureInfoReader2* 
			aSISSignatureInforReader2);

	private:
		CSISSignatureInfoReader(const CSISInstallFile& aInstallationFile);
		CSISSignatureInfoReader(CSISSignatureInfoReader2* aSISSignatureInforReader2);
		void ConstructL(const CSISInstallFile& aSISInstallFile);
		
	public:
		/**
		 * This class is now only a compatibility layer on top of
		 * the CSISSignatureInfoReader2 class.
		 */
		CSISSignatureInfoReader2* iSISSignatureInforReader2;
	};


#endif
