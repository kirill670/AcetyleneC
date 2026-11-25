//
// This header file defines the ZlibEngine class used
// perform memory compression and decompression using
// Zlib.
//
// The ZlibEngine is a Tiny Software (tm) project.
// You may use the code in this project without restriction.
// Contact markn@tiny.com for more information.
//
// Modified by Intuwave to do memory rather than file compression

#if !defined( _ZLIBENGN_H )
#define _ZLIBENGN_H

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the IWZLIB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// IWZLIB_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef IWZLIB_EXPORTS
#define IWZLIB_API __declspec(dllexport)
#else
#define IWZLIB_API __declspec(dllimport)
#endif

//
// All of the Zlib code is compiled in C modules.  Fortunately,
// I can wrap the entire header in an 'extern "C"' declaration,
// and it will then link properly!
//

extern "C" {
#include "sczlib.h"
}

class IWZLIB_API ZlibEngine : public z_stream {
    public :
        ZlibEngine();
        int compress( const unsigned char *input, int inLen,
                      unsigned char *output, int &outLen);
        int decompress( const unsigned char *input, int inLen,
                        unsigned char *output, int &outLen );
};

#endif  // #if !defined( _ZLIBENGN_H )
