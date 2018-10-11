#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 16

int 
main()
{
	int i =0, num_strings;
	char (*strings)[MAX_STRING_LENGTH];
		
	printf("num of strings :");
	scanf("%d",&num_strings);
	//printf("size %d\n", sizeof *strings);
	strings = malloc(sizeof *strings * num_strings);
	for (i=0; i< num_strings; i++) {
		strcpy(strings[i], "This is a test");
		printf("%s\n", strings[i]);
	}
}
