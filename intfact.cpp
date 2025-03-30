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
#define PREC 16384
#define TOLERANCE 10
#define OFFSET 2
using namespace std;
using namespace boost;

bool isZero(int x, int& d) {
	std::vector<int>::iterator it = std::find(zeros.begin(), zeros.end(), x);
	if (it != zeros.end()) {
		d = std::distance(zeros.begin(), it) + 1;
		return true;
	} else {
		return false;
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
	char nn = 0;
	unsigned long long int sum = 0;
	unsigned long long int c = 0, k = 0;
	vector<unsigned long long int>* position = new vector<unsigned long long int>();
	vector<unsigned long long int>* summation = new vector<unsigned long long int>();
	while (k < 14*l) {
		char nn = num[c % l];
		sum += (nn - '0');
		int d = 0;
		bool bIsZero = isZero(sum, d);
		++c;
		if (bIsZero) {
			position->push_back(c);
			summation->push_back(d);
			if (c % l == 0) {
				for (int j = 0; j < position->size(); ++j) {
					int index = summation->at(j);
					char* zero = get_zero(index);
					char zz = zero[position->at(j)-1];
					if (zz == '0') ++k;
					cout << zz << ",";
					if (k == l) exit(0);
				}
				cout << endl;
				position=new vector<unsigned long long int>();
				summation=new vector<unsigned long long int>();
			}
		}
	}
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
