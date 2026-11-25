// 
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

// Telnet Session API
//
//

#ifndef _TELSESS_H_
#define _TELSESS_H_

#include <in_sock.h>
#include <e32std.h>
#include <e32cons.h>
#include <flogger.h>
#include <f32file.h>

#define __TELNETSESSDEBUG__ // Put in Debug mode

class CTelnetControl;

// Used by client to retrieve RFC option state
// Flags for Telnet negotiated options
// 1 = Enabled 0 = Disabled
typedef struct
    {
    TBool    iServerBinary; // RFC 856  (Server Sending in Binary)
    TBool    iClientBinary; // RFC 856  (Client Sending in Binary)
    TBool    iEcho;         // RFC 857  (Server Echoing Data from Client)
    TBool    iNAWS;         // RFC 1073 (Client Providing Window Size Information)
    TBool    iTerminalSpeed;// RFC 1079 (Client Providing Terminal Speed Information)
    TBool    iTerminalType; // RFC 1091 (Client Providing Terminal Type Information)
    TBool    iServerStatus; // RFC 859  (Server Providing Status Information)
    TBool    iClientStatus; // RFC 859  (Client Providing Status Information)
    }TOptionStatus;

// Used by client to configure the Symbian Telnet
class TTelnetConfig
    {
 public:

	 TTelnetConfig() {
		              iAllowLogout = TRUE;        // RFC 727  - Default TRUE = Server Can Logout Client
					  iWindowSize.x = (TInt16)80; // RFC 1073 - Default 80 x 24
					  iWindowSize.y = (TInt16)24;
					  iTermSpeed = _L8("38400");  // RFC 1079 - Default to 38400 Baud Terminal
					  iTermType  = _L8("dumb");   // RFC 1091 - Default to base NVT Terminal
					}
	 ~TTelnetConfig(){}

	typedef struct
		{
		TInt16 x;
		TInt16 y;
		}TWindowSize;

	TWindowSize	iWindowSize; // RFC 1073 - Set to Configure Window Size
	TBuf8<20>	iTermSpeed;  // RFC 1079 - Set to Configure Terminal Speed 
	TBuf8<20>	iTermType;   // RFC 1091 - Set to Configure Terminal Type
	
	TBool		iAllowLogout;// RFC 727  - Set/Clear to Enable/Disable Server Logout
	TBool		iServerEcho; // RFC 857  - Set/Clear to Enable/Disable Server Echo to client
    };

// Client can pass these in overloaded CTelnetSession::Write(TTelnetUserControl& aControlCode);
enum TTelnetUserControl 
    {
    ENotSupported = 0,
    EBrk	= 243,	// Break - NVT 129th ASCII break code // NOT Valid in Binary
    EIp		= 244,	// Interupt Process 
    EAo		= 245,	// Abort Output
    EAyt	= 246,	// Are you there?
    EEc		= 247,	// Erase Character                    // NOT Valid in Binary
    EEl		= 248,  // Erase Line                         // NOT Valid in Binary
    };
// Client MUST override this class
// Client MUST provide a pointer to an instance of this class as a parameter to CTelnetSession::NewL()
class MTelnetNotification
    {
 public:
    virtual void Error(TInt aError) = 0;                  // Miscellaneous Error callback
    virtual void ReadComplete(const TDesC8& aBuffer) = 0; // Last Read to Server completion callback
    virtual void WriteComplete() = 0;                     // Last Write to Server completion callback
    virtual void ConnectionClosed() = 0;                  // Telnet Connection Closed callback
    virtual void Connected() = 0;                         // Telnet Connected callback
    virtual void OptionsChanged() = 0;                    // Telnet RFC Options Changed callback
    };

class CTelnetControl;

class CTelnetSession : public CBase
    {
    //public:
    // Data Structures
 public:
    ~CTelnetSession();
    // Construction
    // Need to add max buffer size to constructor [check]
    IMPORT_C static CTelnetSession* NewL(const TTelnetConfig& aConfig,const MTelnetNotification* aNotifier);
 protected:
    IMPORT_C void ConstructL(const TTelnetConfig& aConfig,const MTelnetNotification* aNotifier);
    //
    // Connection Interface
    //
 public:
    IMPORT_C TInt Connect(const TInetAddr& aNetAddr);
    //Connects to aNetAddr on the standard telnet port (port 23)

    IMPORT_C TInt Connect(const TInetAddr& aNetAddr, TUint aPort);
    // Connects to aNetAddr on user specified port

    IMPORT_C TInt Connect(const TDesC& aServerName);
    // Connects to aSeverName on the standard telnet port (port 23)

    IMPORT_C TInt Connect(const TDesC& aServerName, TUint aPort);
    // Connects to aServerName on user specified port

    IMPORT_C TInt Disconnect();
    // Disconnects current connection 

    // Writes a byte stream over the open telnet connection.
    IMPORT_C TInt Write(const TDesC8& aBuffer);

    IMPORT_C TInt Write(TTelnetUserControl& aControlCode);
    // Writes NVT code to stream. Prepends <IAC> code (255)
	
    IMPORT_C TInt Read();
    // Read data received over telnet buffer.

	//
	// Protocol Interface 
	//
	IMPORT_C TInt DoForceLogout();
	IMPORT_C TInt DoModifyConfig(TTelnetConfig& aConfig);
	IMPORT_C TInt OptionStatus(TOptionStatus& aStatus);
 private:
    CTelnetSession();

 private:
    MTelnetNotification* iNotifier;
    CTelnetControl* iTelnetProtocol;
#ifdef __LOGDEB__
	RFs iFs;
#endif
    };


#endif // _TELNETPROTOCOLAPI_H_
