#include "World.h"

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif // _WIN32_WINNT

#include <windows.h>

World world;

int main(int argc, char* argv[])
{
    ShowWindow(GetConsoleWindow(), SW_SHOW);

    world.init();

    world.m_gameManager.initSession();
    while (!world.m_gameManager.m_quitGame)
    {
        world.m_gameManager.m_inputManager.handleInput();
        SDL_Delay(30);
        world.m_gameManager.update();
        world.m_gameManager.draw();
        SDL_Delay(10);
    }
    world.m_gameManager.deleteSession();
    world.destroy();

    return 0;
}
