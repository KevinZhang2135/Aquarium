#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "fish.h"
#include "anchors.h"
#include "spatial_hash.h"

using namespace std;

class Screen
{
public:
    static const int NUM_FISH = 20;
    static const int GRID_SIZE = 200;

    int width, height;
    int mouse_x, mouse_y;

    Screen(uint width, uint height, bool full_screen = false);
    ~Screen();
    bool Running();
    void HandleEvents();

    void DrawFish(const Fish *fish) const;
    void DrawFins(Anchor *anchor) const;
    void Render() const;

    void UpdateBoid(Fish *fish);
    void Update();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Fish *fishes[NUM_FISH];

    // Spatial hash of points for optimizing searches
    SpatialHash *spatial_hash;
};

int Randint(int min, int max);