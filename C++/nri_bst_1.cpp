// Binary search_bst Tree - Implemenation in C++
// Simple program to create a BST of integers and search an element in it
#include <iostream>
#include <limits>

//Definition of Node for Binary search tree
struct bstnode
{
    bstnode():le(NULL), gt(NULL), data(0) {}
	int data;
	struct bstnode* le;
	struct bstnode* gt;
};

struct bstnode* root = NULL;  // Creating an empty tree

// Print the tree pre-order
// Traverse the root, left sub-tree, right sub-tree
void print_bst(struct bstnode *temp)
{
    if (temp)
    {
        std::cout << temp->data << "\n";
        print_bst(temp->le);
        print_bst(temp->gt);
    }
}

// Function to create a new Node in heap
struct bstnode* insert_new(int data)
{
	struct bstnode *temp  = new (struct bstnode);
	temp->data = data;
	temp->le = temp->gt = NULL;
	return temp;
}

/*
struct bstnode * insert_node(int data)
{
    if (root == NULL)
    { // empty tree
        std::cout << "temp was NULL\n";
		insert_root(data);
	}
    else if (data <= root->data)
    {
        struct bstnode * temp;
        temp = root->le;
        if (temp->le != NULL && temp->gt != NULL)
            (temp->le)->data = data;
    }
    else if (data > root->data)
    {
        root = root->gt;
        insert_node(data);
    }
    else if (data == root->data)
    {
        std::cout << data << " already exists !\n";
    }
}
*/

// To insert data in BST, returns address of root node
struct bstnode* insert_node(struct bstnode* root,int data)
{
	if(root == NULL)
    { // empty tree
		root = insert_new(data);
	}
	// if data to be inserted is lesser, insert in left subtree.
	else if(data <= root->data)
    {
		root->le = insert_node(root->le,data);
	}
	// else, insert in right subtree.
	else
    {
		root->gt = insert_node(root->gt,data);
	}
	return root;
}


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

int main()
{
	//struct bstnode* root = NULL;  // Creating an empty tree
	/*Code to test the logic*/
    /*
    insert_node(root,15);
	insert_node(root,10);
	insert_node(root,20);
	insert_node(root,25);
	insert_node(root,8);
	insert_node(root,12);
    */
    root = insert_node(root,15);
	root = insert_node(root,13);
	root = insert_node(root,12);
	root = insert_node(root,14);
	root = insert_node(root,17);
	root = insert_node(root,16);
    root = insert_node(root,18);
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

    print_bst(root);
    //delete_bst(root);
}
