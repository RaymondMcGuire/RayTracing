#include <iostream>
using namespace std;

int ppm()
{
    int nx = 200;
    int ny = 100;
    cout << "P3\n"
         << nx << ny << "\n255\n";
    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2f;
            int ir = int(r * 255.99);
            int ig = int(g * 255.99);
            int ib = int(b * 255.99);
            cout << ir << " " << ig << " " << ib << "\n";
        }
    }

	return 0;
}