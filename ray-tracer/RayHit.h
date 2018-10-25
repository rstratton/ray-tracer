#pragma once
#include "Vector.h"
#include "Ray.h"

struct RayHit {
    Vector position;
    Vector normal;
    Ray ray;

    RayHit() {};
    RayHit(const RayHit& h) : position(h.position), normal(h.normal), ray(h.ray) {};
    RayHit(Vector ip) : position(ip) {};
    Ray mirror();
};

