#pragma once
#include "Vector.h"
struct Ray {
    Vector start, direction;
    Ray() {};
    Ray(Vector s, Vector d) : start(s), direction(d) {};
};