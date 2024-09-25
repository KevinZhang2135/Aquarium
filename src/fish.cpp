#include "fish.h"

Fish::Fish(int grid_size) : Fish(Vector2(0, 0), 0.0f, grid_size) {}
Fish::Fish(Vector2 position, float angle, int grid_size)
    : search_radius(grid_size)
{
    velocity = {MAX_SPEED, 0};
    velocity = velocity.RotateToAngle(angle + M_PI);

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
        Vector2 separation(SCALE / 2, 0);
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

/// @brief Determines the radius of a fish anchor with continuous piecewise 
/// function
/// @param anchor The anchor of which the radius is set
/// @param anchor_index The position of the anchor
void Fish::SetAnchorRadius(Anchor *anchor, int anchor_index) const
{
    // x-value where the fish radius decreases at a decreasing rate
    float tapering_x = (1 + sqrt(2)) / 2;

    // x-value of the segment on the graph on the interval [0, 2]
    float fish_pos_x = float(anchor_index) / MAX_SEGMENTS * 2;

    // Radius is approximated with a semi-circle before tapering and with a
    // decreasing exponential after tapering
    float fish_radius = SCALE;
    fish_radius *= (fish_pos_x <= tapering_x)
                       ? sqrtf(1 - powf(fish_pos_x - 0.5f, 2)) + (2 - sqrt(2)) / 2
                       : powf(M_E, -fish_pos_x + tapering_x);

    anchor->radius = fish_radius;
}

/// @brief Moves fish away from close boids within collision distance
/// @param close_center The center of close boids
void Fish::Separate(Vector2 close_center)
{
    float factor = 1.0f;
    Vector2 acceleration = head->position.Subtract(close_center);

    velocity = velocity.Add(acceleration.Multiply(factor));
}

/// @brief Matches the velocity and heading of nearby boids
/// @param average_velocity The mean velocity of all nearby boids
void Fish::Align(Vector2 average_velocity)
{
    float factor = 1.0f;
    Vector2 acceleration = average_velocity.Subtract(velocity);

    velocity = velocity.Add(acceleration.Multiply(factor));
}

/// @brief Moves towards the center of nearby boids
/// @param average_position The center of nearby boids
void Fish::Cohere(Vector2 average_position)
{
    float factor = 1.0f;
    Vector2 acceleration = average_position.Subtract(head->position);

    velocity = velocity.Add(acceleration.Multiply(factor));
}

/// @brief Moves the fish using boid behavior
void Fish::Move()
{
    head->MoveTo(head->position.Add(velocity));
}

/// @brief Searches for nearby boids to adjust heading
/// @param nearby_boids The boids that are within a 3x3 cell grid centered on
///                     the fish
void Fish::Update(vector<Fish *> nearby_boids)
{
    // Average of all nearby boids
    Vector2 average_center;
    Vector2 average_velocity;
    uint boid_count = 0;

    // Average center and number of very close boids to avoid
    Vector2 close_center;
    uint close_count = 0;

    for (Fish *boid : nearby_boids)
    {
        Vector2 boid_position = boid->head->position;
        float distance = head->position.DistanceTo(boid_position);

        // Schools with nearby boids within search radius
        if (distance <= search_radius)
        {
            average_center.Add(boid_position);
            average_velocity.Add(boid->velocity);
            boid_count++;
        }

        // Avoids boids within collision distance
        if (this != boid && distance < COLLISION_DIST)
        {
            close_center.Add(boid_position);
            close_count++;
        }
    }

    if (boid_count > 1)
    {
        // Moves towards the center of nearby boids
        average_center.Divide(boid_count);
        Cohere(average_center);

        // Matches the velocity of nearby boids
        average_velocity.Divide(boid_count);
        Align(average_velocity);
    }

    if (close_count > 0)
    {
        // Avoids boids within collision distance
        close_center.Divide(close_count);
        Separate(close_center);
    }

    Move();
}
