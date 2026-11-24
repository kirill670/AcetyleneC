#ifndef AC_VERSION_H
#define AC_VERSION_H

#ifndef AC_BUILD_TAG
#define AC_BUILD_TAG "dev"
#endif

#ifndef AC_BUILD_TITLE
#define AC_BUILD_TITLE AC_BUILD_TAG
#endif

#define AC_APP_NAME "AcetyleneC"
#define AC_APP_VERSION "1.0"

#define AC_BRAND_LINE1 "A Symbian OS custom IDE and SDK based on OSS and official materials"
#define AC_BRAND_LINE2 "by iXlinx Corporation and in honor of NNProject and others."
#define AC_COPYRIGHT "Copyright iXlinx Corporation and Kirill Lavrentiev 2026."
#define AC_LICENSE_NAME "iXlinx Open Platform License 1.0"

#define AC_ABOUT_COMPONENTS \
    "C compiler: TinyCC (ARM EABI, in-tree)\n" \
    "Linker: acetylene-ld\n" \
    "C++ frontend: acetylene-cxx\n" \
    "Post-linker: acetylene-e32fix\n" \
    "Packaging: acetylene-sis\n" \
    "Certificates: acetylene-makekeys (DSA)\n" \
    "MCP bridge: acetylene-mcp-stdio"

#endif
