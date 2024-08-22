#include "spatial_hash.h"

SpatialHash::SpatialHash(Fish *fishes, int num_fish, int grid_size)
    : fishes(fishes),
      num_fish(num_fish),
      grid_size(grid_size)
{

    for (int i = 0; i < num_fish; i++) {
        Fish fish = *(fishes + i);
        std::cout << &fish << std::endl;
    }
}

SpatialHash::~SpatialHash()
{
    delete fishes;
}

int SpatialHash::GetIndicesFromHash() const
{
    return 0;
}

void SpatialHash::SortHashList()
{
}

void SpatialHash::Update()
{
}
