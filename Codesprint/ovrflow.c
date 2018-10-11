#include <stdio.h>
#include <sys/types.h>

main()
{
  unsigned int x,y;
  u_int16_t z;
  u_int64_t a, b;
  u_int32_t c;
  int bit;

  //scanf("%u%u",&x,&y);
  //printf("x %d y %d \n",x,y);
  //z = x+y;
  //printf("z %u\n",z);

  //if (z<x) {
   // printf("overflow\n");
  //}
  a = 0xffffffffffffffffLL;
  b = 0ULL;
  printf("a %llu ~b %llu \n",a, ~b);
  c =0UL;
  printf("enter bit index to set in 32 bit value");
  scanf ("%d",&bit);

  c |= (1<<bit);
  printf("c (set only 4th bit) 0x%08x\n", c);
}
