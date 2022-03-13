#pragma once

#include <string>
#include "defines.h"
#include "Engine.h"

using namespace std;

class Menu
{
public:

    Menu();
    virtual ~Menu();

    string m_img;
    SDL_Texture* m_objectTexture;

    string m_startImg;
    SDL_Texture* m_startTexture;
    SDL_Rect m_startRect;
    SDL_Rect m_startStartRect;


    string m_exitImg;
    SDL_Texture* m_exitTexture;
    SDL_Rect m_exitRect;
    SDL_Rect m_startExitRect;

    string m_logoImg;
    SDL_Texture* m_logoTexture;
    SDL_Rect m_logoRect;

    string m_additionImg;
    string m_subtractionImg;
    string m_multiplicationImg;
    string m_divisionImg;
    string m_startButtonImg;
    string m_infoButtonImg;

    string m_CheckImg;

    SDL_Texture* m_CheckTexture;

    Button m_additionButton;
    Button m_subtractionButton;
    Button m_multiplicationButton;
    Button m_divisionButton;
    Button m_startButton;
    Button m_infoButton;

    bool showInfo;

    string m_backButtonImg;
    Button m_backButton;

    string m_framerImg;
    Button m_framerButton;

    string m_infoImg;
    SDL_Texture* m_infoTexture;

    bool checkA;
    bool checkS;
    bool checkM;
    bool checkD;

    time_t lastClick;
    time_t timeSinceLastClick;

    bool choosingGame;

    float m_sizeMultiplier;


    void load(string config);
    void update();
    void draw();

    void EnlargeButtons(Vector2 coor, SDL_Rect& rect, SDL_Rect startRect);

protected:

private:
};


