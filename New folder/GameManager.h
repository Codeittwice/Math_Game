#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include <SDL.h>

#include "defines.h"
#include "Engine.h"
#include "ConfigManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "GameBoard.h"
#include "Menu.h"
#include "Endgame.h"


class GameManager
{
public:
    GameManager();
    ~GameManager();

    SDL_Renderer* m_renderer;

    SDL_Rect m_backgroundRect;
    SDL_Texture* m_backgroundTexture;

    SDL_Texture* m_spaceshipTexture;
    SDL_Texture* m_spaceshipInsideTexture;
    SDL_Rect m_spaceshipRect;


    availableOperators m_availableOperators;

    int x, y, m_distance;

    string m_pausedBackgroundImg;
    SDL_Texture* m_pausedBackgroundTexture;
    SDL_Rect m_pausedBackgroundRect;

    SDL_Texture* m_titleScreenTexture;///Mars_Spaceship_Inside_FInal.bmp

    SDL_Rect m_presentRect;


    SDL_Event* m_event;
    bool* m_drag;
    bool* m_mouseIsPressed;
    bool* m_mouseIsDoubleClicked;
    Uint8* m_state;
    Vector2* m_mouseCoordinates;

    GAME_STATE m_gameState;
    ConfigManager m_configManager;
    SoundManager m_soundManager;
    InputManager m_inputManager;
    Menu m_menu;
    Endgame m_endgame;

    bool m_quitGame = false;

    string m_backgroundImg;

    string m_creditsImg;
    SDL_Texture* m_creditsTexture;
    int alpha_cr = 0;

    GameBoard m_gameboard;

    void init();
    void update();
    void draw();
    void cleaner();
    void initSession();
    void deleteSession();

};