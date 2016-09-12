#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //For true or false
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h> // For sleep

struct Person
{
    int id;
    char name[20];
    float wt;
    struct Person *next;
};

struct Person *head = NULL;
struct Person *curr = NULL;

void print_list()
{
    struct Person *ptr = head;

    printf("\nPrinting the entire list !\n");
    printf("\n<------------- List starts here ! ------------>\n\n");
    printf("__ID__\t|\t__NAME__\t|\t__WEIGHT__\n");

    while(ptr != NULL)
    {
        printf("%d\t|\t%s\t|\t%f\n", ptr->id, ptr->name, ptr->wt);
        ptr = ptr->next;
    }
    printf("\n<-------------- List ends here ! ------------->\n\n");

    if(!head)
        printf("No head node !\n");
    else
        printf("*** print_list func: DEBUG: Head node is id %d\n", head->id);


    if(!curr)
        printf("No curr node !\n\n");
    else
        printf("*** print_list func: DEBUG: Curr node is id %d\n\n", curr->id);

    return;
}



struct Person* create_list(int ivar, char cvar[], float fvar)
{
    printf("Creating list with headnode as %d\n", ivar);
    struct Person *ptr = (struct Person*) malloc(sizeof(struct Person));

    if(NULL == ptr)
    {
        printf("Node creation failed \n");
        return NULL;
    }

    ptr->id = ivar;
    memcpy(ptr->name, cvar, sizeof(ptr->name));
    //strcpy(ptr->name, cvar);
    //strncpy(ptr->name, cvar, sizeof(ptr->name));
    ptr->wt = fvar;
    ptr->next = NULL;

    head = curr = ptr;
    return ptr;
}


struct Person* add_to_list(int ivar, char cvar[], float fvar, bool add_to_end)
{
    if(NULL == head)
    {
        return (create_list(ivar, cvar, fvar));
    }

    if(add_to_end)
        printf("Adding node with id %d to the end of list\n", ivar);
    else
        printf("Adding node with id %d to the beginning of list\n", ivar);

    struct Person *ptr = (struct Person *)malloc(sizeof(struct Person));

    if(NULL == ptr)
    {
        printf("Node creation failed \n");
        return NULL;
    }

    ptr->id = ivar;
    memcpy(ptr->name, cvar, sizeof(ptr->name));
    //strcpy(ptr->name, cvar);
    //strncpy(ptr->name, cvar, sizeof(ptr->name));
    ptr->wt = fvar;
    ptr->next = NULL;

    if(add_to_end)
    {
        curr->next = ptr;
        curr = ptr;
    }
    else // Add the node to the beginning, and make it the head node !
    {
        ptr->next = head;
        head = ptr;
    }
    return ptr;
}


struct Person* search_in_list(int ivar, struct Person **prev)
{
    struct Person *ptr = head;
    struct Person *tmp = NULL;
    bool found = false;

    //printf("Searching the list for data structure with id %d\n", ivar);

    while(ptr != NULL)
    {
        if(ptr->id == ivar)
        {
            /*printf("Search passed ! Following are the data of the data structure with id %d:\n", ptr->id);
            printf("__ID__\t|\t__NAME__\t|\t__WEIGHT__\n");
            printf("%d\t|\t%s\t|\t%f\n", ptr->id, ptr->name, ptr->wt);*/
            found = true;
            break;
        }
        else
        {
            //printf("Search failed ! id = %d not found\n", ivar);
            tmp = ptr;
            ptr = ptr->next;
        }
    }

    if(true == found)
    {
        if(prev)
            *prev = tmp;
        return ptr;
    }
    else
    {
        return NULL;
    }
}


int delete_from_list(int ivar)
{
    struct Person *prev = NULL;
    struct Person *del = NULL;

    printf("Deleting node with id %d from list\n", ivar);

    del = search_in_list(ivar, &prev);

    if(del == NULL)
    {
        //printf("\nData structure with id = %d not found\n", ivar);
        return -1;
    }
    else
    {
        //printf("\nData structure with id = %d deleted !\n", ivar);
        if(prev != NULL)
            prev->next = del->next;

        if(del == curr)
        {
            curr = prev;
        }
        else if(del == head)
        {
            head = del->next;
        }
    }

    free(del);
    del = NULL;

    return 0;
}


void main()
{
    int i = 3, ret = 0;
    struct Person *ptr = NULL;

    print_list();
    create_list(1, "Naveen Iyer", 72.35);
    print_list();

    add_to_list(2, "Ending N..ln", 83.226, true);
    add_to_list(3, "0123456789", 11.2, true);
    add_to_list(0, "Benjkl Bhsdgs", 31, false);
    add_to_list(4, "CounterStrike", 86.04, true);

    print_list();

    //sleep(10);

    printf("Enter the node id you want to search in list:\n");
    scanf("%d", &i);
    //search_in_list(i, NULL);
    ptr = search_in_list(i, NULL);
    if(NULL == ptr)
    {
        printf("Search failed ! id = %d not found\n", i);
    }
    else
    {
        printf("Search passed ! Following are the data of the data structure with id %d:\n", ptr->id);
        printf("__ID__\t|\t__NAME__\t|\t__WEIGHT__\n");
        printf("%d\t|\t%s\t|\t%f\n", ptr->id, ptr->name, ptr->wt);
    }


    //for(i = 0; i<5; i++)
    //{
    ///*
    printf("Enter the node id you want to delete from the list:\n");
    scanf("%d", &i);
    //delete_from_list(i);
    ret = delete_from_list(i);
    if(ret != 0)
    {
        printf("\nData structure with id = %d not found\n",i);
    }
    else
    {
        printf("\nData structure with id = %d deleted !\n", i);
    }
    print_list();
    //*/
    //}


    ///*
    printf("Sleeping for 1 second and then deleting the complete list !\n");
    sleep(1);

    printf("Now deleting the entire list since the end of program has reached !\n");

    //for(i = 0; i < 4; i++) // Spare-one-last-node approach ! Obsolete ! Use infinite loop instead !
    for(i = 0; i < 10; i++)
    {
        if(head == curr)
        {
            printf(">>>>>>>>>>> |||||||||||  LAST NODE |||||||||| >>>>>>>>>\n");
            break;
        }
        delete_from_list(i); // delete_from_list() calls search_in_list() within itself
        print_list();
    }
    //*/
    if(head)
    {
        printf(">>>>>>>>>>>>>>>>> Head did exist at the end !\n");
        if(head == curr)
        {
            free(head);
            printf(">>>>>>>>>>> |||||||||||  HEAD = CURR !!!!! |||||||||| >>>>>>>>>\n");
        }
        head = NULL;
    }
    else
        printf(">>>>>>>>>>>>>>>>> Head did NOT exist at the end !\n");

    if(curr)
    {
        printf(">>>>>>>>>>>>>>>>> Curr did exist at the end !\n");
        if(curr == head)
        {
            free(curr);
            printf(">>>>>>>>>>> |||||||||||  CURR = HEAD !!!!! |||||||||| >>>>>>>>>\n");
        }
        curr = NULL;
    }
    else
        printf(">>>>>>>>>>>>>>>>> Curr did NOT exist at the end !\n");

    printf("All data structures deleted ! List is now empty ! Printing the list:\n");
    print_list();
}
