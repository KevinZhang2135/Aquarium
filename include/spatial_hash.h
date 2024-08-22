#pragma once

#include <iostream>

#include "fish.h"
#include "vector2.h"

struct HashIndexPair {
    int hash, index;
};

class SpatialHash {
    public:
        SpatialHash(Fish *fishes, int num_fish, int grid_size);
        ~SpatialHash();
        int GetIndicesFromHash() const;
        void SortHashList();
        void Update();
    
    private:
        Fish *fishes;

        int num_fish;
        int grid_size;

        int *hash_list;
        int *start_indices;
};
