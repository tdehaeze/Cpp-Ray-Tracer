#ifndef DEF_MAIN_RAY_TRACING
#define DEF_MAIN_RAY_TRACING

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

using namespace std;

Scene defineScene();

/* for one pixel, return the ray object */
Ray getPixelRay(int i, int j, int W, int H, int fov, Vector center);

/* get the normalize vector normal to the sphere on the intersection point */
Vector getIntersectNormal(double dist_sphere, Ray ray, Sphere sphere);

/* get the point of intersection of a ray and a sphere */
Vector getIntersectPoint(double dist_sphere, Ray ray, Sphere sphere);

/* get the Ray object from a point to a light point */
Ray getRayToLight(Light light, Vector intersect_point);

/* get the Ray object for one ray that reflect on a secular sphere */
Ray getReflectedRay(Ray ray, Sphere sphere, Vector intersect_point, double dist_sphere);

/* get the refracted ray */
Ray getRefractedRay(Ray ray, Vector intersect_point, Vector intersect_normal, double ind_before, double ind_after);

/* set the intensity and the color */
void setIntensity(vector<unsigned char> &pixels, int i, int j, int H, int W, Sphere sphere, double dist, Light light, Ray ray, double coef);

/* set the intensity to zero */
void setIntensityToBlack(vector<unsigned char> &pixels, int i, int j, int H, int W);

/* for a ray that crosses a non secular sphere -> set the pixel color */
void setColorOfRayOnSphere(Ray ray, Sphere sphere, Light light, Scene scene, vector<unsigned char> &pixels, int i, int j, int H, int W);

/* for a ray that crosses a mirror -> set the pixel color */
void setColorOfRayOnMirror(Ray ray, Sphere sphere, Light light, Scene scene, const int max_bounce, int &bounce_counter, vector<unsigned char> &pixels, int i, int j, const int H, const int W);

void setColorOfRayOnTransparent(Ray ray, Sphere sphere, Light light, Scene scene, const int max_bounce, int &bounce_counter, vector<unsigned char> &pixels, int i, int j, const int H, const int W);

void mainfunction(Ray ray, Light light, Scene scene, const int max_bounce, int &bounce_counter, vector<unsigned char> &pixels, int i, int j, const int H, const int W);

#endif

