#include "Plane.h"

bool Plane::intersects(Ray r, RayHit& h) {
    // Taken from graphicscodex.com
    // t = ((P - C).dot(n)) / (w.dot(n))
    // Ray equation: X(t) = P + t*w
    float numerator = (r.start - center).dot(normal);
    float denominator = r.direction.dot(normal);
    if (denominator >= 0) return false;
    float t = -numerator / denominator;
    if (t < 0) return false;
    h.normal = normal;
    h.position = r.start + t*r.direction;
    h.ray = r;
    return true;
}
