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
#include "pi.hpp"
#include "e.hpp"
#define PREC 131072
#define TOLERANCE 10
using namespace std;
using namespace boost;

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
	char* zero = strdup(arb_get_str((const arb_struct*)im, PREC, 0));
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
	char* zero = get_zero(1);
        long long int zero_pos = 0;
	FILE* fp = fopen64("./pi.txt","r");
	fseeko(fp, 2, SEEK_SET);
	FILE* fe = fopen64("./e.txt","r");
	fseeko(fe, 2, SEEK_SET);
	while (1) {
                 char nn = num[zero_pos % l];
		 char zz = zero[zero_pos];
		 long int zero__ = zeros[zero_pos];
		 printf("zz %c nn %c zero_pos %lld, modulo l %lld\n", zz, nn, zero_pos, zero_pos % l);
		 ++zero_pos;
		 if (nn == zz) {
			 char p_trial = pi[zero__];
			 char e_trial = e[zero__];
			 if (p_trial == nn) {
				 printf("pi hit\n");
			 } 
			 if (e_trial == nn) {
				 printf("e hit\n");
			 }
		 }
		 cin.get();
	}
	fclose(fp);
	fclose(fe);
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	//printf("Total time taken is %f seconds\n", time_taken);
}
