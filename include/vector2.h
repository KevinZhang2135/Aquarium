#pragma once

#include <unordered_map>
#include <stdexcept>
#include <string>
#include "SDL.h"

using namespace std;

class Vector2
{
public:
    float x, y;

    Vector2();
    Vector2(float x, float y);

    bool operator==(const Vector2 &other) const;
    bool operator!=(const Vector2 &other) const;

    Vector2 operator+() const;
    Vector2 operator-() const;

    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator*(const float &scalar) const;
    Vector2 operator/(const float &scalar) const;

    Vector2 &operator+=(const Vector2 &other);
    Vector2 &operator-=(const Vector2 &other);
    Vector2 &operator*=(const float &scalar);
    Vector2 &operator/=(const float &scalar);

    float Magnitude() const;
    float Angle() const;

    Vector2 ScaleToLength(float length) const;
    Vector2 Normalize() const;

    Vector2 RotateToAngle(float angle) const;

    float DistanceTo(Vector2 point) const;
    Vector2 MoveTowards(Vector2 point, float length) const;
    Vector2 MoveTowards(float angle, float length) const;

    std::string toString() const;
};