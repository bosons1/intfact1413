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
#include "zeros.hpp"
#include "primes.hpp"
#define PREC 8192
#define TOLERANCE 10
#define OFFSET 2
using namespace std;
using namespace boost;

bool isZero(int x, int& d) {
	std::vector<int>::iterator it = std::find(zeros.begin(), zeros.end(), x);
	if (it != zeros.end()) {
		d = std::distance(zeros.begin(), it) + 1;
		return true;
	} else {
		return false;
	}
}

bool isPrime(int x, int& d) {
	std::vector<int>::iterator it = std::find(primes.begin(), primes.end(), x);
	if (it != primes.end()) {
		d = std::distance(primes.begin(), it) + 1;
		return true;
	} else {
		return false;
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

void* characterize(std::string num, std::string& ps, std::string& es) {
	FILE* pi = fopen64("./pi.txt", "r");
	fseeko(pi, OFFSET, SEEK_SET);
	FILE* e = fopen64("./e.txt","r");
	fseeko(e, OFFSET, SEEK_SET);
	unsigned long long int c = 0;
	long l = num.length();
	char nn = num[c % l];
	int snippet = 0,current_pos=0;
	while (1) {
		char pp = 0, ee = 0;
		fscanf(pi, "%c", &pp);
		fscanf(e, "%c", &ee);
		ps+=boost::lexical_cast<std::string>(pp-'0');
		es+=boost::lexical_cast<std::string>(ee - '0');
		if (pp == nn) {
			char test[4];
			test[0] = pp;
			test[1] = '7';
			test[2] = ee;
			test[3] = '\0';
			int tk = atoi(test);
			int d = 0;
			bool bIsPrime = isPrime(tk, d);
			if (bIsPrime) {
				++c;
				if (c % l == 0) break;
				nn = num[c % l];
			}
		}
	}
	fclose(pi);
	fclose(e);
	return 0;
}

char* factorize(std::string ss) {
	cout << ss << endl;
	return 0;
}

int main(int argc, char* argv[]) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	string num  = std::string(strdup(argv[1]));
	int l = num.length();
	std::string ps = "";
	std::string es = "";
	characterize(num, ps, es);
	char* factor1 = factorize(ps);
	char* factor2 = factorize(es);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
