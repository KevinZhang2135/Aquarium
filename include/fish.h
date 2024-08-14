#pragma once
#include <iostream>
#include <vector>
#include "vector_math.h"
#include "anchors.h"

class Fish
{
public:
    int max_segments = 8;

    Vector2D velocity;
    Head *head;

    Fish();
    Fish(Vector2D position, float angle);
    ~Fish();

    std::vector<Anchor> GetAnchors();
    void MoveTo(float x, float y);
    void MoveTo(Vector2D point);
    
    void Update();

private:
    float max_speed = 10;
    float radius_multiplier = 10;

    float GetAnchorRadiusAt(int segment);
};
