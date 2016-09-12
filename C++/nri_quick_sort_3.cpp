/* Quick Sort

NEW Features:
- Made Swap generic using the C++ concept of "templates" !
- Generic for any data type array (including int, float, double)

Bugs:
- sizeof(arr)/sizeof(int) for all data types was the bug.
In order to make it generic to all data types, changed
sizeof(arr)/sizeof(int)
to
sizeof(arr)/sizeof(*arr)

- Unnecessary include of <vector> header file.

- partition() function was returning tfoo type instead of int.

*/

#include <iostream>
//#include <algorithm> // We are not using random yet


template <typename tfoo>
void swap(tfoo *a, tfoo *b) // Don't use XOR because there might be cases where it won't work & is also slow sometimes
{
    tfoo temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

template <typename tfoo>
int partition(tfoo *arr, int start, int end)
{
    //randomize value
    //srand(time(NULL));
    //tfoo pivot = arr[rand() % (sizeof(arr)/sizeof(*arr))];
    tfoo pivot = arr[end]; // define what pivot means NRI !
    int partition_index = start; // set partition index as start initially
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

template <typename tfoo>
void quick_sort (tfoo *arr, int start, int end)
{
    if (start < end)
    {
        int partition_index = partition(arr, start, end); // calling partition
        quick_sort(arr, start, partition_index - 1);
        quick_sort(arr, partition_index + 1, end);
    }
}

/*
int main()
{
    double arr[] = {21.3,17,23,-3.01, -3.001, -3.13, 0,8,10,4,12,6,-2.5};
    quick_sort(arr, 0, (sizeof(arr)/sizeof(*arr)-1));
    for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
        std::cout << arr[i] << ",";
    return 0;
}
*/
