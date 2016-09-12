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

    /*t1.insert_node(&t1,15);
	t1.insert_node(&t1,13);
	t1.insert_node(&t1,12);
	t1.insert_node(&t1,14);
	t1.insert_node(&t1,17);
	t1.insert_node(&t1,16);
    t1.insert_node(&t1,18);*/

    /*
    insert_node(tree1,15);
	insert_node(tree1,13);
	insert_node(tree1,12);
	insert_node(tree1,14);
	insert_node(tree1,17);
	insert_node(tree1,16);
    insert_node(tree1,18);
    */
    /*
    root = insert_node(root,15);
	root = insert_node(root,13);
	root = insert_node(root,12);
	root = insert_node(root,14);
	root = insert_node(root,17);
	root = insert_node(root,16);
    root = insert_node(root,18);
    */
	//insert_node(foo, 17);
	//insert_node(foo, 16);
    //insert_node(foo, 18);
	// Ask user to enter a number.
	//int number;
	//std::cout<<"Enter number be searched\n";
	//std::cin>>number;
	//If number is found, print "FOUND"
	//if(search_bst(root,number) == true)
    //    std::cout<<"Found\n";
	//else
    //    std::cout<<"Not Found\n";

    t1.print_bst();
    //delete_bst(root);
}
