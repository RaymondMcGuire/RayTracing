#ifndef PERLINH
#define PERLINH

#include "vec3.h"
#include "utils.h"

class perlin
{
public:
	perlin(){}
	float noise(const vec3 &) const;
	float perlin::turb(const vec3&, int = 7) const;
        static vec3 *ranvec;
        static int *perm_x;
        static int *perm_y;
        static int *perm_z;
};

#endif