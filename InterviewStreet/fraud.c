#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define MAX_RECORDS 10240
#define LEN	48
enum {STREET, STATE, CITY};

typedef struct {
	int id;
	int index;
} dealID;

typedef struct {
	int id;
	int fraud;
} orderID;

#define MY_MALLOC(x, y, z) \
	(x) = malloc((z) * sizeof (y));	\
	if ((x) == NULL) {	\
		fprintf(stderr, "malloc failed: size %d\n", z );	\
		exit(1);	\
	}

char (*email)[LEN] ,*email_old;
char (*street)[LEN], *street_old;
char (*city)[LEN], *city_old;
char (*state)[LEN], *state_old;
char (*zip)[LEN], *zip_old;
dealID *deal_id;
orderID *order_id;
uint64_t *cred_card, cred_card_old;
int *fraud_check_indices;


static int
compare(const void *i1, const void *i2)
{
	int val1 = ((dealID*)i1)->id;
	int val2 = ((dealID*)i2)->id;

  return ( (val1 > val2)? 1: (val1 < val2)? -1: 0);
}


//return 0 if email addresses are equivalent, 1 otherwise
int
compare_email(char *e1, char *e2)
{
	char *p1, *p2;
	int flag1 =0, flag2 =0;

	for (p1=e1,p2=e2;  *p1, *p2 ;) {
		if (*p1 == '@' && *p2 == '@') {
			p1++;p2++;
			return(strcasecmp(p1,p2));
		}
		if (flag1 || flag2) {
			if (flag1)  p1++;
			if (flag2)  p2++;
			continue;
		}
		if (*p1 == '+' || *p2 == '+') {
			if (*p1 == '+') flag1 =1;	
			if (*p2 == '+') flag2 =1;	
			continue;
		}
		if (*p1 == '.' || *p2 == '.') {
			if (*p1 == '.') p1++;
			if (*p2 == '.') p2++;
			continue;
		}
		//compare byte before @ here
		if (toupper(*p1) != toupper(*p2)) return 1;
		p1++; p2++;
	}
	//shouldnt come here unless the @ is missing - and we reached end of one (or both) strings
	if (*p1 == 0)
		printf("error! %s has no @ sign \n",e1);
	if (*p2 == 0)
		printf("error! %s has no @ sign \n",e2);
	return 1;
}

int
compare_addr(char *addr1, char *addr2, int mode)
{
	char *p1 , *p2 ;
	char *tmp1 =addr1, *tmp11, *tmp2 =addr2, *tmp22, *ctxt1, *ctxt2;
	//remove spaces in state name (New York = NewYork)
	if (mode == STATE) {
		for (tmp11 =tmp1 = addr1; *addr1;) {
			if (isspace(*addr1)) {
				addr1++;
				continue;
			}
			*tmp1++ = *addr1++;
		}
		*tmp1 =0;
		tmp1 =tmp11;

		for (tmp22 =tmp2 = addr2; *addr2;) {
			if (isspace(*addr2)) {
				addr2++;
				continue;
			}
			*tmp2++ = *addr2++;
		}
		*tmp2 =0;
		tmp2 =tmp22;
	}
	
	//compare each part of addr
	for( ; ; ) {
		p1 = strtok_r(tmp1, " ", &ctxt1);
		p2 = strtok_r(tmp2, " ", &ctxt2);
		tmp1 = NULL;	
		tmp2 = NULL;	
		if (p1 == NULL && p2 == NULL) return 0;
		if (p1 == NULL || p2 == NULL) return 1;
		
		//replace street -> st.
		// Road -> Rd.
		// NewYork -> NY, Illinois ->IL, California -> CA
		if (mode == STREET) {
			if ( !strcasecmp(p1, "St.")) p1 = "Street";  
			if ( !strcasecmp(p2, "St.")) p2 = "Street";
			if ( !strcasecmp(p1, "Rd.")) p1 = "Road";
			if ( !strcasecmp(p2, "Rd.")) p2 = "Road";
		} else if (mode == STATE) {
			if ( !strcasecmp(p1, "NY"))  p1= "NewYork";
			if ( !strcasecmp(p2, "NY"))  p2= "NewYork";
			if ( !strcasecmp(p1, "CA"))  p1= "california";
			if ( !strcasecmp(p2, "CA"))  p2= "california";
			if ( !strcasecmp(p1, "IL")) p1= "illinois";
			if ( !strcasecmp(p2, "IL")) p2= "illinois";
		}
		if (strcasecmp(p1,p2)) return 1;
	}
	return 0;
}


/*
 * more detailed check on the possible fraud entries - we get a bunch of consecutive indices from the sorted array
 * the array was sorted only wrt order_id, so the other values corresponding to a order_id have to be picked from the original index that
 * was tagged with the order_id 
 */
