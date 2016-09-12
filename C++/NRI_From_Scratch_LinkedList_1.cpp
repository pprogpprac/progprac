/* Naveen R. Iyer
"Linked List From Scratch"

NEW Features:
- Modified code to implement class feature of C++.

Features:
- Add node to end or to beginning.
- Delete entire list with no memory leaks.
*/

#include <iostream>

struct node
{
	int val;
	struct node *next;
};

class nri_linked_list
{
private:
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

    void add_to_list(int value, bool add_to_end)
    {
    	struct node *foo = new (struct node);
    	foo->val = value;
    	foo->next = NULL;

    	// If its a new list, then this is the first node, so tail and head both are the same !
    	if(NULL == head)
    		head = tail = foo;
    	else if (add_to_end == true)
    	{
            // Add to end of list
    		tail->next = foo; // THIS IS WHAT YOU FORGOT TO ADD NRI !
    		tail = foo; // After this statement, tail->next should obviously be NULL
    	}
        else
        {
            // Add to beginning of list
            foo->next = head;
            head = foo;
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

    int delete_list(int value)
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
}; // class nri_linked_list

int main()
{
	//--------------------------------------------------------------------
	// Create a linked list with even and odd numbers
    nri_linked_list l1;

	l1.add_to_list(17, true);
	l1.add_to_list(23, true);
	l1.add_to_list(12, true);
	l1.add_to_list(6, false);
	l1.add_to_list(21, true);
    l1.add_to_list(171, false);
	l1.add_to_list(234, true);
	l1.add_to_list(130, true);
	l1.add_to_list(79, true);
	l1.add_to_list(218, true);
	//--------------------------------------------------------------------


	//--------------------------------------------------------------------
	// Testing print_list
	std::cout << "\nPrinting the entire list...\n";
	l1.print_list();
	std::cout << "Done printing the entire list !\n";
	//--------------------------------------------------------------------



    /*
	//--------------------------------------------------------------------
	// Testing search_list
	int num = 0;

	std::cout << "Enter integer to search:\n";
	std::cin >> num;

	if (search_list(num) != NULL)
		std::cout << "Found in list ! :)\n";
	else
		std::cout << "Not Found in list ! :(\n";
	//--------------------------------------------------------------------



	//--------------------------------------------------------------------
	// Testing delete_list
	std::cout << "Enter integer to delete:\n";
	std::cin >> num;

	if (delete_list(num) != -1)
		std::cout << "Deleted node value " << num << "\n";
	else
		std::cout << "Not Found in list ! :(\n";

	std::cout << "\nPrinting the entire list...\n";
	print_list();
	std::cout << "Done printing the entire list !\n";
	//--------------------------------------------------------------------


	//--------------------------------------------------------------------
	// Testing status of head, tail and prev nodes
	if (head == NULL)
		std::cout << "\nHead node is NULL !\n";
	else
		std::cout << "\nHead node value = " << head->val;

	if (tail == NULL)
		std::cout << "\ntail node is NULL !\n";
	else
		std::cout << "\ntail node value = " << tail->val;

	if (prev == NULL)
		std::cout << "\nprevious node value = NULL !\n";
	else
		std::cout << "\nprevious node value = " << prev->val;
	//--------------------------------------------------------------------


	//--------------------------------------------------------------------
	// Delete the entire list (releasing the memory used ofcourse !)
	std::cout << "\n|||||||||||||||||||||||||||||||\nDELETING ENTIRE LIST...\n||||||||||||||||||||||||||||||\n";
	while (head != NULL)
	{
		delete_list(head->val);
		std::cout << "\nPrinting the entire list...\n";
		print_list();
		std::cout << "Done printing the entire list !\n";
	}
    */
	return 0;
}
