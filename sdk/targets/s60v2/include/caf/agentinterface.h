/// agentinterface.h
//Copyright (c) Symbian Software Ltd 2003 - 2004 . All rights reserved.

#ifndef __AGENTINTERFACE_H__
#define __AGENTINTERFACE_H__

#include <e32base.h>
#include <Ecom/ECom.h>
#include <caf/caf.h>

namespace ContentAccess
{
	class CBitset;
	class CCafMimeHeader;
	class CSupplierOutputFile;

	/**
	 * Defines the agent interface for consumer operations.
	 *
	 * This is not an 'M' class because member data may be added in future versions
	 *
	 * @publishedPartner
	 * @prototype
     */
	class CAgentConsumer : public CBase
		{
	public:
		/**
		 * Gets the data size in bytes.
		 *
		 * @param aSize	On return, the size of the file in bytes.
		 * @leave KErrCASizeNotDetermined	Size could not be determined 
		 * 									by the managing agent.
		 */
		virtual void DataSizeL(TInt &aSize) = 0;
		
		/**
		 * Allows a client to query the intent on an opened data
		 * object. 
		 *
		 * Doing so may cause subsequent reads (or other accesses)
		 * to fail. The result of the agent's @e evaluation
		 * of the intent is returned.
		 *
		 * Note that being an evaluation, the CAF agent will not
		 * decrement any rights-state such as play counts.
		 * 
		 * @param aIntent	The intent indicator. 
		 * @return			KErrNone, a Content-Access Framework Error 
		 *					code such as KErrCANotSupported, 
		 *					KErrCANoRights, KErrCANoPermission, 
		 *					or another system-wide error code.
		 */
		virtual TInt EvaluateIntent(TIntent aIntent) = 0;
		
		/**
		 * The client will make a call to this function once it has 
		 * completed its intended operation.
		 *
		 * Note that being an execution, the CAF agent @e will
		 * decrement any rights-state such as play counts.
		 *
		 * @param aIntent	The intent indicator.
		 * @return			KErrNone, a Content-Access Framework Error 
		 *					code such as KErrCANotSupported, 
		 *					KErrCANoRights, KErrCANoPermission, 
		 *					or another system-wide error code.
		 */
		virtual TInt ExecuteIntent(TIntent aIntent) = 0;

		/** 
		 * Reads from a piece of content up to the maximum length of the
		 * descriptor or the end of file.
		 *	
		 * When an attempt is made to read beyond the end of the content,
		 * no error is returned. The descriptor’s length is set to the
		 * number of bytes that were read into it. Therefore, when reading
		 * through content, the end has been reached when the
		 * descriptor length (given by TDesC::Length()) is zero.
		 *
		 * @param aDes	Descriptor into which binary data is read. Any existing
		 * 				contents are overwritten. On return, its length is set
		 *				to the number of bytes read.
		 * @return		KErrNone if successful, otherwise another of the
		 * 				system-wide error codes.
		 */
		virtual TInt Read(TDes8& aDes) const = 0;

		/**
		 * Reads a specified number of bytes of content.
		 * 
		 * See Read(TDes8& aDes)
		 *
		 * @param aDes		Descriptor into which binary data is read. Any existing
		 * 					contents are overwritten. On return, its length is set
		 *					to the number of bytes read.
		 * @param aLength	The maximum number of bytes to read.
		 * @return			KErrNone if successful, otherwise another of the
		 * 					system-wide error codes.
		 */
		virtual TInt Read(TDes8& aDes, TInt aLength) const = 0;

		/**
		 * Reads content asynchronously.
		 *
		 * See Read(TDes8& aDes)
		 *
		 * @param aDes 		Descriptor into which binary data is read. Any
		 * 					existing contents are overwritten. On return,
		 *					its length is set to the number of bytes read. 
		 * @param aStatus	Request status. On completion contains an error
		 * 					code. KErrNone if successful, otherwise another 
		 *					of the system-wide error codes. 
		 */
		virtual void Read(TDes8& aDes, TRequestStatus& aStatus) const = 0;

