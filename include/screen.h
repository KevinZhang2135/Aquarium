#pragma once
#include "SDL2/SDL.h"
#include "fish.h"
#include <iostream>

#define NUM_FISHES 1

class Screen
{
public:
    Screen(int width, int height, bool full_screen = false);
    ~Screen();
    bool Running();

    void HandleEvents();
    void Render();
    void Update();
    

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    Fish *fishes[NUM_FISHES];
};