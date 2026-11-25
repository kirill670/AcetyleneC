/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Nov 27 11:57:44 2002
 */
/* Compiler settings for G:\symbian_connect\mRouterClients\ConnMngmnt\ConnMngmntBox\ConnMngmntBox.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IConnMngmnt = {0xEC000180,0xCEE5,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


const IID LIBID_CONNMNGMNTBOXLib = {0xEC2000E3,0xCEE5,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


const CLSID CLSID_ConnMngmnt = {0xEC100180,0xCEE5,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


const IID IID_IConnMngmntClientSink = {0xEC000182,0xCEE5,0x11D2,{0xA9,0x53,0x00,0x10,0x5A,0x46,0xD6,0xE4}};


#ifdef __cplusplus
}
#endif

