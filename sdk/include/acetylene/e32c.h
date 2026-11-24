#ifndef ACETYLENE_E32C_H
#define ACETYLENE_E32C_H

typedef signed int TInt;
typedef unsigned int TUint;
typedef long long TInt64;
typedef unsigned long long TUint64;
typedef signed int TInt32;
typedef unsigned int TUint32;
typedef unsigned char TBool;
typedef char TText8;
typedef unsigned short TText16;
typedef double TReal;

#define ETrue 1
#define EFalse 0
#define KErrNone 0
#define KErrNotFound (-1)
#define KErrGeneral (-2)
#define KErrNoMemory (-4)
#define KErrArgument (-6)
#define KErrNotSupported (-5)
#define KErrAlreadyExists (-11)
#define KErrInUse (-14)
#define KErrPermissionDenied (-21)

#define GLDEF_C
#define GLREF_C extern
#define GLREF_D extern
#define GLDEF_D
#define LOCAL_C static
#define IMPORT_C
#define EXPORT_C
#define NONSHARABLE_CLASS(x) struct x

#define AC_IMPORT(ret, name, args, mangled) extern ret name args __asm__(mangled)
#define AC_IMPORT_V(ret, name, mangled) extern ret name(void) __asm__(mangled)

#ifdef __cplusplus
extern "C" {
#endif

AC_IMPORT_V(void, User_After, "_ZN4User5AfterEi");
AC_IMPORT_V(TUint, User_TickCount, "_ZN4User9TickCountEv");
AC_IMPORT(void, User_Panic, (const char *aCategory, TInt aReason), "_ZN4User5PanicEPKci");
AC_IMPORT(void, User_Exit, (const char *aReason), "_ZN4User4ExitEPKc");
AC_IMPORT(TInt, User_Halt, (const char *aReason), "_ZN4User4HaltEPKc");
AC_IMPORT(void *, CTrapCleanup_New, (void), "_ZN12CTrapCleanup3NewEv");
AC_IMPORT(void, CTrapCleanup_Release, (void *self), "_ZN12CTrapCleanup7ReleaseEv");

static inline void AcAfter(TInt aMicroSeconds) { ((void (*)(TInt))User_After)(aMicroSeconds); }
static inline TUint AcTickCount(void) { return ((TUint (*)(void))User_TickCount)(); }
static inline void AcPanic(const char *cat, TInt reason) { ((void (*)(const char *, TInt))User_Panic)(cat, reason); }

#ifdef __cplusplus
}
#endif

typedef TInt (*AcE32MainFn)(void);

#endif