void
verify_fraud(int n)
{
	int i, i1,  j,j1;

	for (i=fraud_check_indices[0]; i<fraud_check_indices[0]+ n-1; i++) {
		for (i1=i+1; i1<fraud_check_indices[0]+n; i1++) {
			j = deal_id[i].index; 	//original index
			j1 = deal_id[i1].index; 	//original index of the value to compare
			if (compare_email(email[j], email[j1])	== 0) {
				order_id[j1].fraud =1; 
				order_id[j].fraud =1; 
			} else if ( (strcasecmp(zip[j], zip[j1]) == 0)  &&
								(compare_addr(city[j], city[j1], CITY)	== 0) && 
								(compare_addr(street[j], street[j1], STREET)	== 0) && 
								(compare_addr(state[j], state[j1], STATE)	== 0)) {
							order_id[j1].fraud =1; 
							order_id[j].fraud =1; 
			}
		}
	}
}

int 
main()
{
	char *p;
	int i, j, j1, deal_id_old;
	int ret, no_records, size;
	int fraud_check_match =0;
	int k =0;

#if 0
	printf("enter email 1 :");
	scanf("%s", email1);
	printf("enter email 2 :");
	scanf("%s", email2);
#endif

	size = MAX_RECORDS;
	MY_MALLOC(email, *email, MAX_RECORDS);
	MY_MALLOC(street, *street, MAX_RECORDS);
	MY_MALLOC(city, *city, MAX_RECORDS);
	MY_MALLOC(state, *state, MAX_RECORDS);
	MY_MALLOC(zip, *zip, MAX_RECORDS);
	MY_MALLOC(deal_id, dealID, MAX_RECORDS);
	MY_MALLOC(order_id, orderID, MAX_RECORDS);
	MY_MALLOC(cred_card, uint64_t, MAX_RECORDS);
	MY_MALLOC(fraud_check_indices, int, MAX_RECORDS);
	
	scanf("%d",&no_records);
	for (i=0; i< no_records; i++) {
		scanf("%d,%d,%48[^,],%48[^,],%48[^,],%48[^,],%48[^,],%llu", &order_id[i].id, &deal_id[i].id, email[i], street[i], city[i], state[i], zip[i], &cred_card[i]);
		//printf("%d,%d,%s,%s,%s,%s,%s,%llu\n",order_id[i].id, deal_id[i].id, email[i], street[i], city[i], state[i], zip[i], cred_card[i]);
		deal_id[i].index =i;
	}

	//sort on order id
	qsort(deal_id, no_records, sizeof(dealID), compare);

	//for (i=0; i< no_records; i++) 
	//	printf("%d %d\n", i,deal_id[i].id);

	//check fraud
	//deal ids are sorted here  and we check in this order
	i=0;
	j = deal_id[i].index; 	//original index
	deal_id_old = deal_id[i].id;
	email_old = email[j];
	state_old = state[j];
	city_old = city[j];
	zip_old = zip[j];
	street_old = street[j];
	cred_card_old = cred_card[j];
	char *comma ="";

	for (i=1; i< no_records; i++) {
		j = deal_id[i].index; 	//original index
		j1 = deal_id[i-1].index; 	//original index of the value before this


		if ( (deal_id_old == deal_id[i].id) && (cred_card[j] != cred_card_old) )	{ //same deal id and diff credit card #
			//save this candidate for fraud check
			fraud_check_indices[k++] = i-1;	
			fraud_check_match =1;
#if 0
			if (compare_email(email[j], email_old)	== 0) {
							order_id[j1].fraud =1; 
							order_id[j].fraud =1; 
			} else if ( (strcasecmp(zip[j], zip_old) == 0)  &&
								(compare_addr(city[j], city_old, CITY)	== 0) && 
								(compare_addr(street[j], street_old, STREET)	== 0) && 
								(compare_addr(state[j], state_old, STATE)	== 0)) {
							order_id[j1].fraud =1; 
							order_id[j].fraud =1; 
			}
#endif
		} else {
			if (fraud_check_match) { //last match index was not saved as we always save i-1 when the match is found at i
				fraud_check_indices[k++] = i-1;	
				// we have a bunch of matches to check further now
				verify_fraud(k);
				k =0;	
			}
			fraud_check_match =0;
		}

		deal_id_old  = 	deal_id[i].id;
		email_old = email[j];
		state_old = state[j];
		city_old = city[j];
		zip_old = zip[j];
		street_old = street[j];
		cred_card_old = cred_card[j];
	}
	for (i=0; i< no_records; i++) {
		if (order_id[i].fraud == 1) {
			printf("%s%d",comma, order_id[i].id);
			comma =",";
		}
	}

}
