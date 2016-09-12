/*

Sort a linked list bsaed on node value (considered as ID)

*/

#include <iostream>
#include <string.h>

#include "nri_linked_list.cpp"
#include "nri_merge_sort.cpp"
#include "nri_quick_sort_3.cpp"


int main()
{
	//Step 1: Create an array to store the node IDs.
	int arr[11];


	//Step 2: Create a linked list.
	//--------------------------------------------------------------------
	// Create a linked list with even and odd numbers
    nri_linked_list l1;

	arr[0] = l1.add_as_tail(17);
	arr[1] = l1.add_as_tail(23);
	arr[2] = l1.add_as_tail(-12);
	arr[3] = l1.add_as_head(6);
	arr[4] = l1.add_as_tail(0);
    arr[5] = l1.add_as_head(171);
	arr[6] = l1.add_as_tail(234);
	arr[7] = l1.add_as_tail(6);
	arr[8] = l1.add_as_tail(79);
	arr[9] = l1.add_as_tail(218);
    arr[10] = l1.add_as_tail(221);
	//--------------------------------------------------------------------


	//Step 3: Print the list just to confirm that it was created.
	//--------------------------------------------------------------------
	// Testing print_list
	std::cout << "\nPrinting the entire list...\n";
	l1.print_list();
	std::cout << "Done printing the entire list !\n";
	//--------------------------------------------------------------------


	//Step 4: Print the node IDs from the linked list (Don't bother about the order!).
	std::cout << "\n\nlet's print IDs of nodes:\n";
	for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
        std::cout << arr[i] << ",";

	//Step 5: Sort those node IDs using a suitable sorting algorithm.
	std::cout << "\n\nMerge Sorted !\n";
	merge_sort(arr, sizeof(arr)/sizeof(*arr));

	//std::cout << "\n\nQuick Sorted !\n";
	//quick_sort(arr, 0, (sizeof(arr)/sizeof(*arr)-1));

	//Step 6: Print the sorted IDs just to confirm that they are indeed sorted.
	std::cout << "\nlet's print the sorted IDs of nodes:\n";
	for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
        std::cout << arr[i] << ",";

	std::cout << "\n\n";

	//Step 7: Now that they are sorted, begin deleting and adding nodes according to the sorted array.
	for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
	{
		// Remove node ID based on iteration insert the each of the sorted IDs back as head in reverse.
		//l1.remove_node(arr[i]);
		//l1.add_as_head(arr[(sizeof(arr)/sizeof(*arr)-1) - i]);

		// BUG !! When more than 1 node ID is the same, then it will remove the one it finds first in the list !
		// Remove a node ID wherever it is in the list and then insert it back as head.
		l1.remove_node(arr[(sizeof(arr)/sizeof(*arr)-1) - i]);
		l1.add_as_head(arr[(sizeof(arr)/sizeof(*arr)-1) - i]);
	}

	//Step 8: Print the list just to confirm that it was sorted.
	//--------------------------------------------------------------------
	// Testing print_list
	std::cout << "\nPrinting the entire list...\n";
	l1.print_list();
	std::cout << "Done printing the entire list !\n";

	return 0;
}
