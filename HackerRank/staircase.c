#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main()
{
	int i, j, n;
	char c;
	scanf("%d", &n);

	for(i=0; i<n; i++) {
		for(j=0; j<n; j++) {
			c = (j >= n-1-i)? '#' :' ';
			printf("%c",c);
		}
		printf("\n");
	}
}
