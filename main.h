#ifndef DEF_MAIN_RAY_TRACING
#define DEF_MAIN_RAY_TRACING

#include <stdio.h>
#include <cmath>
#include <vector>
#include <random>
#include <iostream>
#include <omp.h>
#include <chrono>
#include <stdlib.h>

#include "CImg/CImg.h"

#include "Global.h"
#include "helping_functions.h"

#include "Vector.h"
#include "Ray.h"
#include "Light.h"

#include "Object.h"
#include "Sphere.h"
#include "Plan.h"
#include "Cylindre.h"

#include "Scene.h"
#include "Inter.h"

#include "Union.h"
#include "Intersection.h"
#include "Difference.h"

Vector getColor(Ray ray, Light light, Scene scene, int* bounce, int* refract, double indice);

#endif

