#pragma once
#include "Vector.h"
#include "Ray.h"
#include "RayHit.h"
#include "SceneObject.h"

struct Sphere : public SceneObject {
    Vector position;
    float radius;

    Sphere(Vector p, float r) : position(p), radius(r) {};
    bool intersects(Ray, RayHit&);
};