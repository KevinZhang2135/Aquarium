#include <iostream>
#include "screen.h"
#include "vector2.h"
#include "fish.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800

using namespace std;

Screen *screen = nullptr;
void run()
{
    screen = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT);

    while (screen->Running())
    {
        screen->HandleEvents();
        screen->Update();
        screen->Render();
    }

    delete screen;
}

void test()
{
    int width = 800;
    int height = 800;
    int GRID_SIZE = 200;

    unordered_map<Vector2, vector<int>> grid;

    // Generates optimization grid
    int count = 0;
    for (int x = 0; x < width / GRID_SIZE; x++) {
        for (int y = 0; y < height / GRID_SIZE; y++) {
            Vector2 point(x, y);
            grid[point] = {vector<int>()};
            grid[point].push_back(count);
            count++;
        }
    }

    // Reference unpacking
    for (const auto &[key, value] : grid)
    {
        std::cout << key.x << ", " << key.y << std::endl;
    }
}

int main(int argc, char *args[])
{
    run();
    return 0;
}