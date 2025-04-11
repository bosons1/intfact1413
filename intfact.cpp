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
#include <bits/stdc++.h>
#define PREC 16384
#define TOLERANCE 10
#define OFFSET 2
using namespace std;
using namespace boost;


map<int, char*> dict;
char* get_zero(int zero_index, int prec=PREC) {
	if (dict.contains(zero_index)) {
		return dict[zero_index];
	}
	acb_t zeros;
	acb_init(zeros);
	fmpz_t n;
	fmpz_init_set_ui(n, zero_index);
	struct timeval start, end;
	gettimeofday(&start, NULL);
	acb_dirichlet_zeta_zeros(zeros, n, 1, prec);
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Zero generation in %f seconds\n", time_taken);
	arb_t im;
	arb_init(im);
	acb_get_imag(im, zeros);
	char* zero = strdup(arb_get_str((const arb_struct*)im, prec, 0));
	char* ptr = strstr(zero, "+/-");
	*ptr = '\0';
	ptr = strchr(zero,'.');
	zero = ptr + 1;
	dict[zero_index] = zero;
	acb_clear(zeros);
	fmpz_clear(n);
	arb_clear(im);
	return zero;
}

bool isZero(int x, int& d) {
	std::vector<long long int>::iterator it = std::find(zeros.begin(), zeros.end(), x);
	if (it == zeros.end()) {
		return false;
	} else {
		d = std::distance(zeros.begin(), it);
		return true;
	}
	return false;
}

bool isPrime(int x, int& d) {
	std::vector<int>::iterator it = std::find(primes.begin(), primes.end(), x);
	if (it == primes.end()) {
		return false;
	} else {
		d = std::distance(primes.begin(), it);
		return true;
	}
	return false;
}

void* characterize(string num, int divisor, std::string& ss) {
   int sum1 = 0;
   long int c = 0;
   long int l = num.length();
   int count = 0;
   while (1) {
	   char nn = num[c % l];
	   int nk = nn - '0';
	   sum1 += nk;
	   ++c;
	   if (sum1 > 0 && sum1 % divisor == 0) {
		   count = sum1 / divisor;
		   ss += boost::lexical_cast<std::string>(count % 10);
		   sum1 = 0;
                   if (c % l == 0) {
			   break;
		   }
	   }
   }
   return 0;
}

int main(int argc, char* argv[]) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	string num  = std::string(strdup(argv[1]));
	int l = num.length();
	std::string c17 = "";
	std::string c29 = "";
	characterize(num, 17, c17);
	characterize(num, 29, c29);
	cout << c17 << endl;
	cout << c29 << endl;
	int d1 = 0;
	bool bIsZero1 = isZero(atoi((char*)c17.c_str()), d1);
	cout << "d1 " << d1 << endl;
	int d2 = 0;
	bool bIsZero2 = isZero(atoi((char*)c29.c_str()), d2);
	cout << "d2 " << d2 << endl;
	int zero_index = d1;
	char* zero = get_zero(zero_index);
	FILE* pi = fopen64("./pi.txt","r");
	fseeko(pi, OFFSET, SEEK_SET);
	FILE* e = fopen64("./e.txt","r");
	fseeko(e, OFFSET, SEEK_SET);
	unsigned long long int zero_pos = 0;
	unsigned long long int c = 0;
	while (1) {
		char pp = 0, ee = 0;
		fscanf(pi, "%c", &pp);
		fscanf(e, "%c", &ee);
		char zz = zero[zero_pos++];
		char test[4];
		test[0] = pp;
		test[1] = zz;
		test[2] = ee;
		test[3] = '\0';
		int tk = atoi(test);
		int d =0;
		bool bIsPrime1 = isPrime(tk, d);
		test[0] = ee;
		test[2] = pp;
		tk = atoi(test);
		bool bIsPrime2 = isPrime(tk, d);
		++c;
		if (bIsPrime1 && bIsPrime2) {
			printf("zz %c\n", zz);
			if (c % l == 0) break;
		}
	}
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
