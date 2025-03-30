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
#define PREC 2048
#define TOLERANCE 10
#define OFFSET 2
using namespace std;
using namespace boost;

bool isZero(int x) {
	std::vector<int>::iterator it = std::find(zeros.begin(), zeros.end(), x);
	if (it != zeros.end()) {
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
	vector<vector<unsigned long long int>* > posits;
	vector<vector<unsigned long long int>* > sums;
	vector<unsigned long long int>* position = new vector<unsigned long long int>();
	vector<unsigned long long int>* summation = new vector<unsigned long long int>();
	while (k < l) {
		char nn = num[c % l];
		sum += (nn - '0');
		bool bIsZero = isZero(sum);
		++c;
		if (bIsZero) {
			position->push_back(c);
			summation->push_back(sum);
			if (c % l == 0) {
				posits.push_back(position);
				sums.push_back(summation);
				position=new vector<unsigned long long int>();
				summation=new vector<unsigned long long int>();
				++k;
			}
		}
	}
	for (int i = 0; i < posits.size(); ++i) {
		for (int j = 0; j < posits[i]->size();++j) {
			cout << posits[i]->at(j) << ",";
		}
		cout << endl;
	}
	cout << endl;
	gettimeofday(&end, NULL);
	double time_taken = (end.tv_sec-start.tv_sec) + (end.tv_usec-start.tv_usec) / 1e6;
	printf("Total time taken is %f seconds\n", time_taken);
}
