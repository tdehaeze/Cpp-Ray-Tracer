#include <stdio.h>
#include <math.h>
#include <vector>
#include <random>
#include <iostream>
#include "CImg/CImg.h"

#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "Scene.h"
#include "Material.h"

using namespace std;

/* Define the scene with all the spheres and return the scene object */
Scene defineScene()
{
    Scene scene = Scene();
    scene.addSphere(Sphere(Vector(0, 10, -10), 15, Vector(1, 1, 1), 1)); /* main sphere */
    scene.addSphere(Sphere(Vector(-1000, 0, 0), 970, Vector(1, 0, 0), 0)); /* left */
    scene.addSphere(Sphere(Vector(1000, 0, 0), 970, Vector(1, 0, 0), 1)); /* right */
    scene.addSphere(Sphere(Vector(0, 1000, 0), 970, Vector(1, 0, 0), 0)); /* bottom */
    scene.addSphere(Sphere(Vector(0, -1000, 0), 970, Vector(1, 0, 0), 0)); /* top */
    scene.addSphere(Sphere(Vector(0, 0, -1000), 970, Vector(0, 1, 0), 0)); /* front */
    scene.addSphere(Sphere(Vector(0, 0, 1045), 970, Vector(0, 1, 0), 0)); /* back */
    return scene;
}

/* for one pixel, return the ray object */
Ray getPixelRay(int i, int j, int W, int H, int fov, Vector center)
{
    Vector rayDirection = Vector(j-W/2+0.5, i-H/2+0.5, -H/(2*tan(2*M_PI*fov/2/360)));
    rayDirection.Normalize();
    return Ray(center, rayDirection);;
}

/* get the normalize vector normal to the sphere on the intersection point */
Vector getIntersectNormal(double dist_sphere, Ray ray, Sphere sphere)
{
    Vector intersect_normal = ray.origin + dist_sphere*ray.direction - sphere.origin;
    intersect_normal.Normalize();
    return intersect_normal;
}

/* TODO: should implement this function inside an other class (ray or sphere) */
/* get the point of intersection of a ray and a sphere */
Vector getIntersectPoint(double dist_sphere, Ray ray, Sphere sphere)
{
    Vector intersect_normal = getIntersectNormal(dist_sphere, ray, sphere);
    Vector intersect_point = ray.origin + dist_sphere*ray.direction + 0.001*intersect_normal;
    return intersect_point;
}

/* TODO: faire une fonction plus générale pour générer un 
 * object Ray à partir de deux points */

/* get the Ray object from a point to a light point */
Ray getRayToLight(Light light, Vector intersect_point)
{
    Vector ray_direction_bis = light.origin - intersect_point;
    ray_direction_bis.Normalize();
    return Ray(intersect_point, ray_direction_bis);
}

/* get the Ray object for one ray that reflect on a secular sphere */
Ray getReflectedRay(Ray ray, Sphere sphere, Vector intersect_point, double dist_sphere)
{
    Vector intersect_normal = getIntersectNormal(dist_sphere, ray, sphere);
    Vector incident_vector = ray.direction;
    Vector reflected_vector = incident_vector - 2*(incident_vector*intersect_normal)*intersect_normal;
    Ray reflected_ray = Ray(intersect_point, reflected_vector);
    return reflected_ray;
}

/* set the intensity and the color */
void setIntensity(vector<unsigned char> &pixels, int i, int j, int H, int W, Sphere sphere, double dist, Light light, Ray ray)
{
    double intensity = ray.getIntensity(sphere, dist, light);
    double red   = min(255.0, intensity*sphere.material[0]);
    double green = min(255.0, intensity*sphere.material[1]);
    double blue  = min(255.0, intensity*sphere.material[2]);
    pixels[H*i+j]       = red;
    pixels[H*i+j+H*W]   = green;
    pixels[H*i+j+2*H*W] = blue;
}

/* set the intensity to zero */
void setIntensityToBlack(vector<unsigned char> &pixels, int i, int j, int H, int W)
{
    pixels[H*i+j]       = 0;
    pixels[H*i+j+H*W]   = 0;
    pixels[H*i+j+2*H*W] = 0;
}

