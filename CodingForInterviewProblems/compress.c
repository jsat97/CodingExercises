#include <stdio.h>
#include <string.h>

/*
 * compress aabcccccaaa -> a2b1c5a3
 */

int compress(char*buf, char*comp)
{
  int i, len = strlen(buf);
  char last;
  int j=0, count =1;
  int flag = 0;   //compressible or not

  last = buf[0];
  for (i=1; i<=len; i++) {
    if (last == buf[i]) {
      count++;
      if (count >= 2) flag =1;
    } else { //copy into compressed buffer with or w/o count      
      comp[j++] = last;
      if (count > 1)
        comp[j++] = count +'0';
      last = buf[i];
      count = 1;
    }
  }
  comp[j] = 0;
  return flag; 
}


int
compress_in_place(char *buf)
{
	char last=buf[0];
	int len = strlen(buf);
	int i, j=0, count =1;
		
	for (i=1; i<len; i++) {
		if (last == buf[i]) {
			count++;
		} else {
			buf[j++] = last;
			if (count > 1) 
				buf[j++] = count + '0';
			count =1;
			last = buf[i];	
		}
	}
	//the last byte is never written out as its not compared with anything. it may have a count > 1 or 0
	buf[j++] = last;
	if (count > 1) 
		buf[j++] = count + '0';

	buf[j] = 0;
	return 0;
}

int
main()
{
  char buf[512], buf_comp[512];
  int comp;
  
  printf("enter string :");
  scanf("%s", buf);
  //comp = compress(buf, buf_comp);
  //printf("comp %d buff %s\n", comp, buf_comp);
	compress_in_place(buf);
	printf("comp in place %s\n",buf);
}
   
