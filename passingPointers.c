#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

/*struct person
{
    char name[100];
    long int ufid;
    char degree[150];
};*/

int function(char *, int, int);

void main()
{
    int ret = 7;
    char *name = malloc(20 * sizeof(char));
    name = "Naveen Iyer";
    printf("Before func name = %s\n", name);
    ret = function(name, 4, 9);
    if(ret == 0)
    {
        printf("Success !\n");
    }
    else
    {
        printf("Failed !\n");
    }
    printf("After func name = %s\n", name);
}

int function (char *ptr, int x, int y)
{
    memcpy(ptr[0], (char *)x, sizeof(x));
    memcpy(ptr[strlen(ptr)], (char *)y, sizeof(y));
    return 0;
}
