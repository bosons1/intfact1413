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
#include <bits/stdc++.h>
#define PREC 65536
#define TOLERANCE 10
#define OFFSET 2
using namespace std;
using namespace boost;


map<int, string> dict;
char* get_zero(int zero_index, int prec=PREC) {
	if (dict.contains(zero_index)) {
		return strdup((char*)dict[zero_index].c_str());
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
	//	printf("Zero generation in %f seconds\n", time_taken);
	arb_t im;
	arb_init(im);
	acb_get_imag(im, zeros);
	char* zero = strdup(arb_get_str((const arb_struct*)im, prec, 0));
	char* ptr = strstr(zero, "+/-");
	*ptr = '\0';
	ptr = strchr(zero,'.');
	zero = ptr + 1;
        std::string zs = string(zero);
	dict[zero_index] = zs;
	acb_clear(zeros);
	fmpz_clear(n);
	arb_clear(im);
	return zero;
}

bool isZero(int x) {
	std::vector<int>::iterator it = std::find(zeros.begin(), zeros.end(), x);
	if (it == zeros.end()) {
		return false;
	} else {
		return true;
	}
	return false;
}

int main(int argc, char* argv[]) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	string num  = std::string(strdup(argv[1]));
	int l = num.length();
	int zero_index = 1;
	char* zero = get_zero(zero_index);
	unsigned long long int zero_pos = 0, c = 0;
	FILE* pi = fopen64("./pi.txt","r");
	fseek(pi, OFFSET, SEEK_SET);
	FILE* e = fopen64("./e.txt","r");
	fseek(e, OFFSET, SEEK_SET);
	while (1) {
		char zz = zero[zero_pos];
		char nn = num[c % l];
		++c;
		zero_index = zero_index + 1;
		zero = get_zero(zero_index);
		char pp = 0, ee = 0;
		fscanf(pi, "%c", &pp);
		fscanf(e, "%c", &ee);
		if (nn == zz) {
				char test[3];
				test[0] = pp;
				test[1] = ee;
				test[2] = '\0';
				int tk = atoi(test);
				bool bIsZero = isZero(tk);
				if (bIsZero) {
					if (pp == ee) {
		printf("pos %ld zz %c nn %c c_l %lld pp %c ee %c\n", ftello(pi)-OFFSET,zz, nn, c % l, pp, ee);
					printf("Press any key to continue...\n");
					cin.get();
					}
				}
			zero_index = 1;
			zero_pos = c;
			zero = get_zero(zero_index);
                        continue;
		}
	}
	fclose(pi);
	fclose(e);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
