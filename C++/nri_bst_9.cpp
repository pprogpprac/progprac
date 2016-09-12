/* Binary search_bst Tree - Implemenation in C++
   Simple program to create a BST of integers and search an element in it
   v9

NEW FEATURES:
- Delete node function implemented.

- Checked for duplicate insertions.

*/

#include <iostream>

class nri_bst
{
private:
	//Definition of Node for Binary search tree
	struct node
	{
	    node():data(-17),parent(nullptr), lt(nullptr), gt(nullptr){}
		int data;
	    struct node* parent;
		struct node* lt;
		struct node* gt;
	};

	struct node *root = nullptr;

public:
	int level = 0;
	// Print the tree pre-order
	// Traverse the root, left sub-tree, right sub-tree
	void print_bst()
	{
		print_bst(root, level);
	}

	void print_bst(struct node *temp, int tlev)
	{
		//std::cout << "DEBUG: root->data = " << root->data << "\n";
	    if (temp != nullptr)
	    {
			++tlev;
			if (nullptr != temp->lt) print_bst(temp->lt, tlev);
			if (nullptr != temp->gt) print_bst(temp->gt, tlev);

			std::cout << "Level: " << tlev << " || Node: " << temp->data << "\n";
	    }
		//std::cout << "DEBUG: root->data = " << root->data << "\n";
	}


	// To insert data in BST, returns address of root node
	struct node* insert_node(int data)
	{
		insert_node(root, data);
	}

	struct node* insert_node(struct node* temp, int data)
	{
	    //std::cout <<"HERE insert\n";

		if(temp == nullptr) // then its the root.
	    { // empty tree
	        //std::cout <<"HERE insert temp nullptr\n";
	        root = new (struct node);
	        root->data = data;
	        root->parent = nullptr;
	    	root->lt = root->gt = nullptr;
	        //std::cout <<"Root inserted with data = " << root->data << "\n";
			return temp;
		}

		//std::cout << "You are dealing with data = " << data << std::endl;
		//std::cout << "You are dealing with temp->data = " << temp->data << std::endl;
		// if data to be inserted is lesser, insert in left subtree.
		if(data < temp->data)
	    {
	        //std::cout <<"HERE insert temp lt\n";
	        //ldata += 1;
			if (temp->lt == nullptr)
			{
		        //std::cout <<"insert_node func: temp lt: parent node = " << temp->data << "\n";
				struct node* foo = new (struct node);
				foo->data = data;
		        foo->parent = temp;
		    	foo->lt = foo->gt = nullptr;
				temp->lt = foo; // U FORGOT THIS NRI !
				return foo;
			}
			else
				insert_node(temp->lt, data);
		}
		// else if data is greater then insert in right subtree.
		else if (data > temp->data)
	    {
			//std::cout <<"HERE insert temp gt\n";
	        //ldata += 1;
			if (temp->gt == nullptr)
			{
		        //std::cout <<"insert_node func: temp gt: parent node = " << temp->data << "\n";
				struct node* foo = new (struct node);
				foo->data = data;
		        foo->parent = temp;
		    	foo->lt = foo->gt = nullptr;
				temp->gt = foo; // U FORGOT THIS NRI !
				return foo;
			}
			else
				insert_node(temp->gt, data);
		}
		else // data already exists !
		{
			std::cout << "Data already exists. NOT inserting !\n";
			return nullptr;
		}

		return temp;
	}

	struct node* search_bst(int data)
	{
		search_bst(root, data);
	}

	struct node* search_bst(struct node* root, int data)
	{
		if(root == nullptr)
	    {
			return nullptr;
		}
		else if(root->data == data)
	    {
			return root;
		}
		else if(data < root->data)
	    {
			return search_bst(root->lt,data);
		}
		else
	    {
			return search_bst(root->gt,data);
		}
	}

