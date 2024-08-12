#include "fish.h"

Fish::Fish() : Fish(Vector2D(0, 0), 0.0f) {}
Fish::Fish(Vector2D position, float angle)
{
    num_segments = 30;
    max_speed = 10;

    // Creates head
    head = new Head(position);

    // Generates segments from head using angle
    Anchor *segment = head;
    for (int i = 1; i < num_segments; i++) {
        segment->next = new Anchor();
        segment = segment->next;

        // Determines separation distance of each segment
        Vector2D separation(segment->dist_const, 0);
        position = position.Add(separation.RotateToAngle(angle));
        segment->position = position;
    }
}

Fish::~Fish() {
    // Deletes the linked list of segments
    Anchor *prev = head;
    Anchor *temp = nullptr;

    while (prev != nullptr) {
        temp = prev->next;
        delete prev;
        
        prev = temp;
    }
}

// Fetches all the point of each segment
std::vector<Vector2D> Fish::GetPoints() {
    std::vector<Vector2D> points;
    
    Anchor *prev = head;
    Anchor *temp = nullptr;
    
    // Traverses the linked list for each point
    while (prev != nullptr) {
        points.push_back(prev->position);
        prev = prev->next;
    }

    return points;
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
    if (head->position.DistanceTo(point) <= max_speed)
        return;

    velocity = head->position.MoveTowards(point, max_speed);
    head->MoveTo(head->position.Add(velocity));
}

void Fish::Update()
{

}
