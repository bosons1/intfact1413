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
	FILE* fp = fopen64("./pi.txt","r");
	fseek(fp, OFFSET, SEEK_SET);
	FILE* fe = fopen64("./e.txt","r");
	fseek(fe, OFFSET, SEEK_SET);
	unsigned long long int c = 0;
	while (1) {
		bool bValidated = false;
		int target = 0;
		unsigned long long int count = 0;
		while (1) {
			char pp = 0, ee = 0;
			fscanf(fp, "%c", &pp);
			fscanf(fe, "%c", &ee);
			char nn = num[count % l];
			char test[4];
			test[0] = pp;
			test[1] = nn;
			test[2] = ee;
			test[3] = '\0';
			long long i = atoi(test);
			bool bPrime = isPrime(i);
			printf("pp %c ee %c nn %c\n", pp, ee, nn);
			if (bPrime) {
				printf("Prime\n");
				if (count % l == target){
					target++;
					if (target == l) {
						bValidated = true;
						break;
					}
				} else {
					bValidated = false;
					break;
				}
			}
			++count;
		}
		++c;
		printf("validated %d\n", bValidated);
		if (bValidated == true) {
			printf("c %lld\n", c);
			cin.get();
		}
		if (bValidated) {
			//measure it with a zero
		}
		fseek(fp, OFFSET + c, SEEK_SET);
		fseek(fe, OFFSET + c, SEEK_SET);
		printf("\n\n\n");
	}
	fclose(fp);
	fclose(fe);
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
