#pragma once
#include <iostream>
#include "SDL2/SDL.h"
#include "fish.h"


class Screen
{
public:
    static const int NUM_FISHES = 1;
    int mouse_x, mouse_y;

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