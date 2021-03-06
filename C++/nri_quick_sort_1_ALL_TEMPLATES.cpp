/* Quick Sort

NEW Features:
- Made Swap generic using the C++ concept of "templates" !

Features:


Bugs:
-

*/

#include <iostream>
#include <vector>


template <typename tfoo>
void swap(tfoo *a, tfoo *b) // Don't use XOR because there might be cases where it won't work & is also slow sometimes
{
    tfoo temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

template <typename tfoo1, typename tfoo2, typename tfoo3>
tfoo2 partition(tfoo1 *arr, tfoo2 start, tfoo3 end)
{
    tfoo2 pivot = arr[end]; // define what pivot means NRI !
    tfoo2 partition_index = start; // set partition index as start initially
    for (int i = start; i < end; i++)
    {
        if (arr[i] <= pivot)
        {
            swap(&arr[i], &arr[partition_index]); // swap if element is lesser than pivot
            partition_index++;
        }
    }
    swap(&arr[partition_index], &arr[end]); // swap pivot with element at partition index
    return partition_index;
}

template <typename tfoo1, typename tfoo2, typename tfoo3>
void quick_sort (tfoo1 *arr, tfoo2 start, tfoo3 end)
{
    if (start < end)
    {
        tfoo2 partition_index = partition(arr, start, end); // calling partition
        quick_sort(arr, start, partition_index - 1);
        quick_sort(arr, partition_index + 1, end);
    }
}

int main()
{
    int arr[] = {21,17,23,-3,0,8,10,4,12,6,-2};
    quick_sort(arr, 0, (sizeof(arr)/sizeof(int)-1));
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
        std::cout << arr[i] << ",";
    return 0;
}
