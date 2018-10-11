#include <stdio.h>

#define SWAP(x,y)	{\
	int tmp;	\
	tmp = x;	\
	x = y;	\
	y = tmp;	\
}
void
sort(int *arr, int *index_arr, int n)
{
	int i, j;
	for (i=0; i<n; i++) {
		for (j=i+1; j<n; j++) {
			if (arr[i] > arr[j]) { 	
				SWAP(arr[i], arr[j])
				SWAP(index_arr[i], index_arr[j])
			}
		}
	}
}

int
main()
{
	int i, n;
	int arr[10], ind_arr[10];

	printf("no of values ");
	scanf("%d", &n);
	printf("enter %d integers\n", n);
	for (i=0; i<n; i++) {
		scanf("%d", &arr[i]);
		ind_arr[i] =i;	
	}
	sort(arr, ind_arr, n);
	for (i=0; i<n; i++)
		printf("%d %d %d \n",i, arr[i], ind_arr[i]);

}
