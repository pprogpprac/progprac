#include <iostream>
#include "nri_rbt.cpp"

/*
#include <fcntl.h>    // For O_RDWR
#include <unistd.h>   // For open(), creat()
#include <string>

#include <cstdio>
#include <cstdlib>

#include <fstream>
*/

int main(int argc, char **argv)
{
    /*std::FILE *infp    = fopen(argv[1], "r");
	std::FILE *instrfp = fopen(argv[2], "r");
    std::FILE *outfp   = fopen(argv[3], "a");

	if( infp == NULL )
    {
       std::cout << "infp didnt open\n";
    }
	if( instrfp == NULL )
    {
       std::cout << "instrfp didnt open\n";
    }
	if( outfp == NULL )
    {
       std::cout << "outfp didnt open\n";
    }

	std::cout << "argc = " <<  argc << "\n";

	for (int i = 0; i < argc; i++)
	{
		std::cout << argv[i] << std::endl;
	}

	std::cout << "inputDataFileName = " <<  argv[1] << "\n";
    std::cout << "instructionFileName = " << argv[2] << "\n";
    std::cout << "outputDataFilename = " << argv[3] << "\n";

	//fclose (infp);
	//fclose (instrfp);
    //fclose (outfp);

    //std::cout << "Files closed successfully!\n";
    */

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

	// Test Case 3: Fixed incremental input limit.
	int max_input = 200;
	for (int i = 0; i < max_input; i++)
	{
		t1.insert_node(i);
	    t1.print_tree();
	    std::cout << "\n--------------------------\n";
		t1.level_order();
	}
	t1.check_rules_complete_tree();
	t1.print_tree();
	std::cout << "\n--------------------------\n";








    // Testing removal of black leaudf node
    //t1.remove_node(35);
    //t1.print_tree();
    //std::cout << "\n--------------------------\n";

    // Testing removal of non-leaf red node with two children.
    //t1.remove_node(30);
    //t1.print_tree();
    //std::cout << "\n--------------------------\n";


	//t1.display_tree();
	//std::cout << "\n--------------------------\n";
	//t1.level_print();
	//t1.level_order();

	return 0;
}
