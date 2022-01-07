//============================================================
// STUDENT NAME: SHAELYN LAM
// NUS User ID.: E0420477
// COMMENTS TO GRADER:
//
// ============================================================

#include <cmath>
#include "Sphere.h"

using namespace std;



bool Sphere::hit( const Ray &r, double tmin, double tmax, SurfaceHitRecord &rec ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    Vector3d rayOrigin = r.origin() - center;

    double a = 1;
    double b = 2.0 * dot(r.direction(), rayOrigin);
    double c = dot(rayOrigin, rayOrigin) - radius * radius;

    double discriminant = b * b - 4 * a * c;
   
    if (discriminant <= 0) return false;

    double t0 = (-b - pow(discriminant, 0.5)) / (2 * a);
    double t1 = (-b + pow(discriminant, 0.5)) / (2 * a);
    double t;

    if (t0 < tmin && t1 < tmin) {
        return false;
    }
    else if (t0 >= tmin && t1 <= tmin) {
        t = t0;
    }
    else if (t0 <= tmin && t1 >= tmin) {
        t = t1;
    }
    else {
        t = min(t0, t1);
    }

    if (t < tmin || t > tmax) return false;

    // We have a hit -- populate hit record. 
    rec.t = t;
    rec.p = r.pointAtParam(t);
    Vector3d eqn = rec.p - center;
    rec.normal = eqn;
    rec.material = material;
    return true;
}



bool Sphere::shadowHit( const Ray &r, double tmin, double tmax ) const 
{
    //***********************************************
    //*********** WRITE YOUR CODE HERE **************
    //***********************************************
    Vector3d rayOrigin = r.origin() - center;

    double a = 1;
    double b = 2.0 * dot(r.direction(), rayOrigin);
    double c = dot(rayOrigin, rayOrigin) - radius * radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant <= 0) return false;

    double t0 = (-b - pow(discriminant, 0.5)) / (2 * a);
    double t1 = (-b + pow(discriminant, 0.5)) / (2 * a);
    double t;

    if (t0 < tmin && t1 < tmin) {
        return false;
    }
    else if (t0 >= tmin && t1 <= tmin) {
        t = t0;
    }
    else if (t0 <= tmin && t1 >= tmin) {
        t = t1;
    }
    else {
        t = min(t0, t1);
    }

    return (t >= tmin && t <= tmax);
}
