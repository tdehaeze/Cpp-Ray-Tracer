#include "main.h"

#define Z_CAMERA 60
#define ALPHA_DIFF 0.2
#define NB_RAY 20
#define MAX_BOUNCE 5
#define MAX_REFRACT 5
#define NB_ANTI_ALIASING 10
#define ANTI_ALIASING true
#define CST_FRESNEL true

std::default_random_engine engine;
std::uniform_real_distribution <double> distrib(0,1);
std::normal_distribution<double> distribution(-0.5,0.5);

Scene defineScene()
{
    Scene scene = Scene();

    Material* blue        = new Material(Vector(25,  25,  112));
    Material* red         = new Material(Vector(178, 34,  34));
    Material* green       = new Material(Vector(154, 205, 50));
    Material* cyan        = new Material(Vector(0,   139, 139));
    Material* orange      = new Material(Vector(210, 105, 30));
    Material* grey        = new Material(Vector(130, 130, 130));
    /* Material* mirroir     = new Material(Vector(1.,  1.,  1.), 0., 1.); */
    /* Material* transparent = new Material(Vector(1.,  1.,  1.), 1., 0., 1.1); */

    /* 
     * droite -> (+, 0, 0)
     * haut -> (0, -, 0)
     * avant -> (0, 0, -)
     * */

    Sphere * sphere_1 = new Sphere(Vector(20, 20, -30), 10, grey);
    scene.addObject(sphere_1);
    Sphere * sphere_2 = new Sphere(Vector(20, 20, -50), 5, grey);
    scene.addObject(sphere_2);
    Sphere * sphere_3 = new Sphere(Vector(20, 5, -10), 5, blue);
    scene.addObject(sphere_3);
    /* Sphere * sphere_2 = new Sphere(Vector(0, 0, -39), 40, transparent); */
    /* Union * union_1 = new Union(sphere_1, sphere_2); */
    /* Intersection * intersection_1 = new Intersection(sphere_1, sphere_2); */
    /* Sphere * sphere_3 = new Sphere(Vector(3, 0, -7), 2, green); */

    Plan * plan_right = new Plan(Vector(30, 0, 0), Vector(-1, 0, 0), red);
    scene.addObject(plan_right);
    Plan * plan_left = new Plan(Vector(-30, 0, 0), Vector(1, 0, 0), green);
    scene.addObject(plan_left);
    Plan * plan_bottom = new Plan(Vector(0, 30, 0), Vector(0, -1, 0), cyan);
    scene.addObject(plan_bottom);
    Plan * plan_top = new Plan(Vector(0, -30, 0), Vector(0, 1, 0), orange);
    scene.addObject(plan_top);
    Plan * plan_front = new Plan(Vector(0, 0, 100), Vector(0, 0, -1), grey);
    scene.addObject(plan_front);
    Plan * plan_back = new Plan(Vector(0, 0, -80), Vector(0, 0, 1), blue);
    scene.addObject(plan_back);

    /* Cylindre * cylindre = new Cylindre(Vector(10, 10, -20), Vector(0, -10, 0), 9, mirroir); */
    /* Sphere * sphere_inside = new Sphere(Vector(0, -10, 0), 8, mirroir); */
    /* Difference * cylindre_creux = new Difference(cylindre, sphere_inside); */
    /* Sphere * sphere_outside = new Sphere(Vector(0, -10, 0), 9, mirroir); */
    /* Intersection * bol = new Intersection(cylindre_creux, sphere_outside); */
    /* scene.addObject(bol); */

    /* scene.addObject(intersection_1); */
    /* scene.addObject(union_1); */

    /* scene.addObject(sphere_1); */
    /* scene.addObject(sphere_2); */
    /* scene.addObject(sphere_3); */


    /* scene.addObject(cylindre); */

    return scene;
}

double getReflectivity(double current_indice, Inter* inter, Ray ray){
    double R;
    double next_indice = inter->getIndiceAfter();
    /* std::cout << "next_indice : " << next_indice << std::endl; */
    /* std::cout << "current_indice : " << current_indice << std::endl; */

    if (CST_FRESNEL) {
        R = 0.2;
    } else {
        double k0 = std::pow((current_indice-next_indice)/(current_indice+next_indice), 2);
        Vector i;
        if (next_indice > current_indice) {
            i = -ray.getDirection();
        } else {
            i = inter->getRefractedRay(ray).getDirection();
        }
        R = k0 + (1-k0)*std::pow(1-std::abs(i*inter->getNormal()), 5);
    }
    return R;
}

