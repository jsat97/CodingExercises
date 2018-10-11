#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    int t, n, c, m;
    int answer, wrap_no, wrap_rem, extra, exchg;
    scanf("%d", &t);
    while ( t-- )
    {
        scanf("%d%d%d",&n,&c,&m);
        int answer = 0; 
        /** Write the code to compute the answer here. **/
        answer = n/c;
       	printf("answer %d\n", answer); 
        wrap_no = answer;
        extra = 0;
        do {
            exchg = wrap_no/m;
						if (!exchg)
							break;
            wrap_rem = wrap_no%m;    
            extra += exchg;
            wrap_no = exchg + wrap_rem;            
        		printf("exchg %d wrap_rem %d wrap_no %d extra %d\n", exchg, wrap_rem, wrap_no, extra);
        } while (wrap_no);
        answer += extra;
       
        printf("%d\n", answer); 
    }
        
    return 0;
}

