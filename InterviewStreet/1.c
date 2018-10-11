#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct X_ {
	int a;
	char word[32];
	struct X_ *y;
};

typedef struct X_ X;

int 
main()
{
	X xx;
	xx.a =2;

	strcpy(xx.word, "word0000000");
	xx.y = malloc(sizeof(X));
	strcpy(xx.y->word, "word0000001");
	printf("xx.word %s xx.y->word %s \n",xx.word, xx.y->word); 
//	strcpy(xx.y.y.word, "word0000002");
	
}
