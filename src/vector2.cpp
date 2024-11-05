#include "vector2.h"

Vector2::Vector2() : x{0}, y{0} {}
Vector2::Vector2(float x, float y) : x{x}, y{y} {}

bool Vector2::operator==(const Vector2 &other) const
{
    return (x == other.x && y == other.y);
}

bool Vector2::operator!=(const Vector2 &other) const
{
    return !operator==(other);
}

Vector2 Vector2::operator+(const Vector2 &other) const
{
    return Vector2(x + other.x, y + other.y);
}

// void Vector2::operator+=(const Vector2 &other)
// {
//     x += other.x;
//     y += other.y;
// }

/// @brief Returns the Euclidean length of the vector from the origin
/// @return The Euclidean length of the vector from the origin
float Vector2::Magnitude() const
{
    return SDL_sqrtf(powf(x, 2) + powf(y, 2));
}

/// @brief Returns the angle of the vector in radians
/// @return The angle of the vector in radians
float Vector2::Angle() const
{
    if (!x && !y)
        return 0.0f;

    return SDL_atan2f(y, x);
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

/// @brief Returns a new vector scaled to the specified length
/// @param length The specified length of the new vector
/// @return A new vector with specified length
Vector2 Vector2::ScaleToLength(float length) const
{
    if (Magnitude() == 0.0f)
        return Vector2();

    float scalar = length / Magnitude();
    return Multiply(scalar);
}

/// @brief Returns a normalized vector with length 1
/// @return A normalized vector
Vector2 Vector2::Normalize() const
{
    return ScaleToLength(1);
}

/// @brief Returns a new vector rotated to the specified angle
/// @param angle
/// @return A new vector rotated to the specified angle
Vector2 Vector2::RotateToAngle(float angle) const
{
    Vector2 new_vector(
        SDL_cosf(angle) * Magnitude(),
        SDL_sinf(angle) * Magnitude());

    return new_vector;
}

/// @brief Returns the Euclidean distance to the point
/// @param point The point to compare the distance
/// @return The distance to the specified point
float Vector2::DistanceTo(Vector2 point) const
{
    float dx = point.x - this->x; // difference in x
    float dy = point.y - this->y; // difference in y

    return sqrtf(powf(dx, 2) + powf(dy, 2));
}

/// @brief Returns a new vector of length moved towards the specified point
/// @param point The point to move towards
/// @param length The length of the displacement vector
/// @return A new vector of length moved towards the point
Vector2 Vector2::MoveTowards(Vector2 point, float length) const
{
    return point.Subtract(*this).ScaleToLength(length);
}

/// @brief Returns a vector moved length at the specified angle
/// @param angle The angle to move to
/// @param length The length of the displacement vector
/// @return A new vector of length moved at the angle
Vector2 Vector2::MoveTowards(float angle, float length) const
{
    Vector2 displacement(length, 0);
    displacement = displacement.RotateToAngle(angle);

    return *this + displacement;
}

std::string Vector2::toString() const
{
    return std::to_string(x) + " " + std::to_string(y);
}
