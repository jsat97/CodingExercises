#include <stdio.h>

//0,1,1,2,3,5,8,13,21
int
fib(int n)
{
	if (n<=1) return n;
	return fib(n-1) + fib(n-2);
}
		
int
fib_iter(int n)
{
	int i, fib;
	
	int fib_prev = 1;
	int fib_prev_prev = 0;

	for (i=0; i<n; i++) {
		if (i < 2) printf("%d ",i);
		else {
			fib = fib_prev + fib_prev_prev;
			printf("%d ", fib);
			fib_prev_prev = fib_prev;	
			fib_prev =  fib;
		}
	}
	printf("\n");
	return 0;
}



int main()
{
	int n;
	printf("enter n :");
	scanf("%d",&n);
	fib_iter(n);
	return 0;
}
