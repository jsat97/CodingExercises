#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NPERM 100
#define LEN 32
int nperm =0;

char *set[NPERM];
char *set1[NPERM];

//insert c at index in src and return dest, assume we have space
char *insert(char *src, char *dest, char c, int index)
{
  int len, i, j;
  len = strlen(src);
  if (index == len)
    len++;
  for (i=0, j=0; i<len; i++) {
    if (i == index) {
      dest[j++] = c;
    }
    dest[j++] = src[i];
  }
  dest[j] = 0;
}

int
perm(char*s, char**set)
{
  char buf[128];
  char *s1 =s; 
  int i, j, n, len;

  if (*(s+1) == '\0') {
    set[nperm++] = s;
    return(nperm);
  }
  s++;
  n = perm(s, set);
  nperm =0;
  //printf("n %d\n",n);
  for (i=0; i<n; i++) {
    len = strlen(set[i]);
    for (j=0; j< len+1; j++) {
      insert(set[i], set1[nperm], *s1, j); 
      //printf("set[%d] %s set1[%d] %s\n", nperm, set[nperm], nperm, set1[nperm]);
      nperm++;
    }
  }
  for (i=0; i<nperm; i++) {
    strcpy(set[i],set1[i]);
  }
  printf("---\n");
  return(nperm);
}


int
main()
{
  char buf[1024];
  int i, len;

  printf("%s", "enter string :");
  scanf("%s", buf);
  len = strlen(buf); 
  
  for (i=0; i<NPERM; i++) {
    set[i] = malloc(sizeof(char)* LEN);
    set1[i] = malloc(sizeof(char)* LEN);
  }
  perm(buf, set); 
#if 1
  printf("main\n");
  for (i=0; i<nperm; i++) {
    printf("set[%d] = %s\n",i, set[i]);
  }
#endif   
  return(0); 
}
