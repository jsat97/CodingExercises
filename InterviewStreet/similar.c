#include <stdio.h>

int
find_similar(char *s)
{
  int  count, total =0;
  char *s1, *p, *tmp;

  //count the no of chars that match with s
  p = s;
  while(*p) {
    count =0;
    for (s1=s,tmp=p; *tmp; tmp++,s1++) {
      if (*tmp == *s1) {
        count++;
      } else {
        break;
      }
    }
    //printf("p %s count %d\n",p, count);
    total += count;
    p++;
  }
  return total;
}

int main()
{
  char s[100000];
  int i, n, ret;

  scanf("%d",&n);
  for (i=0; i<n; i++) {
    scanf("%s",s);
    ret = find_similar(s);
    printf("%d\n", ret);
  }
}
