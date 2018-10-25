#include "Sphere.h"
#include "RayHit.h"
#include <cmath>

bool Sphere::intersects(Ray r, RayHit& h) {
    float a = r.direction.sqmag();
    Vector v = r.start - position;
    float b = 2 * r.direction.dot(v);
    float c = v.sqmag() - radius * radius;
    float disc = b * b - 4 * a*c;
    if (disc < 0) return false;
    //we only care about the minus in the plus or minus
    float t = (-b - sqrt(disc)) / (2 * a);
    if (t < 0) return false;

    h.position = r.start + r.direction * t;
    h.normal = (h.position - position).normalized();
    h.ray = r;
    return true;
}