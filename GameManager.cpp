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
        file >> tmp >> m_creditsImg;
        file >> tmp >> m_loadingImg;

        file.close();
    }


    m_backgroundTexture = LoadTexture(m_backgroundImg, m_renderer);
    m_creditsTexture = LoadTexture(m_creditsImg, m_renderer);
    m_loadingTexture = LoadTexture(m_loadingImg, m_renderer);

    SDL_SetTextureAlphaMod(m_creditsTexture, alpha_cr);

    m_configManager.init("configManager.txt");
    m_soundManager.init("soundManager.txt");
    Vector2 screenCenter;
    screenCenter.x = world.m_SCREEN_WIDTH;
    screenCenter.y = world.m_SCREEN_HEIGHT;
    m_inputManager.init("inputManager.txt",screenCenter);

    m_menu.load("menu.txt");
    m_endgame.init("endgame.txt");
    m_gameState = CREDITS;
    
}

#pragma region INIT

void GameManager::initSession()
{

    
    
}



#pragma endregion

#pragma region MAIN

void GameManager::update()
{
    if (m_gameState == CREDITS)
    {
        if (alpha_cr == 0) m_soundManager.play(m_soundManager.Credits_str);

        if (alpha_cr <= 255)
        {
            alpha_cr++;
            SDL_SetTextureAlphaMod(m_creditsTexture, alpha_cr);
        }
        else
        {
            m_soundManager.stop(m_soundManager.Credits_str);
            m_gameState = MENU;
        }
    }
    if (m_gameState == MENU)
    {
        m_menu.update();
    }
    if (m_gameState == INIT_GAME)
    {
        if (time(NULL) - loadtimer == 0)
        {
            world.m_gameManager.m_soundManager.stop(world.m_gameManager.m_soundManager.Menu_Music_str);
            m_gameboard.init("gameboard.txt");
            m_gameboard.initSession();

            m_gameboard.player->m_objRect.x = world.m_SCREEN_HEIGHT / 2 * m_inputManager.m_mouseMultiply.x + m_gameboard.player->m_objRect.w / 2;
            m_gameboard.player->m_objRect.y = world.m_SCREEN_HEIGHT / 2 * m_inputManager.m_mouseMultiply.y - m_gameboard.player->m_objRect.h / 2;
        }
        m_gameboard.player->update();

        if (time(NULL) - loadtimer >= 5) 
        {
            m_gameboard.player->setInitialCoordinates(m_gameboard.m_tileMap[0][0]->m_objRect.x, m_gameboard.m_tileMap[0][0]->m_objRect.y);

            m_gameState = GAME;
        }
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
    if (m_gameState == CREDITS)
    {
        SDL_RenderCopy(m_renderer, m_creditsTexture, NULL, NULL);
    }
    if (m_gameState == MENU)
    {
        m_menu.draw();
    }
    if (m_gameState == INIT_GAME)
    {
        SDL_RenderCopy(m_renderer, m_loadingTexture, NULL, NULL);
        m_gameboard.player->draw();
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
