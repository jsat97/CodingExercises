#include <stdio.h>

void
print_bin(unsigned int x)
{
	unsigned int i, max_shift;
	max_shift = (sizeof(x)*8-1);
	for(i=1<<max_shift; i>0; i>>=1) {
		//printf("%d\n",i);
		printf("%c",(x&i)?'1':'0');
	}
	printf("\n");
}

unsigned int
rev(unsigned int x)
{
	unsigned int r=0;
	while(1) {
		r |= x&1;
		x = x>>1;
		if (!x) break;
		r = r<<1;
	}
	return r;
}	

int
main()
{
	int n;
	scanf("%d",&n);
	printf("original value ");
	print_bin(n);
	//printf("reversed value %u\n", rev(n));
	print_bin(rev(n));
	
}
