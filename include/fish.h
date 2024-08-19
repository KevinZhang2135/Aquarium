#pragma once
#include <iostream>
#include "anchors.h"
#include "vector_math.h"

class Fish
{
public:
    int max_segments;
    Vector2D velocity;
    Sint16 fin_x[4], fin_y[4];

    // Body segments
    Head *head;
    Anchor *tail;

    Fish();
    Fish(Vector2D position, float angle);
    ~Fish();

    Sint16* GetFinX(Vector2D anchor_position, int anchor_index);
    Sint16* GetFinY(Vector2D anchor_position, int anchor_index);

    void MoveTo(float x, float y);
    void MoveTo(Vector2D point);
    void Update();

private:
    const float MAX_SPEED = 10;
    const float SCALE = 16;
    

    void SetAnchorRadius(Anchor *anchor, int anchor_index);
};
