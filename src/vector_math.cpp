#include "vector_math.h"

Vector2D::Vector2D(): x(0), y(0) {}
Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

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

// Returns the Euclidean length of the vector from the origin
float Vector2D::Magnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2));
}

// Returns the angle of the vector
float Vector2D::Angle()
{
    M_PI;
    return 1.0f;
}

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
