#include "stdio.h"
#include "stdlib.h"
//#include "header.h"
#include "source.c"

int main(void)
{
    printf("Seven in numeric should be printed: %d\n", returnSeven());
    double var = mult(7.11111111111111111111111111111111, 5);
    printf("var = %.32lf\n", var);
    return 0;
}
