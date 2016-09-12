#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

struct math
{
    int plus;
    int minus;
    float divide;
    float multiply;
};

struct mathmath
{
    struct math A;
    struct math B;
};

struct mathmath function(int, int);

void main()
{
    int zero = 0, two = 2, three = 3;

    printf("\n*** Original order: x then y ***\n");
    printf("Addition Ans = %d\nSubtraction Ans = %d\
          \nMult Ans = %.2f\nDiv Ans = %f\n", \
          function(two, three).A.plus, function(two, three).A.minus,\
          function(two, three).A.multiply, function(two, three).A.divide);

    printf("\n\n*** Order: y then x ***\n");
    printf("Addition Ans = %d\nSubtraction Ans = %d\
          \nMult Ans = %.2f\nDiv Ans = %f\n", \
          function(two, three).B.plus, function(two, three).B.minus,\
          function(two, three).B.multiply, function(two, three).B.divide);

}

struct mathmath function (int x, int y)
{
    struct math M;
    struct math N;

    M.plus = x + y;
    M.minus = x - y;
    M.multiply = x*y;
    M.divide = (float)x/ (float)y;

    N.plus = y + x;
    N.minus = y - x;
    N.multiply = y*x;
    N.divide = (float)y/ (float)x;

    struct mathmath P;
    P.A = M;
    P.B = N;

    return P;
}
