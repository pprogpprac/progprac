/* Naveen R. Iyer
"Linked List From Scratch" v8

Bugs:
- Removed section of code that was accessing class's private data:
Line #198 from NRI_From_Scratch_LinkedList_2: "// Testing status of head, tail and prev nodes"


NEW Features:
- Created swap_node().
- Created a "change_node()" function.
- Changed most of the functions to return struct instead of int.


Features:
- Added additional data to each node, other than just node ID, "id".
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

    int add_as_head(int ival, float fval, const char cval[50])
    {
        struct node *foo = new (struct node);
    	foo->id = ival;
        foo->fdata = fval;
        snprintf(foo->cdata, sizeof(foo->cdata), "%s", cval);
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
        return ival;
    }

    int add_as_tail(int ival, float fval, const char cval[50])
    {
        struct node *foo = new (struct node);
        foo->id = ival;
        foo->fdata = fval;
        //foo->cdata = cval;
        snprintf(foo->cdata, sizeof(foo->cdata), "%s", cval);
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
        return ival;
    }

    struct node * search_list(int ival)
    {
    	struct node *foo = head;

    	while(foo != NULL)
        {
            if(foo->id == ival)
                return foo;
            else
    		{
    			prev = foo;
                foo = foo->next;
    		}
    	}
    	return NULL;
    }

    int remove_node(int ival)
    {
        struct node *foo = search_list(ival);

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

    void swap_node(int node_x, int node_y)
    {
        struct node *foo = search_list(node_x);
        struct node *foo1 = search_list(node_y);
        struct node *temp = new (struct node);

        // Swap data only, NOT next pointers !
        temp->id = foo->id;
        foo->id = foo1->id;
        foo1->id = temp->id;

        temp->fdata = foo->fdata;
        foo->fdata = foo1->fdata;
        foo1->fdata = temp->fdata;

        snprintf(temp->cdata, sizeof(temp->cdata), "%s", foo->cdata);
        snprintf(foo->cdata, sizeof(temp->cdata), "%s", foo1->cdata);
        snprintf(foo1->cdata, sizeof(temp->cdata), "%s", temp->cdata);

        delete(temp);
        temp = NULL;
    }

    struct node * replace_node(int replace_val, int ival, float fval, const char cval[50])
    {
        struct node *foo = search_list(replace_val);

    	// Check if node exists
    	if (foo == NULL)
        {
            return NULL;
        }
        else
        {
            foo->id = ival;
            foo->fdata = fval;
            snprintf(foo->cdata, sizeof(foo->cdata), "%s", cval);
            return foo;
        }
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
