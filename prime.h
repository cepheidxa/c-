#ifndef PRIME_H_H_H
#define PRIME_H_H_H

#include <gmpxx.h>

class PrimeGenerator {
public:
	mpz_class operator()(int bits);
};
#endif
