#include "vector2.h"

Vector2::Vector2() : x{0}, y{0} {}
Vector2::Vector2(float x, float y) : x{x}, y{y} {}

bool Vector2::operator==(const Vector2 other) const
{
    return (this->x == other.x && this->y == other.y);
}

// Returns the Euclidean length of the vector from the origin
float Vector2::Magnitude() const
{
    return SDL_sqrtf(powf(x, 2) + powf(y, 2));
}

// Returns the angle of the vector in radians
float Vector2::Angle() const
{
    if (!x && !y)
        return 0.0f;

    return SDL_atan2f(y, x);
}

/* Basic vector operations */
Vector2 Vector2::Add(Vector2 vector) const
{
    return Vector2(this->x + vector.x, this->y + vector.y);
}

Vector2 Vector2::Subtract(Vector2 vector) const
{
    return Vector2(this->x - vector.x, this->y - vector.y);
}

Vector2 Vector2::Multiply(float scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::Divide(float scalar) const
{
    if (scalar == 0.0f)
        throw std::runtime_error("Zero Division Error: attempted to divide by zero");

    return Vector2(x / scalar, y / scalar);
}

/* Vector scaling */
// Returns a vector with specified length of the same direction
Vector2 Vector2::ScaleToLength(float length) const
{
    if (Magnitude() == 0.0f)
        return Vector2();

    float scalar = length / Magnitude();
    return Multiply(scalar);
}

// Returns a normalized vector with length 1
Vector2 Vector2::Normalize() const
{
    return ScaleToLength(1);
}

/* Vector rotation */
// Returns a vector with specified angle of the same length
Vector2 Vector2::RotateToAngle(float angle) const
{
    Vector2 new_vector(
        SDL_cosf(angle) * Magnitude(),
        SDL_sinf(angle) * Magnitude());

    return new_vector;
}

/* Distance */
// Returns the Euclidean distance to the point
float Vector2::DistanceTo(Vector2 point) const
{
    float dx = point.x - this->x; // difference in x
    float dy = point.y - this->y; // difference in y

    return sqrtf(powf(dx, 2) + powf(dy, 2));
}

// Returns a vector of length moved towards the specified point
Vector2 Vector2::MoveTowards(Vector2 point, float length) const
{
    return point.Subtract(*this).ScaleToLength(length);
}

// Returns a vector moved length towards the specified angle
Vector2 Vector2::MoveTowards(float angle, float length) const
{
    Vector2 displacement(length, 0);
    displacement = displacement.RotateToAngle(angle);

    return Add(displacement);
}
