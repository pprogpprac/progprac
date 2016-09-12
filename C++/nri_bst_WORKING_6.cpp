/* Binary search_bst Tree - Implemenation in C++
   Simple program to create a BST of integers and search an element in it
   v3

   New Features:
   - Added "level" data within each node.

*/

#include <iostream>

class nri_bst
{
private:
	//Definition of Node for Binary search tree
	struct node
	{
	    node():data(-17),level(-17),parent(nullptr), lt(nullptr), gt(nullptr){}
		int data;
	    int level;
	    struct node* parent;
		struct node* lt;
		struct node* gt;
	};

	struct node *root = nullptr;

public:
	// Print the tree pre-order
	// Traverse the root, left sub-tree, right sub-tree
	void print_bst()
	{
		print_bst(root);
	}

	void print_bst(struct node *temp)
	{
	    //std::cout <<"HERE\n";
	    if (temp != nullptr)
	    {
	        //std::cout <<"HERE1\n";
	        std::cout << "print_bst func: data = " << temp->data << "\n";
	        print_bst(temp->lt);
	        print_bst(temp->gt);
	    }
	}

	// To insert data in BST, returns address of root node
	struct node* insert_node(int data)
	{
		insert_node(root, data);
	}

	struct node* insert_node(struct node* temp, int data)
	{
	    //std::cout <<"HERE insert\n";
	    static int tree_level = 0;

		if(temp == nullptr) // then its the root.
	    { // empty tree
	        //std::cout <<"HERE insert temp nullptr\n";
	        root = new (struct node);
	        root->data = data;
	        root->level = tree_level;
	        root->parent = nullptr;
	    	root->lt = root->gt = nullptr;
	        //std::cout <<"Root inserted with data = " << root->data << "\n";
	        tree_level += 1;
			return temp;
		}

		std::cout << "You are dealing with data = " << data << std::endl;
		std::cout << "You are dealing with temp->data = " << temp->data << std::endl;
		// if data to be inserted is lesser, insert in left subtree.
		if(data < temp->data)
	    {
	        //std::cout <<"HERE insert temp lt\n";
	        //ldata += 1;
			if (temp->lt == nullptr)
			{
		        std::cout <<"insert_node func: temp lt: parent node = " << temp->data << "\n";
				struct node* foo = new (struct node);
				foo->data = data;
		        foo->level = tree_level;
		        foo->parent = temp;
		    	foo->lt = foo->gt = nullptr;
				tree_level += 1;
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
		        std::cout <<"insert_node func: temp gt: parent node = " << temp->data << "\n";
				struct node* foo = new (struct node);
				foo->data = data;
		        foo->level = tree_level;
		        foo->parent = temp;
		    	foo->lt = foo->gt = nullptr;
				tree_level += 1;
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

	/*
	//To search an element in BST, returns true if element is found
	bool search_bst(struct node* root, int data)
	{
		if(root == nullptr)
	    {
			return false;
		}
		else if(root->data == data)
	    {
			return true;
		}
		else if(data <= root->data)
	    {
			return search_bst(root->lt,data);
		}
		else
	    {
			return search_bst(root->gt,data);
		}
	}

	void delete_bst(struct node *temp)
	{
	    while (temp != nullptr)
	    {
	        if (!(temp->lt))
	            delete_bst(temp->lt);
	        else if (!temp->gt)
	            delete_bst(temp->gt);
	        else
	        {
	            delete(temp);
	            temp = nullptr;
	        }
	    }
	}
	*/

	/*
	void delete_bst(struct node *temp)
	{
		std::cout << "delete_bst func: Deleting " << temp->data << "\n";
		if (temp == nullptr) // there is no node.
			return;

		else if (temp->lt == nullptr && temp->gt == nullptr) // node is root and has no children.
		{
			std::cout << "delete_bst func: elseif(temp->lt == nullptr && temp->gt == nullptr): Deleting leafnode " << temp->data << "\n";
			//struct node* foo = temp->parent;
			delete(temp);
			temp = nullptr;

			//temp = foo;
			//delete(foo);
			//foo = nullptr;
		}
		else // node has children.
		{
			if (temp->lt == nullptr && temp->gt != nullptr)
			{
				std::cout << "delete_bst func: else // node has children.: temp->gt is NOT nullptr !\n";
				delete_bst(temp->gt);
			}
			if (temp->lt != nullptr && temp->gt == nullptr)
			{
				std::cout << "delete_bst func: else // node has children.: temp->lt is NOT nullptr !\n";
				delete_bst(temp->lt);
			}
			if (temp->lt != nullptr && temp->gt != nullptr)
			{
				std::cout << "delete_bst func: else // node has children.: temp->lt and temp->gt is NOT nullptr !\n";
				delete_bst(temp->lt);
				delete_bst(temp->gt);
			}
		}
	}


	void delete_bst(struct node *temp)
	{
		std::cout << "delete_bst func: Deleting " << temp->data << "\n";
		if (!temp) // there is no node.
			return;
		else
		{
			if ( !(temp->lt) && !(temp->gt) ) // Leaf node (no children).
			{
				std::cout << "Deleting leafnode " << temp->data << "\n";
				//struct node* foo = temp->parent;
				delete(temp);
				temp = nullptr;

				//temp = foo;
				//delete(foo);
				//foo = nullptr;
			}
			else // node has a child or children.
			{
				if ( (temp->lt) && (temp->gt) )
				{
					std::cout << "node " << temp->data << " has both children !\n";
					delete_bst(temp->lt);
					delete_bst(temp->gt);
				}
				else if (!(temp->gt))
				{
					std::cout << "node " << temp->data << " has only lt child !\n";
					delete_bst(temp->lt);
				}
				else if (!(temp->lt))
				{
					std::cout << "node " << temp->data << " has only gt child !\n";
					delete_bst(temp->gt);
				}
			}
		}
	}
	*/

	/*
	bool delete_bst(struct node *temp)
	{
		std::cout << "delete_bst func: node passed is " << temp->data << "\n";
		if (nullptr == temp) // there is no node.
		{
			std::cout << "There is no node !!!!!!!!!!!!!!!!!!!!!!!!! \n";
			return false;
		}
		else
		{
			if ( (nullptr == temp->lt) && (nullptr == temp->gt) ) // Leaf node (no children).
			{
				std::cout << ">>>>>>>>>>>>>>>>>>>>>>> Deleting leafnode " << temp->data << "\n";
				temp->parent = nullptr;
				temp->lt = nullptr;
				temp->gt = nullptr;
				delete(temp);
				//memset(&temp, 0, sizeof(temp)); // = nullptr;
			}
			else // node has a child or children.
			{
				if(temp->lt)
				{
					std::cout << "node " << temp->data << " has lt child !\n";
					delete_bst(temp->lt);
				}

				if(temp->gt)
				{
					std::cout << "node " << temp->data << " has gt child !\n";
					delete_bst(temp->gt);
				}
			}
		}
	}
	*/

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


int main()
{
	struct bhosad
	{
	    bhosad():data(-17),level(-17),parent(nullptr), lt(nullptr), gt(nullptr){}
		int data;
	    int level;
	    struct bhosad* parent;
		struct bhosad* lt;
		struct bhosad* gt;
	}*b1;

	std::cout << "sizeof(b1->parent) == " << sizeof(b1->parent) << std::endl;


	nri_bst t1;  // Creating an empty tree

	/*Code to test the logic*/

	t1.insert_node(15); // should automatically become root.
	t1.insert_node(13);
	t1.insert_node(14);
	t1.insert_node(12);
	t1.insert_node(17);
	t1.insert_node(16);
    t1.insert_node(18);

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
