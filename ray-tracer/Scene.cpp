#include "Scene.h"
#include "RayHit.h"
#include "util.h"

void Scene::addLight(Light l) {
    lights.push_back(l);
}

void Scene::addObject(SceneObject* s) {
    objects.push_back(s);
}

Vector Scene::sampleRadiance(Ray r, int reflectionDepth) {
    if (reflectionDepth == 0)
        int foo = 0;
    RayHit hit;
    Vector radiance(0.f, 0.f, 0.f);
    
    if (!rayIntersectsObject(r, hit)) {
        return radiance;
    }

    radiance += radianceFromLights(hit);

    if (reflectionDepth > 0) {
        // TODO: Incorporate radiance from multiple sources more intelligently
        radiance += sampleRadiance(hit.mirror(), reflectionDepth - 1);
    }

    return radiance;
}

Vector Scene::radianceFromLights(RayHit hit) {
    Vector radiance(0.f, 0.f, 0.f);
    for (size_t i = 0; i < lights.size(); ++i) {
        Vector lightDir = (lights[i].position - hit.position).normalized();
        Ray toLight(hit.position + lightDir * 0.001f, lightDir);
        float val = hit.normal.dot(toLight.direction);

        RayHit _hit;
        if (val > 0.f && !rayIntersectsObject(toLight, _hit)) {
            radiance = radiance + lights[i].color * max(val, 0.f);
        }
    }
    return radiance;
}

bool Scene::rayIntersectsObject(Ray r, RayHit& h) {
    RayHit currentHit, closestHit;
    bool hasHit = false;

    for (size_t i = 0; i < objects.size(); ++i) {
        SceneObject* s = objects[i];
        if (s->intersects(r, currentHit)) {
            if (hasHit) {
                if ((closestHit.position - r.start).sqmag() > (currentHit.position - r.start).sqmag()) {
                    closestHit = currentHit;
                }
            } else {
                closestHit = currentHit;
                hasHit = true;
            }
        }
    }

    h = closestHit;
    return hasHit;
}