		/**
		 * Reads content (up to a specified maximum number of bytes)
		 * asynchronously.
		 *
		 * See Read(TDes8& aDes)
		 *
		 * @param aDes		Descriptor into which binary data is read. Any
		 * 					existing contents are overwritten. On return,
		 *					its length is set to the number of bytes read.
		 * @param aLength	The number of bytes to read from the content
		 * 					into the descriptor. If an attempt is made to
		 *					read more bytes than the descriptor's maximum 
		 *					length, the function returns KErrOverflow. Must 
		 *					not be negative or the function returns KErrGeneral.
		 * @param aStatus	Request status. On completion contains KErrNone 
		 *					if successful, otherwise another of the
		 * 					system-wide error codes.
		 */
		virtual void Read(TDes8& aDes,
						  TInt aLength,
						  TRequestStatus& aStatus) const = 0;

		/**
		 * Changes or retrieves the location of the file pointer within the content
		 *
		 * There are four seek modes used: 
		 *
		 * @li ESeekStart - Sets the file pointer aPos bytes from the start of the file. 
		 * aPos is not modified by the call to Seek()
		 * @li ESeekEnd - Sets the file pointer aPos bytes from the end of the file. 
		 * The aPos parameter supplied should be zero or negative when using ESeekEnd
		 * Upon completion aPos is updated with the current position relative to the 
		 * start of the file.
		 * @li ESeekCurrent - Moves the file pointer aPos bytes from the current 
		 * position. Upon completion aPos is updated with the new position relative 
		 * to the start of the file. Suppling a zero value for the aPos Parameter can be
		 * used to retrieve the current file pointer location 
		 * @li ESeekAddress Sets the aPos parameter to the address of the byte 
		 * aPos bytes from the start 
		 * of the file
		 * @see TSeek
		 *
		 * @param aMode	Seek mode - controls the destination of the
		 * 				seek operation.
		 * 
		 * @param aPos	Offset from either the start, end or current position depending upon 
		 * the seek mode. Negative offsets are used to seek before the current position or
		 * relative to the end of the file.
		 *
		 * @return		KErrNone if successful, otherwise another of the
		 * 				system-wide error codes. Some operations may fail if the
		 * 				content data is sourced over a network connection.
		 */
		virtual TInt Seek(TSeek aMode, TInt& aPos) const = 0;

		/** 
		 * Allows modification of Quality-of-Service parameters relating to
		 * the way content data is delivered. 
		 *	
		 * @note	Setting the buffer-size to 256 bytes can be achieved
		 * 			as follows:
		 *			@code
		 * 			MyData->SetQosL(EQosBufferSize, 256);
		 * 			@endcode
		 *
		 * @param aQosAttr	Specifies the parameter to change. Currently, the
		 * 					only supported QoS attribute is EQosBufferSize.
		 *	
		 * @param aValue	Specifies the new value.
		 */
		virtual void SetQosL(TQosAttribute aQosAttr, TInt aValue) = 0;

		/**
		 * The agent will populate the given attribute object with the
		 * attributes relating to the current piece of content.
		 *
		 * @param aQuerySet		The query CBitset sent to the agent.
		 * @param aResponseSet	The CBitset containing the response
		 * 						from the agent.
		 * 
		 * @leave KErrCANotSupported
		 * @leave KErrCAOutOfRange
		 */
		virtual void GetAttributeL(const CBitset& aQuerySet,
								   CBitset& aResponseSet) = 0;

		/** 
		* Retreives the mime type of the content if known
		*
		* @param aMimeType The agent fills in the content mime type if it knows
		* @return ETrue if the agent knows the mime type, EFalse otherwise
		* @leave KErrOverflow if aMimeType is not large enough to store the mime type
		*/
		virtual TBool GetMimeTypeL(TDes8& aMimeType) const = 0;
		};

	/**
	 *  Defines the agent interface for importing files into the Content
	 *  access framework. 
	 *
	 * This is not an 'M' class because member data may be added in future versions
	 *
	 * @publishedPartner
	 * @prototype
	 */
	class CAgentSupplier : public CBase
		{
	public:
		/** Prepares to import a single file.
		*
		* @param aHeader			The MIME header for this file.
		* @param aSuggestedFileName A filename suggested by the application using the CAF supplier API.
		*/
		virtual void PrepareToImportL(CCafMimeHeader& aHeader, const TDesC& aSuggestedFileName)=0;

		/** Writes a block of data to the file opened by the call to PrepareToImportL().
		*
		* @param aData	The block of data.
		*
		* @return		KErrNone if the data was written successfully, otherwise one 
		* 				of the standard error codes.
		*/
		virtual TInt WriteData(const TDesC8& aData)=0;

