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
#include "pi.hpp"
#include "e.hpp"
#include "primes.hpp"
#define PREC 4096
#define TOLERANCE 10
using namespace std;
using namespace boost;

bool in(int ctr, vector<int> primes) {
      vector<int>::iterator it = std::find(primes.begin(), primes.end(), ctr);
      if (it == primes.end()) {
	      return false;
      } else {
	      return true;
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
	FILE* pi = fopen("./pi.txt","r");
	char pp = 0, ee = 0;
	FILE* e = fopen("./e.txt","r");
	string num  = std::string(strdup(argv[1]));
	int l = num.length();
	long long int c = 0, pos = 0, zero_pos = 0;
	int mid = ceil((l*1.0)/2);
	int zero_index = 1;
	char* zero = get_zero(zero_index);
	int prev_zero_index = 0;
	while (c < mid) {
                 char nn = num[pos % l];
		 char zz = zero[zero_pos++];
		 fscanf(pi, "%c", &pp);
		 if (pp == '.') {
			 fscanf(pi, "%c", &pp);
		 }
		 fscanf(e, "%c", &ee);
		 if (ee == '.') {
			 fscanf(e, "%c", &ee);
		 }
                 ++pos;
		 if (nn == zz) {
			 int prev_pos = pos;
			 while (nn == zz) {
				 nn = num[pos % l];
				 zz = zero[zero_pos++];
				 if (nn == zz){
				 ++pos;
				 }
			 }
			 int d = pos - prev_pos;
			 for (int i = 0; i < d; ++i) {
				 fscanf(pi, "%c", &pp);
				 if (pp == '.') {
					 fscanf(pi, "%c", &pp);
				 }
				 fscanf(e, "%c", &ee);
				 if (ee == '.') {
					 fscanf(e, "%c", &ee);
				 }
			 }
			 if (pos > 0 && pos % l == 0) {
				 int delta = zero_index - prev_zero_index;
				 prev_zero_index = zero_index;
				 char pp1[3], pp2[3];
				 pp1[0] = pp;
				 pp1[1] = ee;
				 pp1[2] = '\0';
				 pp2[0] = ee;
				 pp2[1] = pp;
				 pp2[2] = '\0';
				 int ctr1 = atoi(pp1);
				 int ctr2 = atoi(pp2);
				 if (in(ctr1, primes) || in(ctr2, primes)) {
					 //synthesis
					 printf("\nSynthesis Delta %d\n", delta);
					 ++c;
				 } else {
					 //analysis
					 printf("\nAnalysis Delta %d\n", delta);
				 }
			 }
			 ++zero_index;
			 zero = get_zero(zero_index);
			 zero_pos = 0;
		 }
	}
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	//printf("Total time taken is %f seconds\n", time_taken);
}
