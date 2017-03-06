#ifndef DEF_MAIN_RAY_TRACING
#define DEF_MAIN_RAY_TRACING

#include <stdio.h>
#include <cmath>
#include <vector>
#include <random>
#include <iostream>

#include "CImg/CImg.h"

#include "Vector.h"
#include "Ray.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"
#include "Scene.h"


/* Scene defineScene(); */

/* /1* for one pixel, return the ray object *1/ */
/* Ray getPixelRay(int i, int j, int W, int H, int fov, Vector center); */

/* /1* get the normalize vector normal to the sphere on the intersection point *1/ */
/* Vector getIntersectNormal(double dist_sphere, Ray ray, Sphere sphere); */

/* /1* get the point of intersection of a ray and a sphere *1/ */
/* Vector getIntersectPoint(double dist_sphere, Ray ray, Sphere sphere); */

/* /1* get the Ray object from a point to a light point *1/ */
/* Ray getRayToLight(Light light, Vector intersect_point); */

/* /1* get the Ray object for one ray that reflect on a secular sphere *1/ */
/* Ray getReflectedRay(Ray ray, Sphere sphere, Vector intersect_point, double dist_sphere); */

/* /1* get the refracted ray *1/ */
/* Ray getRefractedRay(Ray ray, Vector intersect_point, Vector intersect_normal, double ind_before, double ind_after); */

/* /1* set the intensity and the color *1/ */
/* void setIntensity(vector<unsigned char> &pixels, int i, int j, int H, int W, Sphere sphere, double dist, Light light, Ray ray, double coef); */

/* /1* set the intensity to zero *1/ */
/* void setIntensityToBlack(vector<unsigned char> &pixels, int i, int j, int H, int W); */

/* /1* for a ray that crosses a non secular sphere -> set the pixel color *1/ */
/* void setColorOfRayOnSphere(Ray ray, Sphere sphere, Light light, Scene scene, vector<unsigned char> &pixels, int i, int j, int H, int W); */

/* /1* for a ray that crosses a mirror -> set the pixel color *1/ */
/* void setColorOfRayOnMirror(Ray ray, Sphere sphere, Light light, Scene scene, const int max_bounce, int &bounce_counter, vector<unsigned char> &pixels, int i, int j, const int H, const int W); */

/* void setColorOfRayOnTransparent(Ray ray, Sphere sphere, Light light, Scene scene, const int max_bounce, int &bounce_counter, vector<unsigned char> &pixels, int i, int j, const int H, const int W); */

/* void mainfunction(Ray ray, Light light, Scene scene, const int max_bounce, int &bounce_counter, vector<unsigned char> &pixels, int i, int j, const int H, const int W); */

#endif

