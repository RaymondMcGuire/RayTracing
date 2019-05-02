#ifndef SPHEREH
#define SPHEREH
#include "hitable.h"

class sphere : public hitable
{
public:
    sphere() {}
	sphere(vec3 cen, float r) : center(cen), radius(r) {};
    sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat_ptr(m){};
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const;
    vec3 center;
    float radius;
    material *mat_ptr;
};

#endif