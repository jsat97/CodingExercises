#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void*
malloc_align(int size, unsigned int align)
{
	char *p, *p_align;
	int size_align;

	size_align = size + align;
	p = malloc(size_align);
	p_align = ((long)p+ align)/align *align;
	
	printf("p %p p_align %p \n", p, p_align);
	*(p_align-1) = p_align -p;
	return p_align;
}


void
free_align(char *p)
{
	char *p_orig;
	int pad; 
	pad = *(p-1);

	p_orig = p- pad;
	printf("freeing p %p \n", p_orig);
	
	free(p_orig);

}


int
main()
{
	unsigned char *p;
	p = malloc_align(100,16);

	printf("main: p %p\n", p);
	free_align(p);
}
