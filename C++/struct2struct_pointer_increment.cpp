/* Naveen R. Iyer
"Linked List From Scratch"

Bugs:
- Removed section of code that was accessing class's private data:
Line #198 from NRI_From_Scratch_LinkedList_2: "// Testing status of head, tail and prev nodes"

NEW Features:
- Defined struct node inside class nri_linked_list instead of outside ! (Don't know why though, probably to avoid globals).
- Implemented destructor !

Features:
- Modified code to implement class feature of C++.

- Add node to end or to beginning.
- Delete entire list with no memory leaks.
*/

#include <iostream>
#include <string.h>

struct node
    {
    	int ival;
        float fval;
    	char *next;
    };


int main()
{
    struct node n1, n2;

    char * cptr;
    int * iptr;

    //int a = 24;
    //char b[17] = "nri_foo";
    int i = 0;
    cptr = new char[17];
    iptr = new int;

    *iptr = 37;
    memcpy(cptr, "nri_mera_lele", sizeof(char)*17);

    std::cout << "iptr value = " << *iptr << "\n";
    std::cout << "cptr value = " << cptr << "\n";

    std::cout << "iptr addr = " << &(*iptr) << "\n";
    std::cout << "cptr addr = " << &(**cptr) << "\n";

    /*

    std::cout << "B4 sizeof(n1) = " << sizeof(n1) << std::endl;
    std::cout << "B4 sizeof(n2) = " << sizeof(n2) << std::endl;

    n1.next = new char[17];
    memcpy(n1.next, "Fellow Naveen", sizeof(char)*17);

    n2.next = new char[17];
    memcpy(n2.next, "Fk u Naveen", sizeof(char)*17);

    std::cout << "AF sizeof(n1) = " << sizeof(n1) << std::endl;
    std::cout << "AF sizeof(n2) = " << sizeof(n2) << std::endl;

    n1.ival = 17;
    n1.fval = 23.98;

    n2.ival = 33;
    n2.fval = 4.4;

    //n1 = n2;

    std::cout << "n1.ival = " << n1.ival;
    std::cout << "\nn1.fval = " << n1.fval;
    std::cout << "\nn1.next = " << n1.next;
    std::cout << "\n&n1.next = " << &n1.next;
    //std::cout << "\n&n1.next = " << &(++(*n1.next)); // Will result in Gellow Naveen
    //std::cout << "\n&n1.next = " << (&n1.next)++;
    //std::cout << "\n&n1.next = " << &(++n1.next);
    std::cout << "\n&n1.next = " << &(++n1.next);
    std::cout << "\n&n1.next = " << &(++n1.next);
    */
    /*std::cout << "\n*n1.next = " << *n1.next;
    //std::cout << "\n*n1.next++ = " << *n1.next++;
    //std::cout << "\nn1.next++ = " << n1.next++;
    std::cout << "\n++(*n1.next) = " << ++(*n1.next);
    std::cout << "\n++n1.next = " << ++n1.next << std::endl;
    std::cout << "\nn1.next = " << n1.next;
    std::cout << "\n&n1.next = " << &n1.next;
    std::cout << "\n&n1.next = " << &(++(*n1.next));*/
    /*
    std::cout << "\nn2.ival = " << n2.ival;
    std::cout << "\nn2.fval = " << n2.fval;
    std::cout << "\nn2.next = " << n2.next << std::endl;

    delete[](n1.next);
    delete[](n2.next);

    */

    return 0;
}
