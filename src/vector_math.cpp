#include "vector_math.h"

Vector2D::Vector2D() : x{0}, y{0} {}
Vector2D::Vector2D(float x, float y) : x{x}, y{y} {}

// Returns the Euclidean length of the vector from the origin
float Vector2D::Magnitude()
{
    return SDL_sqrtf(powf(x, 2) + powf(y, 2));
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
    return {Vector2D(this->x + vector.x, this->y + vector.y)};
}

Vector2D Vector2D::Subtract(Vector2D vector)
{
    return {Vector2D(this->x - vector.x, this->y - vector.y)};
}

Vector2D Vector2D::Multiply(float scalar)
{
    return {Vector2D(x * scalar, y * scalar)};
}

Vector2D Vector2D::Divide(float scalar)
{
    if (scalar == 0.0f)
        throw std::runtime_error("Zero Division Error: attempted to divide by zero");

    return {Vector2D(x / scalar, y / scalar)};
}

/* Vector scaling */
// Returns a vector with specified length of the same direction
Vector2D Vector2D::ScaleToLength(float length)
{
    if (Magnitude() == 0.0f)
        return {Vector2D()};

    float scalar = length / Magnitude();
    return Multiply(scalar);
}

// Returns a normalized vector with length 1
Vector2D Vector2D::Normalize()
{
    return ScaleToLength(1);
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

/* Distance */
// Returns the Euclidean distance to the point
float Vector2D::DistanceTo(Vector2D point)
{
    float dx = point.x - this->x; // difference in x
    float dy = point.y - this->y; // difference in y

    return sqrtf(powf(dx, 2) + powf(dy, 2));
}

// Returns a vector of length moved towards the specified point
Vector2D Vector2D::MoveTowards(Vector2D point, float length) {
    return point.Subtract(*this).ScaleToLength(length);
}

// Returns a vector moved length towards the specified angle
Vector2D Vector2D::MoveTowards(float angle, float length) {
    Vector2D displacement (length, 0);
    displacement = displacement.RotateToAngle(angle);

    return Add(displacement);
}