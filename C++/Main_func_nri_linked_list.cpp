#include <iostream>
#include "nri_linked_list.cpp"

int main()
{
	//--------------------------------------------------------------------
	// Create a linked list with even and odd numbers
    nri_linked_list l1, l2;

	l1.insert_tail(17, 17.52, "Seventeen");
	l1.insert_tail(-23, -23.52, "Minus Twenty Three");
	l1.insert_head(6, 6.52, "Six");
	l1.insert_tail(-23, -23.52, "Minus Twenty Three");
    l1.insert_head(0, 0.52, "Zero");
	l1.insert_tail(7, 7.52, "Seven");
    l1.insert_tail(221, 221.52, "Two Twenty One");

	l2.insert_tail(3, 3.52, "Three");
	l2.insert_tail(-3, -3.52, "Minus Three");
	//--------------------------------------------------------------------


	//--------------------------------------------------------------------
	// Testing print_list
	std::cout << "\nPrinting the list 1...\n";
	l1.print_list();
	std::cout << "Done printing the entire list 1 !\n";

	std::cout << "\nPrinting the list 2...\n";
	l2.print_list();
	std::cout << "Done printing the entire list 2 !\n";
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

	std::cout << "\nReversed the linked list !\n";

	l1.reverse_list();
	l2.reverse_list();

	std::cout << "\nPrinting the list 1...\n";
	l1.print_list();
	std::cout << "Done printing the entire list 1 !\n";

	std::cout << "\nPrinting the list 2...\n";
	l2.print_list();
	std::cout << "Done printing the entire list 2 !\n";


	return 0;
}
