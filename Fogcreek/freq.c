/*
 * @brief solve problem posted on Fog Creek website for tech support position
 *
 * make freq (on mac or linux)
 * ./freq inp (execute)
 * @author Jai 9-Nov-15 (jai_97@rediffmail.com)
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

// get frequency of occurence of each char in given string, in the input text file
char string[] = "abcdefghijklmnopqrstuvwxyz_";

int hist[27];
int str_index[27];

// need descending order, so reverse the usual logic of < and > when comparing arg1 and arg2
int 
compare(const void *a, const void *b) 
{
	int i= *(int*)a;
	int j= *(int*)b;
	int cmp;

	cmp = hist[j]-hist[i];
	return cmp;
}


int 
main(int argc, char *argv[])
{
	int i, j, len, slen, buflen =0, off =0;	
	char line[1024];
	char buf[4096];
	char *file;
	FILE *fp;
	char answer[27];		// doesnt include _, so 1 less + null

	if (argc != 2) {
		fprintf(stderr, "%s <input file>\n", argv[0]);
		return 1;	
	}
	file = argv[1];
	if ( (fp = fopen(file, "r")) == NULL) {
		fprintf(stderr, "open %s failed\n", file);
		return 1;
	}
		
	// read the text into a buffer
	while (1) {
		if (fgets(line, sizeof(line), fp) == NULL) {
			if (feof(fp)) 
				break;
			fprintf(stderr, "error reading input \n");
			return 1;	
		}
		// remove \n at the end
		len = strlen(line);  
		assert(line[len-1] == '\n');
		line[len -1] = 0;
#if DEBUG
		printf("len %d line %s\n", len, line);
#endif
		strncpy(buf+off, line, len-1);
		off += len-1;
		buflen += len-1;
	}

#if DEBUG
	printf("buflen %d last byte %c\n", buflen, buf[buflen-1]);
#endif

	// scan the buffer
	slen = strlen(string);
	for (i=0; i<buflen; i++) {
		for (j=0; j<slen; j++) {		//could be avoided if the whole string is in collation sequence
			if (string[j] == buf[i]) {	
				// hist[buf[i]-'_']++;
				hist[j]++;
				break;
			}
		}
	}
#if DEBUG
	// print frequencies
	for (i=0; i<slen; i++) {
		printf("%c %d\n", string[i], hist[i]);
	}
#endif

	// sort the string index array based on the hist - this is an array whose values are the indices of the string
	for(i=0; i<slen; i++)
		str_index[i] = i;

	qsort(str_index, slen, sizeof(int), (int(*) (const void*, const void*))compare);

	for (i=0; i<slen; i++) {
#if DEBUG
		printf("%d", str_index[i]);
		printf("%c", string[str_index[i]]);
#endif
		answer[i] = string[str_index[i]];
		if (answer[i] == '_') {
			answer[i] = 0;
			break;
		}
	}
	printf("%s\n", answer);
	
}
