#include <iostream>
#include "screen.h"
#include "vector_math.h"
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

    unordered_map<Vector2D, vector<int>> grid;

    // Generates optimization grid
    // int count = 0;
    // for (int x = 0; x < width / GRID_SIZE; x++) {
    //     for (int y = 0; y < height / GRID_SIZE; y++) {
    //         Vector2D point(x, y);
    //         grid[point] = {vector<int>()};
    //         grid[point].push_back(count);
    //         count++;
    //     }
    // }
    // grid[1] = {vector<int>()};
    // grid[1].push_back(1);

    // Reference unpacking
    // for (const auto &[key, value] : grid)
    // {
    //     std::cout << key << ": " << value.at(0) << std::endl;
    // }
}

int main(int argc, char *args[])
{
    test();
    return 0;
}