	// Implement delete_node with 3 special cases - delete a leaf, delete node with one child, delete node with two children.
	void delete_node(int id)
	{
		struct node *temp = search_bst(id);
		struct node *temps_parent = nullptr, *temps_only_child = nullptr;

		if (nullptr == temp)
		{
			std::cout << "Node not found.\n";
		}
		//Case 1 of 3: Delete a leaf node.
		else if (temp->lt == nullptr && temp->gt == nullptr)
		{
			std::cout << "DEBUG: both nullptr.\n";

			// Set its parent's appropriate pointer (pointer as in whether lt or gt) to nullptr.
			temps_parent = temp->parent;
			if(temps_parent->lt == temp)
				temps_parent->lt = nullptr;
			else if(temps_parent->gt == temp)
				temps_parent->gt = nullptr;

			temp->parent = nullptr;
			delete(temp);
			temp = nullptr;
		}


		/*
		Case 2 of 3: Delete a node with one child:

		If the node to be deleted is a left child of the parent, then we connect the left pointer of the parent (of the deleted node) to the single child. Otherwise if the node to be deleted is a right child of the parent, then we connect the right pointer of the parent (of the deleted node) to single child.
		*/

		// Check which child it is of the to-be-deleted node, lt or gt and then delete accordingly.

		else if (temp->lt == nullptr && temp->gt != nullptr)
		{
			std::cout << "DEBUG: To-be-deleted node's gt child is not null.\n";

			// Link its parent's appropriate pointer (pointer as in whether lt or gt) to temp->gt.
			temps_parent = temp->parent;

			std::cout << "DEBUG: temps_parent->data = " << temps_parent->data << "\n";
			if(temps_parent->lt == temp)
			{
				std::cout << "DEBUG: the node was joined as lt with its parent.\n";
				temp->gt = temps_parent->lt;
			}
			else if(temps_parent->gt == temp)
			{
				std::cout << "DEBUG: the node was joined as gt with its parent.\n";
				temp->gt = temps_parent->gt;
			}

			// Then, delete the node.
			temp->parent = nullptr;
			delete(temp);
			temp = nullptr;
		}

		else if (temp->lt != nullptr && temp->gt == nullptr)
		{
			std::cout << "DEBUG: To-be-deleted node's lt child is not null.\n";

			// Link its parent's appropriate pointer (pointer as in whether lt or gt) to temp->lt.
			temps_parent = temp->parent;			
			temps_only_child = temp->lt;

			std::cout << "DEBUG: temps_parent->data = " << temps_parent->data << "\n";
			if(temps_parent->lt == temp)
			{
				std::cout << "DEBUG: the node was joined as lt with its parent.\n";
				temp->lt = temps_parent->lt;
			}
			else if(temps_parent->gt == temp)
			{
				std::cout << "DEBUG: the node was joined as gt with its parent.\n";
				temps_only_child->parent = temps_parent->gt;
				//temps_parent->gt = temps_only_child->parent;
			}

			// Then, delete the node.
			temp->parent = nullptr;
			//temp->lt = nullptr;
			//temp->gt = nullptr;
			delete(temp);
			temp = nullptr;
		}
	}

	void delete_bst(struct node *temp)
	{
		if (temp)
		{
			//std::cout << "delete_bst func: node passed is " << (temp->data) << "\n";
			if (nullptr != temp->lt) delete_bst(temp->lt);
			if (nullptr != temp->gt) delete_bst(temp->gt);
			//if (nullptr != temp->parent) delete_bst(temp->parent);

			std::cout << "delete_bst func: DELETING node " << (temp->data) << "\n";
			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;
		}
	}

	~nri_bst()
	{
		//--------------------------------------------------------------------
        // Delete the entire tree (releasing the memory used ofcourse !)
        if (root)
        {
            delete_bst(root);
        }
        std::cout << "\n||||||||||||||||||||||||||||||\nDELETED ENTIRE TREE !\n||||||||||||||||||||||||||||||\n";
	}
};