Vector getColor(Ray ray, Light light, Scene scene, int bounce, int refract, double current_indice) {
    Vector colors = Vector();

    Inter* inter = new Inter(scene, ray, current_indice);

    if (inter->getObject() != 0 && bounce < MAX_BOUNCE && refract < MAX_REFRACT) {
        if (inter->getObject()->getMaterial()->getReflectivity() != 0.) {
            /* Mirroir Object */
            colors = getColor(inter->getReflectedRay(ray), light, scene, bounce+1, refract, current_indice);
        } else if (inter->getObject()->getMaterial()->getTransparency() != 0.) {
            /* Transparent Object */
            double R = getReflectivity(current_indice, inter, ray);

            if (distrib(engine) < R) {
                /* reflexion */
                colors = getColor(inter->getReflectedRay(ray), light, scene, bounce+1, refract, current_indice);
            } else {
                /* transmision */
                colors = getColor(inter->getRefractedRay(ray), light, scene, bounce, refract+1, inter->getIndiceAfter());
            }
        } else {
            /* Normal Object */
            if(distrib(engine) < ALPHA_DIFF) {
                /* ray to light */
                Ray ray_to_light = Ray(inter->getPointBeforeIntersect(), light);

                Inter* inter_light = new Inter(scene, ray_to_light, current_indice);

                if (inter_light->getObject() == 0 || (inter_light->getObject() != 0 && inter_light->getObject()->getDistance(ray_to_light) > (*inter->getObject()->getIntersect(ray) - light.getOrigin()).norm())) {
                    /* If there is no object or if the object is after the light */
                    double intensity = inter->getIntensity(light);
                    if (DEBUG) std::cout << "Intensity : " << intensity << std::endl;
                    colors = intensity*inter->getObject()->getMaterial()->getColor();
                }
            } else {
                /* random ray */
                /* Vector color_object = inter->getObject()->getMaterial()->getColor(); */
                /* colors = color_object + (2./(M_PI))*color_object.elementWizeProduct(getColor(reflected_ray, light, scene, bounce, refract, current_indice)); */
                colors = (2./(M_PI))*inter->getObject()->getMaterial()->getColor().elementWizeProduct(getColor(inter->getRandomRay(), light, scene, bounce+1, refract, current_indice));
            }
        }
    } else if (bounce == MAX_BOUNCE) {
        /* si on a atteind le max de bounce => on prend un rayon vers la lumière */
        Ray ray_to_light = Ray(inter->getPointBeforeIntersect(), light);

        Inter* inter_light = new Inter(scene, ray_to_light, current_indice);

        if (inter_light->getObject() == 0 || (inter_light->getObject() != 0 && inter_light->getObject()->getDistance(ray_to_light) > (*inter->getObject()->getIntersect(ray) - light.getOrigin()).norm())) {
            double intensity = inter->getIntensity(light);
            if (DEBUG) std::cout << "Intensity : " << intensity << std::endl;
            colors = intensity*inter->getObject()->getMaterial()->getColor();
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

    Light light = Light(Vector(-20, -20, 50), 1000000); /* setup the light source position and luminosity */

    Scene scene = defineScene();

    std::vector<unsigned char> pixels(3*H*W,0); /* define the array of pixels */

    double current_indice = 1.0;

    auto start = std::chrono::steady_clock::now();

#pragma omp parallel for schedule(dynamic,1)

    /* for each pixels */
    /* for (int i = 0; i < W; i++) { */
    /*     for (int j = 0; j < H; j++) { */
    for (int i = W-400; i < W; i++) {
        for (int j = H-400; j < H; j++) {
            Vector final_color = Vector(0, 0, 0);
            if (ANTI_ALIASING) {
                for (int l = 0; l < NB_ANTI_ALIASING; ++l) {
                    double x = distribution(engine);
                    double y = distribution(engine);
                    Ray ray = Ray(center, Vector(j+x-W/2, i+y-H/2, -H/(2*std::tan(2*M_PI*fov/2/360))));

                    /* Ray ray = Ray(center, (j-W/2+u-0.5)*right + (i-H/2+v-0.5)*up + depth*direction); */

                    Vector colors = Vector();
                    for (int k = 0; k < NB_RAY; ++k) {
                        colors += getColor(ray, light, scene, 0, 0, current_indice);
                    }

                    colors = (1.0/(NB_RAY))*colors;

                    final_color += colors;
                }

                final_color = (1.0/(NB_ANTI_ALIASING))*final_color;
            } else {
                Ray ray = Ray(center, Vector(j-W/2+0.5, i-H/2+0.5, -H/(2*std::tan(2*M_PI*fov/2/360))));

                Vector colors = Vector();
                for (int k = 0; k < NB_RAY; ++k) {
                    colors += getColor(ray, light, scene, 0, 0, current_indice);
                }
                colors = (1.0/(NB_RAY))*colors;

                final_color += colors;
            }


            double red   = std::min(255.0, 255.0*std::pow(final_color[0], 1./2.2));
            double green = std::min(255.0, 255.0*std::pow(final_color[1], 1./2.2));
            double blue  = std::min(255.0, 255.0*std::pow(final_color[2], 1./2.2));

            pixels[H*i+j]       = red;
            pixels[H*i+j+H*W]   = green;
            pixels[H*i+j+2*H*W] = blue;
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

