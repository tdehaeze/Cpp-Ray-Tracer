#include "main.h"

#define EPSILON 0.001
#define Z_CAMERA 60

/* for one pixel, return the ray object */
Ray getPixelRay(int i, int j, int W, int H, int fov, Vector center)
{
    Vector rayDirection = Vector(j-W/2+0.5, i-H/2+0.5, -H/(2*std::tan(2*M_PI*fov/2/360)));
    rayDirection.Normalize();
    return Ray(center, rayDirection);;
}

/* /1* get the normalize vector normal to the sphere on the intersection point *1/ */
/* Vector getIntersectNormal(double dist_sphere, Ray ray, Sphere sphere) */
/* { */
/*     Vector intersect_normal = ray.origin + dist_sphere*ray.direction - sphere.origin; */
/*     intersect_normal.Normalize(); */
/*     return intersect_normal; */
/* } */

int main()
{
    const int W = 1024; /* width: number of pixels */
    const int H = 1024; /* height: number of pixels */

    const Vector center = Vector(0, 0, Z_CAMERA); /* point of view: start point for the ray, we look at the negative z */
    const int fov = 60; /* field of view */

    Ray ray = Ray (center, Vector(0, 0, 1)); /* initialize the ray */

    /* Light light = Light(Vector(-20, -20, 50), 1000000000); /1* setup the light source position and luminosity *1/ */

    Material material = Material();

    Sphere* sphere = new Sphere(Vector(0, 0, -70+Z_CAMERA), 10, &material);

    std::vector<unsigned char> pixels(3*H*W,0); /* define the array of pixels */

    /* for each pixels */
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            ray = getPixelRay(i, j, W, H, fov, center); /* get the initial ray object for one pixel */
            Vector* intersect_point = sphere->getIntersect(ray);
            if (intersect_point == 0) {
                pixels[H*i+j]       = 0;
                pixels[H*i+j+H*W]   = 0;
                pixels[H*i+j+2*H*W] = 0;
            } else {
                pixels[H*i+j]       = 255;
                pixels[H*i+j+H*W]   = 255;
                pixels[H*i+j+2*H*W] = 255;
            }
        }
        if (i%10 == 0)
            std::cout << 100*i/H << "%\n";
    }

    cimg_library::CImg<unsigned char> cimg(&pixels[0], W, H, 1, 3);
    cimg.save("fichier.bmp");

    delete sphere;

    return 0;
}

