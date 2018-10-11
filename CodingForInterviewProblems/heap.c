#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int heap[100];

int last =1;
void
insert(int val)
{
	int i, tmp;
	heap[last] = val;
	//printf("last %d heap[last] %d\n",last, heap[last]);
	if (last > 1) { //rebalance
		for (i=last; i>1; i=i/2 ) {
			if (val < heap[i/2]) {
				tmp = heap[i];
				heap[i] = heap[i/2];	
				heap[i/2] = tmp;
			} else
				break;
		}
	}
	last++;
	return;
}

void
print_heap(void)
{
	int i, j =0;
	printf("\n------\n");
	for (i=1; i<last; i++) {
		printf("%d ",	heap[i]);
		//if (i==exp2(j) ) {
		//	printf("\n");
		//	j++;
		//}
	}
}

int max(int n)
{
	int max = heap[n/2];
	for (int i=n/2; i<=n; i++) 
		if (heap[i] > max)
			max = heap[i];

	return max;
}

int main(int argc, char*argv[])
{
	FILE *fp;
	int i,n, val[100];
	if (argc != 2) {
		printf("%s <input file> \n", argv[0]);
		exit(1);
	}
	if ( (fp = fopen(argv[1], "r")) == NULL) {
		printf("fopen error\n");
		exit(1);
	}

	fscanf(fp, "%d", &n);
	for (i=0; i<n; i++)
		fscanf(fp, "%d", &val[i]);
	
	for (i=0; i<n; i++) {
		//printf("inserting val %d\n", val[i]);
		insert(val[i]);
		print_heap();
	}
	printf("max of heap %d\n", max(n));
		
}
