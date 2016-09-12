/* NRI Red Black Tree (RBT) - Implemenation in C++
   v48


   Functions:
   1) void print_tree()
   2) void print_tree(struct node *temp, int tlev)
   3) struct node* insert_node(int id)
   4) struct node* insert_node(struct node* temp, int id)
   5) bool check_rules_assign_color(struct node *temp)
   6) void restructuring(struct node *K, struct node *P, struct node *G, struct node *S)
   7) void recoloring(struct node *P, struct node *G, struct node *S)
   8) bool check_rules_complete_tree()
   9) bool check_rules_complete_tree(struct node *temp)
   10) struct node* search_tree(int id)
   11) struct node* search_tree(struct node* root, int id)
   12) void delete_node(struct node *temp)
   13) void remove_node(int id)
   14) void double_black(struct node *k, struct node *c, struct node *ks)
   15) void delete_tree(struct node *temp)
   16) ~nri_tree()

NEW FEATURES/MODIFICATIONS:
- Implemented Black Deficiency cases !!!!!

- Made both flags, viz., were_levels_assigned and was_root_freed independent of that "same-object" issue ! :).

- There are two flags in this code:
bool were_levels_assigned = false;
and
bool was_root_freed = false;

Of these 2, was_root_freed flag is independent of the same-object issue. However, were_levels_assigned is NOT. This means that for levels to be assigned correctly, you will need to use a different class object.

- Reverted back to v35's print_tree_level_order(). Had modified print_tree_level_order() in v36 assuming there was a bug in that function. Turns out the bug was related to how the nodes were actually being deleted. AR: Check all other usage of delete()s !

- Fixed a bug when deleting entire tree. Remember, do not insert a node with id = 0 !

- Introduced display() which will call all STDOUT functions, namely, print_tree(), print_tree_level_order(), visualize_tree().

- Renamed level_order() to print_tree_level_order().

- Without executing assign_levels() function, the node levels by default will be initialized to -17.

- There are 3 functions that display the entire tree:
	- print_tree()
	- print_tree_level_order()
	- visualize_tree()

Without executing assign_levels() function, the node levels by default will be initialized to -17.
In all of these 3 functions, it is required/mandatory to check whether levels have been assigned to the nodes. Else, each of the node's level information will be -17 which is incorrect. print_tree() will incorrectly display node level information and print_tree_level_order() makes use of node's level while displaying and hence will display all nodes in a single level. However, visualize_tree() would still work, but then, the nodes will still have wrong level information at the end of the day. So long story short, before using any of the above STDOUT functions, assign_levels() has to be executed beforehand.

- Changed return type of check_rules_assign_color() from bool to void.

- Should be bug free now. So you can use this instead of v27 (which so far was considered most stable, although it has a lot of redundant code).

- Redefined check_rules_assign_color(). Removed a lot of redundant code in this function.
- Trying to remove redundant code. Please use v27 for so-far-100%-tested-working-code.

- Added preorder traversal.
- Added postorder traversal.

- Added inorder traversal.

- BUG ALERT ! Search for: "BUG ALERT 6 ! ". Bug alerts 6 & 7 are from same case, which is, case 4 of 4.
- BUG ALERT ! Search for: "BUG ALERT 7 ! ".

- BUG ALERT ! Search for: "BUG ALERT 4 ! ". Bug alerts 4 & 5 are from same case, which is, case 2 of 4.
- BUG ALERT ! Search for: "BUG ALERT 5 ! ".

- BUG ALERT ! Search for: "BUG ALERT 3 ! ".

- Declared shell color variables - reset, red, black - as global (is it really global ?) for that class.
Also, remember that - when you are declaring these variables as global (is it really global ?), the brackets used are curly {} and not the usual round () you would use when you are declaring them inside a function.

- Modified print_tree_level_order() to visualize tree in an ordered space.

- Removed redundant lines of code in print_tree() in the "if" case of root node, had redundant "else" case for red color. Redundancy here is the illogical "if" and "else" cases checking for color for root node since once the node is detected as root, then it has to be black in color.

- BUG ALERT ! Search for: "BUG ALERT 2 ! ".

- BUG ALERT ! Search for: "BUG ALERT 1 ! ".

- Revolutionizing visualization of tree.
	- Checked for BASH shell text-wrap limitations on the generated html file [NO ISSUES FOUND].

- Finalizing display of the entire tree:
	- Found whether a given node to be printed has a sibling or not (so that you need not print spaces).

- Removed unnecessary variable "int level" at the start of public: of class nri_tree.
- Now, root node starts from level 0, not level 1.

- Added Linux BASH shell colors to reflect red and black on Linux BASH shell.

- Commented out unwanted stuff, like vectors and its related function.

- Level-order printing of tree.

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

References
[1] http://pages.cs.wisc.edu/~paton/readings/Red-Black-Trees/

[2] http://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/

[3] https://www.topcoder.com/community/data-science/data-science-tutorials/an-introduction-to-binary-search-and-red-black-trees/

[4] Professor Sartaj Sahni, University of Florida, COP5536 – Advanced Data Structures lecture slides.

[5] http://www.cs.cmu.edu/~clo/www/CMU/DataStructures/Lessons/lesson4_2.htm

*/

