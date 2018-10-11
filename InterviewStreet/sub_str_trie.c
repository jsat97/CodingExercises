#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define MAX_EDGES 26
#define MAX_WORD_LEN 2000
#define NO_VERTEX (1024*1024)

/*
 * substrings problem using trie
 * https://www.hackerrank.com/challenges/find-strings
 */

#if 0
#define DEBUG(x,args ...)  printf(x, ## args);
#else
#define DEBUG(x,args ...)
#endif

typedef struct _Vertex {
	int words;
	int prefix;
	struct _Vertex *edges[MAX_EDGES];
} Vertex;

Vertex root = {0,0};	


char sub_arr_query[500][2000];
int no_query_sort_arr[500] = {0};
static char buf[MAX_WORD_LEN];
int no_vert_alloced =0; 
int no_vert_used =0;
Vertex *vertex_chunk = NULL;

void
alloc_vertex(void)
{
  if (no_vert_alloced  == no_vert_used) { 
		no_vert_alloced +=  NO_VERTEX;
		vertex_chunk = (Vertex*) realloc(vertex_chunk, no_vert_alloced *sizeof(Vertex));
		DEBUG("vertex alloced %d used %d\n",no_vert_alloced, no_vert_used);
  }
}

void
init_vertex(Vertex *v, int edge)
{
	int i, size ;
	Vertex *tmp;
#if ALLOC_VERTEX_CHUNK
	alloc_vertex();
	tmp = vertex_chunk + no_vert_used;
#else
	size = sizeof(Vertex);
	tmp = (Vertex*) malloc(size);
#endif
	tmp->words = tmp->prefix =0;
	v->edges[edge] = tmp;	
	no_vert_used++;

	for (i=0; i<MAX_EDGES; i++) {
		tmp->edges[i] = NULL;
	}
}

void
add_word(Vertex *vertex, char *w)
{
	char c;
	int index;
	
	c = *w;
	index = c -'a';
	//DEBUG("adding %c\n",c);
	if (vertex->edges[index] == NULL) {
		init_vertex(vertex, index);
	}
	w++;
	vertex->prefix++;
	if (*w == 0) {
		//DEBUG("end of word \n");
		vertex->edges[index]->prefix++;
		return;
	}
	if (vertex == &root)
		vertex->words++;
	add_word(vertex->edges[index], w);

}

//find the jth lowest string lexicographically
int
get_all_prefixes(Vertex *vertex)
{
	int i, ret, kprev;
	static char *prefp = buf;
	char *bufp = buf;
	static int j=0, depth =-1, iquery =0, k;
	uint32_t len;
	Vertex *cur_vertex = vertex; 		//keep on stack because we return and take another path

	k = no_query_sort_arr[iquery]-1 ;
	depth++;

	DEBUG("vertex  %p edges \n", vertex);
	for (i=0; i<MAX_EDGES; i++) 
		if (vertex->edges[i] != NULL) 
			DEBUG("%c ",i+'a');
	DEBUG("\n");

	for (i=0; i<MAX_EDGES; i++) {
		if (vertex->edges[i] != NULL) {
			*prefp  = i + 'a';
			*(prefp +1) = 0;
			bufp = prefp;
			DEBUG("edge %d(%c) j %d k %d %s\n",i, i+'a', j, k, buf);
			//store each string in an array - include null byte in length
			len = prefp-buf+2;

			if (j == k) { //we're checking the array index
				//printf("**found **\n");
				//printf("%s\n", buf);
				kprev = k;
				while (kprev == k) { //same index repeats, dont try to find it - because we cant
					memcpy(sub_arr_query[iquery], buf, len); 
					iquery++;	
					//reset the search index to next
					k = no_query_sort_arr[iquery]-1;
				}
					
				if (k == -1) {
					DEBUG("last index found %d\n", no_query_sort_arr[iquery-1] -1);
					return -1;
				}
			}
			j++;
 			prefp++;
			ret = get_all_prefixes(vertex->edges[i]);
			/*
			if (ret == -1) {
				depth--;
				return -1;	
			}
			*/
			prefp = bufp;	
			*(prefp+1) = 0;
			//prefp++;
			DEBUG("after return: edge %d(%c) j %d k %d %s\n", i, i+'a', j, k, buf);
		}
	}
	depth--;
	if (depth != -1) {
		DEBUG("no more edges\n");
		return 0;
	}
	//printf("k = %d not found\n", k);
	return -1;
}

static int
compare(const void *i1, const void *i2)
{
  return ((*(int*)i1 > *(int*)i2)? 1: (*(int*)i1 < *(int*)i2)? -1: 0); 
}


int main()
{
	int i, j, k, m, no_strings, no_queries, max_sub;
  int no_query_arr[500];
  char word[50][2000];
	char *p;
	int *ptr;
	
#if ALLOC_VERTEX_CHUNK			//dumps core at chunk allocation boundaries 
	alloc_vertex();
#endif
	fscanf(stdin, "%d",&no_strings);  
	for (i=0; i<no_strings; i++) {
    fscanf(stdin, "%s",word[i]);
		for (p=word[i]; *p; p++) {
			//DEBUG("adding %s\n",p);
			add_word(&root, p);
		}
	}
	//printf ("add_word done\n");
	fscanf(stdin, "%d",&no_queries);  
  for (i=0; i<no_queries; i++) 
    fscanf(stdin, "%d",&no_query_arr[i]);  

	memcpy(no_query_sort_arr, no_query_arr, sizeof(int)*no_queries);
	qsort(no_query_sort_arr, no_queries, sizeof(int),compare);
#if 0
  for (i=0; i<no_queries; i++) {
		printf("%d\n",no_query_sort_arr[i]); 
	}
#endif

	bzero(sub_arr_query, 2000*500); 

	//store the substrings we finally get for each of the queries here

	k = get_all_prefixes(&root);

	DEBUG("from main\n");
  for (i=0; i<no_queries; i++) {
		//for (m=0; m< no_queries; m++) {
			ptr = bsearch(&no_query_arr[i], &no_query_sort_arr, no_queries, sizeof(int), compare);
			m = (ptr -	no_query_sort_arr);
			//if (no_query_sort_arr[m] ==  no_query_arr[i]) {
				//printf("%d\n",no_query_arr[i]); 		//debug
				if (sub_arr_query[m][0] != 0) {
					printf("%s\n", sub_arr_query[m]);
				} else {
      		printf("INVALID\n");
				}
				//break;
			//}
		//}
	}

}
