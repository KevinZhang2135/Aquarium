#include "screen.h"

Screen::Screen(int width, int height, bool full_screen)
{
    // Seeds random number generator with current time
    srand(time(NULL));

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
        Vector2D position (Randint(0, width), Randint(0, height));
        Fish *fish = new Fish(position, 0.0f);
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
    int i = 0;
    while (anchor != nullptr)
    {
        // 0xAABBGGRR
        Uint32 color = 0xffab4700;
        bool draw_fin = (i == fish->max_segments / 5) || (i == fish->max_segments * 5 / 7);

        // Draws body
        filledCircleColor(
            renderer,
            anchor->position.x,
            anchor->position.y,
            anchor->radius,
            color);

        if (draw_fin) {
            DrawFins(anchor);
        }
            
        anchor = anchor->next;
        i++;
    }
}

void Screen::DrawFins(Anchor *anchor)
{
    Uint32 color = 0xffcc9066;
    int fin_segments = 4;
    float fin_angle = M_PI * 0.7f;
    float fin_radius = anchor->radius * 0.6f;

    // Pectoral fins
    // Switches between negative and positive angles
    for (int sign = -1; sign <= 1; sign += 2)
    {
        // Draws a series of circles extending from the body at the fin angle
        for (int i = 1; i <= fin_segments; i++)
        {
            Vector2D fin_position = anchor->position.MoveTowards(
                anchor->angle + fin_angle * sign,
                fin_radius * (1.0f + i / 2.0f));

            filledCircleColor(
                renderer,
                fin_position.x,
                fin_position.y,
                fin_radius * (1.0f - i / 10.0f),
                color);
        }
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

int Randint(int min, int max) {
    return rand() % (max - min + 1) + min;
}