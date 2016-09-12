/* Naveen R. Iyer
"Linked List From Scratch" v4

Bugs:
- Removed section of code that was accessing class's private data:
Line #198 from NRI_From_Scratch_LinkedList_2: "// Testing status of head, tail and prev nodes"

NEW Features:
- add_to_list() function split into two functions - add_as_head() and add_as_tail().
- Defined struct node inside class nri_linked_list instead of outside ! (Don't know why though, probably to avoid globals).
- Implemented destructor !

Features:
- Modified code to implement class feature of C++.

- Add node to end or to beginning.
- Delete entire list with no memory leaks.
*/

#include <iostream>


class nri_linked_list
{
private:
    struct node
    {
    	int val;
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
    		std::cout << foo->val << std::endl;
    		foo = foo->next;
    	}
    }

    void add_as_head(int value)
    {
        struct node *foo = new (struct node);
    	foo->val = value;
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
    }

    void add_as_tail(int value)
    {
        struct node *foo = new (struct node);
    	foo->val = value;
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
    }

    struct node * search_list(int value)
    {
    	struct node *foo = head;

    	while(foo != NULL)
        {
            if(foo->val == value)
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
        else if (foo->val == head->val)
        {
            head = head->next;

            foo->next = NULL;
            delete(foo);
            foo = NULL;
        }
        else if (foo->val == tail->val)
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
        std::cout << "\n||||||||||||||||||||||||||||||\nDELETING ENTIRE LIST...\n||||||||||||||||||||||||||||||\n";
        while (head != NULL)
        {
            remove_node(head->val);
            std::cout << "\nPrinting the entire list...\n";
            print_list();
            std::cout << "Done printing the entire list !\n";
        }
    }
}; // class nri_linked_list

int main()
{
	//--------------------------------------------------------------------
	// Create a linked list with even and odd numbers
    nri_linked_list l1;

	l1.add_as_tail(17);
	l1.add_as_tail(23);
	l1.add_as_tail(12);
	l1.add_as_head(6);
	l1.add_as_tail(21);
    l1.add_as_head(171);
	l1.add_as_tail(234);
	l1.add_as_tail(130);
	l1.add_as_tail(79);
	l1.add_as_tail(218);
    l1.add_as_tail(221);
	//--------------------------------------------------------------------


	//--------------------------------------------------------------------
	// Testing print_list
	std::cout << "\nPrinting the entire list...\n";
	l1.print_list();
	std::cout << "Done printing the entire list !\n";
	//--------------------------------------------------------------------




	//--------------------------------------------------------------------
	// Testing search_list
	int num = 0;

	std::cout << "Enter integer to search:\n";
	std::cin >> num;

	if (l1.search_list(num) != NULL)
		std::cout << "Found in list ! :)\n";
	else
		std::cout << "Not Found in list ! :(\n";
	//--------------------------------------------------------------------



	//--------------------------------------------------------------------
	// Testing remove_node
	std::cout << "Enter integer to delete:\n";
	std::cin >> num;

	if (l1.remove_node(num) != -1)
		std::cout << "Deleted node value " << num << "\n";
	else
		std::cout << "Not Found in list ! :(\n";

	std::cout << "\nPrinting the entire list...\n";
	l1.print_list();
	std::cout << "Done printing the entire list !\n";
	//--------------------------------------------------------------------


	return 0;
}
