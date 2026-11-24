// data.h
//Copyright (c) Symbian Software Ltd 2003 - 2004 . All rights reserved.

#ifndef __DATA_H__
#define __DATA_H__

#include <e32base.h>
#include <f32file.h>
#include <caf/caf.h>


namespace ContentAccess
{
	class CAgentInfo;
	class CAgentConsumer;

/**
 * Encapsulates the data part of a piece of content. 
 *
 * Once a piece of content is opened, clients use this class
 * to access the data and perform other operations.
 * 
 * The class instance is created by the ContentAccess::CContent class
 * and not directly by the client.
 *
 * This class is initialised with an agent implementation which is
 * responsible for this piece of content.
 *
 * @publishedPartner
 * @prototype
 */
	class CData : public CBase
		{
	public:
		virtual ~CData(); /**< CData destructor. */
		
		/** 
		 Reads from a piece of content up to the maximum length of the
		 descriptor or the end of file.
		 
		 When an attempt is made to read beyond the end of the content
		 no error is returned. The descriptor’s length is set to the
		 number of bytes which were read into it. Therefore, when reading
		 through content, the end has been reached when the
		 descriptor length (given by TDesC::Length()) is zero.
		 
		 @param aDes	Descriptor into which binary data is read. Any existing
		  				contents are overwritten. On return, its length is set 
		  				to the number of bytes read.
		 @return		KErrNone if successful, otherwise another of the
		  				system-wide error codes.
		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		 */
		IMPORT_C TInt Read(TDes8& aDes) const;
		
		/**
		 Reads a specified number of bytes of content.
		  
		 @see Read(TDes8& aDes)
		 
		 @param aDes		Descriptor into which binary data is read. Any existing
		  					contents are overwritten. On return, its length is set
		 					to the number of bytes read.
		 @param aLength	The maximum number of bytes to read.
		 @return			KErrNone if successful, otherwise another of the
		  					system-wide error codes.
		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		 */
		IMPORT_C TInt Read(TDes8& aDes,TInt aLength) const;
		
		/**
		 Reads content asynchronously.
		  
		 @see Read(TDes8& aDes)
		 
		 @param aDes		Descriptor into which binary data is read. Any
		  					existing contents are overwritten. On return, its length 
		  					is set to the number of bytes read. 
		 @param aStatus	Request status. On completion contains an error
		  					code. KErrNone if successful, otherwise another of the
		  					system-wide error codes. 
		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		 */
		IMPORT_C void Read(TDes8& aDes, TRequestStatus& aStatus) const;
		
		/**
		 Reads content (up to a specified maximum number of bytes)
		 asynchronously.
		 
		 @see Read(TDes8& aDes)
		 
		 @param aDes		Descriptor into which binary data is read. Any
		  					existing contents are overwritten. On return, its length
		  					is set to the number of bytes read.
		 @param aLength	The number of bytes to read from the content
		  					into the descriptor. If an attempt is made to read more
		  					bytes than the descriptor's maximum length, the function
		  					returns KErrOverflow. Must not be negative or the function
		  					returns KErrGeneral.
		 @param aStatus	Request status. On completion contains
		  					KErrNone if successful, otherwise another of the
		  					system-wide error codes.
		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		 */
		IMPORT_C void Read(TDes8& aDes,
						   TInt aLength,
						   TRequestStatus& aStatus) const;

		/**
		 Gets the data size in bytes.
		 
		 @param aSize	On return, the size of the file in bytes.
		  
		 @leave KErrCASizeNotDetermined	Size could not be determined 
		  									by the managing agent
		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		 */
		IMPORT_C void DataSizeL(TInt& aSize);
		
		/**
		 Changes or retrieves the location of the file pointer within the content
		 
		 There are four seek modes used: 
		 @li	ESeekStart - Sets the file pointer aPos bytes from the start of the file. 
		 		aPos is not modified by the call to Seek()
		 @li	ESeekEnd - Sets the file pointer aPos bytes from the end of the file. 
		 		The aPos parameter supplied should be zero or negative when using ESeekEnd
		 		Upon completion aPos is updated with the current position relative to the 
		 		start of the file.
		 @li	ESeekCurrent - Moves the file pointer aPos bytes from the current 
		  		position. Upon completion aPos is updated with the new position relative 
		 		to the start of the file. Suppling a zero value for the aPos Parameter can be
		 		used to retrieve the current file pointer location 
		 @li	ESeekAddress Sets the aPos parameter to the address of the byte 
		 		aPos bytes from the start of the file.
		 
		 @see TSeek
		 
		 @param aMode	Seek mode - controls the destination of the seek operation.
		  
		 @param aPos	Offset from either the start, end or current position depending upon 
		  				the seek mode. Negative offsets are used to seek before the current position or
		 				relative to the end of the file.
		 
		 @return		KErrNone if successful, otherwise another of the
		  				system-wide error codes. Some operations may fail if the
		  				content data is sourced over a network connection.
		  				
		 @capability KCapabilityDRM	Access to DRM protected content is only permitted for processes without 
		 							DRM capability. Access to unprotected content is not restricted.
		 */
		IMPORT_C TInt Seek(TSeek aMode,TInt& aPos) const;
		
