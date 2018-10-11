#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i, j, k, n, sum1 =0, sum2 =0, *vals, tmp;
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    scanf("%d", &n);
    if ( (vals = malloc(sizeof(int)*n*n)) == NULL) {
        perror("malloc");
        return 1;
    }
		k =0;
		while(scanf("%d", &tmp) == 1) {
			vals[k] = tmp;
			// printf ("vals[%d] %d \n", k, vals[k]);
			k++;
		}
    for(i=0; i<n; i++, j--) {
      sum1 += vals[i*n +i];
      sum2 += vals[(i+1)*n -1 -i];
			printf("sum1 sum2 %d %d\n", sum1, sum2);
    }
    printf("%d\n", abs(sum1-sum2));
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */    
    return 0;
}
