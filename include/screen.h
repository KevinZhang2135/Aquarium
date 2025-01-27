#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "anchors.h"
#include "fish.h"
#include "spatial_hash.h"

using namespace std;

class Screen {
   public:
    static const int NUM_FISH = 200;
    static const int GRID_SIZE = 200;

    int width, height;
    int mouse_x, mouse_y;

    Screen(uint width, uint height, bool full_screen = false);
    ~Screen();
    bool Running();
    void HandleEvents();

    void DrawFish(const Fish *fish) const;
    void DrawFins(const Anchor *anchor) const;
    void Render() const;

    vector<Fish *> SearchForBoids(Vector2 point) const;
    void UpdateBoid(Fish *fish) const;
    void Update();

   private:
    const bool debug = false;

    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Spatial hash of sorted points by cell for optimizing searches
    SpatialHash *spatial_hash;
};
