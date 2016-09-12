/* Naveen R. Iyer
"Linked List From Scratch" v12

Bugs:
- Removed section of code that was accessing class's private data:
Line #198 from NRI_From_Scratch_LinkedList_2: "// Testing status of head, tail and prev nodes"


NEW Features:
- Re-organized code to make it as generic and universally named as possible !

Features:
- Reverse Linked List function added !

- Created remove_head() function. (Cannot create remove_tail() function in singly-linked list,or can you?)
and therefore modified the destructor.

- Created swap_head() and swap_tail() functions.
- Created swap_node().
- Created a "change_node()" function.
- Changed most of the functions to return struct instead of int.

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

List of functions:
1) print_list()     -> O(n)   -> void print_list()
2) insert_head()    -> O(1)   -> int insert_head(int ival, float fval, const char cval[50])
3) insert_tail()    -> O(1)   -> int insert_tail(int ival, float fval, const char cval[50])
4) search_list()    -> O(n)   -> struct node * search_list(int ival)
5) swap_head()      -> O(n)   -> void swap_head(int node_x)
6) swap_tail()      -> O(n)   -> void swap_tail(int node_x)
7) swap_node()      -> O(n^2) -> void swap_node(int node_x, int node_y)
8) update_node()    -> O(n)   -> struct node * update_node(int replace_id, int ival, float fval, const char cval[50])
9) remove_head()    -> O(1)   -> void remove_head()
10) remove_node()   -> O(n)   -> int remove_node(int ival)
11) reverse_list()  -> O(n)   -> void reverse_list()
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
    void print_list() //O(n)
    {
    	struct node *foo = head;

    	while (foo != NULL)
    	{
    		std::cout << "Node ID: " << foo->id;
            std::cout << ", Node float data: " << foo->fdata;
            std::cout << ", Node string data: " << foo->cdata << std::endl;
    		foo = foo->next;
    	}
    }

    // Add node as head.
    int insert_head(int ival, float fval, const char cval[50]) //O(1)
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

    // Add node as tail.
    int insert_tail(int ival, float fval, const char cval[50]) //O(1)
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

    // Search the list for node with node id "ival".
    struct node * search_list(int ival) // O(n)
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

    // Swap node_x with head node.
    void swap_head(int node_x) // O(n)
    {
        struct node *foo = search_list(node_x);
        struct node *temp = new (struct node);

        // Swap data only, NOT next pointers !
        temp->id = foo->id;
        foo->id = head->id;
        head->id = temp->id;

        temp->fdata = foo->fdata;
        foo->fdata = head->fdata;
        head->fdata = temp->fdata;

        snprintf(temp->cdata, sizeof(temp->cdata), "%s", foo->cdata);
        snprintf(foo->cdata, sizeof(temp->cdata), "%s", head->cdata);
        snprintf(head->cdata, sizeof(temp->cdata), "%s", temp->cdata);

        delete(temp);
        temp = NULL;
    }

    // Swap node_x with tail node.
    void swap_tail(int node_x) // O(n)
    {
        struct node *foo = search_list(node_x);
        struct node *temp = new (struct node);

        // Swap data only, NOT next pointers !
        temp->id = foo->id;
        foo->id = tail->id;
        tail->id = temp->id;

        temp->fdata = foo->fdata;
        foo->fdata = tail->fdata;
        tail->fdata = temp->fdata;

        snprintf(temp->cdata, sizeof(temp->cdata), "%s", foo->cdata);
        snprintf(foo->cdata, sizeof(temp->cdata), "%s", tail->cdata);
        snprintf(tail->cdata, sizeof(temp->cdata), "%s", temp->cdata);

        delete(temp);
        temp = NULL;
    }

    // Swap node_x with node_y.
    void swap_node(int node_x, int node_y) // O(n^2)
    {
        struct node *foo = search_list(node_x);
        struct node *bar = search_list(node_y);

        struct node *temp = new (struct node);

        // Swap data only, NOT next pointers !
        temp->id = foo->id;
        foo->id = bar->id;
        bar->id = temp->id;

        temp->fdata = foo->fdata;
        foo->fdata = bar->fdata;
        bar->fdata = temp->fdata;

        snprintf(temp->cdata, sizeof(temp->cdata), "%s", foo->cdata);
        snprintf(foo->cdata, sizeof(temp->cdata), "%s", bar->cdata);
        snprintf(bar->cdata, sizeof(temp->cdata), "%s", temp->cdata);

        delete(temp);
        temp = NULL;
    }

    // Update a node with new data.
    struct node * update_node(int replace_id, int ival, float fval, const char cval[50]) //O(n)
    {
        struct node *foo = search_list(replace_id);

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

    // Remove head node.
    void remove_head() //O(1)
    {
        struct node *foo = head;
        head = head->next;
        foo->next = NULL;
        delete(foo);
        foo = NULL;
    }

    // Remove any node given by ival.
    int remove_node(int ival) //O(n)
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

    /* Function to reverse the linked list */
    void reverse_list() //O(n)
    {
        //struct node* prev   = NULL;
        prev = NULL;
        struct node* current = head;
        struct node* next;
        while (current != NULL)
        {
            next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }


    ~nri_linked_list() // O(n)
    {
        //--------------------------------------------------------------------
        // Delete the entire list (releasing the memory used ofcourse !)
        while (head != NULL)
        {
            remove_head();
        }
        std::cout << "\n||||||||||||||||||||||||||||||\nDELETED ENTIRE LIST !\n||||||||||||||||||||||||||||||\n";
    }
}; // class nri_linked_list
