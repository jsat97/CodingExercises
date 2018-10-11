#include <stdio.h>
#include <string.h>

int match_index_arr[11][100000];		//10 cases, 100000 each
int icase =0;
int no_match_arr[10];	//total # of matches for each case

//return index in s where a fuzzy match occurs
//match t with s at each point in s and return all match indices
// fuzzy -> at most 1 char mismatch, the actual string is s, pattern is t
int
fuzzy_strncmp(char *s, int len, char* t, int n)
{
	int i,j, ret;
	int  found;
	static int match_index =0, match=0, index_count =0;
	int	fuzz_done =0;
	
	//int s_len = strlen(s);
	char *ps, *pt =t;

	if (len < n) {
		index_count =0;
		match_index =0;
		ret = match;
		match =0;
		return ret;
	}
	found =1;
	for (ps=s; *pt; ps++, pt++) { 
		if (*ps == *pt) {
			continue;	
		} else {
			if (fuzz_done) {
				found =0;	
				break;
			} else {
				fuzz_done=1;
			}
		}
	}
	if (found) {
		//printf("match at index %d \n", match_index);
		match_index_arr[icase][index_count++] = match_index;
		match++;
	//} else {//the fuzz did nt result in a match, so set it back to 0 
	//	fuzz_done=0;
	}
	
	match_index++;
	s++;
	return(fuzzy_strncmp(s, len-1, t, n)); 
}


int
main()
{
	char s[100000], t[100000], temp[1];
	int i, j, ret, ncases;
	scanf("%d", &ncases);
	for (i=0; i<ncases; i++) {
		scanf("%s", s);
		scanf("%s", t);
		fgets(temp, sizeof(temp), stdin);
		no_match_arr[i] = fuzzy_strncmp(s,strlen(s),t,strlen(t));	
		//printf("no_match_arr %d\n",no_match_arr[i]);
		icase++;
	}

	for (i=0; i<ncases; i++) {
		for (j=0; j<no_match_arr[i]; j++) {
			printf("%d%s",match_index_arr[i][j], (j==no_match_arr[i]-1)? "":" ");
		}
		if (i != ncases-1)
			printf("\n");
	}

	//printf("no of matches  %d\n", ret);

}