		/** Closes the file opened by the call to PrepareToImportL().
		*
		* @return	KErrNone if the data was written successfully, otherwise one 
		* 			of the standard error codes
		*/
		virtual TInt WriteDataComplete()=0;

		/** Writes a block of data to the file opened by the call to PrepareToImportL().
		* 
		* Notifies the client when the write operation is complete.
		*
		* @param aData		The block of data.
		* @param aStatus	Used to notify the client when writing is complete.
		*/
		virtual void WriteData(const TDesC8& aData, TRequestStatus& aStatus)=0;

		/** Closes the file opened by the call to PrepareToImportL().
		* 
		* Notifies the client when any final processing operation is complete.
		*
		* @param aStatus	Used to notify the client when writing is complete.
		*/
		virtual void WriteDataComplete(TRequestStatus& aStatus)=0;

		/** Sets the path used to store any output files created by subsequent calls to PrepareToImportL().
		*
		* @param aOutputDirectory A complete path including drive letter.
		* @leave KErrPathNotFound The agent cannot find or is not allowed to access the specified path
		*/
		virtual void SetOutputDirectoryL(const TDesC& aOutputDirectory)=0;

		/** Gets the number of output files produced. 
		*
		* Should reflect the number of files that can be used by the CData interface even if the files are incomplete. 
		* This will allow content rendering to occur as soon as the file is available.
		*
		* @return	The number of output files produced so far.
		*/
		virtual TInt OutputFileCountL() const = 0;

		/** Details of one of the output files.
		* 
		* @param aIndex	Zero based index indicating the file of interest, 
		*               must be less than the value returned by OutputFileCountL().
		* @return		The output file
		*/
		virtual CSupplierOutputFile& OutputFileL(TInt aIndex)=0;
		};

	
	/**
	 * Defines the agent interface for manager operations, which
	 * are independent of any particular piece of content.
	 *
 	 *
	 * This is not an 'M' class because member data may be added in future versions
	 *
 	 * @publishedPartner
	 * @prototype
	 */	
	class CAgentManager : public CBase
		{
	public:
		/*
		   GetDir() operations will go here
		*/
		/**
		 * Instructs the agent to go into 'browse/manage' mode
		 * with initial context relating to the current piece of
		 * content. 
		 *
		 * The agent will take control of the UI and remain
		 * in control until the user exits this mode.
		 * 
		 * @leave KErrCANotSupported.
		 */
		virtual void ManageContentL() = 0;

		/** 
		 * Requests for a piece of content to be deleted.
		 *
		 * @leave KErrCANotSupported.
		 */
		virtual void DeleteContentL(const TDesC& aFileName) = 0;

		/** 
		 * Identifies whether or not the file at the given URI is to be handled by
		 * this agent.
		 * 
		 * @param aURI	Location of the file to be examined.
	     * @return		ETrue if this agent supports and recognises the DRM container, EFalse otherwise. */
		virtual TBool IsRecognizedL(const TDesC& aURI) = 0;

		/** 
		 * Determines whether the file is a DRM  container supported by this agent. 
		 * If it is the agent will fill in the container mime type and content mime 
		 * type. There are two special cases:
		 *
		 * @li If the file needs to be imported through the Supplier API before
		 * it can be used then the agent will leave the aContentMimeType
		 * parameter blank (zero length).
		 *
		 * @li If more than one content file is contained within the file, the agent will
		 * set aContentMimeType to MULTIPLE
		 *
		 * @param aFileName				[IN] Name of the file to recognize. The name is examined, not the file itself
		 * @param aBuffer				[IN] Buffer containing bytes from the start of the file.
		 * @param aContainerMimeType 	[OUT] the container MIME type.
		 * @param aContentMimeType		[OUT] The content MIME type.
	     * @return						ETrue if the file is handled by this agent, EFalse otherwise.
		 */
		virtual TBool DoRecognizeL(const TDesC& aFileName, const TDesC8& aBuffer, TDes8& aContainerMimeType, TDes8& aContentMimeType)=0;

#ifdef SYMBIAN_SECURITY_CAF_RFILE_HANDLE

		/** 
		 * Identifies whether or not the given file handle is to be handled by
		 * this agent.
		 * 
		 * @param aFile File handle to be examined.
	     * @return		ETrue if this agent supports and recognises the DRM container, EFalse otherwise. */
		virtual TBool IsRecognizedL(RFile& aFile) = 0;
#endif
		};
  
} // namespace ContentAccess
#endif // __AGENTINTERFACE_H__
