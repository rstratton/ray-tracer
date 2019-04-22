#include "Camera.h"
#include "Ray.h"
#include "Scene.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "util.h"
#include <thread>

constexpr auto num_threads = 16;

float degToRad(float deg) {
    return deg * M_PI / 180.f;
}

void threadJob(int threadId, Camera* camera, Scene* scene, unsigned char* pixelBuf) {
    float w_prime = 2 * tanf(degToRad(camera->FOV / 2));
    float h_prime = (w_prime * camera->height) / camera->width;

    float w_start = -w_prime / 2;
    float h_start = h_prime / 2;

    float w_step = w_prime / camera->width;
    float h_step = -h_prime / camera->height;

    int chunkSize = ceil((camera->width * camera->height) / (float)num_threads);
    int pixelStart = chunkSize * threadId;
    int pixelEnd = min(pixelStart + chunkSize, camera->width * camera->height);

    for (int k = pixelStart; k < pixelEnd; ++k) {
        int i = k / camera->width;
        int j = k % camera->width;
        Ray ray = Ray(camera->position, Vector(w_start + j * w_step, h_start + i * h_step, -1.f).normalized());
        Vector radiance = scene->sampleRadiance(ray, 3);
        pixelBuf[3 * i*camera->width + 3 * j + 0] = min(radiance.x * 255, 255);
        pixelBuf[3 * i*camera->width + 3 * j + 1] = min(radiance.y * 255, 255);
        pixelBuf[3 * i*camera->width + 3 * j + 2] = min(radiance.z * 255, 255);
    }
}

void renderThreaded(Camera* camera, Scene* scene, unsigned char* pixelBuf) {
    std::vector<std::thread> threads;
    threads.reserve(num_threads);

    for (int i = 0; i < num_threads; ++i) {
        threads.push_back(std::thread(threadJob, i, camera, scene, pixelBuf));
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }
}

void renderUnthreaded(Camera& camera, Scene& scene, unsigned char* pixelBuf) {
    float w_prime = 2 * tanf(degToRad(camera.FOV / 2));
    float h_prime = (w_prime * camera.height) / camera.width;

    float w_start = -w_prime / 2;
    float h_start = h_prime / 2;

    float w_step = w_prime / camera.width;
    float h_step = -h_prime / camera.height;

    for (int i = 0; i < camera.height; ++i) {
        for (int j = 0; j < camera.width; ++j) {
            Ray ray = Ray(camera.position, Vector(w_start + j*w_step, h_start + i*h_step, -1.f).normalized());
            Vector radiance = scene.sampleRadiance(ray, 3);
            pixelBuf[3*i*camera.width + 3*j + 0] = min(radiance.x * 255, 255);
            pixelBuf[3*i*camera.width + 3*j + 1] = min(radiance.y * 255, 255);
            pixelBuf[3*i*camera.width + 3*j + 2] = min(radiance.z * 255, 255);
        }
    }
}

unsigned char* Camera::render(Scene& scene) {
    
    unsigned char* pixelBuf = new unsigned char[width * height * 3];

    //renderUnthreaded(*this, scene, pixelBuf);
    renderThreaded(this, &scene, pixelBuf);

    return pixelBuf;
}

