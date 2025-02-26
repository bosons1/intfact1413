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
#define PREC 65536
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
	zero = ptr - 1;
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
	string rnum = string(num);
	std::reverse(rnum.begin(), rnum.end());
	int l = num.length();
	long long int c = 0;
	char* zero1 = get_zero(1);
	char* zero2 = get_zero(2);
	int lz = strlen(zero1);
	long int zc1 = 0, zc2 = 0;
	char zz1 = 0, zz2 = 0;
	char nn = num[c % l];
	char rnn = rnum[c % l];
	while (1) {
		 fscanf(pi, "%c", &pp);
		 if (pp == '.') {
			 fscanf(pi, "%c", &pp);
		 }
		 if (zc1 >= lz) {
			 printf("Out of precision!!\n");
			 exit(0);
		 }
		 zz1 = zero1[zc1++];
		 if (zz1 == '.') {
			 zz1 = zero1[zc1++];
		 }
		 zz2 = zero2[zc2++];
		 if (zz2 == '.') {
			 zz2 = zero2[zc2++];
		 }
		 fscanf(e, "%c", &ee);
		 if (ee == '.') {
			 fscanf(e, "%c", &ee);
		 }
		 printf("pp %c ee %c zz1 %c zz2 %c\n", pp, ee, zz1, zz2, (c+1) % l);
		 if ((pp == rnn) && (ee == nn)) {
			 ++c;
			 nn = num[c % l];
			 rnn = rnum[c % l];
			 cin.get();
		 }
	}
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	//printf("Total time taken is %f seconds\n", time_taken);
}
