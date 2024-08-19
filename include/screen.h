#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "fish.h"
#include "anchors.h"

using namespace std;

class Screen
{
public:
    static const int NUM_FISHES = 1;
    int mouse_x, mouse_y;

    Screen(int width, int height, bool full_screen = false);
    ~Screen();
    bool Running();
    void HandleEvents();

    void DrawFish(const Fish *fish);
    void DrawFins(Anchor *anchor);
    void Render();
    void Update();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Fish *fishes[NUM_FISHES];
};