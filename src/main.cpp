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
    Vector2 x(1, 1);

    std::cout << x.toString() << std::endl;
    std::cout << (x).Normalize().toString() << std::endl;
}

int main(int argc, char *args[])
{
    test();
    return 0;
}