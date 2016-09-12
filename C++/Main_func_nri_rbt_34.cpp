/*
Main function for nri_rbt.cpp
v34
*/
#include <iostream>
//#include "nri_rbt_WORKING_27.cpp"
#include "nri_rbt.cpp"


int main(int argc, char **argv)
{
    nri_tree t1;  // Creating an empty tree

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

	//t1.assign_levels();
    t1.print_tree();
	std::cout << "\n--------------------------\n";
    t1.level_order();
    t1.visualize_tree();


	return 0;
}
