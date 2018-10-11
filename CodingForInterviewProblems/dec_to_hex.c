
#include <stdio.h>
#include <string.h>

#define SWAP(x,y) {\
char tmp;		\
tmp = x;	\
x = y;		\
y = tmp;	\
}

char *reverse(char *s)
{
	int len = strlen(s);
	char *p1, *p2;
	for (p1=s, p2=s+len-1; p1<p2; p1++, p2-- )
		SWAP(*p1,*p2);
	return s;
}

char *hex(int n ,char *s)
{
	int quot = n, rem;
	char *p = s;
	while(quot) {
		rem = quot %16;
		quot = quot/16;		
		printf("quot %d rem %d\n", quot, rem);
		*p++ = (rem >= 0 && rem <= 9)?rem +'0': (rem >=10 && rem <=15)?'a'+ rem -10:'z';
 }		
	*p =0;
	printf("returning hex %s\n",s);
	return s;
}

int
main()
{
	int n;
	char buf[64];
	printf("enter decimal value :");	
	scanf("%d", &n);
	printf("hex value %s\n", reverse(hex(n, buf)));
}
