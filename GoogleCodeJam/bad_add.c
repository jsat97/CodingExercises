#include <stdio.h>
#include <string.h>

#define MAX 100000

int  comb(int n, int r)
{
	double c, c1, c2, c3;
	c1 = (double) fact(n);
	c2 = (double) fact(n-r);
	c3 = (double) fact(r);
	c = c1/c2/c3;
	return (c);
}

//set of all sets that have m elements -from in[]
int
get_all_sets(int in[], int n, int m)
{
  int i,j,k, l=0;
  int *temp;
  int ncm;
  ncm = comb(n,m);
  out = malloc(sizeof(int*)*ncm);

  for (i=0; i<n-(m-1); i++) {
    temp = malloc(m*sizeof(int));
    for (j=i; j<i+m-1; j++) {
      printf("k %d values %d ",k, in[i,j]);
      temp[k++] = in[i,j];
    }
    out[l++]  = temp;
    printf("\n");
  }
  printf("l %d ncm %d\n",l, ncm);
  return(k);
}


//exclude set[] from in[] and put it in out[]
int
exclude_set(int in[], int n, int set[], int m, int out[])
{
  int i, j,k;
  int temp[MAX];
  memset((void*)temp, 0, MAX*sizeof(int));
  memcpy(temp, in, n*sizeof(int));
  for (i=0; i<m; i++) {
    for (j=0; j<n; j++) {
      if (temp[j] == set[i]) {
        temp[j] = -1;
        break;
      }
    }
  }
  k=0;
  for (j=0; j<n; j++) {
    if (temp[j] != -1) {
      out[k] = temp[j];
      k++;
    }
  }
  return(k);
}

int
main(int argc, char*argv[])
{
  int i, j, no_tests, no_candies, val;
  int candy_vals[MAX];
  int sum_pat =0, sum_sam =0;  
  int set1[MAX], set2[MAX], set_excl[MAX], no_set1, no_set2, no_excl;

  printf("input # of vals in set1 :\n");
  scanf("%d",&no_set1);
  printf("input vals in set1 :\n");
  for(j=0; j<no_set1; j++) {
    scanf("%d",&set1[j]);
  }
  printf("input # of vals in set2 :\n");
  scanf("%d",&no_set2);
  printf("input vals in set2 :\n");
  for(j=0; j<no_set2; j++) {
    scanf("%d",&set2[j]);
  }
  no_excl = exclude_set(set1, no_set1, set2, no_set2, set_excl);
  printf("excluding set2 from set1 \n");
  for(j=0; j<no_excl; j++) {
    printf("%d ",set_excl[j]);
  }

  return(0);
  scanf("%d",&no_tests);
  for(i=0; i<no_tests; i++) {
    scanf("%d",&no_candies);
    for(j=0; j<no_candies; j++) {
      scanf("%d",&candy_vals[j]);
    }
  }    
  for(j=0; j<no_candies; j++) {
    printf("%d",candy_vals[j]);
    sum_pat  = sum_pat^candy_vals[j];
    sum_sam  += sum_sam;
  }
  printf("sum_pat %d sum_sam %d\n",sum_pat, sum_sam);
  return(0);
}
