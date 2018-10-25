#pragma once
struct Vector {
    float x, y, z;

    Vector() : x(0.f), y(0.f), z(0.f) {};
    Vector(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};

    Vector operator+(Vector);
    Vector& operator+=(const Vector&);
    Vector operator-(Vector);
    Vector operator-();
    Vector operator*(float);
    Vector operator/(float);
    Vector normalized();
    float mag();
    float sqmag();
    float dot(Vector);
};

Vector operator*(float, Vector);

