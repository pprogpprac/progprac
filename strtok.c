/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] =",Nice work,bro !|!!,";
  char delimiter[] = "|";
  char *temp;
  int i=0;
  /*printf("Enter a string: \n");
  scanf("%s", str);*/
  printf("The string you entered is \"%s\"\n", str);
  printf ("Splitting string \"%s\" with delimiter as \"%s\" into tokens:\n", str, delimiter);
  temp = strtok (str, delimiter);
  while (temp != NULL)
  {
    printf ("%d iteration: %s\n", i, temp);
    temp = strtok (NULL, delimiter);
    i++;
  }
  return 0;
}
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
*/

/* Simulates a shell, i.e., gets command names and executes them *//*
int main()
{
     char 
     char delimeter[] = " ";
     char *temp = NULL;
     int i=0;
     temp = strtok(str,delimeter);
     while (temp != NULL)
     {
           arg[i++] = temp;                   
           temp = strtok(NULL,delimeter);
     }
     arg[i] = NULL;     
     return 0;
}*/


