#ifndef UTILSH
#define UTILSH
#include <stdlib.h>
#include "vec3.h"
#include "aabb.h"

class Utils
{
public:



	static double random_double() {
		return rand() / (RAND_MAX + 1.0);
	}

	static double _drand48(void)
	{
		long long m = 0x100000000LL;
		int c = 0xB16;
		long long a = 0x5DEECE66DLL;
		static unsigned long long seed = 1;
		seed = (a * seed + c) & 0xFFFFFFFFFFFFLL;
		unsigned int x = seed >> 16;
		return ((double)x / (double)m);
	}

	static aabb surrounding_box(aabb box0, aabb box1)
	{
		vec3 small(fmin(box0.min().x(), box1.min().x()),
				   fmin(box0.min().y(), box1.min().y()),
				   fmin(box0.min().z(), box1.min().z()));
		vec3 big(fmax(box0.max().x(), box1.max().x()),
				 fmax(box0.max().y(), box1.max().y()),
				 fmax(box0.max().z(), box1.max().z()));
		return aabb(small, big);
	}
};

#endif