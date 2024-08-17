#pragma once
#include <iostream>
#include "anchors.h"
#include "vector_math.h"

class Fish
{
public:
    int max_segments;
    Vector2D velocity;

    // Body segments
    Head *head;
    Anchor *tail;
    Sint16 fin_x[4], fin_y[4]; // uses cubic bezier curve

    Fish();
    Fish(Vector2D position, float angle);
    ~Fish();

    void MoveTo(float x, float y);
    void MoveTo(Vector2D point);
    void Update();

private:
    const float MAX_SPEED = 10;
    const float RADIUS_SCALAR = 12;

    void SetAnchorRadius(Anchor *anchor, int anchor_index);
};
