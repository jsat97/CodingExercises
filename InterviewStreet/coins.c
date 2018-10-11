#include <stdio.h>
#include <stdlib.h>

#define MAX_COINS 3
int
main()
{
	int i, sum, ncoins, coin_val[MAX_COINS];
	int *Sum, *nCoins;

	printf("enter # of coins :");
	scanf("%d",&ncoins);
	printf("enter Sum :");
	scanf("%d",sum);

	printf("enter coin denominations :");
	for (i=0; i<ncoins; i++)
		scanf("%d", &coin_val[i]);
	
	nCoins = malloc(sum *sizeof(int));

	for (i=1; i<sum; i++)
		for (j=0; j<ncoins; j++)
		if (coin_val[j] < i) 
			nCoins[i] = 