#include <iostream>
#include <vector>
#include "nri_linked_list.cpp"
#include <queue>
#include <iomanip>
#include <cstring>

class nri_tree
{
private:
	// Definition of node for RB Tree
	// bool color = true (1) if red, false (0) if black.
	struct node
	{
	    node():color(true), id(-17), level(-17), parent(nullptr), lt(nullptr), gt(nullptr){}
		bool color; // 416 bytes to 520 bytes because of addition of bool color to the node.
		int id;
		int level; // Level in the tree. For example, level of root node is 0.
	    struct node* parent;
		struct node* lt;
		struct node* gt;
	};

	struct node *root = nullptr;

	const std::string reset {"\033[0m"};
	const std::string red {"\033[1;31m"};
	const std::string black {"\033[1;30m"};

	bool were_levels_assigned = false; // Manipulated by display() and delete_tree().
	bool was_root_freed = false; // Manipulated by assign_levels(), delete_tree() and ~nri_tree().

public:

	void display()
	{
		if (were_levels_assigned == false) // Remember: In bool data type, false = 0, true = 1.
		{
			assign_levels();
			were_levels_assigned = true;
		}
		print_tree();
		//print_tree_level_order();
		visualize_tree();
	}

	// Print the tree pre-order
	// Traverse the root, left sub-tree, right sub-tree
	void print_tree()
	{
		std::cout << "\n\n\n";
		std::cout << "------------------------------------------------\n";
		std::cout << "DISPLAY ENTIRE TREE AS A DETAILED LIST:\n";
		std::cout << "------------------------------------------------\n";

		print_tree(root);
	}

	// Any form of traversal would work. Whatever pleases your eyes. Pre-order at the moment.
	void print_tree(struct node *temp)
	{
	    if (temp != nullptr)
	    {
			show_details_of_node(temp);
			if (nullptr != temp->lt) print_tree(temp->lt);
			if (nullptr != temp->gt) print_tree(temp->gt);
		}
	}


	void show_details_of_node(struct node *temp)
	{
		if (temp == nullptr)
			std::cout << "There is no such node !\n";
		else // Node exists.
		{
			// Check color.
			if (temp->color == false)
				std::cout << black;
			else
				std::cout << red;

			// Check parent.
			if (temp->parent == nullptr)
				std::cout << "Node: " << temp->id << " \t|| Level: " << temp->level << " \t|| Parent: --";
			else
			{
				node *par = temp->parent;
				std::cout << "Node: " << temp->id << " \t|| Level: " << temp->level << " \t|| Parent: " << par->id;
			}

			// Check lt child.
			if (temp->lt == nullptr)
				std::cout << " \t|| L Child: --";
			else
			{
				node *l = temp->lt;
				std::cout << " \t|| L Child: " << l->id;
			}

			// Check gt child.
			if (temp->gt == nullptr)
				std::cout << " \t|| G Child: --.\n";
			else
			{
				node *g = temp->gt;
				std::cout << " \t|| G Child: " << g->id << ".\n";
			}
		}

		// Reset shell color.
		std::cout << reset;
	}


	void visualize_tree()
	{
		std::cout << "\n\n\n";
		std::cout << "------------------------------------------------\n";
		std::cout << "DISPLAY ENTIRE TREE AS A GRAPH/ACTUAL TREE:\n";
		std::cout << "------------------------------------------------\n";

		visualize_tree(root);
	}

