#include "anchors.h"

Anchor::Anchor()
{
}

void Anchor::Move(Vector2D point)
{
    Vector2D velocity = point.Subtract(position).ScaleToLength(dist_const);
    position = position.Add(velocity);
    if (next != nullptr) {
        (*next).Move(position);
    }
}
