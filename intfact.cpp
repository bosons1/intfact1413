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
	int mid =  ceil((l*1.0)/2);
	long long int c = 0;
	char* zero1 = get_zero(1);
	char* zero2 = get_zero(2);
        long long int zero_pos = 0;
	long long int numerator_sum = 0, denominator_sum = 0;
	long long int numerator_count = 0, denominator_count = 0;
	long long int total_count = 0;
	while (c < mid) {
                 char nn = num[zero_pos % l];
		 char zz1 = zero1[zero_pos];
		 char zz2 = zero2[zero_pos++];
		 printf("zz1 %c nn %c zz2 %c zero_pos %lld\n", zz1, nn, zz2, zero_pos % l);
		 if (nn == zz1) {
			 printf("Hit 1  %c\n", nn);
			 numerator_sum += (nn-'0');
			 numerator_count++;
			 total_count++;
		 } 
		 if (nn == zz2) {
			 printf("hit 2 %c\n", nn);
			 denominator_sum += (nn-'0');
			 denominator_count++;
			 total_count++;
		 }
		 if (nn == zz2 && nn == zz1) {
			 printf("numerator sum %lld\t\tdenominator sum %lld\n", numerator_sum, denominator_sum);
			 printf("numerator count %lld\t\tdenominator count %lld\n", numerator_count, denominator_count);
			 printf("total count %lld\n", total_count);
			 total_count = numerator_count = denominator_count = 0;
			 numerator_sum = denominator_sum = 0;
			 printf("Common Hit %c\n", nn);
			 ++c;
			 if (c >= mid) {
				 break;
			 }
		 }
		 cin.get();
	}
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	//printf("Total time taken is %f seconds\n", time_taken);
}
