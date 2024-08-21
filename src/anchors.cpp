#include "anchors.h"

Anchor::Anchor() : Anchor(Vector2{0, 0}, 0.0f) {}
Anchor::Anchor(Vector2 point, float angle)
{
    this->angle = angle;
    position = point;
    next = nullptr;
}

void Anchor::MoveTo(Vector2 point)
{
    // Does not move if point is within distance constraint
    if (position.DistanceTo(point) <= DIST_CONSTRAINT)
        return;

    Vector2 velocity = position.MoveTowards(point, DIST_CONSTRAINT);
    angle = velocity.Angle();

    position = point.Subtract(velocity);
    
    // Moves the rest of the body using inverse kinematics
    if (next != nullptr)
        next->MoveTo(position);
}

Head::Head() : Anchor() {}
Head::Head(Vector2 point, float angle) : Anchor(point, angle) {}

void Head::MoveTo(Vector2 point)
{
    angle = point.Subtract(position).Angle();
    position = point;

    // Moves the rest of the body using inverse kinematics
    if (next != nullptr)
        next->MoveTo(point);
}
