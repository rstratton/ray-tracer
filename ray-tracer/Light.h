#pragma once
#include "Vector.h"

struct Light {
    Vector position, color;
    Light(Vector p, Vector c) : position(p), color(c) {};
};

