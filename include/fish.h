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

    Fish(int search_radius, Vector2 screen_size);
    Fish(Vector2 position, float angle, int search_radius, Vector2 screen_size);
    ~Fish();

    Vector2 Separate(const Vector2 close_center) const;
    Vector2 Align(const Vector2 average_velocity) const;
    Vector2 Cohere(const Vector2 average_position) const;

    void Move();
    void SetPosition(const Vector2 point);
    void Update(const vector<Fish *> nearby_boids);

private:
    const float MAX_SPEED = 3;
    const float SCALE = 3;
    const float COLLISION_DIST = SCALE * SCALE;

    // The maximum distance the fish can travel off screen before being
    // teleported to the other side
    const float GRID_MARGIN = 50.0f;
    Vector2 min_bound, max_bound;

    int search_radius;
    Vector2 screen_size;

    void SetAnchorRadius(Anchor *anchor, const int anchor_index) const;
};
