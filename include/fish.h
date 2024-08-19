#pragma once
#include <iostream>
#include "anchors.h"
#include "vector_math.h"

class Fish
{
public:
    const int MAX_SEGMENTS = 16;
    Vector2D velocity;

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
    const float SCALE = 8;    
    const float MAX_SPEED = 2;
    
    void SetAnchorRadius(Anchor *anchor, int anchor_index);
};
