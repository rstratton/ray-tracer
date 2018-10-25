#pragma once
#include "Vector.h"
#include "RayHit.h"
#include "SceneObject.h"

struct Plane : public SceneObject {
    Vector normal, center;

    Plane(Vector n, Vector c) : normal(n), center(c) {};
    bool intersects(Ray, RayHit&);
};

