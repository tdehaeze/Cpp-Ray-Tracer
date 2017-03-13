#include "main.h"

#define Z_CAMERA 60

Scene defineScene()
{
    Scene scene = Scene();

    Material* blue        = new Material(Vector(25,  25,  112));
    Material* red         = new Material(Vector(178, 34,  34));
    Material* green       = new Material(Vector(154, 205, 50));
    Material* cyan        = new Material(Vector(0,   139, 139));
    Material* orange      = new Material(Vector(210, 105, 30));
    Material* grey        = new Material(Vector(119, 136, 153));
    /* Material* mirroir     = new Material(Vector(1.,  1.,  1.), 0., 1.); */
    /* Material* transparent = new Material(Vector(1.,  1.,  1.), 1., 0., 1.3); */

    /* 
     * droite -> (+, 0, 0)
     * haut -> (0, -, 0)
     * avant -> (0, 0, -)
     * */

    /* Sphere * sphere_1 = new Sphere(Vector(0, 0, 0), 40, transparent); */
    /* Sphere * sphere_2 = new Sphere(Vector(0, 0, -39), 40, transparent); */
    /* Union * union_1 = new Union(sphere_1, sphere_2); */
    /* Intersection * intersection_1 = new Intersection(sphere_1, sphere_2); */
    /* Sphere * sphere_3 = new Sphere(Vector(3, 0, -7), 2, green); */

    /* Plan * plan_right = new Plan(Vector(30, 0, 0), Vector(-1, 0, 0), green); */
    /* scene.addObject(plan_left); */
    /* Plan * plan_left = new Plan(Vector(-30, 0, 0), Vector(1, 0, 0), red); */
    /* scene.addObject(plan_right); */
    Plan * plan_bottom = new Plan(Vector(0, 30, 0), Vector(0, -1, 0), cyan);
    scene.addObject(plan_bottom);
    /* Plan * plan_top = new Plan(Vector(0, -30, 0), Vector(0, 1, 0), orange); */
    /* scene.addObject(plan_top); */
    /* Plan * plan_front = new Plan(Vector(0, 0, 100), Vector(0, 0, -1), grey); */
    /* scene.addObject(plan_back); */
    /* Plan * plan_back = new Plan(Vector(0, 0, -80), Vector(0, 0, 1), blue); */
    /* scene.addObject(plan_front); */

    Cylindre * cylindre = new Cylindre(Vector(10, 10, -20), Vector(0, -10, 0), 9, red);
    Sphere * sphere_inside = new Sphere(Vector(0, -10, 0), 8, red);
    Difference * cylindre_creux = new Difference(cylindre, sphere_inside);
    Sphere * sphere_outside = new Sphere(Vector(0, -10, 0), 9, red);
    Intersection * bol = new Intersection(cylindre_creux, sphere_outside);
    scene.addObject(bol);

    /* scene.addObject(intersection_1); */
    /* scene.addObject(union_1); */

    /* scene.addObject(sphere_1); */
    /* scene.addObject(sphere_2); */
    /* scene.addObject(sphere_3); */


    /* scene.addObject(cylindre); */

    return scene;
}

std::vector<double> getColorMirroir(Object* object, Ray ray, Light light, Scene scene, int* bounce, int* refract) {
    std::vector<double> colors {0, 0, 0};
    *bounce += 1;
    /* if (DEBUG) std::cout << "reflexion on reflective object" << std::endl; */
    Ray reflected_ray = object->getReflectedRay(ray);
    colors = getColor(reflected_ray, light, scene, bounce, refract);
    return colors;
}

