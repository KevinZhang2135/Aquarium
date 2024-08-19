#include "fish.h"

Fish::Fish() : Fish(Vector2D(0, 0), 0.0f) {}
Fish::Fish(Vector2D position, float angle)
{
    // Creates head
    head = new Head(position, angle);
    SetAnchorRadius(head, 0);

    // Generates segments from head using angle
    Anchor *segment = head;
    for (int i = 1; i < MAX_SEGMENTS; i++)
    {
        segment->next = new Anchor();
        segment = segment->next;

        // Determines the radius of each segment
        SetAnchorRadius(segment, i);

        // Determines separation distance of each segment
        Vector2D separation(SCALE / 2, 0);
        position = position.Add(separation.RotateToAngle(angle));
        segment->position = position;
    }

    tail = segment;
}

// Deletes all segment anchors
Fish::~Fish()
{
    Anchor *prev = head;
    Anchor *temp = nullptr;

    // Loops through each anchor and deletes it
    while (prev != nullptr)
    {
        temp = prev->next;
        delete prev;

        prev = temp;
    }
}

// Moves fish to point
void Fish::MoveTo(float x, float y)
{
    MoveTo(Vector2D({x, y}));
}

// Moves fish to point
void Fish::MoveTo(Vector2D point)
{
    // Does not move if point is within distance constraint
    if (head->position.DistanceTo(point) <= MAX_SPEED)
        return;

    velocity = head->position.MoveTowards(point, MAX_SPEED);
    head->MoveTo(head->position.Add(velocity));
}

void Fish::Update()
{
}

// Uses a continuous piecewise function to approximate the radius of a fish
void Fish::SetAnchorRadius(Anchor *anchor, int anchor_index)
{
    // x-value where the fish radius decreases at a decreasing rate
    float tapering_x = (1 + sqrt(2)) / 2;

    // x-value of the segment on the graph on the interval [0, 2]
    float fish_pos_x = float(anchor_index) / MAX_SEGMENTS * 2;

    // radius is approximated with a semi-circle before tapering and with a
    // decreasing exponential after tapering
    float fish_radius = SCALE;
    fish_radius *= (fish_pos_x <= tapering_x)
        ? sqrtf(1 - powf(fish_pos_x - 0.5f, 2)) + (2 - sqrt(2)) / 2
        : powf(M_E, -fish_pos_x + tapering_x);

    anchor->radius = fish_radius;
}
