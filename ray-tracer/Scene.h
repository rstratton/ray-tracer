#pragma once
#include "Light.h"
#include "Sphere.h"
#include <vector>
using std::vector;

struct Scene {
    vector<Light> lights;
    vector<SceneObject*> objects;

    Scene() {};
    void addLight(Light);
    void addObject(SceneObject*);
    Vector sampleRadiance(Ray ray, int reflectionDepth);
    Vector radianceFromLights(RayHit hit);
    bool rayIntersectsObject(Ray, RayHit&);
};

