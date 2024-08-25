#include "spatial_hash.h"

bool KeyIndexPair::Compare(KeyIndexPair a, KeyIndexPair b)
{
    return a.cell_key < b.cell_key;
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
vector<Fish *> SpatialHash::GetAllFishFromPoint(Vector2 point) const
{
    uint key = HashPoint(point) % num_fish;
    vector<Fish *> indices;

     // Loops from the index of the first fish of a cell
    for (uint i = start_indices[key]; i < num_fish; i++)
    {
        if (spatial_list[i].cell_key != key)
        {
            break;
        }

        uint fish_index = spatial_list[i].fish_index;
        Fish *fish = fishes[fish_index];
        indices.push_back(fish);
    }

    return indices;
}

void SpatialHash::Update()
{
    // Generates a hash for the position of each fish
    for (uint i = 0; i < num_fish; i++)
    {
        Fish *fish = fishes[i];
        Vector2 position = fish->head->position;

        // Converts fish position into hash
        uint key = HashPoint(position) % num_fish;

        spatial_list[i] = KeyIndexPair{key, i};
        start_indices[key] = UINT_MAX;
    }

    // Sorts spatial list by cell key
    std::sort(spatial_list, spatial_list + num_fish, KeyIndexPair::Compare);

    // Finds the index of a first occurrence of consecutive cell keys
    for (uint i = 0; i < num_fish; i++)
    {
        uint key = spatial_list[i].cell_key;
        uint prev_key = (i == 0) ? UINT_MAX : spatial_list[i - 1].cell_key;

        if (key != prev_key)
        {
            start_indices[key] = i;
        }
    }
}
