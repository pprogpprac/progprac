#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>


struct instruct4
{
    int a;
    char b[5];
};

struct instruct3
{
    int a;
    char b[5];
    struct instruct4 ins;
};

struct instruct2
{
    int a;
    char b[5];
    struct instruct3 ins;
};

struct instruct1
{
    int a;
    char b[5];
    struct instruct2 *ins;
};

struct instruct0
{
    int a;
    char b[5];
    struct instruct1 ins;
};

void main()
{
    struct instruct0 in0;
    struct instruct1 *in1;
    /*struct instruct2 in2;
    struct instruct3 in3;
    struct instruct4 in4;*/

    in0.ins.ins = malloc(sizeof(struct instruct2));
    in1 = malloc(sizeof(struct instruct1));
    in1->ins = malloc(sizeof(struct instruct2));

    //in0.ins.ins = malloc(sizeof(struct instruct1));

    in0.a = 0;
    in0.ins.a = 1;
    in0.ins.ins->a = 2;
    in0.ins.ins->ins.a = 3;
    in0.ins.ins->ins.ins.a = 4;

    memcpy(in0.b, "Zero", sizeof("Zero"));
    memcpy(in0.ins.b, "One", sizeof("One"));
    memcpy(in0.ins.ins->b, "Two", sizeof("Two"));
    memcpy(in0.ins.ins->ins.b, "Three", sizeof("Three"));
    memcpy(in0.ins.ins->ins.ins.b, "Four", sizeof("Four"));

    printf("Accessing every structs info via struct0 !\n");

    printf("in0.a = %d\n", in0.a);
    printf("in0.ins.a = %d\n", in0.ins.a);
    printf("in0.ins.ins->a = %d\n", in0.ins.ins->a);
    printf("in0.ins.ins->ins.a = %d\n", in0.ins.ins->ins.a);
    printf("in0.ins.ins->ins.ins.a = %d\n\n", in0.ins.ins->ins.ins.a);

    printf("in0.b = %s\n", in0.b);
    printf("in0.ins.b = %s\n", in0.ins.b);
    printf("in0.ins.ins->b = %s\n", in0.ins.ins->b);
    printf("in0.ins.ins->ins.b = %s\n", in0.ins.ins->ins.b);
    printf("in0.ins.ins->ins.ins.b = %s\n", in0.ins.ins->ins.ins.b);

    // Print addresses of structs
    printf("Address of in0.ins = \t\t\t%p\n", &(in0.ins));
    printf("Address of in0.ins.ins = \t\t%p\n", &(in0.ins.ins));
    printf("Address of in0.ins.ins.ins = \t\t%p\n", &(in0.ins.ins->ins));
    printf("Address of in0.ins.ins.ins.ins = \t%p\n", &(in0.ins.ins->ins.ins));

    printf("Address of in1->ins = \t\t\t%p\n", (in1->ins));
    printf("Address of in1.ins->ins = \t\t%p\n", &(in1->ins->ins));
    printf("Address of in1.ins->ins.ins = \t\t%p\n", &(in1->ins->ins.ins));

    memcpy(in1->b, "OO1OO", sizeof("OO1OO"));
    memcpy(in1->ins->b, "OO2OO", sizeof("OO2OO"));
    memcpy(in1->ins->ins.b, "OO3OO", sizeof("OO3OO"));
    memcpy(in1->ins->ins.ins.b, "OO4OO", sizeof("OO4OO"));

    printf("\n\nUsing in1:\n");
    printf("in1->b = %s\n", in1->b);
    printf("in1->ins->b = %s\n", in1->ins->b);
    printf("in1->ins->ins.b = %s\n", in1->ins->ins.b);
    printf("in1->ins->ins.ins.b = %s\n", in1->ins->ins.ins.b);

    //free(in0.ins.ins);
}
