#include "main.h"

#define Z_CAMERA 60
#define ALPHA_DIFF 0.2
#define NB_RAY 10
#define MAX_BOUNCE 5
#define MAX_REFRACT 5
#define NB_ANTI_ALIASING 10
#define ANTI_ALIASING false
#define CST_FRESNEL true

std::default_random_engine engine;
std::uniform_real_distribution <double> distrib(0,1);
std::normal_distribution<double> distribution(-0.5,0.5);

Scene defineScene()
{
    Scene scene = Scene();

    /* Colors */
    Vector c_blue   = Vector(25,  25,  112);
    Vector c_red    = Vector(178, 34,  34);
    Vector c_green  = Vector(154, 205, 50);
    Vector c_cyan   = Vector(0,   139, 139);
    Vector c_orange = Vector(210, 105, 30);
    Vector c_grey   = Vector(130, 130, 130);

    /* Types */
    Vector t_specular    = Vector(1., 0., 0.);
    Vector t_transparent = Vector(0., 1., 0.);
    Vector t_mirroir     = Vector(0., 0., 1.);

    /* Materials */
    Material* m_blue   = new Material(c_blue,   t_specular);
    Material* m_red    = new Material(c_red,    t_specular);
    Material* m_green  = new Material(c_green,  t_specular);
    Material* m_cyan   = new Material(c_cyan,   t_specular);
    Material* m_orange = new Material(c_orange, t_specular);
    Material* m_grey   = new Material(c_grey,   t_specular);
    Material* m_transparent   = new Material(c_grey,   t_transparent, 1.3);
    Material* m_air   = new Material(c_grey,   t_transparent, 1.);

    Material* m_mirroir   = new Material(c_grey,   t_mirroir, 2.);

    Material* m_light  = new Material(c_grey,   t_specular, 1., 10.);

    /* 
     * droite -> (+, 0, 0)
     * haut -> (0, -, 0)
     * avant -> (0, 0, -)
     * */

    /* Sphere* sphere_1 = new Sphere(Vector(-12, 20, -40), 10, m_red); */
    /* scene.addObject(sphere_1); */
    /* Sphere* sphere_5 = new Sphere(Vector(12, 10, -40), 10, m_transparent); */
    /* scene.addObject(sphere_5); */
    /* Sphere* sphere_2 = new Sphere(Vector(10, 0, 0), 3, m_light); */
    /* scene.addObject(sphere_2); */

    /* Sphere* sphere_3 = new Sphere(Vector(5, 27, -27), 3, m_orange); */
    /* scene.addObject(sphere_3); */
    /* Sphere* sphere_4 = new Sphere(Vector(-5, 10, -40), 5, m_red); */
    /* scene.addObject(sphere_4); */

    /* Sphere* sphere_6 = new Sphere(Vector(10, 15, -40), 10, m_red); */
    /* scene.addObject(sphere_6); */
    /* Sphere* sphere_7 = new Sphere(Vector(10, 5, -40), 10, m_mirroir); */
    /* scene.addObject(sphere_7); */

    /* Cube* cube_1 = new Cube(Vector(0, 35, -50), Vector(20, 0, 0), Vector(0, -20, 0), Vector(0, 0, 20), m_red); */
    /* scene.addObject(cube_1); */

    /* Difference * mirroir_convexe = new Difference(cube_1, sphere_6); */
    /* Difference * mirroir_convexe = new Difference(sphere_6, cube_1); */
    /* Difference * mirroir_convexe = new Difference(sphere_6, sphere_7); */
    /* scene.addObject(mirroir_convexe); */

    Cube* cube_2 = new Cube(Vector(-10, -30, -60), Vector(2, 0, 0), Vector(0, 1, 0), Vector(0, 0, 2), m_light);
    scene.addObject(cube_2);

    Sphere* sphere_3 = new Sphere(Vector(10, 15, -10), 5, m_transparent);
    scene.addObject(sphere_3);
    Sphere* sphere_4 = new Sphere(Vector(10, 15, -10), 4.9, m_air);
    scene.addObject(sphere_4);

    /* Sphere* sphere_2 = new Sphere(Vector(0, 0, -39), 40, transparent); */
    /* Union * union_1 = new Union(sphere_1, sphere_2); */
    /* Intersection * intersection_1 = new Intersection(sphere_1, sphere_2); */
    /* Sphere* sphere_3 = new Sphere(Vector(3, 0, -7), 2, green); */

    Plan* plan_right = new Plan(Vector(30, 0, 0), Vector(-1, 0, 0), m_red);
    scene.addObject(plan_right);
    Plan* plan_left = new Plan(Vector(-30, 0, 0), Vector(1, 0, 0), m_green);
    scene.addObject(plan_left);
    Plan* plan_bottom = new Plan(Vector(0, 30, 0), Vector(0, -1, 0), m_cyan);
    scene.addObject(plan_bottom);
    Plan* plan_top = new Plan(Vector(0, -30, 0), Vector(0, 1, 0), m_blue);
    scene.addObject(plan_top);
    Plan* plan_front = new Plan(Vector(0, 0, 100), Vector(0, 0, -1), m_grey);
    scene.addObject(plan_front);
    Plan* plan_back = new Plan(Vector(0, 0, -80), Vector(0, 0, 1), m_orange);
    scene.addObject(plan_back);

    /* Cylindre * cylindre = new Cylindre(Vector(10, 10, -20), Vector(0, -10, 0), 9, mirroir); */
    /* Sphere* sphere_inside = new Sphere(Vector(0, -10, 0), 8, mirroir); */
    /* Difference * cylindre_creux = new Difference(cylindre, sphere_inside); */
    /* Sphere* sphere_outside = new Sphere(Vector(0, -10, 0), 9, mirroir); */
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

Vector getEffectiveColor(Ray ray, Scene scene, int bounce, int refract, double current_indice, Inter* inter) {
    /* std::cout << "MAX BOUNCE" << std::endl; */
    /* get random emissive object */
    Object* emissive_object = scene.getRandomEmissiveObject();
    /* get random ray to the emissive object */
    Ray ray_to_light = emissive_object->getRandomRayToObject(inter->getPointBeforeIntersect());
    /* std::cout << "EMISSIVITY of emissive object : " << emissive_object->getMaterial()->getEmissivity() << std::endl; */

    Inter* inter_light = new Inter(scene, ray_to_light, current_indice);
    /* std::cout << "EMISSIVITY : " << inter_light->getObject()->getMaterial()->getEmissivity() << std::endl; */

    if (inter_light->getObject() == 0) {
        /* if there is no object from the ray to light
         * this should never happen because the light itself is an object */
        std::cout << "should never go here" << std::endl;
        return Vector(0, 0, 0);
    } else {
        if (inter_light->getObject()->getMaterial()->getEmissivity() > 0) {
            /* if the ray crosses a light */
            double intensity = inter->getIntensity(ray_to_light);
            double emissivity = inter_light->getObject()->getMaterial()->getEmissivity();
            /* std::cout << "intensity : " << intensity << std::endl; */
            /* std::cout << "emissivity : " << emissivity << std::endl; */
            return emissivity*intensity*inter->getObject()->getMaterial()->getColor();
        } else if (bounce < MAX_BOUNCE && refract < MAX_REFRACT) {
            /* If we still have some bounce and refract */
            double type = distrib(engine);
            if (type < inter_light->getObject()->getMaterial()->getSpecularity()) {
                /* The object is only secular => shadow */
                return Vector(0, 0, 0);
            } else if (type < inter_light->getObject()->getMaterial()->getSpecularity() + inter_light->getObject()->getMaterial()->getTransparency()) {
                /* Transparent Object */
                /* std::cout << "Transparent" << std::endl; */

                double R = getReflectivity(current_indice, inter_light, ray_to_light);

                if (distrib(engine) < R) {
                    /* reflexion */
                    return getColor(inter_light->getReflectedRay(ray_to_light), scene, bounce+1, refract, current_indice);
                } else {
                    /* transmision */
                    return getColor(inter_light->getRefractedRay(ray_to_light), scene, bounce, refract+1, inter_light->getIndiceAfter());
                }
            } else {
                /* Reflective Object */
                /* std::cout << "Reflective" << std::endl; */
                return getColor(inter_light->getReflectedRay(ray_to_light), scene, bounce+1, refract, current_indice);
            }
        } else {
            /* there is an object between the point and the light
             * and we reach the max bounce or refract */
            return Vector(0, 0, 0);
        }
    }

}

Vector getColor(Ray ray, Scene scene, int bounce, int refract, double current_indice) {
    Inter* inter = new Inter(scene, ray, current_indice);

    if (inter->getObject() != 0 && bounce < MAX_BOUNCE && refract < MAX_REFRACT) {
        if (inter->getObject()->getMaterial()->getEmissivity() > 0.) {
            /* if the sphere is a light */
            /* std::cout << "Ray is crossing and emissive object" << std::endl; */
            return inter->getObject()->getMaterial()->getEmissivity()*inter->getObject()->getMaterial()->getColor();
        }

        double type = distrib(engine);

        if (type < inter->getObject()->getMaterial()->getSpecularity()) {
            /* Specular Object */
            if(distrib(engine) < ALPHA_DIFF) {
                /* ray to light */
                return getEffectiveColor(ray, scene, bounce, refract, current_indice, inter);
            } else {
                /* random ray */
                return (2./(M_PI))*inter->getObject()->getMaterial()->getColor().elementWizeProduct(getColor(inter->getRandomRay(), scene, bounce+1, refract, current_indice));
                /* return color_object + (2./(M_PI))*color_object.elementWizeProduct(getColor(reflected_ray, light, scene, bounce, refract, current_indice)); */
            }
        } else if (type < inter->getObject()->getMaterial()->getSpecularity() + inter->getObject()->getMaterial()->getTransparency()) {
            /* Transparent Object */
            /* std::cout << "Transparent" << std::endl; */

            double R = getReflectivity(current_indice, inter, ray);

            if (distrib(engine) < R) {
                /* reflexion */
                return getColor(inter->getReflectedRay(ray), scene, bounce+1, refract, current_indice);
            } else {
                /* transmision */
                return getColor(inter->getRefractedRay(ray), scene, bounce, refract+1, inter->getIndiceAfter());
            }
        } else {
            /* Reflective Object */
            /* std::cout << "Reflective" << std::endl; */
            return getColor(inter->getReflectedRay(ray), scene, bounce+1, refract, current_indice);
        }
    } else if (inter->getObject() != 0 && bounce == MAX_BOUNCE) {
        /* si on a atteind le max de bounce => on prend un rayon vers la lumière */
        return getEffectiveColor(ray, scene, bounce, refract, current_indice, inter);
    }
    /* std::cout << "pas top..." << std::endl; */
    return Vector(0, 0, 0);
}

void progressBar(double progress) {
    int barWidth = 70;

    std::cout << "[";
    int pos = barWidth * progress;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

int main()
{
    const int W = 1024; /* width: number of pixels */
    const int H = 1024; /* height: number of pixels */

    const Vector center = Vector(0, 0, Z_CAMERA); /* point of view: start point for the ray, we look at the negative z */
    const int fov = 40; /* field of view */

    /* Light light = Light(Vector(-20, -20, 50), 100000000, 10); /1* setup the light source position and luminosity *1/ */

    Scene scene = defineScene();

    std::vector<unsigned char> pixels(3*H*W,0); /* define the array of pixels */

    double current_indice = 1.0;

    auto start = std::chrono::steady_clock::now();

#pragma omp parallel for schedule(dynamic,1)

    /* for each pixels */
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < H; j++) {
    /* for (int i = W-200; i < W; i++) { */
    /*     for (int j = H-200; j < H; j++) { */
            Vector final_color = Vector(0, 0, 0);
            if (ANTI_ALIASING) {
                for (int l = 0; l < NB_ANTI_ALIASING; ++l) {
                    double x = distribution(engine);
                    double y = distribution(engine);
                    Ray ray = Ray(center, Vector(j+x-W/2, i+y-H/2, -H/(2*std::tan(2*M_PI*fov/2/360))));

                    /* Ray ray = Ray(center, (j-W/2+u-0.5)*right + (i-H/2+v-0.5)*up + depth*direction); */

                    Vector colors = Vector();
                    for (int k = 0; k < NB_RAY; ++k) {
                        colors += getColor(ray, scene, 0, 0, current_indice);
                    }

                    colors = (1.0/(NB_RAY))*colors;

                    final_color += colors;
                }

                final_color = (1.0/(NB_ANTI_ALIASING))*final_color;
            } else {
                Ray ray = Ray(center, Vector(j-W/2+0.5, i-H/2+0.5, -H/(2*std::tan(2*M_PI*fov/2/360))));

                Vector colors = Vector();
                for (int k = 0; k < NB_RAY; ++k) {
                    colors += getColor(ray, scene, 0, 0, current_indice);
                }
                colors = (1.0/(NB_RAY))*colors;

                final_color = colors;
            }

            /* std::cout << final_color << std::endl; */

            double red   = std::min(255.0, 255.0*std::pow(final_color[0], 1./2.2));
            double green = std::min(255.0, 255.0*std::pow(final_color[1], 1./2.2));
            double blue  = std::min(255.0, 255.0*std::pow(final_color[2], 1./2.2));

            pixels[H*i+j]       = red;
            pixels[H*i+j+H*W]   = green;
            pixels[H*i+j+2*H*W] = blue;
        }
        if (i%10 == 0)
            progressBar((double) i/H);
        /*     std::cout << 100*i/H << "%\n"; */
    }

    auto end = std::chrono::steady_clock::now();
    auto diff_time = end-start;

    std::cout << std::chrono::duration <double, std::milli> (diff_time).count() << std::endl;

	if (DEBUG) std::cout << "writing file..." << std::endl;
    cimg_library::CImg<unsigned char> cimg(&pixels[0], W, H, 1, 3);
    cimg.save("fichier.bmp");

    return 0;
}

