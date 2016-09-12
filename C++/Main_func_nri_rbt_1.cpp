#include <iostream>
#include "nri_rbt.cpp"

int main()
{
	nri_tree t1;  // Creating an empty tree

	/*Code to test the logic*/
	/*
	t1.insert_node(15); // should automatically become root.
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(13);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(14);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(12);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

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
	*/


	//----------------------------------------------------------
	// Professor's lecture slide red-black tree.
	t1.insert_node(10);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(7);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(40);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

    t1.insert_node(3);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(8);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(30);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(45);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(1);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(5);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(20);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(35);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(60);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(25);
	t1.print_tree();
	std::cout << "\n--------------------------\n";



	// Checking delete
	/*t1.remove_node(25); // leaf node
	t1.print_tree();
	std::cout << "\n--------------------------\n";*/


	t1.remove_node(20); // node with one child.
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	/*
	t1.insert_node(30);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(20);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(10);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(40);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(35);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(50);
	t1.print_tree();
	std::cout << "\n--------------------------\n";


	//t1.remove_node(20);
	t1.print_tree();
	std::cout << "\n--------------------------\n";
	*/

	/*t1.remove_node(30); // node with two children.
	t1.print_tree();
	std::cout << "\n--------------------------\n";*/

	/*
	//----------------------------------------------------------
	// Topcoder: https://www.topcoder.com/community/data-science/data-science-tutorials/an-introduction-to-binary-search-and-red-black-trees/
	//Red-black tree example
	t1.insert_node(11);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(2);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(14);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

    t1.insert_node(1);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(7);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(15);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(5);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(8);
	t1.print_tree();
	std::cout << "\n--------------------------\n";

	t1.insert_node(4);
	t1.print_tree();
	std::cout << "\n--------------------------\n";
	*/









	//t1.print_tree();

	/*
	t1.print_tree();
	std::cout << "Deleting leaf node...\n";
	t1.delete_node(18);
	t1.print_tree();
	*/

	/*
	t1.print_tree();
	std::cout << "Deleting leaf node...\n";
	t1.delete_node(16);
	t1.print_tree();

	std::cout << "Now that node 17 is a node with one child 16, deleting node 17...\n";
	t1.delete_node(17);
	t1.print_tree();

	t1.delete_node(17);
	*/
	// Delete root ndoe to check case 3: delete a node with two children.
	//t1.delete_node(17);

	//std::cout << "Remove node.\n";
	//t1.remove_node(15);
	//t1.print_tree();


	// Ask user to enter a number.
	/*int number;
	std::cout << "Enter number be searched\n";
	std::cin >> number;

	if(t1.search_tree(number) != nullptr)
        std::cout << "Found\n";
	else
        std::cout<<"Not Found\n";

    t1.print_tree();*/
    //delete_tree(root);
}
