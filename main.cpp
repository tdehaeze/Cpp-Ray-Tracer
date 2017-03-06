#include "main.h"

#define EPSILON 0.001
#define Z_CAMERA 60

std::vector<double> getColor(Ray ray, Light light, Scene scene, int* bounce) {
    Object* intersect_object = scene.getIntersectedObject(ray);
    std::vector<double> colors {0, 0, 0};
    if (intersect_object != 0 && *bounce < 5) {
        if (intersect_object->getMaterial()->getReflectivity() != 0.) {
            *bounce += 1;
            std::cout << *bounce << std::endl;
            Ray * reflected_ray = intersect_object->getReflectedRay(ray);
            colors = getColor(*reflected_ray, light, scene, bounce);
        } else {
            Ray ray_to_light = Ray(*scene.getIntersect(ray)+EPSILON*(*scene.getNormal(ray)), light);
            Object* intersect_object_light = scene.getIntersectedObject(ray_to_light);

            if (intersect_object_light == 0 || (intersect_object_light != 0 && intersect_object_light->getDistance(ray_to_light) > (*intersect_object->getIntersect(ray) - light.getOrigin()).norm())) {
                double intensity = intersect_object->getIntensity(ray, light);
                double red   = std::min(255.0, std::pow(intensity*intersect_object->getMaterial()->getColor()[0], 1./2.2));
                double green = std::min(255.0, std::pow(intensity*intersect_object->getMaterial()->getColor()[1], 1./2.2));
                double blue  = std::min(255.0, std::pow(intensity*intersect_object->getMaterial()->getColor()[2], 1./2.2));
                colors = {red, green, blue};
            }
        }
    }
    return colors;
}

int main()
{
    const int W = 1024; /* width: number of pixels */
    const int H = 1024; /* height: number of pixels */

    const Vector center = Vector(0, 0, Z_CAMERA); /* point of view: start point for the ray, we look at the negative z */
    const int fov = 60; /* field of view */

    Ray ray = Ray (center, Vector(0, 0, 1)); /* initialize the ray */

    Light light = Light(Vector(-20, -20, 50), 100000000); /* setup the light source position and luminosity */

    Material white = Material();
    Material mirroir = Material(Vector(1., 1., 1.), 0., 1.);

    Sphere* sphere = new Sphere(Vector(0, 0, -70+Z_CAMERA), 10, &white);
    Sphere* sphere_bis = new Sphere(Vector(0, 20, -70+Z_CAMERA), 5, &mirroir);
    Sphere* sphere_bottom = new Sphere(Vector(0, 10040, 0), 10000, &white);

    Scene scene = Scene();

    scene.addSphere(sphere);
    scene.addSphere(sphere_bis);
    scene.addSphere(sphere_bottom);

    std::vector<unsigned char> pixels(3*H*W,0); /* define the array of pixels */

    int bounce = 0;

    /* for each pixels */
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            bounce = 0;
            ray = Ray(center, Vector(j-W/2+0.5, i-H/2+0.5, -H/(2*std::tan(2*M_PI*fov/2/360))));
            std::vector<double> colors = getColor(ray, light, scene, &bounce);
            pixels[H*i+j]       = colors[0];
            pixels[H*i+j+H*W]   = colors[1];
            pixels[H*i+j+2*H*W] = colors[2];
        }
        if (i%10 == 0)
            std::cout << 100*i/H << "%\n";
    }

    cimg_library::CImg<unsigned char> cimg(&pixels[0], W, H, 1, 3);
    cimg.save("fichier.bmp");

    return 0;
}

