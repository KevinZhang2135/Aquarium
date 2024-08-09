#include <iostream>
#include "screen.h"
#include "vector_math.h"

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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

    screen->Clean();
    delete screen;
}

void test()
{
    Vector2D point (20, 1);
    Vector2D point2 = point.Subtract(point.Multiply(3));
    cout << "x: " << point2.x << endl;
    cout << "y: " << point2.y << endl;
    cout << "magnitude: " << point2.Magnitude() << endl;
}

int main(int argc, char *args[])
{
    run();
    return 0;
}