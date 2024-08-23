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
}

int main(int argc, char *args[])
{
    run();
    return 0;
}