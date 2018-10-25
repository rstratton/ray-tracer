#include "Vector.h"
#include <cmath>

Vector Vector::operator+(Vector o) {
    return Vector(
        x + o.x,
        y + o.y,
        z + o.z
    );
}

Vector& Vector::operator+=(const Vector& o) {
    x += o.x;
    y += o.y;
    z += o.z;
    return *this;
}

Vector Vector::operator-(Vector o) {
    return Vector(
        x - o.x,
        y - o.y,
        z - o.z
    );
}

Vector Vector::operator-() {
    return Vector(-x, -y, -z);
}

Vector Vector::operator*(float f) {
    return Vector(
        f * x,
        f * y,
        f * z
    );
}

Vector Vector::operator/(float f) {
    return Vector(
        x / f,
        y / f,
        z / f
    );
}

Vector Vector::normalized() {
    return (*this) / mag();
}

float Vector::mag() {
    return sqrt(sqmag());
}

float Vector::sqmag() {
    return x*x + y*y + z*z;
}

float Vector::dot(Vector o) {
    return x * o.x + y * o.y + z * o.z;
}

Vector operator*(float f, Vector v) {
    return Vector(
        f * v.x,
        f * v.y,
        f * v.z
    );
}