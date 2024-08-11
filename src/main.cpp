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
    Fish *fish = new Fish({Vector2D(2, 3)}, M_PI_4);
    delete fish;
}

int main(int argc, char *args[])
{
    run();
    return 0;
}