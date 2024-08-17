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
    }

    // Generates fish
    for (int i = 0; i < NUM_FISHES; i++)
    {
        Fish *fish = new Fish();
        fishes[i] = fish;
    }
}

Screen::~Screen()
{
    for (int i = 0; i < NUM_FISHES; i++)
    {
        delete fishes[i];
    }

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Screen::Running()
{
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

void Screen::DrawFish(const Fish *fish)
{
    Anchor *anchor = fish->head;
    Anchor *temp = nullptr;

    // Traverses the linked list for each anchor of the fish
    while (anchor != nullptr)
    {
        filledCircleRGBA(
            renderer,
            anchor->position.x,
            anchor->position.y,
            anchor->radius,
            255,
            255,
            255,
            255);

        anchor = anchor->next;
    }
}

// Clears and redraws screen
void Screen::Render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (Fish *fish : fishes)
    {
        DrawFish(fish);
    }

    // bezierRGBA(renderer, fin_x, fin_y, 3, 10, 255, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

void Screen::Update()
{
    for (Fish *fish : fishes)
    {
        fish->MoveTo(mouse_x, mouse_y);
    }

    SDL_GetMouseState(&mouse_x, &mouse_y);
    SDL_UpdateWindowSurface(window);
}
