#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(x,y)	((x < y) ? x : y)

static int 
min_array(int *_a,int _n)
{
int _i, _min = INT_MAX;
	for(_i=0; _i<_n; _i++) {
		if (_a[_i] == 0)
			continue;
		_min = MIN(_a[_i],_min);
	}	
	return _min;
}

int 
main() {
	int i, j, cuts, n, m, min, a[1000];
	scanf("%d", &n);
	for(j=0; j<n; j++) {
		scanf("%d", &a[j]);
	}
	while(1) {
		min = min_array(a, n);
		cuts =0;
		m =0;
		for(i=0; i<n; i++) {
			if (a[i] != 0) {
				a[i] -= min;
				if (a[i])			// count non zero vals left
					m++;
				cuts++;
			}
		}
		printf("%d\n", cuts);
		if (!m)
			break;
	}	
}
	
