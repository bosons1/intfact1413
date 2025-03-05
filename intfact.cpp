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
#define PREC 2048
#define TOLERANCE 10
#define OFFSET 2
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

int main(int argc, char* argv[]) {
	struct timeval start, end;
	gettimeofday(&start, NULL);
	string num  = std::string(strdup(argv[1]));
	int l = num.length();
	int mid = ceil(l / 2.0);
        long long int zero_pos = 0, c = 0;
	FILE* fp = fopen64("./pi.txt","r");
//	FILE* fe = fopen64("./e.txt","r");
	fseek(fp, OFFSET, SEEK_SET);
	char target = 0;
	//fseek(fe, OFFSET, SEEK_SET);
	while ((c % l) <= mid) {
		printf("Synthesis...\n");
		while (1) {
                 char nn = num[c % l];
		 char pp = 0/*, ee = 0*/;
		 fscanf(fp, "%c", &pp);
		 //fscanf(fe, "%c", &ee);
		 printf("pp %c\t\tnn %c\n", pp, nn);
		 if (pp == nn) {
			 //if (c % l == zero_pos) {
			//	 target = num[(zero_pos + 1)];
			//	 ++zero_pos;
		                 ++c;
				 target = num[c % l];
				 break;
			 //}
		 }
		 ++c;
		}
		printf("\n\nAnalysis...\n");
		char* zero = get_zero(c);
		unsigned long long int m = 0;
		while (1) {
			char nn = zero[m++];
			char pp = 0;
			fscanf(fp, "%c", &pp);
			printf("pp %c\t\tzz %c\n", pp, nn);
			if ((pp == nn) && (pp == target)) {
				break;
			}
		}
		++c;
		printf("\n");
	}
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	//printf("Total time taken is %f seconds\n", time_taken);
}
