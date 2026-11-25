#include <acetylene/e32c.h>

extern TInt E32Main(void);

TInt AcE32Entry(void) __asm__("E32Main__Fv");

TInt AcE32Entry(void)
    {
    return E32Main();
    }