	// Apparently this function uses post order traversal.
	void visualize_tree(node* p, int indent = 0)
	{
		if(p != nullptr)
		{
	        if(p->gt)
			{
	            visualize_tree(p->gt, indent + 4);
	        }
	        if (indent)
			{
	            std::cout << std::setw(indent) << ' ';
	        }
	        if (p->gt)
			{
				std::cout <<" /\n" << std::setw(indent) << ' ';
			}

			if (p == nullptr)
				std::cout << black << p->id << "\n ";
			else
				if (p->color == false)
					std::cout << black << p->id << "\n ";
				else
					std::cout << red << p->id << "\n ";

	        if(p->lt)
			{
	            std::cout << reset << std::setw(indent) << ' ' <<" \\\n";
	            visualize_tree(p->lt, indent + 4);
	        }
    	}
		std::cout << reset << "\n";
	}

	void print_tree_level_order()
	{
		std::cout << "\n\n\n";
		std::cout << "------------------------------------------------\n";
		std::cout << "DISPLAY ENTIRE TREE LEVEL-BY-LEVEL:\n";
		std::cout << "------------------------------------------------\n";

		print_tree_level_order(root);
	}


	// Function to print Nodes in a binary tree in Level order
	void print_tree_level_order(node *root)
	{
		std::cout << "------------------------------------------------>\n";
		std::cout << "LEVEL |" << "-----TREE-------------------------------->\n";
		std::cout << "------------------------------------------------>\n";
		std::cout << "   0  |";

		if(root == nullptr) return;

		std::queue<node*> Q;
		Q.push(root);

		node *previous = nullptr;
		node *current = nullptr;


		//while there is at least one discovered node
		while(!Q.empty())
		{
			previous = current;
			current = Q.front();
			struct node *currpar = current->parent;
			if(previous != nullptr)
			{
				if (current->level - previous->level > 0)
				{
					std::cout << reset << "\n\n";
					std::cout << reset << "   " << current->level << "  |";
				}
			}

			Q.pop(); // removing the element at front

			if (current->color == 1)
			{
				if (currpar != nullptr)
					std::cout << red << "(" << current->id << "[" << currpar->id << "]"  << "),";
				else
					std::cout << red << "(" << current->id << "[no parent]" << "),"; // IMPOSSIBLE !
			}
			else
			{
				if (currpar != nullptr)
					std::cout << black << "(" << current->id << "[" << currpar->id << "]" << "),";
				else
					std::cout << black << "(" << current->id << "[no parent]" << "),";
			}

			// Now, reset the shell color back to regular.
			std::cout << reset;

			if(current->lt != nullptr) Q.push(current->lt);
			if(current->gt != nullptr) Q.push(current->gt);
		}
	}

	void inorder()
	{
		inorder(root);
	}

	void inorder(node *ptr)
	{
	    if (root == nullptr)
	    {
	        std::cout << "inorder(): Tree is empty." << std::endl;
	        return;
	    }
	    if (ptr != nullptr)
	    {
	        inorder(ptr->lt);
	        std::cout << ptr->id <<", ";
	        inorder(ptr->gt);
	    }
	}

	void preorder()
	{
		preorder(root);
	}

	void preorder(node *ptr)
	{
	    if (root == nullptr)
	    {
	        std::cout << "preorder(): Tree is empty." << std::endl;
	        return;
	    }
	    if (ptr != nullptr)
	    {
	        std::cout << ptr->id << ", ";
	        preorder(ptr->lt);
	        preorder(ptr->gt);
	    }
	}

	void postorder()
	{
		postorder(root);
	}

	void postorder(node *ptr)
	{
	    if (root == nullptr)
	    {
	        std::cout << "postorder(): Tree is empty." << std::endl;
	        return;
	    }
	    if (ptr != nullptr)
	    {
	        postorder(ptr->lt);
	        postorder(ptr->gt);
	        std::cout << ptr->id << ", ";
	    }
	}

	void assign_levels()
	{
		assign_levels(root, -1);
		were_levels_assigned = true;
		was_root_freed = false;
	}

	// Levels have to be assigned via pre-order traversal.
	void assign_levels(struct node *temp, int tlev)
	{
		if (temp != nullptr)
	    {
			temp->level = ++tlev;
			if (nullptr != temp->lt) assign_levels(temp->lt, tlev);
			if (nullptr != temp->gt) assign_levels(temp->gt, tlev);
	    }
	}

