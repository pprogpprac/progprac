#include <iostream>
//#include "nri_rbt_WORKING_27.cpp"
#include "nri_rbt.cpp"


int main(int argc, char **argv)
{
    nri_tree t1;  // Creating an empty tree

	/*
    //----------------------------------------------------------
    // Test Case 1: Professor's lecture slide red-black tree.
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

	// ----------Modifications-----------------

	t1.insert_node(43);
    t1.print_tree();
    std::cout << "\n--------------------------\n";
	t1.insert_node(42);
    t1.print_tree();
    std::cout << "\n--------------------------\n";
	t1.insert_node(44);
    t1.print_tree();
    std::cout << "\n--------------------------\n";

	t1.insert_node(4387);
    t1.print_tree();
    std::cout << "\n--------------------------\n";

	*/

	/*
	// Test Case 2: User Input.
	int x = 0;
	while (1)
	{
		std::cout << "\nEnter new node, else enter anything other than integer:\n";
		std::cin >> x;
		if (std::cin.fail())
			break;
		t1.insert_node(x);
	    t1.print_tree();
	    std::cout << "\n--------------------------\n";
		t1.level_order();
	}
	t1.check_rules_complete_tree();
	t1.print_tree();
	std::cout << "\n--------------------------\n";
	*/

    /*
	// Test Cases 1 & 3: Fixed maximum (given by max_input) incremental input limit.
	int max_input = 16;
	for (int i = max_input; i > 0; --i) // Testing insert() case 1 of 4.
    //for (int i = 1; i <= max_input; ++i) // Testing insert() case 3 of 4.
	{
        //std::cout << "\n------Inserting " << i << "---------------\n";
		t1.insert_node(i);
	    //t1.print_tree();
	    //std::cout << "\n--------------------------\n";
		//t1.level_order();
	}
    */

    // Test Cases 2 & 4:
    t1.insert_node(7);
    t1.insert_node(12);
    t1.insert_node(17);
    t1.insert_node(3);
    t1.insert_node(9);
    t1.insert_node(13);
    t1.insert_node(21);
    t1.insert_node(1);
    t1.insert_node(11);
    t1.insert_node(2); // Testing insert() case 2 of 4.
    t1.insert_node(10); // Testing insert() case 4 of 4.*/

    /*t1.insert_node(10);
    t1.insert_node(7);
    t1.insert_node(40);
    t1.insert_node(3);
    t1.insert_node(8);
    t1.insert_node(30);
    t1.insert_node(45);
    t1.insert_node(1);
    t1.insert_node(5);
    t1.insert_node(20);
    t1.insert_node(35);
    t1.insert_node(60);
    t1.insert_node(25);*/

	t1.assign_levels();
    t1.print_tree();
	std::cout << "\n--------------------------\n";
    t1.level_order();
    t1.post_order();
    //t1.show_details_of_node(2);

    // The check_rules_assign_color() function should not be called whenever the hell you want. It should be called only by functions within the code, like insert_node(). Else, you'll end up making all nodes black (only sparing leaves, since they can still be red, but its parent will be black.) at the expense of more memory resources (check with valgrind, you'll find more unnecessary allocs and frees). Any advantage of doing it again and again? Well, YES ! By reducing number of red nodes, you are reducing the tree height! :). But again, do not forget the tradeoff: if u want to reduce tree height this way, you will consume more unnecessary memory.
    /*
    t1.check_rules_assign_color(t1.search_tree(2));
    t1.print_tree();
	std::cout << "\n--------------------------\n";
    t1.level_order();
    t1.post_order();
    t1.show_details_of_node(2);

    t1.check_rules_assign_color(t1.search_tree(3));
    t1.print_tree();
	std::cout << "\n--------------------------\n";
    t1.level_order();
    t1.post_order();
    t1.show_details_of_node(3);
    */

    /*std::cout << "\n-----------preorder------------\n";
    t1.preorder();
    std::cout << "\n-----------inorder------------\n";
    t1.inorder();
    std::cout << "\n-----------postorder------------\n";
    t1.postorder();
    std::cout << std::endl;*/

	return 0;
}
