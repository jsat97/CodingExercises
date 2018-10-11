#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define MAX_EDGES 26
#define MAX_WORD_LEN 2000

#define BIG_CHUNK	(100*1024*1024)
#define SUBS_INCR	(100*1024*1024)

#define STORE_ONLY_QUERY_STR	1	//store only the strings at the indices we need

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

int n_vertices_alloced =0;
int n_vertices_used =0;
Vertex root = {0,0};	

#if CONTIGUOUS_ARRAY  
uint64_t  nosub_alloced =0;
uint64_t  nosub_len_alloced =0;
char *sub_arr;
uint64_t *sub_len_arr;
#endif

char *sub_arr_query[500];

void
init_vertex(Vertex *v, int edge)
{
	int i;
	Vertex *tmp;
	int size = sizeof(Vertex);
	tmp = (Vertex*) malloc(size);
	tmp->words = tmp->prefix =0;
	v->edges[edge] = tmp;	

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
	if (vertex->edges[index] == NULL) {
		//DEBUG("added new vertex \n");
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
#if STORE_ONLY_QUERY_STR		//store only the strings at the indices we need
int
get_all_prefixes(int *k)
#else
int
get_all_prefixes(Vertex *vertex, int *k)
#endif
{
	int i, ret;
	static char buf[MAX_WORD_LEN], *prefp = buf;
	char *bufp = buf;
	static int j=0, depth =-1;
#if CONTIGUOUS_ARRAY  
	static uint64_t sub_len_arr_last =0, sub_len_arr_index =0; 
#endif
	uint32_t len;
	static Vertex *cur_vertex;

	depth++;
	for (i=0; i<MAX_EDGES; i++) {
		if (cur_vertex[i] != NULL) {
			*prefp  = i + 'a';
			*(prefp +1) = 0;
			bufp = prefp;
			//DEBUG("j %d *k %d %s\n",j, *k, buf);
			//store each string in an array - include null byte in length
			len = prefp-buf+2;
#if CONTIGUOUS_ARRAY  //use 1 contiguous array and store all strings
			//check if we have space before copy
			if ( (sub_len_arr_last + len)  > nosub_alloced)  {
				nosub_alloced += BIG_CHUNK;
				DEBUG("realloc sub_arr nosub_alloced %llu\n",nosub_alloced);
				
        sub_arr =  (char*)(realloc(sub_arr, nosub_alloced*sizeof(char)));
			}
			if (sub_len_arr_index  == nosub_len_alloced)  {
				nosub_len_alloced += SUBS_INCR;
				DEBUG("realloc sub_len_arr nosub_len_alloced %llu\n",nosub_len_alloced);
        sub_len_arr =  (uint64_t*)(realloc(sub_len_arr, nosub_len_alloced*sizeof(uint64_t)));
			}
			memcpy(sub_arr+ sub_len_arr_last, buf, len); 

			sub_len_arr[sub_len_arr_index] = sub_len_arr_last;
			sub_len_arr_last  += len;
			sub_len_arr_index++;
#endif

			if (j == *k) { //we're checking the array index
#if STORE_ONLY_QUERY_STR		//store only the strings at the indices we need
				memcpy(sub_arr_query[i_query], buf, len); 
				i_query++;	
				return 0;
#else
				//printf("%s\n", buf);			//print the substring  at the index we want
				j =0;
				prefp = buf;
				depth--;
				return 0;
#endif
			}
			j++;
 			prefp++;
#if STORE_ONLY_QUERY_STR		//store only the strings at the indices we need
			cur_vertex = cur_vertex->edges[i];
			ret = get_all_prefixes(k); 
#else
			ret = get_all_prefixes(vertex->edges[i], k); 
#endif
			if (ret == 0) {
				depth--;
				return 0;	
			}
			prefp = bufp;	
			*(prefp+1) =0;
		}
	}
	depth--;
	//final return
	if (depth == -1) {
		*k =j; 	//return the total # of substrs
		j =0;
		prefp = buf;
	}
	return -1;
}

static int
compare(const void *i1, const void *i2)
{
  return ((*(int*)i1 > *(int*)i2)? 1: (*(int*)i1 < *(int*)i2)? -1: 0); 
}


int main()
{
	int i, j, k, no_strings, no_queries, max_sub;
  int no_query_arr[500];
  int no_query_sort_arr[500];
  char word[50][2000];
	char *p;
#if 0
	add_word(&root, "tree");
	add_word(&root, "trash");
	add_word(&root, "ambulance");
	add_word(&root, "amber");
	add_word(&root, "train");
	printf("printing prefixes \n");
#endif


#if CONTIGUOUS_ARRAY  //use 1 contiguous array and store all strings
	//store all substrings here
  if (nosub_alloced  == 0) { 
    sub_arr =  (char*)malloc(BIG_CHUNK);
    nosub_alloced += BIG_CHUNK;
  }
	//store cumulative length of substrings here
	if (nosub_len_alloced  == 0) { 
		sub_len_arr =  (uint64_t*)malloc(SUBS_INCR*sizeof(uint64_t));
    nosub_len_alloced += SUBS_INCR;
	}
#endif
	
	fscanf(stdin, "%d",&no_strings);  
	for (i=0; i<no_strings; i++) {
    fscanf(stdin, "%s",word[i]);
		for (p=word[i]; *p; p++) {
			//DEBUG("adding %s\n",p);
			add_word(&root, p);
		}
	}
	fscanf(stdin, "%d",&no_queries);  
  for (i=0; i<no_queries; i++) 
    fscanf(stdin, "%d",&no_query_arr[i]);  

#if STORE_ONLY_QUERY_STR		//store only the strings at the indices we need
	memcpy(no_query_sort_arr, no_query_arr, sizeof(int)*no_queries);
	qsort(no_query_sort_arr, no_query_arr, sizeof(int),compare);

	bzero(sub_arr_query, 500*sizeof(char*));
  for (i=0; i<no_queries; i++)  {
		j = no_query_arr[i]-1 ;
		sub_arr_query[j] = malloc(2000*sizeof(char));
	}
#endif

#if CONTIGUOUS_ARRAY  //use 1 contiguous array and store all strings
	//get the max # of substrings in advance
	//when we store all the strings in 1 array, we call get_all_prefixes only once. this is the time we do it. 
	max_sub = -1;
	get_all_prefixes(&root, &max_sub);
	//DEBUG("max_sub %d\n", max_sub);
#if 0
  for (i=0; i<max_sub; i++) 
		printf("%llu %s\n", sub_len_arr[i],(char*)(sub_arr+sub_len_arr[i]));
#endif
#endif

  for (i=0; i<no_queries; i++) {
#if SEARCH_TRIE_EVERY_TIME		//search the whole trie every time
		//DEBUG("get substring with index %d\n",no_query_arr[i]-1);
		if (no_query_arr[i] > max_sub) {
      printf("INVALID\n");
			continue;
		}	
		j = no_query_arr[i]-1 ;
		k = get_all_prefixes(&root, &j);
		if (k == -1) 
      printf("INVALID\n");
#endif

#if STORE_ONLY_QUERY_STR		//store only the strings at the indices we need
		j = no_query_sort_arr[i]-1 ;
		k = get_all_prefixes(&j);
#endif

#if CONTIGUOUS_ARRAY  //use 1 contiguous array and store all strings
		//get location of string
		printf("%s\n", sub_arr+sub_len_arr[j]);
#endif

#if STORE_ONLY_QUERY_STR		//store only the strings at the indices we need
	for (m=0; m< no_queries; m++)
		if (no_query_sort_arr[m] ==  no_query_arr[i]) {
			if (no_query_sort_arr[m] != NULL)
				printf("%s\n", sub_arr_query[m]);
			else
      	printf("INVALID\n");
		}
	}

#endif
  }

}
