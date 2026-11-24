/*
* ============================================================================
*  Name     : PAlbUtImageRecognizer.h
*  Part of  : PhotoAlbum
*
*  Description:
*
*  Version  :
*
*  Copyright (C) 2002 Nokia Corporation.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia Corporation. All rights are reserved. Copying,
*  including reproducing, storing,  adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia Corporation. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia Corporation.
* ============================================================================
*/

#ifndef __PALBIMAGERECOGNIZER_H_
#define __PALBIMAGERECOGNIZER_H_

// INCLUDE FILES
#include <MdaImageConverter.h>

class CMdaRecognizer;

/**
 * @deprecated
 * @see Image Conversion Library
 * This class implements an image recognizer using IML CMdaRecognizer
 *
 * Basic usage:
 * CPAlbImageRecognizer *iRecog = CPAlbImageRecognizer::NewL();
 * if(KImageFormatJPEG == iRecog->TryRecognizeL(_L("test.jpg")) )
 *     {
 *     RDebug::Print(_L("Wow this really is a JPEG picture"));
 *     }
 * delete iRecog;
 *
 * If the method TryRecognizeL() returns KImageFormatUnknown this doesn't mean
 * that the image format is unknown. IML might have a new plugin installed.
 * For this reason there is a way to get the MIME string originating from the
 * MediaServer.
 *
 * After calling TryRecognizeL() you can get the actual MIME string by using
 * the the method MimeString().
 *
 */
class CPAlbImageRecognizer :
    public CBase,
    public MMdaImageUtilObserver
    {
    public:
        // Enumerations for image formats
        enum EImageFormatId
            {
            KImageFormatPNG=0,
            KImageFormatTIFF,
            KImageFormatGIF,
            KImageFormatMBM,
            KImageFormatBMP,
            KImageFormatJPEG,
            KImageFormatWBMP,
            KImageFormatOTA,
            KImageFormatWMF,
            KImageFormatUPF,
            KImageFormatUnknown,
            KImageFormatERROR,
            KImageFormatNotSupported
            };

    public: // Constructors
        /**
         * Public constructor
         * @return a pointer to the new instance
         */
        IMPORT_C static CPAlbImageRecognizer* NewL();

        /**
         * destructor
         */
        IMPORT_C ~CPAlbImageRecognizer();

    public: // methods
        /**
         * Try to recognize an image file. On error it returns KImageFormatERROR
         * and if the image format can not be identified it returns KImageFormatUnknown
         *
         * @param aFileName Image file name
         * @return Value for image format (EImageFormatId)
         */
        IMPORT_C TInt TryRecognizeL(const TDesC& aFileName);

        /**
         * Get Mime string for image format (for example: "image/jpeg")
         *
         * @return a reference to the mimestring describing the image format
         */
        IMPORT_C const TDesC8& MimeString();

        /**
         * What kind of recognition was used to determine the image format
         * (filename, file header or none).
         *
         * @return CMdaRecognizer::TMatchMethod
         */
        IMPORT_C TInt MatchMethod() const;

        /**
         * Get file information of file, including size and modification time.
         *
         * @param aFilename filename to be examined
         * @param aTime reference to TTime object for storing the modification time
         * @param aSize reference to TInt for storing the file size
         * @return KErrNone if no error happened, otherwise the error code
         */
        IMPORT_C TInt FileInfoL(const TDesC& aFileName, TTime& aTime, TInt& aSize);

        /**
         * Get the frame info (TFrameInfo) for the image stored in file.
         * @param aFilename filename to be examined
         * @param aFrameInfo reference to TFrameInfo object
         */
        IMPORT_C void FrameInfoL(const TDesC& aFileName, TFrameInfo& aFrameInfo);
           /**
         * Check if the recognized file was a picture.
         * @param aFormat the format returned by TryRecognizeL(...)
         * @return ETrue if format is a picture.
         */
        IMPORT_C TBool IsPicture(TInt aFormat);

        /**
         * Check if the recognized file was a image.
         * @param aFormat the format returned by TryRecognizeL(...)
         * @return ETrue if format is an image.
         */
        IMPORT_C TBool IsImage(TInt aFormat);


    private: // From MMdaImageUtilObserver
        /**
         * Observer for IML, called when creation complete
         * @param aError KErrNone or error code if an error occured
         */
        void MiuoCreateComplete(TInt aError);
        /**
         * Observer for IML, called when file has been opened
         * @param aError KErrNone or error code if an error occured
         */
        void MiuoOpenComplete(TInt aError);
        /**
         * Observer for IML, called when conversion complete (Rotate, scale..)
         * @param aError KErrNone or error code if an error occured
         */
        void MiuoConvertComplete(TInt aError);

    private: // private methods
        /**
         * Default constructor private
         */
        CPAlbImageRecognizer();

        /**
         * Second phase constructor - private
         */
        void ConstructL();
        /**
         * Reads the mime types from resource file
         */
        void ReadMimeTypesL();
        /**
         * Recognize the image format using the mime string.
         *
         * @param aMimeString descriptor containing the mime string of the image
         * @return a value from EImageFormatId describing the format
         */
        TInt DecideFileFormat(const TDesC8& aMimeString);

        /**
         * Reads 256 bytes from file aFileName to descriptor given in aBuf.
         *
         * @param aFileName name of the file to open
         * @param aBuf a buffer (descriptor) with 256 bytes free space.
         * @return KErrNone if succesful, otherwise an error code.
         */
        TInt ReadFileL(const TDesC& aFileName, TDes8& aBuf);

        /**
         * Begings waiting an asynchronous request to complete.
         * Calls CActiveScheduler::Start() unless it was started already by
         * this object.
         * NOTE! There must always be a EndActiveWait() at some point
         * if BeginActiveWait() was called.
         */
        void BeginActiveWait();

        /**
         * Ends waiting an asynchronous request to complete.
         * Calls CActiveSceduler::Stop() if BeginActiveWait() was
         * called previously.
         */
        void EndActiveWait();

    private:
        // Owns: MDA image file loader utility
        CMdaImageFileToBitmapUtility* iLoader;

        // Owns: pointer to the image recognizer object from MDASVR
        CMdaRecognizer* iReg;

        // Owns: mime types array constructed from resource
        CArrayPtrFlat<HBufC8>* iMimeArray;

        // The match method used
        TInt iMatchMethod;

        // Owned file server session
        RFs iFsSession;

        // Denotes if CActiveScheduler::Start() was called
        TBool iAsyncOperation;

        // Internal error code
        TInt iError;

        CActiveSchedulerWait iWait;
    };

#endif // __PALBUTIMAGERECOGNIZER_H_

// End of File