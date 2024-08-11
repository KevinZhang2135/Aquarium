#include "anchors.h"

Anchor::Anchor() : Anchor(Vector2D{0, 0}) {}

Anchor::Anchor(Vector2D point)
{
    dist_const = 20;
    position = point;
    next = nullptr;
}

void Anchor::MoveTo(Vector2D point)
{  
    // Does not move if point is within distance constraint
    Vector2D velocity = point.Subtract(position);
    if (velocity.Magnitude() <= dist_const) {
        return;
    }
        
    velocity = velocity.ScaleToLength(dist_const);
    position = point.Subtract(velocity);

    // Moves the rest of the body using inverse kinematics
    if (next != nullptr) 
        (*next).MoveTo(position);
}

Head::Head() : Anchor() {}
Head::Head(Vector2D point) : Anchor(point) {}

void Head::MoveTo(Vector2D point) {
    position = point;

    // Moves the rest of the body using inverse kinematics
    if (next != nullptr)
        (*next).MoveTo(point);
}
