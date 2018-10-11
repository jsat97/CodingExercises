#define N 100000

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define MAX_UINT64 0xffffffffffffffffULL
#define MASK1(n) (0ULL|(1ULL<<(n)))    //nth bit from LSB is 1
#define MASK0(n) ~(0ULL|(1ULL<<(n)))    //nth bit from LSB is 0
#define MASK2(n) ((1ULL<<(n))-1ULL)    // lower n bits are 1
#define MASK3(n) (~(1ULL<<(n))+1ULL)    // lower n bits are 0
#define SET_BIT(x,n) ((x) |= MASK1(n))
#define CLEAR_BIT(x,n) ((x) &= MASK0(n))  
#define KEEP_BITS(x,n)  ((x) &= MASK2(n))    //keep lower n bits only, zero the rest
#define GET_BIT(x,n) (((x)>>(n)) & 0x1)

#define DEBUG 1

char a[N+1], b[N+1];    //1 null byte at the end

char *decimal_to_binary(u_int64_t n, char *buf)
{
   int c, d, count;
   count = 0;
 
   for ( c = 63 ; c >= 0 ; c-- )
   {
      d = n >> c;
 
      if ( d & 1 )
         *(buf+count) = 1 + '0';
      else
         *(buf+count) = 0 + '0';
 
      count++;
   }
//   *(buf+count) = '\0';
  return(buf);
}

int create_input(int nbit, int no_lines)
{
  char buf1[64], *pa =&a[N-1];
  char buf2[64], *pb =&b[N-1];
  char buf[65];
  int nol;

  u_int64_t a_bin[N] = {0ULL}, b_bin[N] = {0ULL}, c_bin[N] = {0ULL}; 
  u_int64_t  temp1, temp2;
  int i;
  int nword, left,  b1, b2;

  nword = nbit/64; 
  left = nbit%64;
  if (left)
    nword++; 
  a[N] = b[N] = '\0';
  
  for (i=nword-1; i>=0; i--) {
    temp1 = rand();
    temp2 = rand();
    a_bin[i] = ( (temp1 <<32) | (temp2 & 0xffffffff)) ;
    temp1 = rand();
    temp2 = rand();
    b_bin[i] = ((temp1 <<32) | (temp2 & 0xffffffff)) ;

    if (i ==0 && left) { //fill up only remaining bits
      //if left != 0, the last word needs to be zerod for 64-left bits
      //a_bin[i] &= ((1<<(left-1))-1);
      //b_bin[i] &= ((1<<(left-1))-1);
      KEEP_BITS(a_bin[i], left); 
      KEEP_BITS(b_bin[i], left); 
    }
    decimal_to_binary(a_bin[i],buf1);
    decimal_to_binary(b_bin[i],buf2);
#if DEBUG
    {
    int j;
    printf("buffers \n");
    for (j=0; j<64; j++)
      printf("%c",buf1[j]);
    printf("\n");
    for (j=0; j<64; j++)
      printf("%c",buf2[j]);
    printf("\n");
    }
#endif
    if (i ==0 && left) { //copy only LSB bytes
      strncpy(pa-left+1, buf1+64-left, left);
      strncpy(pb-left+1, buf2+64-left, left);
      pa -= left;
      pb -= left;
    } else {
      strncpy(pa-63, buf1, 64);
      strncpy(pb-63, buf2, 64);
      pa -= 64;
      pb -= 64;
    }
  }

  // pa and pb should point to the begining now
  //printf("outside loop: pa %p a %p a pb %p b %p \n",pa, a, pb, b); 
  
  fprintf(stderr, "check initial value: a_bin[%d] = %016llx\n",nword-1, a_bin[nword-1]);
  fprintf(stderr, "check initial value: b_bin[%d] = %016llx\n",nword-1, b_bin[nword-1]);

  printf("%d %d\n",nbit,no_lines);
  printf("%s\n",pa+1);
  printf("%s\n",pb+1);
  nol = no_lines/4;

  for (i=0; i< nol; i++) {
    b1 =  1 + (int) ((float)(nbit-1) * (rand() / (RAND_MAX + 1.0)));
    printf("set_a %d %d\n",b1, 1);
    printf("get_c %d\n",b1);

    b2 =  1 + (int) ((float)(nbit-1) * (rand() / (RAND_MAX + 1.0)));
    printf("set_b %d %d\n",b2, 0);
    printf("get_c %d\n",b2);
  }

  (1 == 1) ?SET_BIT(a_bin[nword-1], b1):CLEAR_BIT(a_bin[nword-1], b1); 
  c_bin[nword-1] = a_bin[nword-1] + b_bin[nword-1];
  buf[64] = '\0';
#if DEBUG
  printf("a_bin[%d] = %s\n",nword-1, decimal_to_binary(a_bin[nword-1], buf));
  printf("b_bin[%d] = %s\n",nword-1, decimal_to_binary(b_bin[nword-1], buf));
  printf("c_bin[%d] = %s\n",nword-1, decimal_to_binary(c_bin[nword-1], buf));
#endif  
  printf("\nget_c %d = %llu\n",b1, GET_BIT(c_bin[nword-1], b1));

  (0 == 1) ?SET_BIT(b_bin[nword-1], b2):CLEAR_BIT(b_bin[nword-1], b2); 
  c_bin[nword-1] = a_bin[nword-1] + b_bin[nword-1];
  buf[64] = '\0';
#if DEBUG
  printf("a_bin[%d] = %s\n",nword-1, decimal_to_binary(a_bin[nword-1], buf));
  printf("b_bin[%d] = %s\n",nword-1, decimal_to_binary(b_bin[nword-1], buf));
  //printf("c_bin[%d] = %016llx\n",nword-1, c_bin[nword-1]);
  printf("c_bin[%d] = %s\n",nword-1, decimal_to_binary(c_bin[nword-1], buf));
#endif  

  printf("\nget_c %d = %llu\n",b2, GET_BIT(c_bin[nword-1], b2));


  //printf("a_bin[%d] = %016llx\n",nword-1, a_bin[nword-1]);
  //printf("b_bin[%d] = %016llx\n",nword-1, b_bin[nword-1]);
  //printf("c_bin[%d] = %016llx\n",nword-1, c_bin[nword-1]);

  return(0);
}


int main()
{
  int nbit, no_lines;
  //printf("nbit = ");
  scanf("%d %d",&nbit, &no_lines);
  create_input(nbit, no_lines);
  return(0);
}
