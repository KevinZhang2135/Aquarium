#pragma once
#include <iostream>
#include <vector>

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

    Fish(int grid_size);
    Fish(Vector2 position, float angle, int grid_size);
    ~Fish();

    void Separate(Vector2 close_center);
    void Align(Vector2 average_velocity);
    void Cohere(Vector2 average_position);
    void Move();

    void Update(vector<Fish *> nearby_boids);

private:
    const float MAX_SPEED = 2;
    const float SCALE = 4;   
    const float COLLISION_DIST = SCALE * 4; 
    
    int search_radius; 
    
    void SetAnchorRadius(Anchor *anchor, int anchor_index);
};
