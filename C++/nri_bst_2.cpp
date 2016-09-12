/* Binary search_bst Tree - Implemenation in C++
   Simple program to create a BST of integers and search an element in it
   v2

   New Features:
   - Added "level" data within each node.

*/

#include <iostream>

//Definition of Node for Binary search tree
struct bstnode
{
    bstnode():data(-17),level(-1),parent(NULL), le(NULL), gt(NULL){}
	int data;
    int level;
    struct bstnode* parent;
	struct bstnode* le;
	struct bstnode* gt;
};

struct bstnode *par = NULL;

// Print the tree pre-order
// Traverse the root, left sub-tree, right sub-tree
void print_bst(struct bstnode *temp)
{
    std::cout <<"HERE\n";
    if (temp != NULL)
    {
        std::cout <<"HERE1\n";
        std::cout << temp->data << "\t" << "parent->data: " << temp->parent->data << "\n";
        print_bst(temp->le);
        print_bst(temp->gt);
    }
}
/*
// Function to create a new Node in heap
struct bstnode* new_node(int data, int ldata, struct bstnode *par)
{
	struct bstnode *temp  = new (struct bstnode);
	temp->data = data;
    temp->level = ldata;
    temp->parent = par;
	temp->le = temp->gt = NULL;
	return temp; // return the parent pointer.
}

*/

// To insert data in BST, returns address of root node
struct bstnode* insert_node(struct bstnode* temp, int data)
{
    //std::cout <<"HERE insert\n";
    static int tree_level = 0;

	if(!temp)
    { // empty tree
        std::cout <<"HERE insert temp NULL\n";
        struct bstnode *temp  = new (struct bstnode);
        temp->data = data;
        temp->level = tree_level;
        temp->parent = par;
    	temp->le = temp->gt = NULL;
        std::cout <<"HERE insert temp NULL -> temp->data = " << temp->data << "\n";
        tree_level += 1;
	}
	// if data to be inserted is lesser, insert in left subtree.
	else if(data <= temp->data)
    {
        std::cout <<"HERE insert temp le\n";
        //ldata += 1;
        par = temp;
        std::cout <<"HERE insert temp le -> par->data = " << par->data << "\n";
		insert_node(temp->le, data);
	}
	// else, insert in right subtree.
	else
    {
        std::cout <<"HERE insert temp gt\n";
        //ldata += 1;
        par = temp;
        std::cout <<"HERE insert temp gt -> par->data = " << par->data << "\n";
		insert_node(temp->gt, data);
	}
	return temp;
}

/*
//To search an element in BST, returns true if element is found
bool search_bst(struct bstnode* root, int data)
{
	if(root == NULL)
    {
		return false;
	}
	else if(root->data == data)
    {
		return true;
	}
	else if(data <= root->data)
    {
		return search_bst(root->le,data);
	}
	else
    {
		return search_bst(root->gt,data);
	}
}

void delete_bst(struct bstnode *temp)
{
    while (temp != NULL)
    {
        if (!(temp->le))
            delete_bst(temp->le);
        else if (!temp->gt)
            delete_bst(temp->gt);
        else
        {
            delete(temp);
            temp = NULL;
        }
    }
}
*/

int main()
{
	struct bstnode* tree1 = NULL;  // Creating an empty tree

	/*Code to test the logic*/

    insert_node(tree1,15);
	insert_node(tree1,13);
	insert_node(tree1,12);
	insert_node(tree1,14);
	insert_node(tree1,17);
	insert_node(tree1,16);
    insert_node(tree1,18);

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

    print_bst(tree1);
    //delete_bst(root);
}
