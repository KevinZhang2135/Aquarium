#pragma once
#include <cmath>
#include "vector_math.h"
#include "anchors.h"

class Fish
{
public:
    Vector2D position;
    Vector2D velocity;

    Fish();
    void Move(Vector2D point);
    void Update();

private:
    float max_speed;
    int num_segments;
    Anchor head;
};
