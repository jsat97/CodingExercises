#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NOSUB 256

/*
 *Brute force method to generate unique substrings in the union of all substrings of several strings. The final result is lexicographically
 *ordered. A given index in the final set is picked.
 * https://www.hackerrank.com/challenges/find-strings
 */

#if 0
#define DEBUG(x,args ...)  printf(x, ## args);
#else
#define DEBUG(x,args ...)
#endif

char **sub_arr = NULL;
char **sub_un_arr  = NULL;
//find all the unique substrings in a string
int 
find_subtrings(char *s)
{
  char *p =s, *p1;
  int len, i=0;
  static int nosub_alloced =0;

  if (nosub_alloced  == 0) { 
    sub_arr =  (char**)(malloc(NOSUB *sizeof(char*)));
    nosub_alloced += NOSUB;
  }
  
  while (*p) {
    for (p1 = p; *p1; p1++) {
      len = p1-p+1;
      sub_arr[i] = (char*)malloc( (len+1)*sizeof(char));
      strncpy(sub_arr[i], p, len);
      sub_arr[i][len] = 0;
      //printf("%d %s\n",i,sub_arr[i]);
      i++;
      if (i == nosub_alloced) {
        nosub_alloced += NOSUB;
        sub_arr =  (char**)(realloc(sub_arr, nosub_alloced*sizeof(char*)));
      }
    }
    p++;
  }
  return(i);
}

static int
compare(const void *p1, const void *p2)
{
  return strcmp(* (char * const *) p1, * (char * const *) p2);
}


int
unique(char **s, int n)
{
  int i,j =1;
  char *prev;
  qsort(s,n,sizeof(char*),compare);
  //remove duplicates
  prev = s[0];
  for (i=1; i<n; i++) {
    if (!strcmp(prev, s[i])) continue;
    s[j++] = s[i];
    prev = s[i];
  }
  return j;
}


int main()
{
  int i, j, k, no_subs, no_unq_subs, no_unq_un_subs, no_strings, no_queries;
  int no_query_arr[501];
  char str[51][2001];
  int nosub_un_alloced =0;  
  
  k=0;

  if (nosub_un_alloced  == 0) {
    sub_un_arr =  (char**)(malloc(NOSUB *sizeof(char*)));
    nosub_un_alloced = NOSUB;
  }
     
  fscanf(stdin, "%d",&no_strings);  
	DEBUG("%d\n", no_strings);
  for (i=0; i<no_strings; i++) {
    fscanf(stdin, "%s",str[i]);
		DEBUG("%s\n", str[i]);
    no_subs = find_subtrings(str[i]);
    no_unq_subs = unique(sub_arr, no_subs);
  
    for (j=0; j<no_unq_subs; j++) {
			DEBUG("%s ",sub_arr[j]);
      //make union by adding this to another array
     if (k == nosub_un_alloced) {
				nosub_un_alloced += NOSUB;	
        sub_un_arr =  (char**)(realloc(sub_un_arr, nosub_un_alloced*sizeof(char*)));
      }
      sub_un_arr[k++] = sub_arr[j];  
    }
    DEBUG("\n");
  }
  no_unq_un_subs = unique(sub_un_arr, k);
  DEBUG("no_unq_un_subs %d \nsub_un_arr\n", no_unq_un_subs);
  for (i=0; i<no_unq_un_subs; i++)
    DEBUG("%s ",sub_un_arr[i]);
  DEBUG("\n");
  
  fscanf(stdin, "%d",&no_queries);  
  for (i=0; i<no_queries; i++) 
    fscanf(stdin, "%d",&no_query_arr[i]);  

  for (i=0; i<no_queries; i++) {
    if (no_query_arr[i] > no_unq_un_subs)
      printf("INVALID\n");
    else 
      printf("%s\n",sub_un_arr[no_query_arr[i] -1]);
  }
}