std::vector<double> getColor(Ray ray, Light light, Scene scene, int* bounce, int* refract) {
    if (DEBUG) std::cout << "OK -2" << std::endl;
    Object* intersect_object = scene.getIntersectedObject(ray);
    if (DEBUG) std::cout << "OK -1" << std::endl;
    std::vector<double> colors {0, 0, 0};
    if (DEBUG) std::cout << "OK 0" << std::endl;
    if (intersect_object != 0 && *bounce < 2 && *refract < 5) {
        if (DEBUG) std::cout << "OK 1" << std::endl;
        if (intersect_object->getMaterial()->getReflectivity() != 0.) { /* Mirroir Object */
            colors = getColorMirroir(intersect_object, ray, light, scene, bounce, refract);
        } else if (intersect_object->getMaterial()->getTransparency() != 0.) { /* Transparent Object */
            double current_indice = 1.;
            double next_indice = 1.;

            if ( intersect_object->isInside(intersect_object->getPointBeforeIntersect(ray)) ) { /* going outside object */
                /* if (DEBUG) std::cout << "going outside" << std::endl; */
                current_indice = intersect_object->getMaterial()->getIndice();
            } else { /* going inside object */
                /* if (DEBUG) std::cout << "going inside" << std::endl; */
                next_indice = intersect_object->getMaterial()->getIndice();
            }

            double ind_frac = current_indice/next_indice;
            Vector intersect_normal = *intersect_object->getNormal(ray);
            double prod_scalaire = std::abs(intersect_normal*ray.getDirection());
            double frac = 1-ind_frac*ind_frac*(1 - prod_scalaire*prod_scalaire);

            if (frac < 0) { /* only reflexion */
                colors = getColorMirroir(intersect_object, ray, light, scene, bounce, refract);
            } else { /* only refraction */
                *refract += 1;
                /* if (DEBUG) std::cout << "refraction" << std::endl; */
                Ray refracted_ray = intersect_object->getRefractedRay(ray, current_indice, next_indice);
                colors = getColor(refracted_ray, light, scene, bounce, refract);
            }

        } else { /* Normal Object */
            if (DEBUG) std::cout << "OK 2" << std::endl;
            Ray ray_to_light = Ray(intersect_object->getPointBeforeIntersect(ray), light);
            if (DEBUG) std::cout << "OK 3" << std::endl;
            Object* intersect_object_light = scene.getIntersectedObject(ray_to_light);
            if (DEBUG) std::cout << "OK 4" << std::endl;

            if (intersect_object_light == 0 || (intersect_object_light != 0 && intersect_object_light->getDistance(ray_to_light) > (*intersect_object->getIntersect(ray) - light.getOrigin()).norm())) {
                if (DEBUG) std::cout << "OK 5" << std::endl;
                double intensity = intersect_object->getIntensity(ray, light);
                if (DEBUG) std::cout << "Intensity : " << intensity << std::endl;
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
    const int fov = 40; /* field of view */

    Ray ray = Ray (center, Vector(0, 0, 1)); /* initialize the ray */

    Light light = Light(Vector(-20, -20, 50), 1000000); /* setup the light source position and luminosity */


    Scene scene = defineScene();

    std::vector<unsigned char> pixels(3*H*W,0); /* define the array of pixels */

    int bounce = 0;
    int refract = 0;

    auto start = std::chrono::steady_clock::now();

/* #pragma omp parallel for schedule(dynamic,1) */

    /* for each pixels */
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
            bounce = 0;
            refract = 0;
            ray = Ray(center, Vector(j-W/2+0.5, i-H/2+0.5, -H/(2*std::tan(2*M_PI*fov/2/360))));
            std::vector<double> colors = getColor(ray, light, scene, &bounce, &refract);
            pixels[H*i+j]       = colors[0];
            pixels[H*i+j+H*W]   = colors[1];
            pixels[H*i+j+2*H*W] = colors[2];
        }
        if (i%10 == 0)
            std::cout << 100*i/H << "%\n";
    }

    auto end = std::chrono::steady_clock::now();
    auto diff_time = end-start;

    std::cout << std::chrono::duration <double, std::milli> (diff_time).count() << std::endl;

	if (DEBUG) std::cout << "writing file..." << std::endl;
    cimg_library::CImg<unsigned char> cimg(&pixels[0], W, H, 1, 3);
    cimg.save("fichier.bmp");

    return 0;
}

