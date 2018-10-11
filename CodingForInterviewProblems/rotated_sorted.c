#include <stdio.h>

//sorted array has been rotated, find the minimum
//1,2,3,4,5,6,7 -> rotate at 2 -> 3,4,5,6,7,1,2
//1,2,3,4,5,6,7,8  -> rotate at 4 -> 5,6,7,8,1,2,3,4
//find the  part of the array where sequence is not sorted by binary search
int
binary_search(int *arr, int start, int end)
{
	int i, mid, old;
	mid = (start +end)/2;
	if (arr[mid+1] < arr[mid]) //mid point could be such that we have only increasing in the first half and also the 2nd half, so check this
		return arr[mid+1];
	old = arr[start];
	for (i=start+1; i<=mid; i++) {
		if (arr[i] < old) { 
			return arr[i];
		}
		old = arr[i];
	}
	return binary_search(arr, mid+1, end);
}

int
main()
{
	//int arr[] = {3,4,5,6,7,1,2};
	int arr[] = {5,6,7,8,1,2,3,4};
	printf("min %d\n", binary_search(arr, 0, sizeof(arr)/sizeof(arr[0])-1)); 	
	return 0;
}
