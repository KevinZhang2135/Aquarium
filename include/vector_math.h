#pragma once
#include <cmath>
#include <stdexcept>

class Vector2D {
    public:
        float x, y;

        Vector2D();
        Vector2D(float x, float y);

        Vector2D Add(Vector2D vector);
        Vector2D Subtract(Vector2D vector);
        Vector2D Multiply(float scalar);
        Vector2D Divide(float scalar);

        float Magnitude();
        float Angle();

        Vector2D ScaleToLength(float length);
        Vector2D Normalize();

        
        
};