/////////////////////////// By Naveen R. Iyer      ////////////////////////
/////////////////////////// UFID: 60116379         ////////////////////////
/////////////////////////// Email: niyer@ufl.edu   ////////////////////////
/////////////////////////// Date: 23rd Feb, 2015   ////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

//#define DEVICE "/dev/test22dev4"
char DEVICE[100] = "lolgiri";


int main()
{
    int fd;

    int i, ch;
    int mybreak = 0;

//    int fd = open("pgiri", O_WRONLY | O_CREAT | O_TRUNC);
    char write_buf[100], read_buf[100];
    /*char *read_buf = calloc(1024 * sizeof(char), sizeof(char));
    char *write_buf = calloc(1024 * sizeof(char), sizeof(char));*/

    int select = 0;
    fd = open(DEVICE, O_RDWR);
    if(fd < 0)
        printf("Error opening)\n");
    while(1)
    {
        printf("Options:\n1 = read\n2 = write\n3 = lseek & read\n4 = lseek & write\n5 = Exit\nEnter option:\n");
        scanf("%d", &ch);

        switch(ch)
        {
            case 1:

                read(fd, read_buf, sizeof(read_buf));
                /*printf("sizeof(read_buf) = %ld\n", sizeof(read_buf));
                printf("strlen(read_buf) = %ld\n", strlen(read_buf));*/
                printf("\nDevice says: %s\n\n", read_buf);
                break;

            case 2:
                printf("Enter Data to write: ");
                scanf(" %[^\n]", write_buf);
                /*printf("sizeof(write_buf) = %ld\n", sizeof(write_buf));
                printf("strlen(write_buf) = %ld\n", strlen(write_buf));*/
                write(fd, write_buf, strlen(write_buf));
                break;

            case 3:
                //lseek_device(fd);
                read(fd, read_buf, sizeof(read_buf));
                printf("Device says: %s\n", read_buf);
                break;

            case 4:
                //lseek_device(fd);
                printf("Enter Data to write: ");
                scanf(" %[^\n]", write_buf);
                write(fd, write_buf, strlen(write_buf));
                break;

            case 5:
                printf("Exit option selected\n");
                mybreak = 1;
                break;

            default:
                printf("Command not recognized\n");
                break;
        }
        //close(fd);
        if(mybreak == 1)
        {
            close(fd);
            break;
        }

    }
    return 0;
}
