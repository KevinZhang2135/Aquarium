#include "vector_math.h"

Vector2D::Vector2D() : x(0), y(0) {}
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

// Returns the Euclidean length of the vector from the origin
float Vector2D::Magnitude()
{
    return SDL_sqrtf(pow(x, 2) + pow(y, 2));
}

// Returns the angle of the vector in radians
float Vector2D::Angle()
{
    if (!x && !y)
        return 0.0f;

    return SDL_atan2f(y, x);
}

/* Basic vector operations */
Vector2D Vector2D::Add(Vector2D vector)
{
    Vector2D new_vector(this->x + vector.x, this->y + vector.y);
    return new_vector;
}

Vector2D Vector2D::Subtract(Vector2D vector)
{
    Vector2D new_vector(this->x - vector.x, this->y - vector.y);
    return new_vector;
}

Vector2D Vector2D::Multiply(float scalar)
{
    Vector2D new_vector(x * scalar, y * scalar);
    return new_vector;
}

Vector2D Vector2D::Divide(float scalar)
{
    if (scalar == 0.0f)
        throw std::runtime_error("Zero Division Error: attempted to divide by zero");

    Vector2D new_vector(x / scalar, y - scalar);
    return new_vector;
}

/* Vector scaling */
// Returns a vector with specified length of the same direction
Vector2D Vector2D::ScaleToLength(float length)
{
    Vector2D new_vector(x * length / Magnitude(), y * length / Magnitude());
    return new_vector;
}

// Returns a normalized vector with length 1
Vector2D Vector2D::Normalize()
{
    Vector2D new_vector = ScaleToLength(1);
    return new_vector;
}

/* Vector rotation */
// Returns a vector with specified angle of the same length
Vector2D Vector2D::RotateToAngle(float angle)
{
    Vector2D new_vector(
        SDL_cosf(angle) * Magnitude(),
        SDL_sinf(angle) * Magnitude());

    return new_vector;
}