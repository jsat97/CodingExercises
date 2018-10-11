#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define COMMA ","
#define LB "("
#define RB ")"


int output1[100];

int  get_input_vals(char *s, int *val1, int *val2, int *val3)
{
	char *p ,*p1, *p_begin, *p_end;
	int len;

	p_begin = strchr(s, '(');
	p_end = strchr(s, ')');
	len = p_end-p_begin+2;	//+1 for comma after )

	p = p_begin+1;
	p1 = strtok(p, COMMA) ;
	*val1 = atoi(p1);
	*val2 = atoi( (p1 = strtok(NULL, COMMA)) );
	*val3 = atoi( (p1 = strtok(NULL, RB)) );
	return(len);
}

double fact(int n)
{
	double f =1.0;
	int i;
	
	for (i=n; i>0; i--) {
		f = f * i;	
	}
	return(f);
}

double  comb(int n, int r)
{
	double c, c1, c2, c3;
	c1 = (double) fact(n);
	c2 = (double) fact(n-r);
	c3 = (double) fact(r);
	c = c1/c2/c3;
	return (c);
}

void GetPlayCount(int input1,char* input2)
{
	int  i, ib, ig, len, tot_len=0;
	int m, n, p;
	double no_groups;
	char *p_in, *p1;

	for (i=0; i< input1; i++) {
		no_groups =0;
		p_in = strdup(input2);
		p1 = p_in + (u_char)tot_len;
		len = get_input_vals(p1, &m, &n, &p);
		tot_len += len;
		//printf("m %d n %d p %d len %d\n",m,n,p,len);
		if (m < 4 || n < 1 || p < 5) {
			output1[i] = 0;
			free(p_in);	
			continue;
		}
		for (ib=4; ib<= m; ib++) {
			ig = p-ib;
			ig = (ig >=1 && ig <=n)? ig:0;
			no_groups += ((ig == 0) ? 0: comb(m,ib)*comb(n,ig));
		}
		//printf("no_groups %f \n",no_groups);
		output1[i] = no_groups;
		free(p_in);	
	}
}

int main(int argc, char*argv[])
{
	int i;
	int input1 = 5;
	GetPlayCount (input1, "(5,2,5),(6,3,6),(8,4,6),(100,1,5),(100,10,51)");
	for (i=0; i<input1; i++)
		printf("output1[%d] = %ld\n",i, (int)output1[i]);	
}

