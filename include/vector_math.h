#pragma once

#include <unordered_map>
#include <stdexcept>
#include "SDL.h"

using namespace std;

class Vector2D {
    public:
        float x, y;

        Vector2D();
        Vector2D(float x, float y);

        bool operator==(const Vector2D other) const;

        float Magnitude();
        float Angle();

        /* Basic vector operations */
        Vector2D Add(Vector2D vector);
        Vector2D Subtract(Vector2D vector);
        Vector2D Multiply(float scalar);
        Vector2D Divide(float scalar);

        /* Vector scaling */
        Vector2D ScaleToLength(float length);
        Vector2D Normalize();

        /* Vector rotation */
        Vector2D RotateToAngle(float angle);

        /* Distance */
        float DistanceTo(Vector2D point);
        Vector2D MoveTowards(Vector2D point, float length);
        Vector2D MoveTowards(float angle, float length);
};

template <>
struct hash<Vector2D> {
    size_t operator()(const Vector2D &point) const;
};