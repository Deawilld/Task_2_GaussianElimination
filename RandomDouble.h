#include "stdint.h"

class RandomDouble {
	uint64_t x;
	uint64_t y;
	uint64_t z;

private:
	void my_hash(int iters = 10);

public:
	RandomDouble(uint64_t seed);

	double nextd();
	double nextnonzero();

	double nextsignbit();

	double nextsigned();

	double nextlognorm();
	double nextlognormsigned();
};