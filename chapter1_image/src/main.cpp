#include <iostream>
#include "vec3.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
using namespace std;

int main()
{
	int nx = 800;
	int ny = 400;
	int n = 4;
	unsigned char *data = new unsigned char[nx * ny * n];

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			//float r = float(i) / float(nx);
			//float g = float(ny - 1 - j) / float(ny);
			//float b = 0.2f;
			//int ir = int(r * 255.99);
			//int ig = int(g * 255.99);
			//int ib = int(b * 255.99);
			//cout << ir << " " << ig << " " << ib << "\n";

			vec3 col(float(i) / float(nx), float(ny - 1 - j) / float(ny), 0.2f);
			data[j * nx * n + i * n + 0] = int(255.99 * col.r());
			data[j * nx * n + i * n + 1] = int(255.99 * col.g());
			data[j * nx * n + i * n + 2] = int(255.99 * col.b());
			data[j * nx * n + i * n + 3] = 255;
		}
	}

	cout << "write png to file!" << endl;
	stbi_write_png("cpt1_1.png", nx, ny, n, data, nx * 4);
	stbi_image_free(data);
	return 0;
}