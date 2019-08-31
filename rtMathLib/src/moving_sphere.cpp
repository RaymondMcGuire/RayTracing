#include "moving_sphere.h"

bool moving_sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const
{
    vec3 oc = r.origin() - center(r.time());
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - a * c;
    if (discriminant > 0)
    {
        float temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }

        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center(r.time())) / radius;
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

vec3 moving_sphere::center(float time) const
{
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::bounding_box(float t0, float t1, aabb &box) const
{
    aabb box0(center(t0) - vec3(radius, radius, radius), center(t0) + vec3(radius, radius, radius));
    aabb box1(center(t1) - vec3(radius, radius, radius), center(t1) + vec3(radius, radius, radius));
    box = Utils::surrounding_box(box0, box1);
    return true;
}