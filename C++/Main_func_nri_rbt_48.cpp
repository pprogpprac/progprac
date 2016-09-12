/*
Main function for nri_rbt.cpp
v48

MODIFICATIONS:
- Introduced display() which will call all STDOUT functions, namely, print_tree(), print_tree_level_order(), visualize_tree().

- Renamed level_order() to print_tree_level_order().

*/
#include <iostream>
//#include "nri_rbt_WORKING_27.cpp"
#include "nri_rbt.cpp"


int main(int argc, char **argv)
{
    nri_tree t1;  // Creating an empty tree


	// Test Cases 1 & 3: Fixed maximum (given by max_input) incremental input limit.
	int max_input = 32;
	for (int i = max_input; i > 0; --i) // Testing insert() case 1 of 4.
    //for (int i = 1; i <= max_input; ++i) // Testing insert() case 3 of 4.
	{
        //std::cout << "\n------Inserting " << i << "---------------\n";
		t1.insert_node(i);
	    //t1.print_tree();
	    //std::cout << "\n--------------------------\n";
		//t1.level_order();
	}
    t1.display();

    // Test Cases 2 & 4:
    /*t1.insert_node(7);
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

    //t1.display();
    //t1.remove_node(97); // Case 1 of 5.
    //t1.remove_node(21); // Case 3 of 5.
    //t1.remove_node(12); // Case 2 of 5.

    // Case 4(lt exists) of 5.
    //t1.insert_node(8);
    //t1.display();
    //t1.remove_node(12);
    //t1.display();


    ////////////////////////////////////////////////////////////////////
    ////////////////// Testing delete cases ////////////////////////////
    ////////////////////////////////////////////////////////////////////
    /*
    // Case 1: LNB.
    t1.insert_node(10);
    t1.display();
    t1.remove_node(10);
    t1.display();

    t1.delete_tree();


    // Case 2: LYR.
    t1.insert_node(10);
    t1.insert_node(40);
    t1.insert_node(7);
    t1.insert_node(3);
    t1.insert_node(8);
    t1.insert_node(30);
    t1.insert_node(45);
    t1.insert_node(60);
    t1.insert_node(1);
    t1.insert_node(5);
    t1.insert_node(20);
    t1.insert_node(35);
    t1.insert_node(25);
    t1.display();
    t1.remove_node(25);
    t1.display();

    t1.delete_tree();

    // Case 3: LYB.
    t1.insert_node(10);
    t1.insert_node(40);
    t1.insert_node(7);
    t1.insert_node(3);
    t1.insert_node(8);
    t1.insert_node(30);
    t1.insert_node(45);
    t1.insert_node(60);
    t1.insert_node(1);
    t1.insert_node(5);
    t1.insert_node(20);
    t1.insert_node(35);
    t1.insert_node(25);
    t1.display();
    t1.remove_node(8);

    t1.delete_tree();

    // Case 4.1: 1CNB. Child is lt.
    t1.insert_node(10);
    t1.insert_node(7);
    t1.display();
    t1.remove_node(10);
    t1.display();

    t1.delete_tree();

    // Case 4.2: 1CNB. Child is gt.
    t1.insert_node(10);
    t1.insert_node(40);
    t1.display();
    t1.remove_node(10);
    t1.display();

    t1.delete_tree();

    // Case 5.1: 1CYR. Child is lt.
    // Couldn't figure out how to implement this case.
    //t1.display();
    //t1.remove_node(40);

    // Case 5.2: 1CYR. Child is gt.
    // Couldn't figure out how to implement this case.
    //t1.display();
    //t1.remove_node(40);

    // Case 6.1: 1CYB. Child is lt.
    t1.insert_node(10);
    t1.insert_node(40);
    t1.insert_node(7);
    t1.insert_node(3);
    t1.insert_node(8);
    t1.insert_node(30);
    t1.insert_node(45);
    t1.insert_node(43);
    t1.insert_node(1);
    t1.insert_node(5);
    t1.insert_node(20);
    t1.insert_node(35);
    t1.insert_node(25);
    t1.display();
    t1.remove_node(45);
    t1.display();

    t1.delete_tree();

    // Case 6.2: 1CYB. Child is gt.
    t1.insert_node(10);
    t1.insert_node(40);
    t1.insert_node(7);
    t1.insert_node(3);
    t1.insert_node(8);
    t1.insert_node(30);
    t1.insert_node(45);
    t1.insert_node(60);
    t1.insert_node(1);
    t1.insert_node(5);
    t1.insert_node(20);
    t1.insert_node(35);
    t1.insert_node(25);
    t1.display();
    t1.remove_node(45);
    t1.display();

    t1.delete_tree();


    std::cout << "***************************** Case 7 - 2CNB.\n";
    // Case 7: 2CNB.
    t1.insert_node(10);
    t1.insert_node(40);
    t1.insert_node(7);
    t1.display();
    t1.remove_node(10);
    t1.display();

    t1.delete_tree();


    std::cout << "***************************** Case 8 - 2CYR. Smallest from gt subtree.\n";
    // Case 8: 2CYR. // # of blacks different bug ! - FIXED by deciding which replacement strategy to use. But remember, for this kind of decision-making-for-replacement-strategy to work, you will need to create a separate object for other case tree since the flag for assigning levels is NOT independent of "same-object".
    // Use smallest from gt subtree.
    t1.insert_node(10);
    t1.insert_node(7);
    t1.insert_node(3);
    t1.insert_node(8);
    t1.insert_node(40);
    t1.insert_node(30);
    t1.insert_node(20);
    t1.insert_node(35); // This node makes the difference.
    t1.display();
    t1.remove_node(30);
    t1.display();

    t1.delete_tree();

    std::cout << "***************************** Case 8 - 2CYR. Biggest from lt subtree.\n";
    // Use biggest from lt subtree.
    t1.insert_node(10);
    t1.insert_node(7);
    t1.insert_node(3);
    t1.insert_node(8);
    t1.insert_node(40);
    t1.insert_node(30);
    t1.insert_node(20);
    t1.insert_node(21); // This node makes the difference.
    t1.display();
    t1.remove_node(30);
    t1.display();

    t1.delete_tree();

    std::cout << "***************************** Case 9 - 2CYB.\n";
    ////////////////////////////////
    // Case 9: 2CYB.
    ////////////////////////////////
    t1.insert_node(10);
    t1.insert_node(7);
    t1.insert_node(3);
    t1.insert_node(8);
    t1.insert_node(1);
    t1.insert_node(5);
    t1.insert_node(40);
    t1.insert_node(30);
    t1.insert_node(20);
    t1.insert_node(35);
    t1.display();
    t1.remove_node(3);
    t1.display();

    t1.delete_tree();


    std::cout << "***************************** Case 9 - 2CYB. Another case - replacement candidate is a black node.\n";
    ////////////////////////////////
    // Case 9: 2CYB. Another case - replacement candidate is a black node.
    ////////////////////////////////
    t1.insert_node(10);
    t1.insert_node(7);
    t1.insert_node(3);
    t1.insert_node(8);
    t1.insert_node(1);
    t1.insert_node(5);
    t1.insert_node(40);
    t1.insert_node(30);
    t1.insert_node(20);
    t1.insert_node(35);
    t1.insert_node(0);
    t1.insert_node(2);
    t1.insert_node(4);
    t1.insert_node(6);

    t1.insert_node(33);
    t1.insert_node(34);

    t1.display();
    t1.remove_node(30);
    t1.display();
    */
	return 0;
}
