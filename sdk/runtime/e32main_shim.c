#include <acetylene/e32c.h>

extern TInt E32Main(void);

TInt AcE32Entry(void) __asm__("_Z7E32Mainv");

TInt AcE32Entry(void)
{
    return E32Main();
}

void _fp_init(void)
{
}
