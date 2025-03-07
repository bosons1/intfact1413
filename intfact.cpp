#include <iostream>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <boost/lexical_cast.hpp>
#include <acb.h>
#include <acb_dirichlet.h>
#include <flint/fmpz.h>
#include <gmp.h>
#include "primes.hpp"
#define PREC 2048
#define TOLERANCE 10
#define OFFSET 2
using namespace std;
using namespace boost;

bool isPrime(int x) {
	std::vector<int>::iterator it = std::find(primes.begin(), primes.end(), x);
	if (it != primes.end()) {
		return true;
	} else {
		return false;
	}
}

int get_index(int x) {
	printf("x %d", x);
	std::vector<int>::iterator it = std::find(primes.begin(), primes.end(), x);
	if (it != primes.end()) {
		int k =  std::distance(primes.begin(), it);
		printf("k %d\n", k);
		return k+1;
	} else {
		return -1;
	}
}

char* get_zero(int zero_index, int prec=PREC) {
	acb_t zeros;
	acb_init(zeros);
	fmpz_t n;
	fmpz_init_set_ui(n, zero_index);
	struct timeval start, end;
	gettimeofday(&start, NULL);
	acb_dirichlet_zeta_zeros(zeros, n, 1, prec);
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	//	printf("Zero generation in %f seconds\n", time_taken);
	arb_t im;
	arb_init(im);
	acb_get_imag(im, zeros);
	char* zero = strdup(arb_get_str((const arb_struct*)im, prec, 0));
	char* ptr = strstr(zero, "+/-");
	*ptr = '\0';
	ptr = strchr(zero,'.');
	zero = ptr + 1;
	acb_clear(zeros);
	fmpz_clear(n);
	arb_clear(im);
	return zero;
}

int main(int argc, char* argv[]) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	string num  = std::string(strdup(argv[1]));
	int l = num.length();
	long long int c = 0;
	FILE* fp = fopen64("./pi.txt","r");
	fseek(fp, OFFSET, SEEK_SET);
	FILE* fe = fopen64("./e.txt","r");
	fseek(fe, OFFSET, SEEK_SET);
	//Terminating condition not known yet
	//Find breakoff point for pi
	//after the breakoff point, 
	//get the appropriate zero 
	//and run it along the digits of pi
	//if "resolution point" fits
	//then accept else reject
	//continue after the breakoff point
	//along the digits of pi 
	//to find the next breakoff point
	//and repeat the process
	//terminate when? will find out TBD 
	char* zero = 0;
	int i = 0;
	long long int zero_pos = 0;
	while (1) {
		while (1) {
			//find the breakoff point along the digits of pi
			char nn = num[c % l];
			char pp = 0;
			fscanf(fp, "%c", &pp);
			char ee = 0;
			fscanf(fe, "%c", &ee);
			char test[4];
			test[0] = pp;
			test[1] = nn;
			test[2] = ee;
			test[3] = '\0';
			i = atoi(test);
			bool bPrime = isPrime(i);
			printf("pp %c nn %c ee %c\n", pp, nn,ee);
			if (bPrime) {
				printf("hit\n");
				cin.get();
				++c;
				break;
			} else {
				++c;
			}
		}
		//found the breakoff point
		//now find fitment along the digits of pi
		//for appropriate zero
		long long int zero_index = get_index(i);
		printf("zero index %lld\n", zero_index);
		char* zero = get_zero(zero_index);
		char target = num[c % l];
		printf("target %c\n", target);
		int lz = strlen(zero);
		long long int zero_pos = 0;
		int iteration = 1;
		while (1) {
			if (zero_pos >= lz) {
				printf("Out of Precision !!\n");
				exit(1);
			}
			char zz = zero[zero_pos++];
			char pp = 0, ee = 0;
			fscanf(fp, "%c", &pp);
		        fscanf(fe, "%c", &ee);
			printf("pp %c zz %c ee %c\n", pp, zz,ee);
			char test[4];
			test[0] = pp;
			test[1] = zz;
			test[2] = ee;
			test[3] = '\0';
			int j = atoi(test);
			bool bPrime = isPrime(j);
			if (bPrime) {
				if (zz == target) {
					printf("iteration %d c  %lld c_l %lld\n", iteration,c, c % l);
					iteration = 0;
					++c;
					cin.get();
					break;
				} else {
                                        zero_index = get_index(j);
					zero = get_zero(zero_index);
		                        printf("zero index %lld\n", zero_index);
					++iteration;
					zero_pos = 0;
					cin.get();
					continue;
				}
			}
		}
					if (c % l == 0 ) break;
	}
	fclose(fp);
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
