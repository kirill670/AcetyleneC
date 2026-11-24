#include <acetylene/e32c.h>
#include <stdio.h>

static TInt Add(TInt a, TInt b)
    {
    return a + b;
    }

GLDEF_C TInt E32Main(void)
    {
    TInt total = 0;
    TInt i;
    for (i = 0; i < 10; i++)
        {
        total += Add(i, 7);
        }
    printf("total=%d\n", (int)total);
    return total;
    }
