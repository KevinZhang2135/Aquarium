#include "screen.h"

Screen::Screen(int width, int height, bool full_screen = false)
{
    int flags = (full_screen) ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
    isRunning = SDL_Init(SDL_INIT_VIDEO) == 0;

    if (isRunning)
    {
        window = window = SDL_CreateWindow(
            "Aquarium",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
            flags);

        renderer = SDL_CreateRenderer(window, -1, 0);
        (renderer) && SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
}

bool Screen::Running() {
    return isRunning;
}

void Screen::HandleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;

    default:
        break;
    }
}

// Clears and redraws screen
void Screen::Render()
{
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void Screen::Update()
{
    SDL_UpdateWindowSurface(window);
}

// Deallocates resources used
void Screen::Clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}
