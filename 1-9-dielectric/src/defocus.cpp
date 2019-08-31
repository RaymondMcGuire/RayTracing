// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb/stb_image_write.h"
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb/stb_image.h"

// #include <iostream>
// #include "sphere.h"
// #include"camera.h"
// #include"hitable_list.h"
// #include"lambertian.h"
// #include"metal.h"
// #include"dielectric.h"
// #include"float.h"

// using namespace std;

// vec3 color(const ray&r, hitable *world, int depth){
// 	hit_record rec;
// 	if(world->hit(r,0.001, FLT_MAX,rec)){
// 		ray scattered;
// 		vec3 attenuation;
// 		if(depth<50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
// 			return attenuation*color(scattered,world,depth+1);
// 		}else{
// 			return vec3(0,0,0);
// 		}
// 	}else{
// 		vec3 unit_direction = unit_vector(r.direction());
// 			float t = 0.5*(unit_direction.y() +1.0);
//     	return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
// 	}
// }

// int main()
// {
//    int nx = 800;
//     int ny =400;
//     int ns = 100;
//     int n = 4;

// 	hitable *list[5];
// 	list[0] = new sphere(vec3(0,0,-1),0.5,new lambertian(vec3(0.8,0.3,0.3)));
// 	list[1] = new sphere(vec3(0,-100.5,-1),100,new lambertian(vec3(0.8,0.8,0.0)));
// 	list[2] = new sphere(vec3(1,0,-1),0.5,new metal(vec3(0.8,0.6,0.2),0.1));
// 	list[3] = new sphere(vec3(-1,0,-1),0.5,new dielectric(1.5));
// 	list[4] = new sphere(vec3(-1,0,-1),-0.45,new dielectric(1.5));
// 	hitable *world = new hitable_list(list,5);
    
// 	vec3 lookfrom(3,3,2);
// 	vec3 lookat(0,0,-1);
// 	float dist_to_focus = (lookfrom-lookat).length();
// 	float aperture = 2.0;

// 	camera cam(lookfrom,lookat,vec3(0,1,0),20,float(nx)/float(ny),aperture,dist_to_focus);

// 	unsigned char *data = new unsigned char[nx * ny * n];
// 	for (int j = ny - 1; j >= 0; j--)
// 	{
// 		for (int i = 0; i < nx; i++)
// 		{   
//             vec3 col(0,0,0);
//             for (int s = 0; s < ns; s++)
//             {
//                   float u = float(i+ Utils::_drand48()) / float(nx);
//             float v = float(ny - 1 - (j+ Utils::_drand48())) / float(ny);
//             ray r = cam.get_ray(u,v);
// 			vec3 p = r.point_at_parameter(2.0);
// 			col+=color(r,world, 0);
//             }
//             col/=float(ns);
// 			//use gamma2, ^{1/2}
// 			col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));
// 			data[j * nx * n + i * n + 0] = int(255.99 * col.r());
// 			data[j * nx * n + i * n + 1] = int(255.99 * col.g());
// 			data[j * nx * n + i * n + 2] = int(255.99 * col.b());
// 			data[j * nx * n + i * n + 3] = 255;
// 		}
// 	}

//     cout << "write png to file!" << endl;
// 	stbi_write_png("cpt9_dielectric_defocus.png", nx, ny, n, data, nx * 4);
// 	stbi_image_free(data);
// 	return 0;
// }