#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void main()
{
    char *name = malloc(sizeof(char));
    char *namestr = malloc(sizeof(char));
    char *namemem = malloc(sizeof(char));
    //char name[50];
    name = "Naveen R. Iyer";
    strcpy(namestr, "Naveen R. Iyer");
    memcpy(namestr, "Naveen R. Iyer", strlen("Naveen R. Iyer"));
    //strcpy(name, "Naveen R. Iyer");
    int i = 0;
    for(i = 0; i < 16; i++)
    {
        printf("Iteration %d: Address = %p AddressStr = %p AddressMem = %p\n", i, &name[i], &namestr[i], &namemem[i]);
    }
}
