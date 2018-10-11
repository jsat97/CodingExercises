#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static int
compare(const void *i1, const void *i2)
{
  return ((*(int*)i1 > *(int*)i2)? 1: (*(int*)i1 < *(int*)i2)? -1: 0); 
}

int
main()
{
  int no_query_arr[500];
  int no_query_sort_arr[500];
	int i, no_queries;

	fscanf(stdin, "%d",&no_queries);  
  for (i=0; i<no_queries; i++) 
    fscanf(stdin, "%d",&no_query_arr[i]);  

	memcpy(no_query_sort_arr, no_query_arr, sizeof(int)*no_queries);
	qsort(no_query_sort_arr, no_queries, sizeof(int),compare);

  for (i=0; i<no_queries; i++) 
		printf("%d \n",no_query_sort_arr[i]);
	printf("\n");	
	
}


