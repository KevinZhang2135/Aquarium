#pragma once
#include <vector>
#include "vector_math.h"
#include "anchors.h"

class Fish
{
public:
    int num_segments;
    Vector2D position;
    Vector2D velocity;

    Fish();
    Fish(Vector2D position, float angle);
    ~Fish();

    std::vector<Vector2D> GetPoints();
    void MoveTo(float x, float y);
    void MoveTo(Vector2D point);
    
    void Update();

private:
    float max_speed;
    Head *head;
};
