#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

struct person
{
    char name[100];
    long int ufid;
    char degree[150];
};

struct person Nitin =
{
    .name = "Nitin J. Sanket",
    .ufid = 12345678,
    .degree = "Master of Engineering"
};

struct person Kamine =
{
    .name = "Kamine Saale",
    .ufid = 36368787,
    .degree = "Master of Technology"
};


void main()
{
    struct person Naveen =
    {
        .name = "Naveen R. Iyer",
        .ufid = 60116379,
        .degree = "Master of Science"
    };

    struct person *People;

    printf("\n\t*** Details of people ***\n");
    printf("*NAME*\t\t*UFID*\t\t*DEGREE*\n");
    printf("%s\t%ld\t%s\n", Naveen.name, Naveen.ufid, Naveen.degree);
    printf("%s\t%ld\t%s\n", Nitin.name, Nitin.ufid, Nitin.degree);
    printf("%s\t%ld\t%s\n", Kamine.name, Kamine.ufid, Kamine.degree);
}
