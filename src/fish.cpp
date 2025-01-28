#include "fish.h"

Fish::Fish(const int search_radius, const Vector2 screen_size)
    : Fish(Vector2(0, 0), 0.0f, search_radius, screen_size) {}

Fish::Fish(Vector2 position, float angle, int search_radius, Vector2 screen_size)
    : search_radius(search_radius),
      screen_size(screen_size),
      min_bound(Vector2(-GRID_MARGIN, -GRID_MARGIN)),
      max_bound(-min_bound + screen_size) {
    velocity = {MAX_SPEED, 0};
    velocity = velocity.RotateToAngle(angle + M_PI);

    // Creates head
    head = new Head(position, angle);
    SetAnchorRadius(head, 0);

    // Generates segments from head using angle
    Anchor *segment = head;
    for (int i = 1; i < MAX_SEGMENTS; i++) {
        segment->next = new Anchor();
        segment = segment->next;

        // Determines the radius of each segment
        SetAnchorRadius(segment, i);

        // Determines separation distance of each segment
        Vector2 separation(SCALE / 2, 0);
        position += separation.RotateToAngle(angle);
        segment->position = position;
    }

    tail = segment;
}

Fish::~Fish() {
    Anchor *prev = head, *temp = nullptr;

    // Loops through each anchor and deletes it
    while (prev != nullptr) {
        temp = prev->next;
        delete prev;

        prev = temp;
    }
}

/// @brief Determines the radius of a fish anchor with continuous piecewise
/// function
/// @param anchor The anchor of which the radius is set
/// @param anchor_index The position of the anchor
void Fish::SetAnchorRadius(Anchor *anchor, const int anchor_index) const {
    // x-value where the fish radius decreases at a decreasing rate
    float tapering_x = (1 + sqrt(2)) / 2;

    // x-value of the segment on the graph on the interval [0, 2]
    float fish_pos_x = float(anchor_index) / MAX_SEGMENTS * 2;

    // Radius is approximated with a semi-circle before tapering and with a
    // decreasing exponential after tapering
    float fish_radius = SCALE;
    fish_radius *= (fish_pos_x <= tapering_x) ? sqrtf(1 - powf(fish_pos_x - 0.5f, 2)) + (2 - sqrt(2)) / 2
                                              : powf(M_E, -fish_pos_x + tapering_x);

    anchor->radius = fish_radius;
}

/// @brief Moves fish away from close boids within collision distance
/// @param close_center The center of close boids
/// @return The acceleration away from the center
Vector2 Fish::Separate(const Vector2 close_center) const {
    float factor = 0.1f;
    Vector2 acceleration = head->position - close_center;

    return acceleration * factor;
}

/// @brief Matches the velocity and heading of nearby boids
/// @param average_velocity The mean velocity of all nearby boids
/// @return The acceleration towards the mean heading
Vector2 Fish::Align(const Vector2 average_velocity) const {
    float factor = 0.005f;
    Vector2 acceleration = average_velocity - velocity;

    return acceleration * factor;
}

/// @brief Moves towards the center of nearby boids
/// @param average_position The center of nearby boids
/// @return The acceleration towards the center
Vector2 Fish::Cohere(const Vector2 average_position) const {
    float factor = 0.0001f;
    Vector2 acceleration = average_position - head->position;

    return acceleration * factor;
}

/// @brief Sets the head position of the fish to the specified point without
/// gradual procedural movement
/// @param point The specified point to set the head position to
void Fish::SetPosition(const Vector2 point) { head->SetPosition(point); }

/// @brief Moves the fish using boid behavior
void Fish::Move() {
    head->MoveTo(head->position + velocity);

    // Keeps fish within margin distance outside the screen
    Vector2 min_bound = {-float(GRID_MARGIN), -float(GRID_MARGIN)};
    Vector2 max_bound = -min_bound + screen_size;

    Vector2 new_position = head->position;

    // left bound
    if (head->position.x < min_bound.x) {
        new_position.x = max_bound.x;
    }

    // right bound
    else if (head->position.x > max_bound.x) {
        new_position.x = min_bound.x;
    }

    // top bound
    if (head->position.y < min_bound.y) {
        new_position.y = max_bound.y;
    }

    // bottom bound
    else if (head->position.y > max_bound.y) {
        new_position.y = min_bound.y;
    }

    if (new_position != head->position) {
        SetPosition(new_position);
    }
}

/// @brief Searches for nearby boids to adjust heading
/// @param nearby_boids The boids that are within a 3x3 cell grid centered on
///                     the fish
void Fish::Update(const vector<Fish *> nearby_boids) {
    // Average of all nearby boids
    Vector2 average_center, average_velocity;
    uint boid_count = 0;

    // Average center and number of very close boids to avoid
    Vector2 close_center;
    uint close_count = 0;

    for (Fish *boid : nearby_boids) {
        if (boid != this) {
            Vector2 boid_position = boid->head->position;
            float distance = head->position.DistanceTo(boid_position);

            // Schools with nearby boids within search radius
            if (distance <= search_radius) {
                average_center += boid_position;
                average_velocity += boid->velocity;
                boid_count++;
            }

            // Avoids boids within collision distance
            if (distance < COLLISION_DIST) {
                close_center += boid_position;
                close_count++;
            }
        }
    }

    // Handles the cohesion, alignment, and separation behavior of boids
    Vector2 cohere, align, separate;
    if (boid_count > 1) {
        // Moves towards the center of nearby boids
        average_center /= boid_count;
        cohere = Cohere(average_center);

        // Matches the velocity of nearby boids
        average_velocity /= boid_count;
        align = Align(average_velocity);
    }

    if (close_count > 0) {
        // Avoids boids within collision distance
        close_center /= close_count;
        separate = Separate(close_center);
    }

    velocity += cohere + align + separate;
    velocity = velocity.ScaleToLength(MAX_SPEED);
}