		/** 
		 * Allows modification of Quality-of-Service parameters relating to
		 * the way content data is delivered. 
		 *
		 * @note	Setting the buffer-size to 256 bytes can be achieved
		 * 			as follows:
		 * 			@code
		 * 			MyData->SetQosL(EQosBufferSize, 256);
		 * 			@endcode
		 *	
		 * @param aQosAttr	Specifies the parameter to change. Currently, the
		 * 					only supported QoS attribute is EQosBufferSize.
		 * @param aValue	Specifies the new value.
		 */
		IMPORT_C void SetQosL(TQosAttribute aQosAttr, TInt aValue);
		
		/**
		 Allows a client to query the intent on an opened data
		 object. 
		 
		 Doing so may cause subsequent reads (or other accesses) to fail. 
		 The result of the agent's @e evaluation of the intent is returned.
		 
		 Note that being an evaluation, the CAF agent will not
		 decrement any rights-state such as play counts.
		  
		 @param aIntent	The intent indicator. 
		 @return			KErrNone, a Content-Access Framework Error code
		  					such as KErrCANotSupported, KErrCANoRights,
		  					KErrCANoPermission, or another system-wide error code.

		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		 */
		IMPORT_C TInt EvaluateIntent(TIntent aIntent);

		/**
		 The client will make a call to this function once it has 
		 completed its intended operation.
		 
		 Note that being an execution, the CAF agent @e will
		 decrement any rights-state such as play counts.
		 
		 @param aIntent	The intent indicator.
		 @return			KErrNone, a Content-Access Framework Error code
		  					such as KErrCANotSupported, KErrCANoRights,
		  					KErrCANoPermission, or another system-wide error code.
		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		 */
		IMPORT_C TInt ExecuteIntent(TIntent aIntent);


		/** 
		Retreives the mime type of the content if known
		
		@param aMimeType The agent fills in the content mime type if it knows
		@return ETrue if the agent knows the mime type, EFalse otherwise
		@leave KErrOverflow if aMimeType is not large enough to store the mime type
		@capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		*/
		IMPORT_C TBool GetMimeTypeL(TDes8& aMimeType) const;
		
	private:
		/** Only allow CContent to create this instance. */
		friend class CContent;
		
		void ConstructL(CAgentInfo& aAgent,
						const TDesC& aURI,
						TIntent aIntent,
						TContentShareMode aShareMode); 
		
		/** 
		 Creates a new CData object. 
		 
		 May only be invoked by CContent factory object.
		 
		 @param aAgent	The agent determined to support this content
		 @param aURI		The path-name  of the target content.
		 @param aIntent	A CA intent string.
		 @param aShareMode The share mode used to open this content
		  
		 @leave KErrCANoRights, KErrCANoPermission.
		 @capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		 */
		static CData* NewL(CAgentInfo& aAgent,
						   const TDesC& aURI,
						   TIntent aIntent,
						   TContentShareMode aShareMode); 
		
		/** See CData::NewL 
		
		@capability KCapabilityDRM Access to DRM protected content is only permitted for processes without DRM capability. Access to unprotected content is not restricted
		*/
		static CData* NewLC(CAgentInfo& aAgent,
							const TDesC& aURI,
							TIntent aIntent,
							TContentShareMode aShareMode); 
		CData(); 

#ifdef SYMBIAN_SECURITY_CAF_RFILE_HANDLE	
	public:
		static CData* NewL(CAgentInfo& aAgent,
						   RFile& aFile,
						   TIntent aIntent); 
		
		static CData* NewLC(CAgentInfo& aAgent,
							RFile& aFile,
							TIntent aIntent); 
	
	private:	
		void ConstructL(CAgentInfo& aAgent,
						RFile& aFile,
						TIntent aIntent);
#endif 

	private:
		CAgentConsumer *iConsumer; 
		// Need to increment the reference count of a CAgentInfo 
		// otherwise ECOM will unload the agent when we least expect it
		CAgentInfo *iAgent;
		};
} // namespace ContentAccess
#endif /* __DATA_H__ */

