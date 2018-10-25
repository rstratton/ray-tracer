#include "Camera.h"
#include "Ray.h"
#include "Scene.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "util.h"

float degToRad(float deg) {
    return deg * M_PI / 180.f;
}

unsigned char* Camera::render(Scene& scene) {
    float w_prime = 2 * tanf(degToRad(FOV / 2));
    float h_prime = (w_prime * height) / width;

    float w_start = -w_prime / 2;
    float h_start = h_prime / 2;

    float w_step = w_prime / width;
    float h_step = -h_prime / height;

    unsigned char* pixelBuf = new unsigned char[width * height * 3];

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Ray ray = Ray(position, Vector(w_start + j*w_step, h_start + i*h_step, -1.f).normalized());
            Vector radiance = scene.sampleRadiance(ray, 3);
            pixelBuf[3*i*width + 3*j + 0] = min(radiance.x * 255, 255);
            pixelBuf[3*i*width + 3*j + 1] = min(radiance.y * 255, 255);
            pixelBuf[3*i*width + 3*j + 2] = min(radiance.z * 255, 255);
        }
    }

    return pixelBuf;
}
