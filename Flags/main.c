#include "flags.h"
#include <stdio.h>
#include <stdbool.h>


int main(void)
{
    flag_set(FLAG_1);
    bool ret = flag_get(FLAG_1);
    printf("Flag 1 is set: %d \n", ret);
    flag_clear(FLAG_1);
    ret = flag_get(FLAG_1);
    printf("Flag 1 is set: %d", ret);

}