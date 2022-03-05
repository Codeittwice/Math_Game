#include "GameManager.h"
#include "World.h"

extern World world;

GameManager::GameManager()
{
    world.m_quitScene = false;
}

GameManager::~GameManager()
{

}

void GameManager::init()
{
    m_renderer = world.m_main_renderer;
    //m_soundManager = world.m_soundManager;
    m_drag = &world.m_inputManager->m_drag;
    m_mouseIsPressed = &world.m_inputManager->m_mouseIsClicked;
    m_mouseIsDoubleClicked = &world.m_inputManager->m_mouseIsDoubleClicked;
    m_mouseCoordinates = &world.m_inputManager->m_mouseCoor;
    m_event = &world.m_event;

    m_backgroundRect = {
    0,
    0,
    1920,
    1080
    };

    string config = "config\\gameManager.txt";


    ifstream file;

    file.open(config);

    SDL_StartTextInput();

    if (file.is_open())
    {
        string tmp;

        file >> tmp >> m_backgroundImg;

        file.close();
    }


    m_backgroundTexture = LoadTexture(m_backgroundImg, m_renderer);

    m_configManager.init("configManager.txt");
    m_soundManager.init("soundManager.txt");
    Vector2 screenCenter;
    screenCenter.x = world.m_SCREEN_WIDTH;
    screenCenter.y = world.m_SCREEN_HEIGHT;
    m_inputManager.init("inputManager.txt",screenCenter);

    m_menu.load("menu.txt");
    m_endgame.init("endgame.txt");
    m_gameState = MENU;
    
}

#pragma region INIT

void GameManager::initSession()
{

    
    
}



#pragma endregion

#pragma region MAIN

void GameManager::update()
{
    if (m_gameState == MENU)
    {
        m_menu.update();
    }
    if (m_gameState == INIT_GAME)
    {
        world.m_gameManager.m_soundManager.stop(world.m_gameManager.m_soundManager.Menu_Music_str);
        m_gameboard.init("gameboard.txt");
        m_gameboard.initSession();
        m_gameState = GAME;
    }
    if (m_gameState == GAME)
    {
        m_gameboard.update();
    }
    if (m_gameState == EXIT)
    {
        cleaner();
        deleteSession();
        m_quitGame = true;
    }
    
    if (m_gameState == ENDGAME)
    {
        m_endgame.update();
        m_gameboard.deleteSession();
    }

}

void GameManager::draw()
{

    SDL_RenderClear(m_renderer);
    if (m_gameState == MENU)
    {
        m_menu.draw();
    }

    if (m_gameState == GAME)
    {
        SDL_RenderCopy(m_renderer, m_backgroundTexture, NULL, NULL);
        m_gameboard.draw();
    }
    if (m_gameState == ENDGAME)
    {
        m_endgame.draw();
    }

    SDL_RenderPresent(m_renderer);
}

#pragma endregion




void GameManager::cleaner()
{
   
}

void GameManager::deleteSession()
{
    
}
