#include <iostream>
//#include "screen.h"
#include "vector_math.h"


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Screen *screen = nullptr;
int main(int argc, char *args[])
{
    Vector2D point (2, 3);
    std::cout << point.x << std::endl;
    // screen = new Screen(SCREEN_WIDTH, SCREEN_HEIGHT);

    // while (screen->Running()) {
    //     screen->HandleEvents();
    //     screen->Update();
    //     screen->Render();
    // }

    // screen->Clean();
    // delete screen;
    return 0;
}