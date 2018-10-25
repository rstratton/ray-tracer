#pragma once
#include "Vector.h"
#include "Scene.h"

struct Camera {
    const float FOV = 60.f;
    const int width, height;
    Vector position;

    Camera(int w, int h, Vector p) : width(w), height(h), position(p) {};
    unsigned char* render(Scene&);
};
