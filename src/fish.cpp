#include "fish.h"

Fish::Fish()
{
    max_speed = 20;
    num_segments = 5;

    head;
}

// Moves fish to point
void Fish::Move(Vector2D point)
{
    velocity = point.Subtract(position).ScaleToLength(max_speed);
}

void Fish::Update() {
    
}
