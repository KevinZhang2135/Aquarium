#pragma once

#include <iostream>
#include <vector>
#include <limits>

#include "fish.h"
#include "vector2.h"

class SpatialHash
{
    struct KeyIndexPair
    {
        uint cell_key, fish_index;
        static bool Compare(KeyIndexPair a, KeyIndexPair b);
    };

public:
    vector<Fish *> fishes;

    SpatialHash(int num_fish, int grid_size, Vector2 screen_size);
    ~SpatialHash();

    uint HashPoint(Vector2 point) const;
    vector<Fish *> GetFishFromPoint(Vector2 point) const;
    void Update();

private:
    int num_fish;
    int grid_size;

    // List of key-index pairs
    KeyIndexPair *spatial_list;

    // List of the start indices of consecutive cell positions for a
    // sorted spatial list
    int *start_indices;
};

int Randint(int min, int max);