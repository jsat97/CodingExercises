#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

#define N 100000
#define BITS_UINT64 (64)
#define M (N/BITS_UINT64 + 1) 
#define MASK1(n) (0ULL|(1ULL<<(n)))    //nth bit from LSB is 1
#define MASK0(n) ~(0ULL|(1ULL<<(n)))    //nth bit from LSB is 0
#define MASK2(n) (~(1ULL<<(n)))    // lower n bits are 1
#define SET_BIT(x,n) ((x) |= MASK1(n))
#define CLEAR_BIT(x,n) ((x) &= MASK0(n))  
#define KEEP_BITS(x,n)  ((x) &= MASK2(n))    //keep lower n bits only, zero the rest
#define GET_BIT(x,n) (((x)>>(n)) & 0x1)


#if DEBUG
#define FILENAME "input00.txt"
#define MY_DEBUG(x) printf x;  
#else
#define MY_DEBUG(x)
#endif

#if DEBUG
#define DUMP(x,y) { \
  for (i=0; i<(y); i++) { \
    printf(" i %d 0x%016llx",i, (x)[i]);  \
  } \
  printf("\n"); \
}
#else
#define DUMP(x,y)
#endif

FILE *fp;

char a[N+1], b[N+1];    //last one for NULL byte
u_int64_t a_bin[M] = {0ULL};
u_int64_t b_bin[M] = {0ULL};


//n is the no of words in the bit array
void set_bit(int bit, int n, int val, u_int64_t bin[])
{
  int i, i_left, ii;
  i = bit/BITS_UINT64 ;   //index in array from the right
  ii = bit%BITS_UINT64;   //bit position in the 64 bit word from the right

  //array index from the left
  i_left = n-1-i;

  if (val == 1) {
    SET_BIT(bin[i_left], ii); 
  } else {
    CLEAR_BIT(bin[i_left], ii); 
  }

}

//n is the no of words in the array of 64 bit values
int get_bit(int bit, int n, u_int64_t bin1[], u_int64_t bin2[])
{
  int i, j, j_left, ret;
  u_int64_t bin_sum[M+1] = {0ULL}; //incase  we overflow the Mth word
  
  int over_flow =0, bit_pos;

  //add the 2 arrays and get the bit we want
  //starting from LSB (right), add each word and check for overflow
  for (i=n-1; i >= 0; i--) {
    bin_sum[i+1] = bin1[i] + bin2[i] +over_flow;
    if (bin_sum[i+1] < bin1[i])  { //overflow
      over_flow = 1ULL;
    } else {
      over_flow = 0ULL;
    }  
  }   
  bin_sum[i] =over_flow;

  j = bit/BITS_UINT64 ;   //index of array from right
  j_left = n-j;          //array index from left, bin_sum[] has n  as the last index
  bit_pos = bit%BITS_UINT64;    //bit posn in this value
  ret = GET_BIT(bin_sum[j_left], bit_pos);

  DUMP(bin_sum,n+1);
  //MY_DEBUG(("j_left %d shift %d\n",j_left, shift));

  return(ret); 
}

int convert_to_bin(int n, char *s, u_int64_t bin[])
{
  int i =0, j =0, nword, nb;
  int c,left;
  u_int64_t pow2 =1;

  //MY_DEBUG (("\nconvert_to_bin: s = %s \n",s));
  
  nword = n/BITS_UINT64 ;   //# of 8 byte values in the binary array
  left = n%BITS_UINT64 ;
  if (left)
    nword++;

  //in the binary array, set LSB first from the end of the byte array we have
  nb = nword -1;

  u_int64_t value =0ULL;
  for (i=n-1; i>=0; i--) {
    c = s[i];
    value +=  (c == '1')? pow2:0;
    //MY_DEBUG(("j %d c %c pow 0x%016llx value 0x%016llx\n",j, c, pow2, value));
    pow2 = 2* pow2;
    bin[nb] = value;
    if (j == (BITS_UINT64-1)) {   //begining of next word
      pow2 =1;
      value =0;
      nb--; 
      if (nb < 0) {
        printf("error: nb < 0 at i= %d j= %d \n",i,j);
        exit(1);
      }
      j=0;
    } else {
      j++;
    } 
  }
  MY_DEBUG(("\n"));
  return(nword);
}

int main()
{
  int  a_nw, b_nw, n, q, idx, val;
  char buf[64], temp[64];
  int line_count =0;
  char output[N+2], *p_output = output;
#if DEBUG
  int i;
#endif

  fp = stdin; 
#if 0
  if ( (fp = fopen(FILENAME,"r")) == NULL) {
    fprintf(stderr, "fopen failed\n");
    exit(1);
  } 
#endif

  fscanf(fp, "%d %d", &n, &q);  
  fgetc(fp);
  fscanf(fp, "%s",a);
  fgetc(fp);
  fscanf(fp, "%s",b);
  fgetc(fp);
  a_nw = convert_to_bin(n, a, a_bin);  
  MY_DEBUG (("nw %d a_bin",a_nw));

  DUMP(a_bin,a_nw);

  b_nw = convert_to_bin(n, b, b_bin);  
  MY_DEBUG (("nw %d b_bin",b_nw));
  
  if (a_nw != b_nw) {
    printf("error. a_nw (%d) != b_nw (%d)\n",a_nw, b_nw); 
    exit(1);
  }
  DUMP(b_bin,b_nw);


  while (line_count < q) {
    if (fgets(buf, sizeof(buf), fp) == NULL) {
      fprintf(stderr, "fgets returned error at line %d\n", line_count);
      exit(1);
    }
    //printf("buf %s\n",buf);

    if (!strncmp(buf, "set_a",5)) {
      sscanf(buf,"%s %d %d", temp, &idx, &val);   
      MY_DEBUG(("set_a %d %d\n",idx, val));
      set_bit(idx, a_nw, val, a_bin);
      DUMP(a_bin,a_nw);
    } else if (!strncmp(buf, "set_b",5) )  {
      sscanf(buf,"%s %d %d", temp, &idx, &val);   
      MY_DEBUG(("set_b %d %d\n",idx, val));
      set_bit(idx, b_nw, val, b_bin);
      DUMP(b_bin,b_nw);
    } else if (!strncmp(buf, "get_c",5) )  {
      sscanf(buf,"%s %d", temp, &idx);   
      MY_DEBUG(("get_c %d\n",idx));
      val = get_bit(idx, a_nw, a_bin, b_bin);
      MY_DEBUG(("%d\n",val));
      sprintf(p_output, "%d",val);
      p_output++;
    }
    line_count++;
  }
  *p_output ='\0';
  printf("%s\n",output);

  return(0);  
}
