#include <math.h>
#pragma hdrstop
#include "RandomDouble.h"

void RandomDouble::my_hash(int iters) {
	for (int i = 0; i < iters; i++) {
		z ^= x + y;
		x += z - (y << i + 3);
		y = (y >> 12 - i) ^ x;
		z ^= (x << 36) + (y >> 22);
		y ^= (z >> 12) - (x << 7 + i);
		x ^= (x >> 23) ^ (z + i) - (y - ~i);
	}
}

RandomDouble::RandomDouble(uint64_t seed) {
	x = seed;
	y = 0;
	z = 0;
}

double RandomDouble::nextd() {
	my_hash();
	return double(x >> 12)/(~uint64_t(0) >> 12);
}

double RandomDouble::nextnonzero() {
	my_hash();
	return double((x >> 12) + 1) / (uint64_t(1) << 52);
}

double RandomDouble::nextsignbit() {
	my_hash(3);
	return ((x >> (y & 0xf)) & 1) ? -1 : 1;
}

double RandomDouble::nextsigned() {
	return nextd() * nextsignbit();
}

double RandomDouble::nextlognorm() {
	return -log(nextnonzero());
}

double RandomDouble::nextlognormsigned() {
	return log(nextnonzero()) * nextsignbit();
}