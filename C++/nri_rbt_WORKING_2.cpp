/* NRI Red Black Tree (RBT) - Implemenation in C++
   v2

Functions:
1) print_tree()
2) insert_node()
3) search_tree()
4) remove_node()
5) delete_tree()

NEW FEATURES:
- Commented unwanted DEBUG print statements.

- Renamed delete_node() to remove_node().

- Delete function for node with two children implemented.

- Delete function for node with no children (leaf node) and node with only one child implemented.

- Checked for duplicate insertions.

BUG:

- Fixed delete node with only one child issue.

NOTES:

Source: http://algoviz.org/OpenDSA/Books/OpenDSA/html/BinaryTreeTraversal.html#

There are three ways of tree traversal:
1) Preorder : Parent -> Children
2) Postorder: Children -> Parent
3) Inorder	: Left/Less than Children -> Parent -> Right/Greater than Children. (Basically, ascending order).


1) We might wish to make sure that we visit any given node before we visit its children. This is called a preorder traversal.

2) We might wish to visit each node only after we visit its children (and their subtrees). For example, this would be necessary if we wish to return all nodes in the tree to free store. We would like to delete the children of a node before deleting the node itself. But to do that requires that the children's children be deleted first, and so on. This is called a postorder traversal.

3) An inorder traversal first visits the left child (including its entire subtree), then visits the node, and finally visits the right child (including its entire subtree). The Red Black Tree makes use of this traversal to print all nodes in "ascending order" of value.

*/

#include <iostream>

class nri_tree
{
private:
	//D efinition of node for RB Tree
	// bool color = true if red, false if black.
	struct node
	{
	    node():color(true), id(-17), level(-17), parent(nullptr), lt(nullptr), gt(nullptr){}
		bool color; // 416 bytes to 520 bytes because of addition of bool color to the node.
		int id;
		int level;
	    struct node* parent;
		struct node* lt;
		struct node* gt;
	};

	struct node *root = nullptr;

public:
	int level = 0;
	// Print the tree pre-order
	// Traverse the root, left sub-tree, right sub-tree
	void print_tree()
	{
		print_tree(root, level);
	}

	void print_tree(struct node *temp, int tlev)
	{
		//std::cout << "DEBUG: root->id = " << root->id << "\n";
	    if (temp != nullptr)
	    {
			++tlev;
			if (nullptr != temp->lt) print_tree(temp->lt, tlev);
			if (nullptr != temp->gt) print_tree(temp->gt, tlev);

			struct node* foo = temp->parent;
			temp->level = tlev;

			if (foo == nullptr)
			{
				if (temp->color == false)
				{
					std::cout<< "Node: " << temp->id << " \t|| Color: BLACK" << "\t|| Level: " << tlev << " \t|| Parent node: NULL\n";
				}
				else
				{
					std::cout<< "Node: " << temp->id << " \t|| Color: RED" << " \t|| Level: " << tlev << " \t|| Parent node: NULL\n";
				}
			}
			else
			{
				if (temp->color == false)
				{
					std::cout<< "Node: " << temp->id << " \t|| Color: BLACK" << " \t|| Level: " << tlev << " \t|| Parent node: " << foo->id << "\n";
				}
				else
				{
					std::cout<< "Node: " << temp->id << " \t|| Color: RED" << " \t|| Level: " << tlev << " \t|| Parent node: " << foo->id << "\n";
				}
			}
	    }
		//std::cout << "DEBUG: root->id = " << root->id << "\n";
	}


	// To insert id in tree, returns address of root node
	struct node* insert_node(int id)
	{
		insert_node(root, id);
	}

	struct node* insert_node(struct node* temp, int id)
	{
	    //std::cout <<"HERE insert\n";

		if(temp == nullptr) // then its the root.
	    { // empty tree
	        //std::cout <<"HERE insert temp nullptr\n";
	        root = new (struct node);
			root->color = false;
	        root->id = id;
	        root->parent = nullptr;
	    	root->lt = root->gt = nullptr;
	        //std::cout <<"Root inserted with id = " << root->id << "\n";
			return temp;
		}

