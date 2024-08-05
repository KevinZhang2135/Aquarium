#pragma once

#include <SDL2/SDL.h>

class Screen
{
public:
    

    Screen(int width, int height, bool full_screen = false);
    bool Running();
    void HandleEvents();
    void Render();
    void Update();
    void Clean();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    
};