#pragma once

#include <iostream>
#include <vector>

#include "fish.h"
#include "vector2.h"

struct KeyIndexPair
{
    uint key, index;

    static bool Compare(KeyIndexPair a, KeyIndexPair b);
};

class SpatialHash
{
public:
    SpatialHash(Fish *fishes[], int num_fish, int grid_size);
    ~SpatialHash();

    uint HashPoint(Vector2 point) const;
    vector<uint> GetIndicesFromPoint(Vector2 point) const;
    void FindStartIndices();
    void Update();

private:
    int num_fish;
    int grid_size;

    Fish **fishes;

    // List of key-index pairs
    KeyIndexPair *spatial_list;

    // List of the start indices of consecutive cell positions for a
    // sorted spatial list
    int *start_indices;
    
};
