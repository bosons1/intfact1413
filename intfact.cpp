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
#define PREC 8192
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
	FILE* pi = fopen("./pi.txt","r");
	char pp = 0, ee = 0;
	fscanf(pi, "%c", &pp);
	fscanf(pi, "%c", &pp);
	FILE* e = fopen("./e.txt","r");
	fscanf(e, "%c", &ee);
	fscanf(e, "%c", &ee);
	string num  = std::string(strdup(argv[1]));
	string rnum = num;
	std::reverse(rnum.begin(), rnum.end());
	int l = num.length();
	long long int c = 0;
	char nn = num[c % l];
	char rnn = rnum[c % l];
	printf("Length of String %d\n", l);
	while (1) {
		 fscanf(pi, "%c", &pp);
		 fscanf(e, "%c", &ee);
//		 printf("pp %c ee %c\n",pp, ee);
		 if (pp == rnn && ee == nn) {
			 ++c;
			 printf("k %ld\t\tc % lld\t,", ftell(pi)-2, c % l);
			 nn = num[c % l];
			 rnn = rnum[c % l];
			 if (c % l == 0) {
				 cin.get();
			 }
		 }
	}
	fclose(pi);
	fclose(e);
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
