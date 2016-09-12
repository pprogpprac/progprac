/* Naveen R. Iyer
"Linked List From Scratch" v7

Bugs:
- Removed section of code that was accessing class's private data:
Line #198 from NRI_From_Scratch_LinkedList_2: "// Testing status of head, tail and prev nodes"

NEW Features:
- Added additional data to each node, other than just node ID, "id".


Features:
- Changed all values, 'val's, of the nodes to node IDs, 'ID's.
- Changed return type of add_as_head() and add_as_tail() from void to int (returning its id).
- Commented out the print_list() from destructor to make it less verbose on the STDOUT !

- Modified code to implement class feature of C++.

- Add node to end or to beginning.
- Delete entire list with no memory leaks.

- Removed main function. Code only consists of a class which can be #included !
- add_to_list() function split into two functions - add_as_head() and add_as_tail().
- Defined struct node inside class nri_linked_list instead of outside ! (Don't know why though, probably to avoid globals).
- Implemented destructor !

*/

#include <iostream>
#include <cstdio> // For snprintf() !


class nri_linked_list
{
private:
    struct node
    {
    	int id;
        float fdata;
        char cdata[50];
    	struct node *next;
    };

    struct node *head = NULL;
    struct node *tail = NULL;
    struct node *prev = NULL;

public:
    void print_list()
    {
    	struct node *foo = head;

    	while (foo != NULL)
    	{
    		std::cout << "\nNode ID: " << foo->id;
            std::cout << ", Node float data: " << foo->fdata;
            std::cout << ", Node string data: " << foo->cdata << std::endl;
    		foo = foo->next;
    	}
    }

    int add_as_head(int value)
    {
        struct node *foo = new (struct node);
    	foo->id = value;
        foo->fdata = float(value) + 0.52;
        snprintf(foo->cdata, sizeof(foo->cdata), "Added as %.2f head !", foo->fdata);
    	foo->next = NULL;

    	// If its a new list, then this is the first node, so tail and head both are the same !
    	if(NULL == head)
    		head = tail = foo;
        else
        {
            // Add to beginning of list
            foo->next = head;
            head = foo;
        }
        return value;
    }

    int add_as_tail(int value)
    {
        struct node *foo = new (struct node);
    	foo->id = value;
        foo->fdata = float(value) + 0.52;
        snprintf(foo->cdata, sizeof(foo->cdata), "Added as %.2f tail !", foo->fdata);
    	foo->next = NULL;

        // If its a new list, then this is the first node, so tail and head both are the same !
    	if(NULL == head)
    		head = tail = foo;
    	else
    	{
            // Add to end of list
    		tail->next = foo; // THIS IS WHAT YOU FORGOT TO ADD NRI !
    		tail = foo; // After this statement, tail->next should obviously be NULL
    	}
        return value;
    }

    struct node * search_list(int value)
    {
    	struct node *foo = head;

    	while(foo != NULL)
        {
            if(foo->id == value)
                return foo;
            else
    		{
    			prev = foo;
                foo = foo->next;
    		}
    	}
    	return NULL;
    }

    int remove_node(int value)
    {
        struct node *foo = search_list(value);

    	// Check if node exists
    	if (foo == NULL)
        {
            return -1;
        }
        else if (foo->id == head->id)
        {
            head = head->next;

            foo->next = NULL;
            delete(foo);
            foo = NULL;
        }
        else if (foo->id == tail->id)
        {
            //tail->next = prev->next;
            tail = prev;
            prev->next = foo->next;

            foo->next = NULL;
            delete(foo);
            foo = NULL;
        }
        else
        {
            prev->next = foo->next;

            foo->next = NULL;
            delete(foo);
            foo = NULL;
        }
        return 0;
    }

    ~nri_linked_list()
    {
        //--------------------------------------------------------------------
        // Delete the entire list (releasing the memory used ofcourse !)
        //std::cout << "\n||||||||||||||||||||||||||||||\nDELETING ENTIRE LIST...\n||||||||||||||||||||||||||||||\n";
        while (head != NULL)
        {
            remove_node(head->id);
            //std::cout << "\nPrinting the entire list...\n";
            //print_list();
            //std::cout << "Done printing the entire list !\n";
        }
        std::cout << "\n||||||||||||||||||||||||||||||\nDELETED ENTIRE LIST !\n||||||||||||||||||||||||||||||\n";
    }
}; // class nri_linked_list
