#include "SDL2/SDL.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc, char *args[])
{
    int flags = SDL_WINDOW_SHOWN;
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool isRunning = SDL_Init(SDL_INIT_VIDEO) == 0;
    if (isRunning)
    {
        window = window = SDL_CreateWindow(
            "Aquarium",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            800,
            600,
            flags);

        renderer = SDL_CreateRenderer(window, -1, 0);
        (renderer) && SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }

    while (isRunning)
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

        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}