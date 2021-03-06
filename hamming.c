#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define MAX(X, Y) ((X > Y) ? X : Y)

int check_binary(char *string);
int power_of_2(int x);
void add_parity_space(char *string);
void remove_parity_space(char *string);
void calculate_parity(char *string);
void alter_a_bit(char* string);
int *bad_parity(char* string);

void print_usage (void) {
	printf("usage: hamming <binary string>\n");
	printf("ex:    hamming \"10011010\"\n");
}

int main (int argc, char *argv[], char *arge[]) {
	if (argc < 2) {
		print_usage();
		return 0;
	}
	
	// check if argv[1] is a binary string
	if (!check_binary(argv[1])) {
		fprintf(stderr, "%s is not a binary string\n", argv[1]);
		return -1;
	}
	
	// init rand()
	srand(time(NULL));
	
	// copy the argv[1] message
	// calculate final message length
	// so we don't need to realloc it everytime
	int len = strlen(argv[1]);
    int parity_len = 2;
    for (int i = 0; i<=len; i++) {
        //printf("t:%d - %s\n",t,power_of_2(t+1) ? "YES" : "NO");
        parity_len++;
        if (power_of_2(parity_len)) {
            parity_len++;
        }
    }
    printf("F2^%d -> F2^%d\n",len, parity_len-1);
	char *message = (char*)malloc(parity_len*sizeof(char));
	strncpy(message, argv[1], len+1);
	
	// print the raw binary message
	printf("[•] encoding   '%s' (len:%d)\n",message,len);
	
	// then add spaces for parity bits
	// and calculate them
	add_parity_space(message);
	calculate_parity(message);
	printf("[•] sent       '%s' (len:%d)\n",message,(int)strlen(message));
	
	// copy the message and alter one bit
	char *bad = (char*)malloc(strlen(message)*sizeof(char));
	strncpy(bad, message, strlen(message));
	alter_a_bit(bad);
	
	// print altered message
	printf("[•] recieve    '%s' (len:%d)\n",bad,(int)strlen(bad));
	
	// check parity to correct the altered message
	int *bad_bits = bad_parity(bad);
	int i = 0, sum=0;
	printf("[?] corrupted parity bits :");
	while (bad_bits[i] != -1) {
		sum+=bad_bits[i]+1;
		printf(" %d",bad_bits[i]+1);
		i++;
	}
	printf("\n");
	printf("[?] fixed data bit at index %d\n",sum);
	free(bad_bits);
	
	// correct if necessary
	if (sum>0) {
		bad[sum-1] = (bad[sum-1] == '0') ? '1' : '0';
		printf("[•] corrected  '%s' (len:%d)\n",bad,(int)strlen(bad));
	}else {
		printf("[•] already_ok '%s' (len:%d)\n",bad,(int)strlen(bad));
	}
	
	// remove the parity bits
	remove_parity_space(bad);
	printf("[•] decoding   '%s' (len:%d)\n",bad,(int)strlen(bad));
	
	// compare with original message
	printf("[•] %s\n",strncmp(argv[1],bad,len) == 0 ? "message successfully decoded" : "failed to decode message");
    
    //printf(" in: '%s'\n",argv[1]);
    //printf("out: '%s'\n",bad);
	
	// free memory space
	free(message);
	free(bad);
	
	return 0;
}

int check_binary(char *string) {
	int i = 0;
	for (i=0; i<strlen(string); i++) {
		if (string[i] != '0' && string[i] != '1') {
			return 0;
		}
	}
	return 1;
}

int power_of_2 (int x) {
  return ((x != 0) && !(x & (x - 1)));
}

void add_parity_space(char *string) {
	int i,j, len=strlen(string);
	for (i=0; i<len; i++) {
		if (power_of_2(i+1)) {
			len+=1;
			for (j = len-1 ; j>i; j--) {
				string[j]=string[j-1];
			}
			string[i]='0';
			string[len] = '\0';
		}
	}
}

void remove_parity_space(char *string) {
	int i = 0, j=0;
	char *data = (char*)malloc(strlen(string)*sizeof(char));
	for (i=0; i<strlen(string); i++) {
		if (!power_of_2(i+1)) {
			data[j]=string[i];
			j++;
		}
	}
	for (i = 0; i < strlen(string); i++) {
		if (i<j)
			string[i]=data[i];
		else 
			string[i]='\0';
	}
	free(data);
}

void calculate_parity(char *string) {
	int i = 0, j = 0, k = 0, parity;
	for (i=0; i<strlen(string); i++) {
		if (power_of_2(i+1)) {
			j=i;
			parity = 0;
			//printf("check bit %d :",i+1);
			while (j<strlen(string)) {
				for (k=j; k < j+i+1; k++) {
					if (k >= strlen(string) || k==i) {continue;}
					//printf(" %d",k+1);
					parity = (parity+string[k])%2;
				}
				j=k+i+1;
			}
			string[i]=(parity == 0) ? '0' : '1';
			//printf("\n");
		}
	}
	
}

void alter_a_bit(char* string) {
	int index = rand()%strlen(string);
	string[index] = (string[index] == '0') ? '1' : '0';
}

int *bad_parity(char* string) {
	int i=0, j=0, len=strlen(string);
	int *bad_parity = (int *)malloc(sizeof(int));
	char *check = (char*)malloc(len*sizeof(char));
	
	bad_parity[0] = bad_parity[1] = -1;
	strncpy(check, string, len);
	calculate_parity(check);
	//printf("[•] parity_ck '%s' (len:%d)\n",check,(int)strlen(check));
	
	// compare all parity bits
	for(i=0; i<len; i++) {
		if (power_of_2(i+1) && string[i] != check[i]) {
			int *tmp = (int *)realloc(bad_parity, j+1*sizeof(int));
			if (tmp) {bad_parity = tmp;}
			bad_parity[j] = i;
			bad_parity[j+1] = -1;
			j++;
		}
	}
	
	free(check);
	return bad_parity;
}
