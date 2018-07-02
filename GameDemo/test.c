#include <stdio.h>
#include <string.h>
main()
{
    typedef struct _a {
        int id;
        char name[50];
    }A;

    A a = {1, "孙建春"};
    A b;

    memcpy(&b, &a, 1);
    printf("%d\n", b.id);
    return 0;
}
