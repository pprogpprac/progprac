#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

float Plus    (float a, float b)
{
    return a+b;
}

float Minus   (float a, float b) { return a-b; }
float Multiply(float a, float b) { return a*b; }

float Divide  (float a, float b)
{
    return a/b;
}

void Switch_With_Function_Pointer(float a, float b, float (*pt2Func)(float, float))
{
   float result = pt2Func(a, b);    // call using function pointer
   printf("Switch replaced by function pointer:\n %f (op) %f = %f\n", a, b, result);  // display result
}

void main()
{
   float a, b;
   printf("Enter a and b:\n");
   scanf("%f %f", &a, &b);

   // Answer with function pointer
   Switch_With_Function_Pointer(a, b, &Multiply); // works even without "&" before Multiply

   // Answer without function pointer (regular function call)
   printf("\nWithout function pointer:\n");
   printf("a - b = %f\n", Minus(a, b));
}
