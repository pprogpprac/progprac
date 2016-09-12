#include <iostream>
#include "nri_bst.cpp"

int main()
{
	nri_bst t1;  // Creating an empty tree

	/*Code to test the logic*/

	t1.insert_node(15); // should automatically become root.
	t1.insert_node(13);
	t1.insert_node(14);
	t1.insert_node(12);
	t1.insert_node(17);
	t1.insert_node(16);
    t1.insert_node(18);
	t1.insert_node(18);
	t1.insert_node(13);

	t1.insert_node(-13);
	t1.insert_node(-14);
	t1.insert_node(-12);
	t1.insert_node(0);
	t1.insert_node(-16);
    t1.insert_node(-18);

	t1.print_bst();

	/*
	t1.print_bst();
	std::cout << "Deleting leaf node...\n";
	t1.delete_node(18);
	t1.print_bst();
	*/

	/*
	t1.print_bst();
	std::cout << "Deleting leaf node...\n";
	t1.delete_node(16);
	t1.print_bst();

	std::cout << "Now that node 17 is a node with one child 16, deleting node 17...\n";
	t1.delete_node(17);
	t1.print_bst();

	t1.delete_node(17);
	*/
	// Delete root ndoe to check case 3: delete a node with two children.
	//t1.delete_node(17);

	std::cout << "Remove node.\n";
	t1.remove_node(15);
	t1.print_bst();


	// Ask user to enter a number.
	/*int number;
	std::cout << "Enter number be searched\n";
	std::cin >> number;

	if(t1.search_bst(number) != nullptr)
        std::cout << "Found\n";
	else
        std::cout<<"Not Found\n";

    t1.print_bst();*/
    //delete_bst(root);
}
