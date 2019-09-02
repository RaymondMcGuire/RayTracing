#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "omp.h"

#include <iostream>
#include "sphere.h"
#include "moving_sphere.h"
#include "camera.h"
#include "bvh.h"
#include "hitable_list.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "texture.h"

#include "float.h"

using namespace std;

#define NUM_THREADS 8

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

hitable *two_perlin_spheres() {
    texture *pertext = new noise_texture();
    hitable **list = new hitable*[2];
    list[0] =  new sphere(vec3(0,-1000, 0), 1000, new lambertian( pertext ));
    list[1] =  new sphere(vec3(0, 2, 0), 2, new lambertian( pertext ));
    return new hitable_list(list,2);
}

int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);

	int nx = 400;
	int ny = 200;
	int ns = 100;
	int n = 4;

	hitable *world = two_perlin_spheres();

	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.0;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus, 0.0, 1.0);

	unsigned char *data = new unsigned char[nx * ny * n];
	int cnt = 0;
	omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for shared(cnt)
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(i + Utils::_drand48()) / float(nx);
				float v = float(ny - 1 - (j + Utils::_drand48())) / float(ny);
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
		}

		int id = omp_get_thread_num();
		cout << "thread: " << id << " processed: " << float(cnt) / float(nx * ny) * 100.0 << "%" << endl;
	}

	cout << "write png to file!" << endl;
	stbi_write_png("2-1.png", nx, ny, n, data, nx * 4);
	stbi_image_free(data);
	return 0;
}