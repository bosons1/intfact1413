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
	long long int c = 0;
	FILE* fp = fopen64("./pi.txt","r");
	fseek(fp, OFFSET, SEEK_SET);
	//Terminating condition not known yet
	//Find breakoff point for pi
	//after the breakoff point, 
	//get the appropriate zero 
	//and run it along the digits of pi
	//if "resolution point" fits
	//then accept else reject
	//continue after the breakoff point
	//along the digits of pi 
	//to find the next breakoff point
	//and repeat the process
	//terminate when? will find out TBD 
	while (1) {
		while (1) {
			//find the breakoff point along the digits of pi
			char nn = num[c % l];
			char pp = 0;
			fscanf(fp, "%c", &pp);
			printf("pp %c\t\t nn %c\n", pp, nn);
			if (pp == nn) {
				long int pos = ftello(fp);
				while (pp == nn) {
					++c;
					nn = num[c % l];
					fscanf(fp, "%c", &pp);
					if (pp == nn) {
			                        printf("pp %c\t\t nn %c\n", pp, nn);
						pos = ftello(fp);
					}
				}
				fseeko(fp, pos, SEEK_SET);
				--c;
				nn = num[c % l];
				printf("hit\n");
				break;
			}
		}
		//found the breakoff point
		//now find fitment along the digits of pi
		//for appropriate zero
		long long int zero_index = (c + 1);
		printf("zero index %lld\n", zero_index);
		long int prev_pos = zero_index;
		char target = num[zero_index % l];
		printf("target %c\n", target);
		char* zero = get_zero(zero_index);
		int lz = strlen(zero);
		long long int zero_pos = 0;
		while (1) {
			if (zero_pos >= lz) {
				printf("Out of Precision !!\n");
				exit(1);
			}
			char zz = zero[zero_pos++];
			char pp = 0;
			fscanf(fp, "%c", &pp);
			printf("pp %c zz %c\n", pp, zz);
			if (pp == zz) {
				long int pos = ftello(fp);
				while (pp == zz) {
					zz = zero[zero_pos++];
					fscanf(fp, "%c", &pp);
					if (pp == zz) {
			                        printf("zz %c\t\t pp %c\n", zz, pp);
						pos = ftello(fp);
					}
				}
				fseeko(fp, pos, SEEK_SET);
				--zero_pos;
				zz = zero[zero_pos % l];
				printf("hit\n");
				if (pp == target) {
					c += 2; 
					printf("Goal reached");
					cin.get();
				} else {
					printf("Goal Missed");
					c = zero_index;
					fseeko(fp, zero_index, SEEK_SET);
				}
				break;
			}
		}
	}
	fclose(fp);
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
