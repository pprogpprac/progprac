/* Binary Search Tree v1

New Features:
Features:
Bugs:
List of functions:

*/

#include <iostream>

class nri_bst
{
private:
	struct bstnode
    {
    	int id;
        bstnode *le; // le = less than or equal to.
    	bstnode *gt; // gt = greater than.
    };

public:
	// Function to create a new Node in heap
	bstnode* create_bst(int data)
	{
		bstnode* newNode = new (struct bstnode);
		newNode->id = data;
		newNode->le = newNode->gt = NULL;
		return newNode;
	}

	// To insert data in BST, returns address of root node
	bstnode* insert_node(bstnode* root,int data)
	{
		if(root == NULL)  // empty tree
			root = create_bst(data);

		// if data to be inserted is lesser, insert in le subtree.
		else if(data <= root->id)
			root->le = Insert(root->le,data);

		// else, insert in rt subtree.
		else
			root->rt = Insert(root->rt,data);

		return root;
	}
	//To search an element in BST, returns true if element is found
	bool search_bst(bstnode* root,int data)
	{
		if(root == NULL)
			return false;

		else if(root->id == data)
			return true;

		else if(data <= root->id)
			return Search(root->le,data);

		else
			return Search(root->rt,data);

	}
};
