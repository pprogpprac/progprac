#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>

/*
struct Person
{
    int USN;
    char name[5];
    float weight;
};
*/

///*
union Person
{
    int USN;
    char name[5];
    //float weight;
    float USN;
};
//*/

void main()
{
    //struct Person p;
    union Person p;

    strcpy(p.name, "Iyer");
    p.USN = 6011;
    //p.weight = 70.5;
    p.USN = 63.79;
    //strcpy(p.name, "Iyer");

    printf("p.USN = %d\n", p.USN);
    printf("p.name = %s\n", p.name);
    //printf("p.weight = %f\n", p.weight);

    printf("sizeof(p.USN) = %zu\n", sizeof(p.USN));
    printf("sizeof(p.name) = %zu\n", sizeof(p.name));
    //printf("sizeof(p.weight) = %zu\n", sizeof(p.weight));

    printf("sizeof(p) = %zu\n", sizeof(p));
}
