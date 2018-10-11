#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
	char buf[12], buf1[12];
	int hr, newhr;
	char *p, *p1 = NULL, *p2 = NULL;

	scanf("%s", buf);
	// p = strtok(buf,":");
	p = strchr(buf, ':');
	*p =0;
	hr = atoi(buf);
	printf("hr %d p %s \n", hr, p+1);
	p1 = strstr(p+1, "AM");
	p2 = strstr(p+1, "PM");

	if (p1) {
		newhr = (hr == 12)? hr-12 : hr;
		*p1 =0;
	} else if (p2) {
		newhr = (hr == 12)? hr : hr+12;
		*p2 =0;
	}
	printf("hr %d newhr %d p %s \n", hr, newhr, p+1);
	sprintf(buf1, "%02d:%s", newhr, p+1);  		
	printf("%s\n", buf1);
}
