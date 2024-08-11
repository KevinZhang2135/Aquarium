#pragma once
#include <stdexcept>
#include "SDL2/SDL.h"

class Vector2D {
    public:
        float x, y;

        Vector2D();
        Vector2D(float x, float y);

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
      
};