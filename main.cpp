#include <stdio.h>
#include <math.h>
#include <vector>
#include "CImg/CImg.h"

#include "Vector.h"
#include "Ray.h"
#include "Sphere.h"
#include "Light.h"
#include "Scene.h"
#include "Material.h"

using namespace std;

int main()
{
    const int W = 1024;
    const int H = 1024;

    const Vector center = Vector(0, 0, 55);
    const int fov = 60;

    Ray ray = Ray (center, Vector(0, 0, 1));

    Scene scene = Scene();
    scene.addSphere(Sphere(Vector(0, 0, -10), 20, Vector(100, 100, 100)));
    scene.addSphere(Sphere(Vector(-1000, 0, 0), 970, Vector(0, 0, 100)));
    scene.addSphere(Sphere(Vector(1000, 0, 0), 970, Vector(0, 100, 0)));
    scene.addSphere(Sphere(Vector(0, 1000, 0), 970, Vector(100, 0, 0)));
    scene.addSphere(Sphere(Vector(0, -1000, 0), 970, Vector(0, 100, 100)));
    scene.addSphere(Sphere(Vector(0, 0, -1000), 970, Vector(100, 0, 100)));

    Light light = Light(Vector(-10, -10, 50), 1000000);

    /* Définition du tableau de pixels */
    vector<unsigned char> pixels(3*H*W,0);

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            Vector rayDirection = Vector(j-W/2+0.5, i-H/2+0.5, -H/(2*tan(2*M_PI*fov/2/360)));
            rayDirection.Normalize();

            ray = Ray(center, rayDirection);

            Sphere firstSphere = scene.getSphere(ray);

            if (firstSphere.radius > 0) {
                double t = ray.getIntersect(firstSphere);

                if (t > 0){
                    double intensity = ray.getIntensity(firstSphere, t, light);
                    double red   = min(255.0, intensity*firstSphere.material[0]);
                    double green = min(255.0, intensity*firstSphere.material[1]);
                    double blue  = min(255.0, intensity*firstSphere.material[2]);
                    pixels[H*i+j] = red;
                    pixels[H*i+j+H*W] = green;
                    pixels[H*i+j+2*H*W] = blue;
                } else {
                    pixels[H*i+j] = 0;
                    pixels[H*i+j+H*W] = 0;
                    pixels[H*i+j+2*H*W] = 0;
                }
            }
        }
    }

    cimg_library::CImg<unsigned char> cimg(&pixels[0], W, H, 1, 3);
    cimg.save("fichier.bmp");
    return 0;
}

