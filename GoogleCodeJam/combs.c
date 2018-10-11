/* begin combs.c */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char *S = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
int N, count;
char P[100];

void enumerate(char *P, int K, int n_i) {
    int i;
    if (K == 0)
        printf("%d. %s\n", ++count, P);
    else
        for (i = n_i; i < N; i++) {
            P[strlen(P)+1] = '\0';
            P[strlen(P)] = S[i];
            enumerate(P, K-1, i+1);
            P[strlen(P)-1] = '\0';
        }
}

int main(int argc, char **argv) {
    int M, max = strlen(S);
    if (argc != 3) {
        printf("usage: combs <int M> <int N>\n");
        return 0;
    }
    M = atoi(argv[1]);
    if (M < 1 || M > max) {
        printf("error: M must lie between 1 and %d, inclusive\n", max);
        return 0;
    }
    N = atoi(argv[2]);
    if (N < M || N > max) {
        printf("error: N must lie between %d and %d, inclusive\n", M, max);
        return 0;
    }
    enumerate(P, M, 0);
    return 0;
}

/* end combs.c */

