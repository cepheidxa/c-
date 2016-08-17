#include <iostream>
#include <cstdlib>
#include <cstring>
#include <gmpxx.h>
#include "bbs.h"

using namespace std;

mpz_class BBS_BASE::operator ()(int bits)
{
	mpz_class ret = 0;
	for(int i = 0; i < bits; i++) {
		mX = mX * mX % mN;
		ret <<= 1;
		ret |= mX % 2;
	}
	return ret;
}

void BBS_BASE::getRand(void *buf, int len)
{
	unsigned long tmp = 0;
	unsigned long *s = reinterpret_cast<unsigned long *>(buf);
	for(int i = 0; i < len / sizeof(unsigned long); i++) {
		tmp = 0;
		for(int j = 0; j < sizeof(unsigned long) * 8; j++) {
			mX = mX * mX % mN;
			tmp <<= 1;
			if(mX % 2 == 1)
				tmp |= 1;
		}
		s[i] = tmp;
	}

	if(len % sizeof(unsigned long)) {
		tmp = 0;
		for(int j = 0; j < len % sizeof(unsigned long); j++) {
			mX = mX * mX % mN;
			tmp <<= 1;
			if(mX % 2 == 1)
				tmp |= 1;
		}
		char *t = reinterpret_cast<char *>(&tmp);
		memcpy((char *)buf + len - len % sizeof(unsigned long), t + sizeof(unsigned long) - len % sizeof(unsigned long), len % sizeof(unsigned long));
	}
}