/* for a ray that crosses a non secular sphere -> set the pixel color */
void setColorOfRayOnSphere(Ray ray, Sphere sphere, Light light, Scene scene, vector<unsigned char> &pixels, int i, int j, int H, int W)
{
    /* get the distance to the crossed sphere */
    double dist_sphere = ray.getDistanceToSphere(sphere);

    /* get the intersect point */
    Vector intersect_point = getIntersectPoint(dist_sphere, ray, sphere);

    /* get the Ray object for the ray that goes from the intersect point to the light */
    Ray ray_dir_light = getRayToLight(light, intersect_point);

    /* get the intersect sphere of the ray that is directed to light */
    Sphere sphere_bis = scene.getSphere(ray_dir_light);

    if (sphere_bis.radius <= 0) { /* If there is no sphere between the point and the source light */
        /* TODO : techniquement, ça n'arrive jamais car ici la scene est entourée de spheres */
        setIntensity(pixels, i, j, H, W, sphere, dist_sphere, light, ray);
    } else { /* If there is one sphere on the ray path */
        double dist_sphere_bis = ray_dir_light.getDistanceToSphere(sphere_bis); /* dist_sphere_bis is the distance to the sphere */

        /* TODO : should do a method on Vector to get the distance between two points */
        /* get the distance from the intersect point to the light */
        double distance_light = (light.origin - intersect_point).norm();

        if (dist_sphere_bis > 0 && dist_sphere_bis < distance_light){ /* if the sphere is between the point and the light source => shadow */
            setIntensityToBlack(pixels, i, j, H, W);
        } else { /* if the sphere is after the light source => light */
            setIntensity(pixels, i, j, H, W, sphere, dist_sphere, light, ray);
        }
    }
}

/* for a ray that crosses a mirror -> set the pixel color */
void setColorOfRayOnMirror(Ray ray, Sphere sphere, Light light, Scene scene, const int max_bounce, int &bounce_counter, vector<unsigned char> &pixels, int i, int j, const int H, const int W)
{
    bounce_counter += 1;
    if (bounce_counter > 1)
        std::cout << "bounce: " << bounce_counter << '\n';

    if (bounce_counter < max_bounce) {
        /* get the distance to the crossed sphere */
        double dist_sphere = ray.getDistanceToSphere(sphere);

        /* get the intersect point */
        Vector intersect_point = getIntersectPoint(dist_sphere, ray, sphere);

        /* get the reflected ray on the mirror */
        Ray reflected_ray = getReflectedRay(ray, sphere, intersect_point, dist_sphere);

        /* get if the reflected ray crosses a sphere */
        Sphere crossed_sphere = scene.getSphere(reflected_ray);

        if (crossed_sphere.radius <= 0) { /* If there is no sphere that the reflected ray crosses */
            setIntensityToBlack(pixels, i, j, H, W);
        } else { /* If there is one sphere on the reflected ray path */
            if (crossed_sphere.seculaire == 1) { /* if the sphere crossed is also a mirror */
                setColorOfRayOnMirror(reflected_ray, crossed_sphere, light, scene, max_bounce, bounce_counter, pixels, i, j, H, W);
            } else { /* if the sphere is not a mirror */
                setColorOfRayOnSphere(reflected_ray, crossed_sphere, light, scene, pixels, i, j, H, W);
            }
        }
    } else {
        /* max number of bounce => black */
        setIntensityToBlack(pixels, i, j, H, W);
    }
}

int main()
{
    const int W = 1024; /* width: number of pixels */
    const int H = 1024; /* height: number of pixels */

    const Vector center = Vector(0, 0, 55); /* point of view: start point for the ray, we look at the negative z */
    const int fov = 80; /* field of view */

    const int max_bounce = 5; /* maximal bounce for one ray */

    int bounce_counter = 0;

    Ray ray = Ray (center, Vector(0, 0, 1)); /* initialize the ray */

    Scene scene = defineScene(); /* setup the scene with the spheres */

    Light light = Light(Vector(-20, -20, 50), 2000000); /* setup the light source position and luminosity */

    vector<unsigned char> pixels(3*H*W,0); /* define the array of pixels */

    /* for each pixels */
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            bounce_counter = 0;
            ray = getPixelRay(i, j, W, H, fov, center); /* get the initial ray object for one pixel */

            Sphere firstSphere = scene.getSphere(ray); /* get the first sphere that the ray crosses, if there is not, the radius of the sphere is -1 */

            if (firstSphere.radius <= 0) { /* If the ray cross no sphere */
                /* no light on the pixel => black */
                setIntensityToBlack(pixels, i, j, H, W);
            } else { /* If the ray cross one sphere */
                if (firstSphere.seculaire  == 1) { /* if the sphere is a mirror */
                    /* set the color for the ray on the mirror */
                    setColorOfRayOnMirror(ray, firstSphere, light, scene, max_bounce, bounce_counter, pixels, i, j, H, W);
                } else { /* If the sphere is not a mirror */
                    /* set the color for the ray on the sphere */
                    setColorOfRayOnSphere(ray, firstSphere, light, scene, pixels, i, j, H, W);
                }
            }
        }
        if (i%10 == 0)
            std::cout << 100*i/H << "%\n";
    }

    cimg_library::CImg<unsigned char> cimg(&pixels[0], W, H, 1, 3);
    cimg.save("fichier.bmp");
    return 0;
}

