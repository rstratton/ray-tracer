#include "Vector.h"
#include "Camera.h"
#include "Light.h"
#include "Scene.h"
#include "Plane.h"

#pragma warning(disable:4996)

const int WIDTH = 4000;
const int HEIGHT = 4000;

void writePPM(unsigned char *buf, int width, int height, const char *fn) {
    FILE *fp = fopen(fn, "wb");
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "255\n");
    for (int i = 0; i < width*height*3; ++i) {
        // Map the iteration count to colors by just alternating between
        // two greys.

        fputc(buf[i], fp);
    }
    fclose(fp);
    printf("Wrote image file %s\n", fn);
}

int main(int argc, char** argv) {
    Camera c = Camera(WIDTH, HEIGHT, Vector(0, 3, 15));
    Scene s;
    s.addLight(Light(Vector(100, 100, 50), Vector(1.f, 1.f, 0.8f)));
    s.addLight(Light(Vector(-100, 20, -20), Vector(0.8f, 0.8f, 1.0f)));

    for (int i = -6; i < 7; i += 3) {
        for (int j = 0; j < 15; j += 3) {
            s.addObject(
                new Sphere(
                    Vector(i, 0, -j),
                    1.0f
                )
            );
        }
    }

    s.addObject(new Plane(Vector(0.f, 1.f, 0.f), Vector(0.f, -1.f, 0.f)));

    unsigned char* pixels = c.render(s);
    writePPM(pixels, WIDTH, HEIGHT, "..\\renders\\image.ppm");
	return 0;
}
