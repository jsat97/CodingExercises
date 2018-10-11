#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_MATCHES 100
#define AVERAGE (5.0)


int output1;

void GetBestBowlerCount(int input1,char* input2)
{
	char **players, *p, *p1, *p_sav;
	int sum, i,j, no_players;
	float average;
	char buf[MAX_MATCHES];

	no_players = input1;
	if (!no_players) {
		output1 =0;	
		return;
	}

	if ( (players =  (char **) malloc(no_players *sizeof(char*))) == NULL) {
		perror("malloc -1");
		exit(2);
	}
	p = strdup(input2);
	p_sav =p;
	p1 = strchr(p, '}');
	*p1 =0;

	for (i=0; i< no_players; i++) {
		
		if ( (players[i] = malloc (MAX_MATCHES *sizeof(char))) == NULL) {
			perror("malloc -2");
			exit(2);
		}
		p++;
		
		p1 =p;
		while (*p && *p != ',') p++;
		*p =0;
		strcpy(players[i], p1);

		//printf("%d player %s\n",i, players[i]);
		sum = 0;
		for (j=0; j< strlen(players[i]); j++) {
			sum += players[i][j] - '0';
		}
		average = sum/(float)(j);
		//printf("%d sum %d matches %d aver %f\n",i, sum, j, average);
		if (average >= AVERAGE) output1++;
	}
	free(p_sav);
	for (i=0; i< no_players; i++) {
		free(players[i]);
	}
	free(players);

}

int main(int argc, char*argv[])
{
	//GetBestBowlerCount(2, "{123456,89359}");
	GetBestBowlerCount(3, "{123456,35,9}");
	printf("count %d\n", output1);
}


