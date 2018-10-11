#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int val, digit, no_divs, t, i, n;
    scanf("%d", &t);
    for(i=0; i<t; i++){
        scanf("%d", &n);
        no_divs =0;
        val = n;
        while(val) {
            digit = val - val/10*10;
						if (digit) {
            	if (n%digit == 0) 
                 no_divs = no_divs+1;
						}
            val = val/10;
        }
        printf("%d\n", no_divs);
    }
    return 0;
}

