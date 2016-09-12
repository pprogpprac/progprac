/* Merge Sort

NEW Features:


Bugs:


*/
#include <iostream>

// Function to Merge Arrays L and R into A.
// lefCount = number of elements in L
// rightCount = number of elements in R.

template <typename tfoo>
void merge(tfoo *A, tfoo *L, int leftCount, tfoo *R, int rightCount)
{
	int i,j,k;

	// i - to mark the index of left aubarray (L)
	// j - to mark the index of right sub-raay (R)
	// k - to mark the index of merged subarray (A)
	i = 0; j = 0; k =0;

	while(i<leftCount && j< rightCount)
	{
		if(L[i]  < R[j]) A[k++] = L[i++];
		else A[k++] = R[j++];
	}
	while(i < leftCount) A[k++] = L[i++];
	while(j < rightCount) A[k++] = R[j++];
}

template <typename tfoo>
void merge_sort(tfoo *arr, int asize)
{
	if(asize < 2)
		return;
	int mid = asize/2;
	tfoo left[mid];
	tfoo right[asize - mid];
	for (int i = 0; i < mid; i++)
		left[i] = arr[i];
	for(int i = mid; i < asize; i++)
		right[i-mid] = arr[i];

	merge_sort (left, sizeof(left)/sizeof(*left));
	merge_sort (right, sizeof(right)/sizeof(*right));
	merge(arr, left, sizeof(left)/sizeof(*left), right, sizeof(right)/sizeof(*right));
}

/*
int main()
{
	double arr[] = {21.3,17,23,-3.01, -3.001, -3.13, 0,8,10,4,12,6,-2.5};
	//double arr[] = {21.3,17,23,-3.01, -3.001, -3.13, 0,8,8,4,12,6,-2.5};
	//int arr[] = {21,17,23,-3, -3, 13, 0,8,10,4,12,6,-2};
    merge_sort(arr, sizeof(arr)/sizeof(*arr));
	std::cout << "\n\n ||||||||| FINALLY |||||||||\n";
    for (int i = 0; i < sizeof(arr)/sizeof(*arr); i++)
        std::cout << arr[i] << ",";
    return 0;
}
*/
