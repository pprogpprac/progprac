/* Naveen R. Iyer
Problem Statement: Create a linked list (master_list) with even and odd numbers in random order.
From this list, create two new lists, even_list - consisting of all even elements of master_list
and odd_list - consisting of all odd elements of master_list.
*/

#include <iostream>

struct node
{
	int val;
	struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;
struct node *prev = NULL;

struct node *even_list_head = NULL;
struct node *even_list_tail = NULL;

struct node *odd_list_head = NULL;
struct node *odd_list_tail = NULL;

void create_even_odd_lists(struct node*);

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

int main()
{
	//--------------------------------------------------------------------
	// Create a linked list with even and odd numbers
	add_to_list(17, true);
	add_to_list(23, true);
	add_to_list(12, true);
	add_to_list(6, false);
	add_to_list(21, true);
    add_to_list(171, false);
	add_to_list(134, true);
	add_to_list(230, true);
	add_to_list(79, true);
	add_to_list(218, true);
	//--------------------------------------------------------------------


	//--------------------------------------------------------------------
	// Testing print_list
	std::cout << "\nPrinting the entire list...\n";
	print_list();
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

	/*even_list_head_node = create_even_list(head);
	std::cout << "\n ||| SHUDNT B MODIFIED Printing the entire list...\n";
	print_list();
	std::cout << " ||| SHUDNT B MODIFIED Done printing the entire list !\n";
	odd_list_head_node = create_odd_list(head);*/

	create_even_odd_lists(head);

	// Print even list
	std::cout << "\nPrinting the entire EVEN list...\n";
	struct node *foo = even_list_head;

	while (foo != NULL)
	{
		std::cout << foo->val << std::endl;
		foo = foo->next;
	}
	std::cout << "Done printing the entire EVEN list !\n";



	// Print odd list
	std::cout << "\nPrinting the entire ODD list...\n";
	struct node *foo1 = odd_list_head;

	while (foo1 != NULL)
	{
		std::cout << foo1->val << std::endl;
		foo1 = foo1->next;
	}
	std::cout << "Done printing the entire ODD list !\n";

	return 0;
}

void create_even_odd_lists(struct node* node_head)
{
	while(node_head != NULL)
    {
        if(node_head->val % 2 == 0)
		{
			struct node* foo = new (struct node);
			foo->val = -1;
			foo->next = NULL;

			foo = node_head;

			std::cout << "DEBUG EVEN: node_head->val = " << foo->val << std::endl;

			if(NULL == even_list_head)
			{
				even_list_head = even_list_tail = foo;
			}
			else
			{
				even_list_tail->next = foo;
				even_list_tail = foo;
			}
		}
		else
		{
			struct node* foo = new (struct node);
			foo->val = -1;
			foo->next = NULL;

			foo = node_head;

			std::cout << "DEBUG ODD: node_head->val = " << foo->val << std::endl;

			if(NULL == odd_list_head)
			{
				odd_list_head = odd_list_tail = foo;
			}
			else
			{
				odd_list_tail->next = foo;
				odd_list_tail = foo;
			}
		}
		node_head = node_head->next;
	}
}
