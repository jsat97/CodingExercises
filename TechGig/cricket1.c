#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_MATCHES 100
#define AVERAGE (5.0)


int output1;

char *next_token(char *s)
{
	while (*s && *s != ',') s++;
	return(s);
}

float Aver(char *buff)
{
	int j =0, sum =0; 
	float average;
	while (buff[j]) {
		sum += buff[j] - '0';
		j++;
	}
	//if (!j) return(0);
	average = sum/(float)(j);
	return(average);
}


void GetBestBowlerCount(int input1,char* input2)
{
	char  *p, *p1, *p_sav;
	int  i;
	float average;
	char buf[MAX_MATCHES];

	//if (!input1) return;

	p = strdup(input2);
	p_sav =p;
	p1 = strchr(p, '}');
	*p1 =0;

	for (i=0; i< input1; i++) {
		p++;
		
		p1 =p;
		//while (isspace(*p1)) p1++; 
		//while (*p && *p != ',') p++;
		p = next_token(p);
		*p =0;

		strcpy(buf, p1);

		average = Aver(buf);
		//printf("%d wickets %s aver %f\n",i, buf,average);
		if (average >= AVERAGE) output1++;
	}
	free(p_sav);
	
}

int main(int argc, char*argv[])
{
	output1 =0;
	GetBestBowlerCount(3, "{123456,89359,99999}");
	printf("count %d\n", output1);
	output1 =0;
	GetBestBowlerCount(3, "{123456,35,9}");
	printf("count %d\n", output1);
	output1 =0;
	GetBestBowlerCount(3, "{123456,,123}");
	printf("count %d\n", output1);
	output1 =0;
	GetBestBowlerCount(0, "{}");
	printf("count %d\n", output1);
	return(0);
}


