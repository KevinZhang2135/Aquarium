#pragma once
#include <iostream>
#include "anchors.h"
#include "vector2.h"

class Fish
{
public:
    const int MAX_SEGMENTS = 16;
    Vector2 velocity;

    // Body segments
    Head *head;
    Anchor *tail;

    Fish();
    Fish(Vector2 position, float angle);
    ~Fish();

    void MoveTo(float x, float y);
    void MoveTo(Vector2 point);
    void Update();

private:
    const float SCALE = 8;    
    const float MAX_SPEED = 2;
    
    void SetAnchorRadius(Anchor *anchor, int anchor_index);
};