	// To insert id in tree, returns address of root node
	struct node* insert_node(int id)
	{
		insert_node(root, id);
	}

	struct node* insert_node(struct node* temp, int id)
	{
		/*std::cout << "insert_node(): Inserting = " << id << "\n";
		if(temp != nullptr)
			std::cout << "insert_node(): temp passed to me now = " << temp->id << "\n";
		else
			std::cout << "insert_node(): temp passed to me now = nullptr\n";*/


		if(temp == nullptr) // then its the root.
	    { // empty tree
	        root = new (struct node);
			root->color = false;
	        root->id = id;
	        root->parent = nullptr;
	    	root->lt = root->gt = nullptr;
			return temp;
		}

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

				//foo->color = check_rules_assign_color(foo); // Send foo to check_rules_assign_color() IFF its parent is assigned.  // BUG ALERT 2 !
				check_rules_assign_color(foo); // Send foo to check_rules_assign_color() IFF
				//std::cout << "insert_node(): Assigned color: " << foo->color << " \tto node: " << foo->id << "\n";
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

				//foo->color = check_rules_assign_color(foo); // BUG ALERT 2 !
				check_rules_assign_color(foo); // Send foo to check_rules_assign_color() IFF
				//std::cout << "insert_node(): Assigned color: " << foo->color << " \tto node: " << foo->id << "\n";
				return foo;
			}
			else
				insert_node(temp->gt, id);
		}
		else // id already exists !
		{
			std::cout << "insert_node(): id already exists. NOT inserting !\n";
			return nullptr;
		}

		return temp;
	} // End of struct node* insert_node(struct node* temp, int id)

	void check_rules_assign_color(struct node *temp)
	{
		if (temp->parent != nullptr) // which means its NOT root.
		{
			struct node *par = temp->parent;

			// Remember: If parent is red, then grandparent HAS TO EXIST. Because if grandparent does not exist, then it means parent is root and root CANNOT be red anyway. So, in a red-black tree implementation, if parent is red, then grandparent has to exist, else your implementation is incorrect.
			if (par->color == true) // Problem arises only when parent's color is also red. Remember: By default all nodes are inserted as red.
			{
				struct node *grand_par = par->parent; // Grandparent will definitely exist.
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

				// If parent's sibling color = NULL or black.
				//if (par_sibling->color == false || par_sibling == nullptr) // This will cause segmentation fault. This is were language semantics is important. The if statement conditions are checked starting from the left-most condition and then going towards the right-most.

				// Remember: par_sibling could be nullptr. So, to avoid segmentation fault, first check if its' nullptr. Because if it is nullptr, then the if statement won't go to next condition since its logical OR operation, so if any1 is true then if statement doesn't need to care about other conditions. However, for logical AND, the issue is different.
				if (par_sibling == nullptr || par_sibling->color == false)
				{
					//std::cout << "check_rules_assign_color(): RESTRUCTURING required since parent's sibling color = NULL/black.\n";
					restructuring(temp, par, grand_par, par_sibling);

					// Remember: You are passing colors to top of tree, so check grand parent.
					//std::cout << "check_rules_assign_color(): Passing grangparent = " << grand_par->id << "\n";
					check_rules_assign_color(grand_par); // U MADE MISTAKE HERE NRI !
				}
				else if(par_sibling->color == true) // If parent's sibling's color is red.
				{
					std::cout << "check_rules_assign_color(): RECOLORING required.We are trying to assign color for node: " << temp->id << "\n";
					recoloring(par, grand_par, par_sibling);

					// Remember: You are passing colors to top of tree, so check grand parent.
					//std::cout << "check_rules_assign_color(): Passing grangparent = " << grand_par->id << "\n";
					check_rules_assign_color(grand_par); // U MADE MISTAKE HERE NRI !
				}
			}
		} // if (temp->parent != nullptr) // which means its NOT root.
	} // End of bool check_rules_assign_color(struct node *temp)

	void restructuring(struct node *K, struct node *P, struct node *G, struct node *S)
	{
		if (G->lt == P && P->lt == K)
		{
			std::cout << "restructuring(): Case 1 of 4 (LLb): (G->lt == P && P->lt == K)\n";

			// ---------------------
			// Starting from top, get all pointers fixed upto bottom. Basically, follow top-down approach here.
			// ---------------------
			// Step 1: Secure the original top node's parent (that is, grandparent's parent).
			// In this case, the (final) top node is P (that is, the final top node).
			if (G != root)
			{
				//std::cout << "G is not root.\n";
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
				//std::cout << "restructuring(): G is root.\n";
				P->parent = nullptr; // U NEED THIS NRI !
				root = P;
			}

			// Step 2: Point the children's parent to this newly formed top node from step 1.
			G->parent = P;
			K->parent = P;

			// Step 3: In this case, top node P only has gt child to be taken care of and it goes to G as G's lt child.
			struct node *pgt = P->gt;
			G->lt = pgt;
			if (pgt != nullptr) // BUG ALERT 3 ! Remember: pgt could also be a nullptr.
				pgt->parent = G;
			P->gt = G;

			// Step 4: In this case, the color of P (the final top node) and G (the original top node) will change.
			P->color = false; // false = black
			G->color = true;
		}
		else if (G->lt == P && P->gt == K)
		{
			std::cout << "restructuring(): Case 2 of 4 (LRb): (G->lt == P && P->gt == K)\n";

			// ---------------------
			// Starting from top, get all pointers fixed upto bottom. Basically, follow top-down approach here.
			// ---------------------
			// Step 1: Secure the original top node's parent (that is, grandparent's parent).
			// In this case, the (final) top node is K (that is, the final top node).
			if (G != root)
			{
				//std::cout << "G is not root.\n";
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
				//std::cout << "restructuring(): G is root.\n";
				K->parent = nullptr; // U NEED THIS NRI !
				root = K;
			}

			// Step 2: Point the children's parent to this newly formed top node from step 1.
			P->parent = K;
			G->parent = K;

			// Step 3: Secure the lt children of K. lt child of K goes to P as P's gt child.
			struct node *klt = K->lt;
			P->gt = klt;
			if (klt != nullptr) // BUG ALERT 4 ! Remember: klt could also be a nullptr.
				klt->parent = P;
			K->lt = P;

			// Step 3: Secure the gt children of K. gt child of K goes to G as G's lt child.
			struct node *kgt = K->gt;
			G->lt = kgt;
			if (kgt != nullptr) // BUG ALERT 5 ! Remember: kgt could also be a nullptr.
				kgt->parent = G;
			K->gt = G;

			// Step 4: Finally, check if color needs to be changed as part of the procedure/step (not to be confused with recoloring). In this case, the color of P and S remain the same. Color of G (the original top node) and K (the final top node) need to change.
			G->color = true; // true = red
			K->color = false;

			//print_tree();
		}
		else if (G->gt == P && P->gt == K)
		{
			std::cout << "restructuring(): Case 3 of 4 (RRb): (G->gt == P && P->gt == K)\n";

			// ---------------------
			// Starting from top, get all pointers fixed upto bottom. Basically, follow top-down approach here.
			// ---------------------
			// Step 1: Secure the original top node's parent (that is, grandparent's parent).
			// In this case, the (final) top node is P (that is, the final top node).
			if (G != root)
			{
				//std::cout << "G is not root.\n";
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
				//std::cout << "restructuring(): G is root.\n";
				P->parent = nullptr; // U NEED THIS NRI !
				root = P;
			}

			// Step 2: Point the children's parent to this newly formed top node from step 1.
			G->parent = P;
			K->parent = P;

			// Step 3: In this case, top node P only has lt child to be taken care of and it goes to G as G's gt child.
			struct node *plt = P->lt;
			G->gt = plt;
			if (plt != nullptr) // BUG ALERT 1 ! Remember: plt could also be a nullptr.
				plt->parent = G;
			P->lt = G;

			// Step 4: In this case, the color of P (the final top node) and G (the original top node) will change.
			P->color = false;
			G->color = true;
		}
		else if (G->gt == P && P->lt == K)
		{
			std::cout << "restructuring(): Case 4 of 4 (RLb): (G->gt == P && P->lt == K)\n";

			// ---------------------
			// Starting from top, get all pointers fixed upto bottom. Basically, follow top-down approach here.
			// ---------------------
			// Step 1: Secure the original top node's parent (that is, grandparent's parent).
			// In this case, the (final) top node is K (that is, the final top node).
			if (G != root)
			{
				//std::cout << "G is not root.\n";
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
				//std::cout << "restructuring(): G is root.\n";
				K->parent = nullptr; // U NEED THIS NRI !
				root = K;
			}

			// Step 2: Point the children's parent to this newly formed top node from step 1.
			P->parent = K;
			G->parent = K;

			// Step 3: Secure the lt child of K. lt child of K goes to G as G's gt child.
			struct node *klt = K->lt;
			G->gt = klt;
			if (klt != nullptr) // BUG ALERT 6 ! Remember: klt could also be a nullptr.
				klt->parent = G;
			K->lt = G;

			// Step 3: Secure the gt children of K. gt child of K goes to P as P's lt child.
			struct node *kgt = K->gt;
			P->lt = kgt;
			if (kgt != nullptr) // BUG ALERT 7 ! Remember: kgt could also be a nullptr.
				kgt->parent = P;
			K->gt = P;

			// Step 4: Finally, check if color needs to be changed as part of the procedure/step (not to be confused with recoloring). In this case, the color of P and S remain the same. Color of G (the original top node) and K (the final top node) need to change.
			G->color = true; // true = red
			K->color = false;
		}
	}

	void recoloring(struct node *P, struct node *G, struct node *S)
	{
		std::cout << "recoloring(): I was called ! \n";
		//std::cout << "Immediately inside recoloring (): G->id: " << G->id << "\n";
		//std::cout << "Immediately inside recoloring (): P->id: " << P->id << "\n";
		//std::cout << "Immediately inside recoloring (): S->id: " << S->id << "\n";
		if (G != root) // G should be red and other two should be black.
		{
			//std::cout << "recoloring(): G is black and other two red. Making G red and other two black.\n";
			G->color = true;
			P->color = false;
			S->color = false;
		}
		else if (G == root) // All three should be made black.
		{
			//std::cout << "recoloring(): G is root which is black. So making other two black.\n";
			//std::cout << "root->id: " << root->id << "\n";
			// G->color = false; // No need to do this, since its already supposed to be black.
			P->color = false;
			S->color = false;
		}
	} // End of recoloring()


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

	////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////// DELETE CASES //////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////


	void remove_node(int id)
	{
		struct node *temp = search_tree(id);

		//No node // WORKS ! VERIFIED !
		if (nullptr == temp)
		{
			std::cout << "remove_node(): No node.\n";
		}

		// Case 1: LNB.
		else if (temp->lt == nullptr && temp->gt == nullptr && temp->parent == nullptr && temp->color == 0)
		{
			std::cout << "remove_node(): Case 1: LNB.\n";
			temp->parent = nullptr; // Should be nullptr since its the root, but still double checking ! :)
			temp->lt = nullptr; // Should be nullptr since its a leaf, but still double checking ! :)
			temp->gt = nullptr; // Should be nullptr since its a leaf, but still double checking ! :)
			delete(temp);
			temp = nullptr;
			root = nullptr;
			return;
		}

		// Case 2: LYR.
		else if (temp->lt == nullptr && temp->gt == nullptr && temp->parent != nullptr && temp->color == 1)
		{
			std::cout << "remove_node(): Case 2: LYR.\n";

			if (temp->parent)
			{
				node *temppar = temp->parent;
				if (temppar->lt == temp)
					temppar->lt = nullptr;
				else if (temppar->gt == temp)
					temppar->gt = nullptr;
				temp->parent = nullptr;
			}

			if (temp->lt)
				temp->lt = nullptr;
			if (temp->gt)
				temp->gt = nullptr;

			delete (temp);
			temp = nullptr;


			return;
		}

		// Case 3: LYB.
		else if (temp->lt == nullptr && temp->gt == nullptr && temp->parent != nullptr && temp->color == 0)
		{
			std::cout << "remove_node(): Case 3: LYB.\n";
			std::cout << "remove_node(): Black Deficient.\n";

			node *temppar = temp->parent;
			node *tempsibling = nullptr;
			if (temppar->lt == temp)
				tempsibling = temppar->gt;
			else if (temppar->gt == temp)
				tempsibling = temppar->lt;

			black_deficient(tempsibling, temppar, temp);
			return;
		}

		// Case 4.1: 1CNB. Child is lt.
		else if (temp->lt != nullptr && temp->gt == nullptr && temp->parent == nullptr && temp->color == 0)
		{
			std::cout << "remove_node(): Case 4.1: 1CNB. Child is lt.\n";
			root = temp->lt;
			root->color = false;
			root->lt = nullptr;
			root->gt = nullptr;
			root->parent = nullptr;

			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;
			return;
		}

		// Case 4.2: 1CNB. Child is gt.
		else if (temp->lt == nullptr && temp->gt != nullptr && temp->parent == nullptr && temp->color == 0)
		{
			std::cout << "remove_node(): Case 4.2: 1CNB. Child is gt.\n";
			root = temp->gt;
			root->color = false;
			root->lt = nullptr;
			root->gt = nullptr;
			root->parent = nullptr;

			temp->parent = nullptr; // Should be nullptr since its the root, but still double checking ! :)
			temp->lt = nullptr; // Should be nullptr since its a leaf, but still double checking ! :)
			temp->gt = nullptr; // Should be nullptr since its a leaf, but still double checking ! :)
			delete(temp);
			temp = nullptr;
			return;
		}


		// Case 5.1: 1CYR. Child is lt.
		else if (temp->lt != nullptr && temp->gt == nullptr && temp->parent != nullptr && temp->color == 1)
		{
			std::cout << "remove_node(): Case 5.1: 1CYR. Child is lt.\n";
			node *temppar = temp->parent;
			node *tempchild = temp->lt;
			if (temppar->lt == temp)
			{
				temppar->lt = tempchild;
				tempchild->parent = temppar;
			}
			else if (temppar->gt == temp)
			{
				temppar->gt = tempchild;
				tempchild->parent = temppar;
			}
			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;
			return;
		}

		// Case 5.2: 1CYR. Child is gt.
		else if (temp->lt == nullptr && temp->gt != nullptr && temp->parent != nullptr && temp->color == 1)
		{
			std::cout << "remove_node(): Case 5.2: 1CYR. Child is gt.\n";
			node *temppar = temp->parent;
			node *tempchild = temp->gt;
			if (temppar->lt == temp)
			{
				temppar->lt = tempchild;
				tempchild->parent = temppar;
			}
			else if (temppar->gt == temp)
			{
				temppar->gt = tempchild;
				tempchild->parent = temppar;
			}
			temp->parent = nullptr;
			temp->lt = nullptr;
			temp->gt = nullptr;
			delete(temp);
			temp = nullptr;
			return;
		}

		// Case 6.1: 1CYB. Child is lt.
		else if (temp->lt != nullptr && temp->gt == nullptr && temp->parent != nullptr && temp->color == 0)
		{
			std::cout << "remove_node(): Case 6.1: 1CYB. Child is lt.\n";
			std::cout << "remove_node(): Black Deficient.\n";

			node *temppar = temp->parent;
			node *tempsibling = nullptr;
			if (temppar->lt == temp)
				tempsibling = temppar->gt;
			else if (temppar->gt == temp)
				tempsibling = temppar->lt;

			black_deficient(tempsibling, temppar, temp);
		}

		// Case 6.2: 1CYB. Child is gt.
		else if (temp->lt == nullptr && temp->gt != nullptr && temp->parent != nullptr && temp->color == 0)
		{
			std::cout << "remove_node(): Case 6.2: 1CYB. Child is gt.\n";
			std::cout << "remove_node(): Black Deficient.\n";

			node *temppar = temp->parent;
			node *tempsibling = nullptr;
			if (temppar->lt == temp)
				tempsibling = temppar->gt;
			else if (temppar->gt == temp)
				tempsibling = temppar->lt;

			black_deficient(tempsibling, temppar, temp);

		}

		// Case 7: 2C.
		else if (temp->lt != nullptr && temp->gt != nullptr)
		{
			std::cout << "remove_node(): Case 7: 2C.\n";

			// Take a backup of the node-to-be-deleted first.
			struct node *foo = nullptr;
			struct node *temppar = nullptr;

			foo = temp;

			////////////////////////////////////////////////////////////////////////
			// Decision on which replacement strategy to use out of the 2 available.
			////////////////////////////////////////////////////////////////////////
			// Step 1 of 3: Extract the smallest node from gt subtree.
			node *small = temp->gt;
			while (small->lt != nullptr) // Iteration
				small = small->lt;

			// Step 2 of 3: Extract the biggest node from lt subtree.
			node *big = temp->lt;
			while (big->gt != nullptr) // Iteration
				big = big->gt;

			std::cout << "remove_node(): Case 7: Big ID = " << big->id << "\n";
			std::cout << "remove_node(): Case 7: Big Level = " << big->level << "\n";
			std::cout << "remove_node(): Case 7: Small ID = " << small->id << "\n";
			std::cout << "remove_node(): Case 7: Small Level = " << small->level << "\n";

			// Step 3 of 3: Now the decision.
			if (big->level > small->level)
			{
				std::cout << "remove_node(): Case 7: Decided to go with biggest from lt subtree.\n";
				// Case: Biggest from lt subtree.
				temp = temp->lt;
				while (temp->gt != nullptr) // Iteration
					temp = temp->gt;
			}
			else
			{
				std::cout << "remove_node(): Case 7: Decided to go with smallest from gt subtree.\n";
				// Case: Smallest from gt subtree.
				temp = temp->gt;
				while (temp->lt != nullptr) // Iteration
					temp = temp->lt;
			}

			/*
			// Case: Biggest from lt subtree.
			temp = temp->lt;
			while (temp->gt != nullptr) // Iteration
				temp = temp->gt;
			*/

			/*
			// Case: Smallest from gt subtree.
			temp = temp->gt;
			while (temp->lt != nullptr) // Iteration
				temp = temp->lt;
			*/

			std::cout << "remove_node(): Case 7: Node to be replaced = " << foo->id << "\n";
			std::cout << "remove_node(): Case 7: Node to be replaced color = " << foo->color << "\n";
			std::cout << "remove_node(): Case 7: Replacement candidate node = " << temp->id << "\n";
			std::cout << "remove_node(): Case 7: Replacement candidate node color = " << temp->color << "\n";

			if (temp->color == true)
			{
				// Now, replace the to-be-deleted node.
				// First, make sure the to-be-replaced node's parent is no longer pointing to it.
				temppar = temp->parent;

				if (temppar->lt == temp)
					temppar->lt = nullptr;
				else if (temppar->gt == temp)
					temppar->gt = nullptr;

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

				// Make replaced node color as red.
				//foo->color = true;
			}
			else
				remove_node(temp->id);

			return;
		}
	}

	void black_deficient(node *s, node *p, node *k)
	{
		// I think totally 9 cases.
	}

	void delete_tree()
	{
		if (was_root_freed == false)
			was_root_freed = true;

		delete_tree(root);

		// Change this flag back to false, so you can re-use the class object.
		were_levels_assigned = false;
	}

	void delete_tree(struct node *temp)
	{
		if (temp != nullptr)
		{
			if (temp->lt != nullptr) delete_tree(temp->lt);
			if (temp->gt != nullptr) delete_tree(temp->gt);

			if (temp->parent)
			{
				node *temppar = temp->parent;
				if (temppar->lt == temp)
					temppar->lt = nullptr;
				else if (temppar->gt == temp)
					temppar->gt = nullptr;
				temp->parent = nullptr;
			}

			if (temp->lt)
				temp->lt = nullptr;
			if (temp->gt)
				temp->gt = nullptr;

			if (temp == root)
			{
				delete (temp);
				temp = nullptr;
				root = nullptr;
				//std::cout << "::::::::::::::::::::::::::LOLGIRI:::::::::::::::::::::::::::\n";
			}
			else
			{
				delete (temp);
				temp = nullptr;
				//std::cout << "::::::::::::::::::::::::::NON-ROOT:::::::::::::::::::::::::::\n";
			}
		}
	}

	~nri_tree()
	{
		//std::cout << "Destructor: was_root_freed = " << was_root_freed << "\n";
		//--------------------------------------------------------------------
        // Delete the entire tree (releasing the memory used ofcourse !)
        if (was_root_freed == false)
        {
            delete_tree();
        }
		else
		{
			std::cout << "\n~nri_tree(): NOTHING NEEDED TO BE FREE'D !";
		}
		//root = nullptr;
        std::cout << "\n||||||||||||||||||||\nDESTRUCTOR CALLED ! DELETED ENTIRE TREE !\n||||||||||||||||||||\n";
	}
};
