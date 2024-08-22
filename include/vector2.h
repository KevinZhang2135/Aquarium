#pragma once

#include <unordered_map>
#include <stdexcept>
#include "SDL.h"

using namespace std;

class Vector2 {
    public:
        float x, y;

        Vector2();
        Vector2(float x, float y);

        bool operator==(const Vector2 other) const;

        float Magnitude();
        float Angle();

        /* Basic vector operations */
        Vector2 Add(Vector2 vector);
        Vector2 Subtract(Vector2 vector);
        Vector2 Multiply(float scalar);
        Vector2 Divide(float scalar);

        /* Vector scaling */
        Vector2 ScaleToLength(float length);
        Vector2 Normalize();

        /* Vector rotation */
        Vector2 RotateToAngle(float angle);

        /* Distance */
        float DistanceTo(Vector2 point);
        Vector2 MoveTowards(Vector2 point, float length);
        Vector2 MoveTowards(float angle, float length);
};

template <>
struct hash<Vector2> {
    size_t operator()(const Vector2 &point) const;
};