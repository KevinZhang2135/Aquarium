#include "fish.h"

Fish::Fish() : Fish(0.0f) {}
Fish::Fish(float angle)
{
    max_speed = 20;
    num_segments = 5;
}

// Moves fish to point
void Fish::Move(Vector2D point)
{
    velocity = point.Subtract(position).ScaleToLength(max_speed);
}

void Fish::Update()
{
}
