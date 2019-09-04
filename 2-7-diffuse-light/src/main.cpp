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
#include "surface_texture.h"
#include "diffuse_light.h"
#include "aa_rect.h"

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
		vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return emitted + attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return emitted;
		}
	}
	else
	{
		return vec3(0, 0, 0);
	}
}

hitable *cornell_box() {
    hitable **list = new hitable*[6];
    int i = 0;
    material *red = new lambertian(new constant_texture(vec3(0.65, 0.05, 0.05)));
    material *white = new lambertian(new constant_texture(vec3(0.73, 0.73, 0.73)));
    material *green = new lambertian(new constant_texture(vec3(0.12, 0.45, 0.15)));
    material *light = new diffuse_light(new constant_texture(vec3(15, 15, 15)));

	list[i++] = new flip_normals(new yz_rect(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rect(0, 555, 0, 555, 0, red);
	list[i++] = new xz_rect(213, 343, 227, 332, 554, light);
	list[i++] = new flip_normals(new xz_rect(0, 555, 0, 555, 555, white));
	list[i++] = new xz_rect(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normals(new xy_rect(0, 555, 0, 555, 555, white));

    return new hitable_list(list,i);
}

hitable *simple_light()
{
	texture *pertext = new noise_texture(4);
	hitable **list = new hitable *[4];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(pertext));
	list[1] = new sphere(vec3(0, 2, 0), 2, new lambertian(pertext));
	list[2] = new sphere(vec3(0, 7, 0), 2,
						 new diffuse_light(new constant_texture(vec3(4, 4, 4))));
	list[3] = new xy_rect(3, 5, 1, 3, -2,
						  new diffuse_light(new constant_texture(vec3(4, 4, 4))));
	return new hitable_list(list, 4);
}

int main()
{
	cout.setf(ios::fixed);
	cout.precision(2);

	int nx = 800;
	int ny = 800;
	int ns = 100;
	int n = 4;

	hitable *world = cornell_box();

	vec3 lookfrom(278, 278, -800);
	vec3 lookat(278,278,0);
	float dist_to_focus = 10.0;
	float aperture = 0.0;
	float vfov = 40.0;

	camera cam(lookfrom, lookat, vec3(0, 1, 0), vfov, float(nx) / float(ny), aperture, dist_to_focus, 0.0, 1.0);

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
				float u = float(i + Utils::random_double()) / float(nx);
				float v = float(ny - 1 - (j + Utils::random_double())) / float(ny);
				ray r = cam.get_ray(u, v);
				vec3 p = r.point_at_parameter(2.0);
				col += color(r, world, 0);
			}
			col /= float(ns);
			//use gamma2, ^{1/2}
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int r = int(255.99 * col.r());
			int g = int(255.99 * col.g());
			int b = int(255.99 * col.b());

			r = Utils::saturate_cast<int>(r, 0, 255);
			g = Utils::saturate_cast<int>(g, 0, 255);
			b = Utils::saturate_cast<int>(b, 0, 255);

			data[j * nx * n + i * n + 0] = r;
			data[j * nx * n + i * n + 1] = g;
			data[j * nx * n + i * n + 2] = b;
			data[j * nx * n + i * n + 3] = 255;

			cnt++;
		}

		int id = omp_get_thread_num();
		cout << "thread: " << id << " processed: " << float(cnt) / float(nx * ny) * 100.0;
		cout << endl;
	}

	cout << "write png to file!" << endl;
	stbi_write_png("2-7-3.png", nx, ny, n, data, nx * 4);
	stbi_image_free(data);
	return 0;
}