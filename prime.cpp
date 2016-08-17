#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <gmpxx.h>
#include "prime.h"

using namespace std;

#define RANDOM_DEV "/dev/urandom"

mpz_class PrimeGenerator::operator ()(int bits)
{
	int len = (bits + sizeof(unsigned long) - 1) / sizeof(unsigned long);
	unsigned long *p = new unsigned long[len];
	assert(p != NULL);
	mpz_class prime;
	
	int fd = open(RANDOM_DEV, O_RDONLY);
	assert(fd != -1);
	
	do {
		prime = 0;
		int ret = read(fd, p, len * sizeof(unsigned long));
		assert(ret == sizeof(unsigned long));
		for(int i = 0; i < len; i++) {
			prime <<= sizeof(unsigned long);
			prime |= p[i];
		}
		prime |= 1;
	} while(mpz_probab_prime_p(prime.get_mpz_t(), 100) == 0);
	close(fd);
	delete[] p;
	return prime;
}
