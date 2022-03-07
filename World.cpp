#include "World.h"
#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

World::World()
{
    m_endGame = false;
    m_main_renderer = nullptr;
    m_main_window = nullptr;
    m_inputManager = new InputManager();
    m_soundManager = new SoundManager();
}

World::~World()
{
    //dtor
}

void World::init()
{
    srand(time(NULL));

    m_SCREEN_WIDTH = 1920;
    m_SCREEN_HEIGHT = 1080;

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    m_main_window = SDL_CreateWindow("Red Voyage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, 0);
	m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_PRESENTVSYNC);
    improveRenderer();

    m_soundManager -> init("soundManager.txt");

    // m_soundManager -> play("Background_Music.mp3");

    string cursorImg = "img\\" + MENU_FOLDER + "cursor.bmp";

    SDL_Surface* loadSurface = SDL_LoadBMP((cursorImg.c_str()));
    SDL_Cursor* cursor = SDL_CreateColorCursor(loadSurface, 10, 5);
    SDL_SetCursor(cursor);

    loadSurface = nullptr;
    cursor = nullptr;

    improveRenderer();
    m_gameManager.init();
}

void World::improveRenderer()
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto desktopWidth = DM.w;
    auto desktopHeight = DM.h;

    m_gameManager.m_inputManager.m_mouseMultiply.x = (double) m_SCREEN_WIDTH / (double)desktopWidth;
    m_gameManager.m_inputManager.m_mouseMultiply.y = (double) m_SCREEN_HEIGHT / (double)desktopHeight;
    m_gameManager.m_inputManager.setMouseMultiply(m_gameManager.m_inputManager.m_mouseMultiply);

    if(SDL_SetWindowFullscreen(m_main_window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
    {
        cout << "SDL_IMPROVE_RENDERER FAILED: %s\n" << SDL_GetError() << endl;
    }
    //m_SCREEN_WIDTH = desktopWidth;
    //m_SCREEN_HEIGHT = desktopHeight;
    SDL_RenderSetLogicalSize(m_main_renderer, 1920, 1080);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void World::destroy()
{
    SDL_DestroyWindow(m_main_window);
    SDL_DestroyRenderer(m_main_renderer);
    //m_soundManager -> destroyChunks();
}

void World::input()
{
    m_inputManager->handleInput();
}
