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
    int i = 0;
    while (anchor != nullptr)
    {
        int anchor_index = fish->max_segments / 4;
        bool draw_fin = i == anchor_index || i == anchor_index * 3;

        // 0xAABBGGRR
        Uint32 color = 0xffffffff;

        // Draws body
        circleColor(
            renderer,
            anchor->position.x,
            anchor->position.y,
            anchor->radius,
            color);

        if (draw_fin)
            DrawFins(anchor);

        anchor = anchor->next;
        i++;
    }
}

void Screen::DrawFins(Anchor *anchor)
{
    Uint32 color = 0xff0000ff;

    int fin_segments = 10;
    float fin_angle = M_PI * 0.6f;
    float fin_radius = anchor->radius * 0.7f;

    // Pectoral fins
    // for (int i = 1; i < fin_segments; i++)
    // {
    // Draws the left and right fins
    // for (int j = -1; j <= 1; j += 2)
    // {
    //     Vector2D fin_position = anchor->position.MoveTowards(
    //         anchor->angle + fin_angle * j,
    //         fin_radius);

    //     circleColor(
    //         renderer,
    //         fin_position.x,
    //         fin_position.y,
    //         fin_radius,
    //         color);
    // }
    // }

    // Switches between negative and positive angles
    for (int sign = -1; sign <= 1; sign += 2)
    {
        for (int i = 1; i < fin_segments; i++)
        {
            Vector2D fin_position = anchor->position.MoveTowards(
                anchor->angle + fin_angle * sign,
                fin_radius * (1.0f - i / 10.0f));

            circleColor(
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
