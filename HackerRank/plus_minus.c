#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
	int n, tmp, k;
	int pos_count =0, neg_count = 0, zero_count =0;
	scanf("%d", &n);
	k =0;
	while(scanf("%d", &tmp) == 1) {
		// vals[k] = tmp;
		// printf ("vals[%d] %d \n", k, vals[k]);
		(tmp > 0) ? pos_count++: (tmp < 0)? neg_count++: zero_count++;

		k++;
	}
	printf("%.3f\n%.3f\n%.3f\n", (float)pos_count/n,
									(float)neg_count/n,  	(float)zero_count/n);
} 