		//std::cout << "You are dealing with id = " << id << std::endl;
		//std::cout << "You are dealing with temp->id = " << temp->id << std::endl;
		// if id to be inserted is lesser, insert in left subtree.
		if(id < temp->id)
	    {
			if (temp->lt == nullptr)
			{
		        //std::cout <<"insert_node func: temp lt: parent node = " << temp->id << "\n";
				struct node* foo = new (struct node);
				foo->id = id;
		        foo->parent = temp;
		    	foo->lt = foo->gt = nullptr;
				temp->lt = foo; // U FORGOT THIS NRI !
				return foo;
			}
			else
				insert_node(temp->lt, id);
		}
		// else if id is greater then insert in right subtree.
		else if (id > temp->id)
	    {
			if (temp->gt == nullptr)
			{
		        //std::cout <<"insert_node func: temp gt: parent node = " << temp->id << "\n";
				struct node* foo = new (struct node);
				foo->id = id;
		        foo->parent = temp;
		    	foo->lt = foo->gt = nullptr;
				temp->gt = foo; // U FORGOT THIS NRI !
				return foo;
			}
			else
				insert_node(temp->gt, id);
		}
		else // id already exists !
		{
			std::cout << "id already exists. NOT inserting !\n";
			return nullptr;
		}

		return temp;
	}

	struct node* search_tree(int id)
	{
		search_tree(root, id);
	}

	struct node* search_tree(struct node* root, int id)
	{
		if(root == nullptr)
	    {
			return nullptr;
		}
		else if(root->id == id)
	    {
			return root;
		}
		else if(id < root->id)
	    {
			return search_tree(root->lt,id);
		}
		else
	    {
			return search_tree(root->gt,id);
		}
	}

