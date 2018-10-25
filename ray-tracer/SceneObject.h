#pragma once
#include "RayHit.h"

struct SceneObject {
    virtual bool intersects(Ray, RayHit&) { return false; };
};

