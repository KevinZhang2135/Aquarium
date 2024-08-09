#include "screen.h"

Screen::Screen(int width, int height, bool full_screen)
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

    // Generates fish
    for (int i = 0; i < NUM_FISHES; i++) {
        Fish *fish = new Fish();
        fishes[i] = fish;
    }
}

Screen::~Screen()
{
    for (int i = 0; i < NUM_FISHES; i++) {
        delete fishes[i];
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
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
    int i = 0;
    for (Fish *fish : fishes) {
        bool notNull = fish == NULL;
        std::cout << "Fish "<< i << ": ";
        std::cout << fish << std::endl;
        i++;
    }

    SDL_RenderPresent(renderer);
}

void Screen::Update()
{
    SDL_UpdateWindowSurface(window);
}


