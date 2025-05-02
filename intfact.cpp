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
#include <bits/stdc++.h>
#include "primes.hpp"
#define OFFSET 2
using namespace std;
using namespace boost;

bool isPrime(int x) {
	std::vector<int>::iterator it = std::find(primes.begin(), primes.end(), x);
	if (it == primes.end()) {
		return false;
	} else {
		return true;
	}
	return false;
}

int main(int argc, char* argv[]) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	char* num  = strdup(argv[1]);
	FILE* pi = fopen("./pi.txt","r");
	FILE* e = fopen("./e.txt","r");
	fseek(pi, OFFSET, SEEK_SET);
	fseek(e, OFFSET, SEEK_SET);
	mpz_t nz;
	mpz_init(nz);
	mpz_set_str(nz, num, 10);
	unsigned long long int c = 0, count = 0;
	std::string champernowne = "0";
	std::string factor = "";
	while (1) {
		char* ns = strdup(mpz_get_str(0, 10, nz));
		long int l = strlen(ns);
		fseek(pi, l-1, SEEK_CUR);
		fseek(e, l-1, SEEK_CUR);
		char pp = 0, ee = 0;
		fscanf(pi, "%c", &pp);
		fscanf(e, "%c", &ee);
		char nn = ns[l - 1];
		char test[4];
		test[0] = pp;
		test[1] = nn;
		test[2] = ee;
		test[3] = '\0';
		int tk = atoi(test);
		bool bIsPrime = isPrime(tk);
		if (bIsPrime) {
			long int pos = ftell(pi) - 1;
			while (pos > champernowne.length()) {
			    champernowne += boost::lexical_cast<std::string>(++c);
			}
			long int ll = champernowne.length();
		        if (pos == ll) {
			    char last = champernowne[ll - 1];
			    factor += boost::lexical_cast<std::string>(last-'0');
			    ++count;
			    if (count == l) break;
			    bool bIsPrime_c = isPrime(c);
			    if (bIsPrime_c) {
				    fseek(pi, OFFSET, SEEK_SET);
				    fseek(e, OFFSET, SEEK_SET);
				    mpz_add_ui(nz, nz, 1);
				    continue;
			    }
			} 	
		}
		mpz_add_ui(nz, nz, 1);
	}
	mpz_clear(nz);
	fclose(pi);
	fclose(e);
	gettimeofday(&end, NULL);
	cout << factor << endl;
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
