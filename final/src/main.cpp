#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include <iostream>
#include "sphere.h"
#include "camera.h"
#include "hitable_list.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "float.h"

using namespace std;

vec3 color(const ray &r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
	}
	else
	{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

hitable *random_scene()
{
	int n = 500;
	hitable **list = new hitable *[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int _a = -11; _a < 11; _a++)
	{
		for (int _b = -11; _b < 11; _b++)
		{
			float choose_mat = _drand48();
			vec3 center(_a + 0.9 * _drand48(), 0.2, _b + 0.9 * _drand48());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{ // diffuse
					list[i++] = new sphere(center, 0.2, new lambertian(vec3(_drand48() * _drand48(), _drand48() * _drand48(), _drand48() * _drand48())));
				}
				else if (choose_mat < 0.95)
				{ // metal
					list[i++] = new sphere(center, 0.2,
										   new metal(vec3(0.5 * (1 + _drand48()), 0.5 * (1 + _drand48()), 0.5 * (1 + _drand48())), 0.5 * _drand48()));
				}
				else
				{ // glass
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1.0, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0));

	return new hitable_list(list, i);
}

int main()
{	
	cout.precision(2);

	int nx = 1920;
	int ny = 1080;
	int ns = 100;
	int n = 4;

	hitable *world = random_scene();

	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

	unsigned char *data = new unsigned char[nx * ny * n];
	int cnt = 0;
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + _drand48()) / float(nx);
				float v = float(ny - 1 - (j + _drand48())) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			//use gamma2, ^{1/2}
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			data[j * nx * n + i * n + 0] = int(255.99 * col.r());
			data[j * nx * n + i * n + 1] = int(255.99 * col.g());
			data[j * nx * n + i * n + 2] = int(255.99 * col.b());
			data[j * nx * n + i * n + 3] = 255;

			cnt++;
			cout << "processed:" << float(cnt) / (nx*ny) * 100 << "%" << endl;
		}
	}

	cout << "write png to file!" << endl;
	stbi_write_png("final_result.png", nx, ny, n, data, nx * 4);
	stbi_image_free(data);
	return 0;
}