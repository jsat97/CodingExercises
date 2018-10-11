#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(x,y)	((x < y) ? x : y)
int
main()
{
	int i, j, k, n, t, min_width, width[100000];
	int entry_lane, exit_lane;
	scanf("%d %d", &n, &t);
	for(j=0; j<n; j++) {
		scanf("%d", &width[j]);
	}
	for(i=0; i<t; i++){
		scanf("%d %d", &entry_lane, &exit_lane);
		// find the min width for entry and exit
		min_width = INT_MAX;
		for(k=entry_lane; k<= exit_lane; k++) {
			min_width = MIN(min_width, width[k]);
		} 
		printf("%d\n", min_width);
	}
}
