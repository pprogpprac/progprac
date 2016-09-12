/* NRI Red Black Tree (RBT) - Implemenation in C++
   v9


Functions:
1) print_tree()
2) insert_node()
3) search_tree()
4) remove_node()
5) delete_tree()

NEW FEATURES:
- Delete cases implemented !

- Restructuring for the rest of the 3 out of 4 cases done. Question is, do I need to implement recursion here?

- Restructuring completed case 2 of 4 !

- Modify inert_node function to assign the appropriate colors to root and leaf nodes.

- Just a little bit of modifications. No new features introduced in v3.

- Commented unwanted DEBUG print statements.

- Renamed delete_node() to remove_node().

- Delete function for node with two children implemented.

- Delete function for node with no children (leaf node) and node with only one child implemented.

- Checked for duplicate insertions.

WORKING REQUIREMENTS:
- print_tree() function has to be executed at the end of all initial inserts in order to set the levels of nodes.

BUGs:
- Mistake in a comment "(LET'S SAY I PICK THIS ONE IN THIS CODE !)" in remove_node(). You actually picked "2) Pick the largest node from left/less than subtree." but mentioned in the comment as having picked 1).

- Fixed code-not-entering-restructuring case.

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
	    node():color(true), id(-17), count(0), level(-17), parent(nullptr), lt(nullptr), gt(nullptr){}
		bool color; // 416 bytes to 520 bytes because of addition of bool color to the node.
		int id;
		int count;
		int level; // Level in the tree. For example, level of root node is 1, level of the root's children is 2.
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
					std::cout<< "Node: " << temp->id << " \t|| Color: BLACK" << " \t|| Level: " << tlev << " \t|| Parent node: NULL\n";
				}
				else
				{
					std::cout<< "Node: " << temp->id << " \t|| Color: RED" << " \t\t|| Level: " << tlev << " \t|| Parent node: NULL\n";
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
					std::cout<< "Node: " << temp->id << " \t|| Color: RED" << " \t\t|| Level: " << tlev << " \t|| Parent node: " << foo->id << "\n";
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

		//std::cout << "DEBUG: You are dealing with id = " << id << std::endl;
		//std::cout << "DEBUG: You are dealing with temp->id = " << temp->id << std::endl;
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
				foo->color = check_rules_assign_color(foo); // Send foo to check_rules_assign_color() IFF its parent is assigned.
				//std::cout << "DEBUG: Assigned color: " << foo->color << " \tto node: " << foo->id << "\n";
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
				foo->color = check_rules_assign_color(foo);
				//std::cout << ">>> DEBUG: Assigned color: " << foo->color << " \tto node: " << foo->id << "\n";
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
	} // End of struct node* insert_node(struct node* temp, int id)

	bool check_rules_assign_color(struct node *temp)
	{
		if (temp->parent == nullptr) // which means its root.
		{
			check_rules_complete_tree(root);
		}
		else
		{
			//std::cout<< "Node: " << par->id << " \t|| Color: " << par->color << "\n";
			struct node *par = temp->parent;
			//std::cout<< "Node: " << par->id << " \t|| Color: " << par->color << "\n";

			if (par->color == false) // false = black // If parent's color is black.
			{
				return true;
			}
			else // Parent's color is red.
			{
				struct node *grand_par = par->parent;
				struct node *par_sibling = nullptr;

				// Check the relationship (whether lt child or gt child) of the parent's sibling with grandparent.
				if (grand_par->lt == par)
				{
					par_sibling = grand_par->gt;
				}
				else if (grand_par->gt == par)
				{
					par_sibling = grand_par->lt;
				}

				/*std::cout << "{}grand_par->color: " << grand_par->color << "\n";
				std::cout << "{}par->color: " << par->color << "\n";
				std::cout << "{}par_sibling->color: " << par_sibling->color << "\n";*/
				// If parent's sibling color = NULL or black.
				if (par_sibling == nullptr || par_sibling->color == false)
				{
					std::cout << "=========================== If parent's sibling color = NULL or black. RESTRUCTURING required.================================\n";
					restructuring(temp, par, grand_par, par_sibling);
				}
				else if(par_sibling->color == true) // If parent's sibling's color is red.
				{
					std::cout << "Recoloring required.We are trying to assign color for node: " << temp->id << "\n";
					recoloring(par, grand_par, par_sibling);
					//std::cout << "grand_par->color: " << grand_par->color << "\n";
					//std::cout << "par->color: " << par->color << "\n";
					//std::cout << "par_sibling->color: " << par_sibling->color << "\n";
					std::cout << "Gotta check double reds !\n";

					// Remember: You are passing colors to top of tree, so check grand parent.
					if (check_rules_assign_color(grand_par) == true) // U MADE MISTAKE HERE NRI !
					{
						std::cout << "DOUBLE RED DETECTED !\n";
					}
					else
						std::cout << "DOUBLE RED NOT DETECTED !\n";

					return true;
				}
			}
		}
	} // End of bool check_rules_assign_color(struct node *temp)

	void restructuring(struct node *K, struct node *P, struct node *G, struct node *S)
	{
		if (G->lt == P && P->lt == K)
		{
			std::cout << "Case 1 of 4: (G->lt == P && P->lt == K)\n";

			// ---------------------
			// Starting from top, get all pointers fixed upto bottom. Basically, follow top-down approach here.
			// ---------------------
			// Step 1: Secure the original top node's parent (that is, grandparent's parent).
			// In this case, the (final) top node is P (that is, the final top node).
			if (G != root)
			{
				std::cout << "G is not root.\n";
				struct node *gpar = G->parent;
				if (gpar->lt == G)
				{
					gpar->lt = P;
				}
				else if(gpar->gt == G)
				{
					gpar->gt = P;
				}
				P->parent = G->parent;
			}
			else
			{
				std::cout << "G is root.\n";
				P->parent = nullptr; // U NEED THIS NRI !
				root = P;
			}

			// Step 2: Point the children's parent to this newly formed top node from step 1.
			G->parent = P;
			K->parent = P;

			// Step 3: In this case, top node P only has gt child to be taken care of and it goes to G as G's lt child.
			struct node *pgt = P->gt;
			G->lt = pgt;
			pgt->parent = G;
			P->gt = G;

			// Step 4: In this case, the color of P (the final top node) and G (the original top node) will change.
			P->color = false; // false = black
			G->color = true;
		}
		else if (G->lt == P && P->gt == K)
		{
			std::cout << "Case 2 of 4: (G->lt == P && P->gt == K)\n";

			// ---------------------
			// Starting from top, get all pointers fixed upto bottom. Basically, follow top-down approach here.
			// ---------------------
			// Step 1: Secure the original top node's parent (that is, grandparent's parent).
			// In this case, the (final) top node is K (that is, the final top node).
			if (G != root)
			{
				std::cout << "G is not root.\n";
				struct node *gpar = G->parent;
				if (gpar->lt == G)
				{
					gpar->lt = K;
				}
				else if(gpar->gt == G)
				{
					gpar->gt = K;
				}
				K->parent = G->parent;
			}
			else
			{
				std::cout << "G is root.\n";
				K->parent = nullptr; // U NEED THIS NRI !
				root = K;
			}

			// Step 2: Point the children's parent to this newly formed top node from step 1.
			P->parent = K;
			G->parent = K;

			// Step 3: Secure the lt children of K. lt child of K goes to P as P's gt child.
			struct node *klt = K->lt;
			P->gt = klt;
			klt->parent = P;
			K->lt = P;

			// Step 3: Secure the gt children of K. gt child of K goes to G as G's lt child.
			struct node *kgt = K->gt;
			G->lt = kgt;
			kgt->parent = G;
			K->gt = G;

			// Step 4: Finally, check if color needs to be changed as part of the procedure/step (not to be confused with recoloring). In this case, the color of P and S remain the same. Color of G (the original top node) and K (the final top node) need to change.
			G->color = true; // true = red
			K->color = false;

			//print_tree();
		}
		else if (G->gt == P && P->gt == K)
		{
			std::cout << "Case 3 of 4: (G->gt == P && P->gt == K)\n";

			// ---------------------
			// Starting from top, get all pointers fixed upto bottom. Basically, follow top-down approach here.
			// ---------------------
			// Step 1: Secure the original top node's parent (that is, grandparent's parent).
			// In this case, the (final) top node is P (that is, the final top node).
			if (G != root)
			{
				std::cout << "G is not root.\n";
				struct node *gpar = G->parent;
				if (gpar->lt == G)
				{
					gpar->lt = P;
				}
				else if(gpar->gt == G)
				{
					gpar->gt = P;
				}
				P->parent = G->parent;
			}
			else
			{
				std::cout << "G is root.\n";
				P->parent = nullptr; // U NEED THIS NRI !
				root = P;
			}

			// Step 2: Point the children's parent to this newly formed top node from step 1.
			G->parent = P;
			K->parent = P;

			// Step 3: In this case, top node P only has lt child to be taken care of and it goes to G as G's gt child.
			struct node *plt = P->lt;
			G->gt = plt;
			plt->parent = G;
			P->lt = G;

			// Step 4: In this case, the color of P (the final top node) and G (the original top node) will change.
			P->color = false;
			G->color = true;
		}
		else if (G->gt == P && P->lt == K)
		{
			std::cout << "Case 4 of 4: (G->gt == P && P->lt == K)\n";

			// ---------------------
			// Starting from top, get all pointers fixed upto bottom. Basically, follow top-down approach here.
			// ---------------------
			// Step 1: Secure the original top node's parent (that is, grandparent's parent).
			// In this case, the (final) top node is K (that is, the final top node).
			if (G != root)
			{
				std::cout << "G is not root.\n";
				struct node *gpar = G->parent;
				if (gpar->lt == G)
				{
					gpar->lt = K;
				}
				else if(gpar->gt == G)
				{
					gpar->gt = K;
				}
				K->parent = G->parent;
			}
			else
			{
				std::cout << "G is root.\n";
				K->parent = nullptr; // U NEED THIS NRI !
				root = K;
			}

			// Step 2: Point the children's parent to this newly formed top node from step 1.
			P->parent = K;
			G->parent = K;

			// Step 3: Secure the lt child of K. lt child of K goes to G as G's gt child.
			struct node *klt = K->lt;
			G->gt = klt;
			klt->parent = G;
			K->lt = G;

			// Step 3: Secure the gt children of K. gt child of K goes to P as P's lt child.
			struct node *kgt = K->gt;
			P->lt = kgt;
			kgt->parent = P;
			K->gt = P;

			// Step 4: Finally, check if color needs to be changed as part of the procedure/step (not to be confused with recoloring). In this case, the color of P and S remain the same. Color of G (the original top node) and K (the final top node) need to change.
			G->color = true; // true = red
			K->color = false;
		}
	}

	void recoloring(struct node *P, struct node *G, struct node *S)
	{
		std::cout << "Immediately inside recoloring (): G->id: " << G->id << "\n";
		std::cout << "Immediately inside recoloring (): P->id: " << P->id << "\n";
		std::cout << "Immediately inside recoloring (): S->id: " << S->id << "\n";
		if (G != root) // G should be red and other two should be black.
		{
			std::cout << "G is black and other two red. Making G red and other two black.\n";
			G->color = true;
			P->color = false;
			S->color = false;
		}
		else if (G == root) // All three should be made black.
		{
			std::cout << "G is root which is black. So making other two black.\n";
			//std::cout << "root->id: " << root->id << "\n";
			// G->color = false; // No need to do this, since its already supposed to be black.
			P->color = false;
			S->color = false;
		}
	}

	bool check_rules_complete_tree(struct node *temp)
	{
		//std::cout << "Node sent to check for double red = " << temp->id << "\n";
		//std::cout << "check double red () node = " << temp->id << " \t color = " << temp->color << "\n";
		if (temp->lt != nullptr)
		{
			struct node *ltchild = temp->lt;
			//std::cout << "check double red () lt = " << ltchild->id << " \t color = " << ltchild->color << "\n";
			if (ltchild->color == true && temp->color == true)
			{
				//std::cout << "DEBUG: ??????????? SHUD return true.\n";
				std::cout << "check_rules_complete_tree(): Node in TROUBLE for being red = " << ltchild->id << "\n";

				struct node *P = ltchild->parent;
				struct node *G = P->parent;
				struct node *S = nullptr;

				// Check the relationship (whether lt child or gt child) of the parent's sibling with grandparent.
				if (G->lt == P)
				{
					S = G->gt;
				}
				else if (G->gt == P)
				{
					S = G->lt;
				}

				std::cout << "check_rules_complete_tree(): Correctional recoloring required !\n";
				recoloring(P, G, S);
				//check_rules_assign_color(P);

				return true;
			}
			else
				check_rules_complete_tree(ltchild);
		}
		if (temp->gt != nullptr)
		{
			struct node *gtchild = temp->gt;
			if (gtchild->color == true && temp->color == true)
			{
				std::cout << "Node in TROUBLE for being red = " << gtchild->id << "\n";

				struct node *P = gtchild->parent;
				struct node *G = P->parent;
				struct node *S = nullptr;

				// Check the relationship (whether lt child or gt child) of the parent's sibling with grandparent.
				if (G->lt == P)
				{
					S = G->gt;
				}
				else if (G->gt == P)
				{
					S = G->lt;
				}

				std::cout << "Correctional recoloring required !\n";
				recoloring(P, G, S);
				//check_rules_assign_color(P);

				return true;
			}
			else
				check_rules_complete_tree(gtchild);
		}
		//return false; // U MADE MISTAKE HERE NRI !
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

//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------
	// Implement remove_node with 3 special cases - delete a leaf, delete node with one child, delete node with two children.
	void remove_node (int id)
	{
		struct node *k = search_tree(id);
		struct node *c1 = nullptr, *c2 = nullptr;
		struct node *kpar = nullptr;

		if (nullptr == k)
		{
			std::cout << "remove_node(): Node not found.\n";
		}
		else if (k->lt == nullptr && k->gt == nullptr)
		{
			kpar = k->parent;
			std::cout << "remove_node(): k is a leaf node. !\n";
			if (kpar->parent == nullptr)
			{
				root = kpar;
				root->color = false;
				return;
			}
			else if (k->color == 1)
				remove_node(0, k);
			else // Then its sure that k does have a parent who is not root node.
			{
				if (kpar->color == 0) // Both k and kpar are black.
				{
					std::cout << "remove_node(): k is a leaf node and its black. Therefore, DOUBLE BLACK !\n";
					if ()
					double_black(k);
				}
			}
		}
		else
		{
			//std::cout << "remove_node(): k is definitely NOT a leaf node. Let's now see how many children it has, 1 or 2:\n";
			// Check if remove node with two children OR NOT.
			if (nullptr != k->lt)
				c1 = k->lt;
			if (nullptr != k->gt)
				c2 = k->lt;

			if (c1 != nullptr && c2 != nullptr)
			{
				std::cout << "remove_node(): k has two children !\n";
				remove_node(-17, k);
			}
			else // OK, so now you know you are removing a node with one child.
			{
				std::cout << "remove_node(): k has only one child !\n";
				struct node *c = nullptr;

				// Find out which child it is, lt or gt.
				if (k->lt != nullptr)
					c = k->lt;
				else if(k->gt != nullptr)
					c = k->gt;

				if (k->color == 1 || c->color == 1)
					remove_node(0, k); // then pass black color.
				else
				{
					std::cout << "remove_node(): DOUBLE BLACK NODE ! \n";
					double_black(k);
				}
			}
		}
	} // End of void remove_node (int id)

	void double_black(struct node *temp)
	{
		std::cout << "double_black() called.\n";
	}

	struct node * remove_leaf_or_1(struct node *temp)
	{
		// --------------- *************************** -------------------------
		// --------------- *************************** -------------------------
		// --------------- *************************** -------------------------
		struct node *temps_parent = nullptr, *temps_only_child = nullptr;

		//Case 1 of 3: Delete a leaf node.
		if (temp->lt == nullptr && temp->gt == nullptr)
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

			return nullptr;
		}

		// Case 2 of 3: Delete a node with one child:
		// Check which child exists of the to-be-deleted node, lt or gt and then delete accordingly.

		else if (temp->lt == nullptr && temp->gt != nullptr)
		{
			// Link its parent's appropriate pointer (pointer as in whether lt or gt) to temp->lt.
			temps_parent = temp->parent;

			temps_only_child = temp->gt;

			// Determine whether the to-be-deleted node was an lt or a gt child of its parent.
			if(temps_parent->lt == temp)
			{
				temps_parent->lt = temp->gt; // THIS IS ALSO WHERE U WENT WRONG NRI !
				temps_only_child->parent = temps_parent->lt; // THIS IS WHERE U HAD GONE WRONG NRI !
			}

			else if(temps_parent->gt == temp)
			{
				temps_parent->gt = temp->gt; // THIS IS ALSO WHERE U WENT WRONG NRI !
				temps_only_child->parent = temps_parent->gt; // THIS IS WHERE U HAD GONE WRONG NRI !
			}

			// Then, delete the node.
			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;

			return temps_only_child;
		}

		else if (temp->lt != nullptr && temp->gt == nullptr)
		{
			// Link its parent's appropriate pointer (pointer as in whether lt or gt) to temp->lt.
			temps_parent = temp->parent;

			temps_only_child = temp->lt;

			if(temps_parent->lt == temp)
			{
				temps_parent->lt = temp->lt; // THIS IS ALSO WHERE U WENT WRONG NRI !
				temps_only_child->parent = temps_parent->lt; // THIS IS WHERE U HAD GONE WRONG NRI !
			}
			else if(temps_parent->gt == temp)
			{
				temps_parent->gt = temp->lt; // THIS IS ALSO WHERE U WENT WRONG NRI !
				temps_only_child->parent = temps_parent->gt; // THIS IS WHERE U HAD GONE WRONG NRI !
			}

			// Then, delete the node.
			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;

			return temps_only_child;
		}
		// --------------- *************************** -------------------------
		// --------------- *************************** -------------------------
		// --------------- *************************** -------------------------
	}

	void remove_node(int node_color, struct node *temp)
	{
		if (node_color == 1)
		{
			std::cout << "remove_node() ORIGINAL: Node to be colored is red.\n";
			std::cout << "remove_node() ORIGINAL: Node color = " << temp->color << "\n";
			//std::cout << "remove_node() ORIGINAL: Node to be colored is red.\n";
			bool col = 1; //Red

			temp = remove_leaf_or_1(temp);
			if (temp != nullptr)
			{
				temp->color = col;
			}
		}
		else if(node_color == 0)
		{
			std::cout << "remove_node() ORIGINAL: Node to be colored is black.\n";
			std::cout << "remove_node() ORIGINAL: Node color = " << temp->color << "\n";
			bool col = 0; //Black

			temp = remove_leaf_or_1(temp);
			if (temp != nullptr) // Has a child or else it would be a leaf node.
			{
				temp->color = col;
			}
		}
		else
		{
			std::cout << "remove_node() ORIGINAL: Node with two children set to be removed !\n";
			// Case 3 of 3: Delete a node with two children:
			struct node * foo = nullptr;
			struct node *temps_parent = nullptr, *temps_only_child = nullptr;

			foo = temp;

			temp = temp->lt;
			while (temp->gt != nullptr) // Iteration
				temp = temp->gt;

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
        std::cout << "\n||||||||||||||||||||\nDESTRUCTOR CALLED ! DELETED ENTIRE TREE !\n||||||||||||||||||||\n";
	}
};
