#include <stdio.h>
#include <sys/types.h>
#define MAX_UINT64 0xffffffffffffffffULL

#define MASK1(n) (0ULL|(1ULL<<(n)))    //nth bit from LSB is 1
#define MASK0(n) ~(0ULL|(1ULL<<(n)))    //nth bit from LSB is 0
#define MASK2(n) ((1ULL<<(n))-1)    // lower n bits are 1
#define MASK3(n) (~(1ULL<<(n))+1)    // lower n bits are 0
#define SET_BIT(x,n) ((x) |= MASK1(n))
#define CLEAR_BIT(x,n) ((x) &= MASK0(n))  
#define KEEP_BITS(x,n)  ((x) &= MASK2(n))    //keep lower n bits only, zero the rest
#define GET_BIT(x,n) (((x)>>(n)) & 0x1)

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
 *(buf+count) = '\0';
  return(buf);
}

main(){
  char buf[65];
  int n;
  u_int64_t val =0ULL;
#if 0
  printf("make mask with nth bit from LSB = 1/0 - enter n :");
  scanf("%d",&n);
  val = MASK1(n);
  decimal_to_binary(val, buf);
  printf("%s\n",buf);

  val = MASK0(n);
  decimal_to_binary(val, buf);
  printf("%s\n",buf);


  printf("set nth bit from LSB - enter n, value :");
  val =0ULL;
  scanf("%d %d",&n, &val);
  SET_BIT(val,n);
  decimal_to_binary(val, buf);
  printf("%s\n",buf);

  printf("clear nth bit from LSB - enter n, value :");
  val =0ULL;
  scanf("%d %ull",&n, &val);
  CLEAR_BIT(val,n);
  decimal_to_binary(val, buf);
  printf("%s\n",buf);


  printf("mask keeping n bits from LSB - enter n :");
  scanf("%d",&n);
  val = MASK2(n);
  decimal_to_binary(val, buf);
  printf("%s\n",buf);

  printf("mask clearing n bits from LSB - enter n :");
  scanf("%d",&n);
  val = MASK3(n);
  decimal_to_binary(val, buf);
  printf("%s\n",buf);
#endif
  printf("keep n bits from LSB in given value - enter n, value(hex) :");
  val =0ULL;
  scanf("%d %llx",&n, &val);
  KEEP_BITS(val,n);
  decimal_to_binary(val, buf);
  printf("%s\n",buf);


}
