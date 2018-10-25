#include "RayHit.h"

Ray RayHit::mirror() {
    Vector v = -ray.direction.normalized(), n = normal.normalized();
    Vector direction = (n * (2 * v.dot(n))) - v;
    return Ray(position, direction);
}