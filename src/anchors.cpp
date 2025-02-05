#include "anchors.h"

Anchor::Anchor() : Anchor(Vector2{0, 0}, 0.0f) {}
Anchor::Anchor(Vector2 point, float angle) {
    this->angle = angle;
    position = point;
    next = nullptr;
}

/// @brief Moves the anchor by a vector pointing towards a point
/// @param point The point to move towards
void Anchor::MoveTo(const Vector2 point) {
    // Does not move if point is within distance constraint
    if (position.DistanceTo(point) <= DIST_CONSTRAINT) {
        return;
    }

    Vector2 velocity = position.MoveTowards(point, DIST_CONSTRAINT);
    angle = velocity.Angle();

    position = point - velocity;

    // Moves the rest of the body using inverse kinematics
    if (next != nullptr) {
        next->MoveTo(position);
    }
}

/// @brief Sets the position of the anchor to the specified point without gradual procedural movement
/// @param point The specified point to set the anchor position to
void Anchor::SetPosition(const Vector2 point) {
    position = point.MoveTowards(angle, DIST_CONSTRAINT);

    // Sets the rest of the anchors using inverse kinematics
    if (next != nullptr) {
        next->SetPosition(position);
    }
}

Head::Head() : Anchor() {}
Head::Head(const Vector2 point, const float angle) : Anchor(point, angle) {}

/// @brief Moves the head by a vector pointing towards a point
/// @param point The point to move towards
void Head::MoveTo(const Vector2 point) {
    angle = (point - position).Angle();
    position = point;

    // Moves the rest of the body using inverse kinematics
    if (next != nullptr) {
        next->MoveTo(point);
    }
}

/// @brief Sets the position of the head to the specified point without gradual procedural movement
/// @param point The specified point to set the head position to
void Head::SetPosition(const Vector2 point) {
    position = point;

    // Sets the rest of the anchors using inverse kinematics
    if (next != nullptr) {
        next->SetPosition(position);
    }
}