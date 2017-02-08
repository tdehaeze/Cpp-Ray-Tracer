#include "main.h"

#define EPSILON 0.001
#define Z_CAMERA 60

/* Define the scene with all the spheres and return the scene object */
Scene defineScene()
{
    Scene scene = Scene();
    int sphere_size = 10000;
    int top         = 40;
    int bottom      = 10;
    int right       = 30;
    int left        = 30;
    int front       = 80;
    int back        = 10;

    /* origine, radius, color, mirror, transparent, indice */
    int radius           = 10;
    int from_bottom      = 0;
    int from_front       = 30;
    int horizontal_right = 0;
    scene.addSphere(Sphere(Vector(horizontal_right, bottom-radius-from_bottom, -front+radius+from_front+Z_CAMERA), radius, Vector(25,25,112), 0, 1, 1.1));
    radius           = 5;
    from_bottom      = 0;
    from_front       = 10;
    horizontal_right = 0;
    scene.addSphere(Sphere(Vector(horizontal_right, bottom-radius-from_bottom, -front+radius+from_front+Z_CAMERA), radius, Vector(25,25,112), 1, 0, 1));

    scene.addSphere(Sphere(Vector(-(sphere_size+left), 0,                  0),                             sphere_size, Vector(178, 34,  34),  0, 0, 1)); /* left */
    scene.addSphere(Sphere(Vector(sphere_size+right,   0,                  0),                             sphere_size, Vector(154, 205, 50),  0, 0, 1)); /* right */
    scene.addSphere(Sphere(Vector(0,                   sphere_size+bottom, 0),                             sphere_size, Vector(0,   139, 139), 0, 0, 1)); /* bottom */
    scene.addSphere(Sphere(Vector(0,                   -(sphere_size+top), 0),                             sphere_size, Vector(210, 105, 30),  0, 0, 1)); /* top */
    scene.addSphere(Sphere(Vector(0,                   0,                  -(sphere_size+front-Z_CAMERA)), sphere_size, Vector(119, 136, 153), 0, 0, 1)); /* front */
    scene.addSphere(Sphere(Vector(0,                   0,                  sphere_size+back+Z_CAMERA),     sphere_size, Vector(173, 255, 47),  0, 0, 1)); /* back */
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
    Vector intersect_point = ray.origin + dist_sphere*ray.direction + EPSILON*intersect_normal;
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

/* get the refracted ray */
Ray getRefractedRay(Ray ray, Vector intersect_point, Vector intersect_normal, double ind_before, double ind_after)
{
    double ind_frac = ind_before/ind_after;
    double prod_scalaire = abs(intersect_normal*ray.direction);

    Vector refracted_direction = ind_frac*ray.direction - (-ind_frac*prod_scalaire + sqrt(1-ind_frac*ind_frac*(1 - prod_scalaire*prod_scalaire)))*intersect_normal;
    refracted_direction.Normalize();

    if (intersect_normal*ray.direction > 0) { /* we are inside the sphere and going outside */
        return Ray(intersect_point+0.01*intersect_normal, refracted_direction);
    } else { /* we are outside the sphere and comming inside */
        return Ray(intersect_point-0.01*intersect_normal, refracted_direction);
    }
}

/* set the intensity and the color */
void setIntensity(vector<unsigned char> &pixels, int i, int j, int H, int W, Sphere sphere, double dist, Light light, Ray ray, double coef)
{
    double intensity = ray.getIntensity(sphere, dist, light);
    double red   = min(255.0, coef*intensity*sphere.material[0]);
    double green = min(255.0, coef*intensity*sphere.material[1]);
    double blue  = min(255.0, coef*intensity*sphere.material[2]);
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
        setIntensity(pixels, i, j, H, W, sphere, dist_sphere, light, ray, 1);
    } else { /* If there is one sphere on the ray path */
        double dist_sphere_bis = ray_dir_light.getDistanceToSphere(sphere_bis); /* dist_sphere_bis is the distance to the sphere */

        /* get the distance from the intersect point to the light */
        double distance_light = (light.origin - intersect_point).norm();

        if (dist_sphere_bis > 0 && dist_sphere_bis < distance_light){ /* if the sphere is between the point and the light source => shadow */
            /* std::cout << "sphere => shadow \n"; */
            if (sphere_bis.transparent == 1) {
                setIntensity(pixels, i, j, H, W, sphere, dist_sphere, light, ray, 0.3);
            } else {
                setIntensityToBlack(pixels, i, j, H, W);
            }
        } else { /* if the sphere is after the light source => light */
            setIntensity(pixels, i, j, H, W, sphere, dist_sphere, light, ray, 1);
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
            if (crossed_sphere.mirror == 1) { /* if the sphere crossed is also a mirror */
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

void setColorOfRayOnTransparent(Ray ray, Sphere sphere, Light light, Scene scene, const int max_bounce, int &bounce_counter, vector<unsigned char> &pixels, int i, int j, const int H, const int W)
{
/* ===============================
 * get the indice before crossing the sphere
 * =============================== */
    /* get the distance to the crossed sphere */
    double dist_sphere = ray.getDistanceToSphere(sphere);

    /* get the intersect point */
    Vector intersect_point = getIntersectPoint(dist_sphere, ray, sphere);

    /* get the intersect normal */
    Vector intersect_normal = getIntersectNormal(dist_sphere, ray, sphere);

    /* get a point just before crossing the sphere (depending if we where inside or outside the sphere) */
    Vector point_before_cross;
    if (intersect_normal*ray.direction > 0) {
        point_before_cross = intersect_point - 0.01*intersect_normal;
    } else {
        point_before_cross = intersect_point + 0.01*intersect_normal;
    }

    /* get the current sphere */
    Sphere current_sphere = scene.getCurrentSphere(point_before_cross);

    /* get the current indice */
    double current_indice = current_sphere.indice;

/* ===============================
 * get the indice after crossing the sphere
 * =============================== */
    /* get a point just after crossing the sphere (depending if we where inside or outside the sphere) */
    Vector point_after_cross;
    if (intersect_normal*ray.direction > 0) {
        point_after_cross = intersect_point + 0.01*intersect_normal;
    } else {
        point_after_cross = intersect_point - 0.01*intersect_normal;
    }

    /* get the next sphere */
    Sphere next_sphere = scene.getCurrentSphere(point_after_cross);

    /* get the next indice */
    double next_indice = next_sphere.indice;

    double ind_frac = current_indice/next_indice;
    double prod_scalaire = abs(intersect_normal*ray.direction);
    double frac = 1-ind_frac*ind_frac*(1 - prod_scalaire*prod_scalaire);

    if (frac < 0) { /* only reflexion */
        /* std::cout << "reflexion" << '\n'; */
        setColorOfRayOnMirror(ray, sphere, light, scene, max_bounce, bounce_counter, pixels, i, j, H, W);
    } else { /* only refraction */
        /* calculate the refracted ray */
        /* std::cout << "refraction : " << ind_frac << '\n'; */
        /* std::cout << "i : " << i << " ; j : " << j << '\n'; */
        Ray refracted_ray = getRefractedRay(ray, intersect_point, intersect_normal, current_indice, next_indice);
        mainfunction(refracted_ray, light, scene, max_bounce, bounce_counter, pixels, i, j, H, W);
    }
}

void mainfunction(Ray ray, Light light, Scene scene, const int max_bounce, int &bounce_counter, vector<unsigned char> &pixels, int i, int j, const int H, const int W)
{
    Sphere sphere = scene.getSphere(ray); /* get the first sphere that the ray crosses, if there is not, the radius of the sphere is -1 */

    if (sphere.radius <= 0) { /* If the ray cross no sphere */
        /* std::cout << "no sphere" << '\n'; */
        /* no light on the pixel => black */
        setIntensityToBlack(pixels, i, j, H, W);
    } else { /* If the ray cross one sphere */
        if (sphere.mirror == 1) { /* if the sphere is a mirror */
            setColorOfRayOnMirror(ray, sphere, light, scene, max_bounce, bounce_counter, pixels, i, j, H, W);
        } else if (sphere.transparent == 1) { /* If the sphere is transparent */
            setColorOfRayOnTransparent(ray, sphere, light, scene, max_bounce, bounce_counter, pixels, i, j, H, W);
        } else { /* if the sphere is a normal sphere */
            /* std::cout << "normal sphere" << '\n'; */
            setColorOfRayOnSphere(ray, sphere, light, scene, pixels, i, j, H, W);
        }
    }
}

int main()
{
    const int W = 1024; /* width: number of pixels */
    const int H = 1024; /* height: number of pixels */

    const Vector center = Vector(0, 0, Z_CAMERA); /* point of view: start point for the ray, we look at the negative z */
    const int fov = 60; /* field of view */

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
            mainfunction(ray, light, scene, max_bounce, bounce_counter, pixels, i, j, H, W);
        }
        if (i%10 == 0)
            std::cout << 100*i/H << "%\n";
    }

    cimg_library::CImg<unsigned char> cimg(&pixels[0], W, H, 1, 3);
    cimg.save("fichier.bmp");
    return 0;
}

