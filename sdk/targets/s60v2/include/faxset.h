// FAXSET.H
//
// Copyright (c) Symbian Software Ltd. 1997-2004.  All rights reserved.
//
/** @file
 */

/********************************************************************/

// Contents : for saving/restoring persistent fax settings

/********************************************************************/

#ifndef __FAXSET_H
#define __FAXSET_H

#include <cdblen.h> 
#include <cdbcols.h>

#ifdef SYMBIAN_COMMS_REPOSITORY
 #include <s32strm.h>
 #include <f32file.h>
#else
 #include <commdb.h>
#endif

/********************************************************************/

class TFaxSettings
/** Fax configuration information.

Contains persistent information applicable to all fax sessions. 

@publishedAll
@released
*/
   {
 public:
   IMPORT_C void ExternalizeL (RWriteStream &) const;
   IMPORT_C void InternalizeL (RReadStream &);
   IMPORT_C TFaxSettings& operator=(const TFaxSettings& aFaxSettings);
	/** The local Fax ID string, which must be exactly 20 characters, with only 0-9, 
	space, and + permissible for exact conformance with ITU T.30. */
   TBuf8 < 20 > iFaxId ;
	/** Maximum speed of fax session in bps. */
   TInt iMaxSpeed;
	/** Minimum speed of fax session in bps. */
   TInt iMinSpeed;
	/** Preferred resolution. */
   TFaxResolution iPreferredResolution;
	/** Preferred compression. */
   TFaxCompression iPreferredCompression;
	/** If 1, use error correction mode (ECM), else 0. */
   TInt iPreferredECM;
	/** Switches fax logging on or off. This must be left on. */
   TInt iVerbose;
	/** The delay between dialling and receiving from a faxback service (seconds). */
   TInt iFaxOnDemandDelay ;
	/** The fax class. */
   TFaxClass iFaxClass;
   };

/********************************************************************/

// now the CFaxSettings class

class CFaxSettings : public CBase
/**
@internalComponent
*/
   {
public:
   static CFaxSettings * NewL ();
   static CFaxSettings * NewLC ();
   ~CFaxSettings ();
   void ValidateAndSetClassL (TFaxSettings *);

protected:
   void ConstructL ();
 protected:
   RFs iFileSession;
   };

/********************************************************************/

#endif

