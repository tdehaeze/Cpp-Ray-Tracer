#ifndef DEF_RAY
#define DEF_RAY

class Object {
public:
    Vector origin;
    Vector direction;
    Ray(Vector orig, Vector direct);
    double getDistanceToSphere(const Sphere sphere);
    double getIntensity(const Sphere sphere, double t, Light light);
    /* N'appelez cette fonction que si il y a une intersection */
    /* Vector getIntersect(const Sphere sphere); */
};

#endif

