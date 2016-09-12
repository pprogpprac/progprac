#include <stdio.h>

void main()
{
	int *ptrb, b;
	printf("Enter a number: \n");
	scanf("%d", &b);
	ptrb = &b;
	printf("Address using variable 'b' = %d is %p\n", b, (void *)&b);
	printf("Address using pointer to 'b' is %p\n", ptrb);
	printf("The value stored in variable 'b''s address, viz, %p is %d\n", ptrb, *ptrb);
	
	printf("The value stored in address 0x7fff48a9e17c is %d\n", *(0x7fff48a9e17c));
}
