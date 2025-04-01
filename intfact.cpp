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
	if (it != zeros.end()) {
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
}

char* factorize(std::string ss) {
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