	// Implement remove_node with 3 special cases - delete a leaf, delete node with one child, delete node with two children.
	void remove_node(int id)
	{
		struct node *temp = search_tree(id);
		struct node *temps_parent = nullptr, *temps_only_child = nullptr;

		if (nullptr == temp)
		{
			std::cout << "Node not found.\n";
		}
		//Case 1 of 3: Delete a leaf node.
		else if (temp->lt == nullptr && temp->gt == nullptr)
		{
			//std::cout << "DEBUG: both nullptr.\n";

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

		// Check which child exists of the to-be-deleted node, lt or gt and then delete accordingly.

		else if (temp->lt == nullptr && temp->gt != nullptr)
		{
			//std::cout << "DEBUG: To-be-deleted node's gt child is not null.\n";

			// Link its parent's appropriate pointer (pointer as in whether lt or gt) to temp->lt.
			temps_parent = temp->parent;

			temps_only_child = temp->gt;
			//temps_only_child->level = temp->level;

			//std::cout << "DEBUG: temps_parent->id = " << temps_parent->id << "\n";
			//std::cout << "DEBUG: temps_only_child->id = " << temps_only_child->id << "\n";

			// Determine whether the to-be-deleted node was an lt or a gt child of its parent.
			if(temps_parent->lt == temp)
			{
				//std::cout << "DEBUG: the node was joined as lt with its parent.\n";

				/* Remember: U shud always assign pointer that already exists to a pointer that has
				not yet been assigned, that is,
				the correct method is:
				pointer-to-be-assigned = pointer-that-already-exists

				incorrect method is:
				pointer-that-already-exists = pointer-to-be-assigned
				*/

				temps_parent->lt = temp->gt; // THIS IS ALSO WHERE U WENT WRONG NRI !
				temps_only_child->parent = temps_parent->lt; // THIS IS WHERE U HAD GONE WRONG NRI !
			}

			else if(temps_parent->gt == temp)
			{
				//std::cout << "DEBUG: the node was joined as gt with its parent.\n";

				/* Remember: U shud always assign pointer that already exists to a pointer that has
				not yet been assigned, that is,
				the correct method is:
				pointer-to-be-assigned = pointer-that-already-exists

				incorrect method is:
				pointer-that-already-exists = pointer-to-be-assigned
				*/

				temps_parent->gt = temp->gt; // THIS IS ALSO WHERE U WENT WRONG NRI !
				temps_only_child->parent = temps_parent->gt; // THIS IS WHERE U HAD GONE WRONG NRI !
			}

			// Then, delete the node.
			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;
		}

		else if (temp->lt != nullptr && temp->gt == nullptr)
		{
			//std::cout << "DEBUG: To-be-deleted node's lt child is not null.\n";

			// Link its parent's appropriate pointer (pointer as in whether lt or gt) to temp->lt.
			temps_parent = temp->parent;

			temps_only_child = temp->lt;
			//temps_only_child->level = temp->level;

			//std::cout << "DEBUG: temps_parent->id = " << temps_parent->id << "\n";
			//std::cout << "DEBUG: temps_only_child->id = " << temps_only_child->id << "\n";

			if(temps_parent->lt == temp)
			{
				//std::cout << "DEBUG: the node was joined as lt with its parent.\n";

				/* Remember: U shud always assign pointer that already exists to a pointer that has
				not yet been assigned, that is,
				the correct method is:
				pointer-to-be-assigned = pointer-that-already-exists

				incorrect method is:
				pointer-that-already-exists = pointer-to-be-assigned
				*/

				temps_parent->lt = temp->lt; // THIS IS ALSO WHERE U WENT WRONG NRI !
				temps_only_child->parent = temps_parent->lt; // THIS IS WHERE U HAD GONE WRONG NRI !
			}
			else if(temps_parent->gt == temp)
			{
				//std::cout << "DEBUG: the node was joined as gt with its parent.\n";

				/* Remember: U shud always assign pointer that already exists to a pointer that has
				not yet been assigned, that is,
				the correct method is:
				pointer-to-be-assigned = pointer-that-already-exists

				incorrect method is:
				pointer-that-already-exists = pointer-to-be-assigned
				*/

				temps_parent->gt = temp->lt; // THIS IS ALSO WHERE U WENT WRONG NRI !
				temps_only_child->parent = temps_parent->gt; // THIS IS WHERE U HAD GONE WRONG NRI !
			}

			// Then, delete the node.
			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;
		}

		/*
		Case 3 of 3: Delete a node with two children:

		You will need to then find a replacement candidate for such a node. How do you find that?
		Pick one of the two ways:
		1) Pick the smallest node from right/greater than subtree. (LET'S SAY I PICK THIS ONE IN THIS CODE !)
		or
		2) Pick the largest node from left/less than subtree.

		If you wanted smallest from lt tree, then its easy, because you are trying to find the node with minimum value in a Red Black Tree. To do that, just traverse the node from root to left recursively until left is NULL. The node whose left is NULL is the node with minimum value.

		However, if you want the largest from lt subtree, then?
		My algorithm:
		From root, traverse lt tree and immediately after passing the root node, traverse only on the gt recursively until gt node is NULL.


		*/
		else if (temp->lt != nullptr && temp->gt != nullptr)
		{
			// Take a backup of the node-to-be-deleted first.
			struct node * foo = nullptr;

			foo = temp;

			temp = temp->lt;
			while (temp->gt != nullptr)
				temp = temp->gt;

			//std::cout << "Node to be replaced = " << foo->id << "\n";
			//std::cout << "Replacement candidate node = " << temp->id << "\n";

			// Now, replace the to-be-deleted node.

			// First, make sure the to-be-replaced node's parent is no longer pointing to it.
			temps_parent = temp->parent;

			if (temps_parent->lt == temp)
				temps_parent->lt = nullptr;
			else if (temps_parent->gt == temp)
				temps_parent->gt = nullptr;

			// Second, replace foo. Note that other data remains the same, like the color of the node.
			foo->id = temp->id;
			temp->lt = foo->lt;
			temp->gt = foo->gt;
			temp->parent = foo->parent;

			// Finally, delete foo.
			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;
		}

	} // End of void remove_node(int id)

	void delete_tree(struct node *temp)
	{
		if (temp)
		{
			//std::cout << "delete_tree func: node passed is " << (temp->id) << "\n";
			if (nullptr != temp->lt) delete_tree(temp->lt);
			if (nullptr != temp->gt) delete_tree(temp->gt);
			//if (nullptr != temp->parent) delete_tree(temp->parent);

			//std::cout << "delete_tree func: DELETING node " << (temp->id) << "\n";
			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;
		}
	}

	~nri_tree()
	{
		//--------------------------------------------------------------------
        // Delete the entire tree (releasing the memory used ofcourse !)
        if (root)
        {
            delete_tree(root);
        }
        std::cout << "\n||||||||||||||||||||||||||||||\nDELETED ENTIRE TREE !\n||||||||||||||||||||||||||||||\n";
	}
};
