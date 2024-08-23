#include "spatial_hash.h"

bool KeyIndexPair::Compare(KeyIndexPair a, KeyIndexPair b)
{
    return a.key < b.key;
}

SpatialHash::SpatialHash(Fish *fishes[], int num_fish, int grid_size)
    : fishes(fishes),
      num_fish(num_fish),
      grid_size(grid_size)
{
    spatial_list = new KeyIndexPair[grid_size];
    start_indices = new int[grid_size];

    Update();
}

SpatialHash::~SpatialHash()
{
    delete[] fishes;
    delete[] spatial_list;
    delete[] start_indices;
}

// Generates a hash value by multiplying the x and y components of the cell
// coordinate of a point by two arbitary prime numbers and summing them
uint SpatialHash::HashPoint(Vector2 point) const
{
    int cell_x = point.x / grid_size;
    int cell_y = point.y / grid_size;

    return cell_x * 67474109 + cell_y * 87513581;
}

// Retrieves the indices of all fish in a cell
vector<uint> SpatialHash::GetIndicesFromPoint(Vector2 point) const
{
    uint key = HashPoint(point) % num_fish;
    uint i = start_indices[key];

    int cnt = 0;
    vector<uint> indices;
    if (i == -1){
        std::cout << "None" << std::endl;
        return indices;
    }

    
    while (spatial_list[i].key == key) {
        std::cout << spatial_list[i].index << std::endl;
        indices.push_back(spatial_list[i].index);
        i++;
    }

    return indices;
}

// Loops through each key and marks the start of consecutive cell keys
void SpatialHash::FindStartIndices()
{
    uint key = 0;
    uint i = 0;

    while (key < num_fish)
    {
        if (key < spatial_list[i].key)
        {
            start_indices[key] = -1;
            key++;
        }
        else if (key == spatial_list[i].key)
        {
            start_indices[key] = i;
            key++;
            i++;
        }
        else
        {
            i++;
        }
    }
}

void SpatialHash::Update()
{
    // Generates a hash for the position of each fish
    for (uint i = 0; i < num_fish; i++)
    {
        Fish *fish = fishes[i];
        uint key = HashPoint(fish->head->position) % num_fish;

        spatial_list[i] = KeyIndexPair{key, i};
    }

    std::sort(spatial_list, spatial_list + num_fish, KeyIndexPair::Compare);
    FindStartIndices();
}
