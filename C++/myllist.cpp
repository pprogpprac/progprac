#include <iostream>
#include <cstring>
#include <unistd.h> // For sleep

using namespace std;

int num_of_nodes = 0;

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

    cout << "\n*** print_list func says - Printing the entire list !\n";
    cout << "\n<------------- List starts here ! ------------>\n\n";
    cout << "__ID__\t|\t__NAME__\t|\t__WEIGHT__\n";

    while(ptr != NULL)
    {
        cout << ptr->id << "\t|\t" << ptr->name << "\t|\t " << ptr->wt << "\n";
        ptr = ptr->next;
    }
    cout << "\n<-------------- List ends here ! ------------->\n\n";

    if(!head)
        cout << "*** print_list func says - No head node !\n";
    else
        cout << "*** print_list func: DEBUG: Head node is id " << head->id << "\n";


    if(!curr)
        cout << "*** print_list func says - No curr node !\n\n";
    else
        cout << "*** print_list func: DEBUG: Curr node is id " << curr->id << "\n\n";

    return;
}

struct Person* create_list(int ivar, char cvar[], float fvar)
{
    cout << "*** create_list func says - Creating list with headnode as " << ivar << "\n";
    struct Person *ptr = new Person;

    if(NULL == ptr)
    {
        cout << "*** create_list func says - Node creation failed \n";
        return NULL;
    }

    ptr->id = ivar;
    memcpy(ptr->name, cvar, sizeof(ptr->name));
    ptr->wt = fvar;
    ptr->next = NULL;

    head = curr = ptr;
    num_of_nodes++;
    return ptr;
}

struct Person* add_to_list(int ivar, char cvar[], float fvar, bool add_to_end)
{
    if(NULL == head)
    {
        return (create_list(ivar, cvar, fvar));
    }

    if(add_to_end)
        cout << "*** add_to_list func says - Adding node with id " << ivar << " to the end of list\n";
    else
        cout << "*** add_to_list func says - Adding node with id " << ivar << " to the beginning of list\n";

    struct Person *ptr = new Person;

    if(NULL == ptr)
    {
        cout << "*** add_to_list func says - Node creation failed \n";
        return NULL;
    }

    ptr->id = ivar;
    memcpy(ptr->name, cvar, sizeof(ptr->name));
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
    num_of_nodes++;
    return ptr;
}

struct Person* search_in_list(int ivar, struct Person **prev)
{
    struct Person *ptr = head;
    struct Person *tmp = NULL;
    bool found = false;

    while(ptr != NULL)
    {
        if(ptr->id == ivar)
        {
            found = true;
            break;
        }
        else
        {
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

    cout << "*** delete_from_list func says - Deleting node with id " << ivar << " from list\n";

    del = search_in_list(ivar, &prev);

    if(del == NULL)
    {
        return -1;
    }
    else
    {
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

    delete(del);
    del = NULL;

    num_of_nodes--;

    return 0;
}

int main()
{
    int i = 3, ret = 0;
    struct Person *ptr = NULL;

    print_list();
    create_list(1, (char *) "Naveen Iyer", 72.35);
    print_list();

    add_to_list(2, (char *) "Ending N..ln", 83.226, true);
    add_to_list(3, (char *) "0123456789", 11.2, true);
    add_to_list(0, (char *) "Benjkl Bhsdgs", 31, false);
    add_to_list(4, (char *) "CounterStrike", 86.04, true);

    print_list();

    cout << "*** Main func says - Enter the node id you want to search in list:\n";
    cin >> i;

    ptr = search_in_list(i, NULL);
    if(NULL == ptr)
    {
        cout << "*** Main func says - Search failed ! id = " << i << " not found\n";
    }
    else
    {
        cout << "*** Main func says - Search passed ! Following are the data of the data structure with id " << ptr->id << ":\n";
        cout << "__ID__\t|\t__NAME__\t|\t__WEIGHT__\n";
        cout << ptr->id << "\t|\t" << ptr->name << "\t|\t" << ptr->wt << "\n";
    }

    cout << "*** Main func says - Enter the node id you want to delete from the list:\n";
    cin >> i;

    ret = delete_from_list(i);
    if(ret != 0)
    {
        cout << "\n*** Main func says - Data structure with id = " << i << " not found\n";
    }
    else
    {
        cout << "\n*** Main func says - Data structure with id = " << i << " deleted !\n";
    }
    print_list();

    cout << "*** Main func says - Sleeping for 3 seconds and then deleting the complete list !\n";
    sleep(3);

    cout << "*** Main func says - Now deleting the entire list since the end of program has reached !\n";

    //for(i = 0; i < 4; i++) // Spare-one-last-node approach ! Obsolete ! Use infinite loop instead !

    //Count the number of nodes in the linked list
    cout << "*** Main func says - Total number of nodes in the linked list = " << num_of_nodes << endl;
    sleep(3);

    for(i = 0; i < 10; i++)
    {
        if(head == curr)
        {
            cout << "*** Main func says - >>>>>>>>>>> |||||||||||  LAST NODE |||||||||| >>>>>>>>>\n";
            break;
        }
        delete_from_list(i); // delete_from_list() calls search_in_list() within itself
        print_list();
    }

    if(head)
    {
        cout << "*** Main func says - >>>>>>>>>>>>>>>>> Head did exist at the end !\n";
        if(head == curr)
        {
            delete(head);
            cout << "*** Main func says - >>>>>>>>>>> |||||||||||  HEAD = CURR !!!!! |||||||||| >>>>>>>>>\n";
        }
        head = NULL;
    }
    else
        cout << "*** Main func says - >>>>>>>>>>>>>>>>> Head did NOT exist at the end !\n";

    if(curr)
    {
        cout << "*** Main func says - >>>>>>>>>>>>>>>>> Curr did exist at the end !\n";
        if(curr == head)
        {
            delete(curr);
            cout << "*** Main func says - >>>>>>>>>>> |||||||||||  CURR = HEAD !!!!! |||||||||| >>>>>>>>>\n";
        }
        curr = NULL;
    }
    else
        cout << "*** Main func says - >>>>>>>>>>>>>>>>> Curr did NOT exist at the end !\n";

    cout << "*** Main func says - All data structures deleted ! List is now empty ! Printing the list:\n";
    print_list();

    return 0;
}
