#include "Menu.h"
#include <fstream>
#include "Engine.h"

#include "World.h"

extern World world;

Menu::Menu()
{
    //ctor
    m_sizeMultiplier = 4.5;
    ///CHANGED LATER ON IN THE INITIALISATION
    choosingGame = false;
}

Menu::~Menu()
{
    //dtor
}

void Menu::load(string config)
{
    config = "config//" + config;

    ifstream stream;
    stream.open(config.c_str());

    ///Read the variables from a configuration file
    string tmp;
    stream >> tmp >> m_img;

    stream >> tmp >> m_startImg;
    stream >> tmp >> m_startRect.w >> m_startRect.h;

    stream >> tmp >> m_exitImg;
    stream >> tmp >> m_exitRect.w >> m_exitRect.h;

    stream >> tmp >> m_logoImg;
    stream >> tmp >> m_logoRect.w >> m_logoRect.h;

    stream >> tmp >> m_startButtonImg;
    stream >> tmp >> m_startButton.objectRect.w >> m_startButton.objectRect.h;

    stream >> tmp >> m_additionImg;
    stream >> tmp >> m_additionButton.objectRect.w >> m_additionButton.objectRect.h;

    stream >> tmp >> m_subtractionImg;
    stream >> tmp >> m_subtractionButton.objectRect.w >> m_subtractionButton.objectRect.h;

    stream >> tmp >> m_multiplicationImg;
    stream >> tmp >> m_multiplicationButton.objectRect.w >> m_multiplicationButton.objectRect.h;

    stream >> tmp >> m_divisionImg;
    stream >> tmp >> m_divisionButton.objectRect.w >> m_divisionButton.objectRect.h;

    stream >> tmp >> m_backButtonImg;
    stream >> tmp >> m_backButton.objectRect.w >> m_backButton.objectRect.h;

    stream >> tmp >> m_framerImg;
    stream >> tmp >> m_framerButton.objectRect.w >> m_framerButton.objectRect.h;

    stream >> tmp >> m_CheckImg;

    stream.close();

    ///Apply multiplier to change images to fit the screen

    m_exitRect.w *= m_sizeMultiplier;
    m_exitRect.h *= m_sizeMultiplier;

    m_sizeMultiplier = 3.5;

    m_startRect.w *= m_sizeMultiplier;
    m_startRect.h *= m_sizeMultiplier;

    //m_logoRect.w *= m_sizeMultiplier;
    //m_logoRect.h *= m_sizeMultiplier;

    ///Perform mathematical formulas to set the position of the buttons

    m_startRect.x = (1920 - m_startRect.w) / 2;
    m_startRect.y = 650;

    m_exitRect.x = 0;
    m_exitRect.y = 0;

    m_logoRect.x = (1920 - m_logoRect.w) / 2;
    m_logoRect.y = 100;


    m_startStartRect = m_startRect;
    m_startExitRect = m_exitRect;

    //////////////BUTTONS/////////////////////


    m_sizeMultiplier = 4;
    ///------------BACK BUTTON-------------------///
    m_backButton.objectRect.w *= m_sizeMultiplier;
    m_backButton.objectRect.h *= m_sizeMultiplier;
    m_backButton.objectRect.x = 5;
    m_backButton.objectRect.y = m_exitRect.h + 20;
    m_backButton.startRect = m_backButton.objectRect;

    m_sizeMultiplier = 2.0;

    ///------------ADDITION BUTTON-------------------///
    m_additionButton.objectRect.w *= m_sizeMultiplier;
    m_additionButton.objectRect.h *= m_sizeMultiplier;
    m_additionButton.objectRect.x = (1920 - m_additionButton.objectRect.w) / 2;
    m_additionButton.objectRect.y = 200;
    m_additionButton.startRect = m_additionButton.objectRect;


    ///------------SUBTRACTION BUTTON-------------------///
    m_subtractionButton.objectRect.w *= m_sizeMultiplier;
    m_subtractionButton.objectRect.h *= m_sizeMultiplier;
    m_subtractionButton.objectRect.x = (1920 - m_subtractionButton.objectRect.w) / 2;
    m_subtractionButton.objectRect.y = 300;
    m_subtractionButton.startRect = m_subtractionButton.objectRect;


    ///------------MULTIPLICATION BUTTON-------------------///
    m_multiplicationButton.objectRect.w *= m_sizeMultiplier;
    m_multiplicationButton.objectRect.h *= m_sizeMultiplier;
    m_multiplicationButton.objectRect.x = (1920 - m_multiplicationButton.objectRect.w) / 2;
    m_multiplicationButton.objectRect.y = 400;
    m_multiplicationButton.startRect = m_multiplicationButton.objectRect;


    ///------------DIVISION BUTTON-------------------///
    m_divisionButton.objectRect.w *= m_sizeMultiplier;
    m_divisionButton.objectRect.h *= m_sizeMultiplier;
    m_divisionButton.objectRect.x = (1920 - m_divisionButton.objectRect.w) / 2;
    m_divisionButton.objectRect.y = 500;
    m_divisionButton.startRect = m_divisionButton.objectRect;

    m_sizeMultiplier = 3.0;
    ///------------START BUTTON-------------------///
    m_startButton.objectRect.w *= m_sizeMultiplier;
    m_startButton.objectRect.h *= m_sizeMultiplier;
    m_startButton.objectRect.x = (1920 - m_startButton.objectRect.w) / 2;
    m_startButton.objectRect.y = 800;
    m_startButton.startRect = m_startButton.objectRect;
    

    ///------------FRAMER-------------------///
    m_framerButton.objectRect.w = m_startButton.objectRect.w;
    m_framerButton.objectRect.h = m_startButton.objectRect.y - m_additionButton.objectRect.y - 100;
    m_framerButton.objectRect.x = m_additionButton.objectRect.x - (m_startButton.objectRect.w - m_divisionButton.objectRect.w) / 2;
    m_framerButton.objectRect.y = m_additionButton.objectRect.y - 40;
    m_framerButton.startRect = m_framerButton.objectRect;

    ///Load textures from the input images so that they appear on the screen

    m_objectTexture = LoadTexture(m_img, world.m_main_renderer);

    m_startTexture = LoadTexture(m_startImg, world.m_main_renderer);
    m_exitTexture = LoadTexture(m_exitImg, world.m_main_renderer);

    m_logoTexture = LoadTexture(m_logoImg, world.m_main_renderer);

    m_additionButton.objTexture = LoadTexture(m_additionImg, world.m_main_renderer);
    m_subtractionButton.objTexture = LoadTexture(m_subtractionImg, world.m_main_renderer);
    m_multiplicationButton.objTexture = LoadTexture(m_multiplicationImg, world.m_main_renderer);
    m_divisionButton.objTexture = LoadTexture(m_divisionImg, world.m_main_renderer);
    m_startButton.objTexture = LoadTexture(m_startButtonImg, world.m_main_renderer);

    m_backButton.objTexture = LoadTexture(m_backButtonImg, world.m_main_renderer);
    m_framerButton.objTexture = LoadTexture(m_framerImg, world.m_main_renderer);


    m_CheckTexture = LoadTexture(m_CheckImg, world.m_main_renderer);


    world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Menu_Music_str);

    checkA = false;
    checkS = false;
    checkM = false;
    checkD = false;
    /*SDL_SetTextureColorMod(m_additionButton.objTexture, 100, 100, 100);
    SDL_SetTextureColorMod(m_subtractionButton.objTexture, 100, 100, 100);
    SDL_SetTextureColorMod(m_multiplicationButton.objTexture, 100, 100, 100);
    SDL_SetTextureColorMod(m_divisionButton.objTexture, 100, 100, 100);*/



}

void Menu::update()
{

    ///Check if the mouse is pressed and then if it is on(inside) the buttons and perform their assigned actions
    world.m_gameManager.m_inputManager.handleInput();
    timeSinceLastClick = time(NULL) - lastClick;

    if (timeSinceLastClick >= 1 && world.m_gameManager.m_inputManager.m_mouseIsClicked) 
    {
        lastClick = time(NULL);

        if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_exitRect)) {
            world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

            world.m_gameManager.m_gameState = EXIT;
        }
        if (!choosingGame)
        {
            

            if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_startRect)) {
                world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

                choosingGame = true;

            }
        
        }
        else
        {
            if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_startButton.objectRect))
            {
                world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);
                if (world.m_gameManager.m_availableOperators.add || world.m_gameManager.m_availableOperators.subtract ||
                    world.m_gameManager.m_availableOperators.multiply || world.m_gameManager.m_availableOperators.divide)
                {
                    world.m_gameManager.m_gameState = INIT_GAME;
                    world.m_gameManager.loadtimer = time(NULL);
                    choosingGame = false;
                }
            }

            if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_additionButton.objectRect))
            {
                world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

                if (!world.m_gameManager.m_availableOperators.add)
                {
                    world.m_gameManager.m_availableOperators.add = true;
                    checkA = true;
                    //SDL_SetTextureColorMod(m_additionButton.objTexture, 250, 250, 250);
                }
                else {
                    world.m_gameManager.m_availableOperators.add = false;
                    checkA = false;
                    //SDL_SetTextureColorMod(m_additionButton.objTexture, 100, 100, 100);
                }

            }

            if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_subtractionButton.objectRect))
            {
                world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

                if (!world.m_gameManager.m_availableOperators.subtract)
                {
                    world.m_gameManager.m_availableOperators.subtract = true;
                    checkS = true;
                    //SDL_SetTextureColorMod(m_subtractionButton.objTexture, 250, 250, 250);
                }
                else {
                    world.m_gameManager.m_availableOperators.subtract = false;
                    checkS = false;
                    //SDL_SetTextureColorMod(m_subtractionButton.objTexture, 100, 100, 100);
                }
            }

            if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_multiplicationButton.objectRect))
            {
                world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

                if (!world.m_gameManager.m_availableOperators.multiply)
                {
                    world.m_gameManager.m_availableOperators.multiply = true; 
                    checkM = true;
                    //SDL_SetTextureColorMod(m_multiplicationButton.objTexture, 250, 250, 250);
                }
                else {
                    world.m_gameManager.m_availableOperators.multiply = false;
                    checkM = false;
                    //SDL_SetTextureColorMod(m_multiplicationButton.objTexture, 100, 100, 100);
                }
            }

            if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_divisionButton.objectRect))
            {
                world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

                if (!world.m_gameManager.m_availableOperators.divide)
                {
                    world.m_gameManager.m_availableOperators.divide = true;
                    checkD = true;
                    //SDL_SetTextureColorMod(m_divisionButton.objTexture, 250, 250, 250);
                }
                else {
                    world.m_gameManager.m_availableOperators.divide = false;
                    checkD = false;
                    //SDL_SetTextureColorMod(m_divisionButton.objTexture, 100, 100, 100);
                }
            }
            
            if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_backButton.objectRect)) {

                world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

                choosingGame = false;
            }

        }
    }

    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor, m_startRect, m_startStartRect);
    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor, m_exitRect, m_startExitRect);

    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor, m_startButton.objectRect, m_startButton.startRect);


    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor, m_additionButton.objectRect, m_additionButton.startRect);
    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor, m_subtractionButton.objectRect, m_subtractionButton.startRect);
    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor, m_multiplicationButton.objectRect, m_multiplicationButton.startRect);
    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor, m_divisionButton.objectRect, m_divisionButton.startRect);

    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor, m_backButton.objectRect, m_backButton.startRect);

}

void Menu::draw()
{
    
    SDL_RenderCopy(world.m_main_renderer, m_objectTexture, NULL, NULL);
    SDL_RenderCopy(world.m_main_renderer, m_exitTexture, NULL, &m_exitRect);

    if (!choosingGame)
    {
        SDL_RenderCopy(world.m_main_renderer, m_startTexture, NULL, &m_startRect);
        SDL_RenderCopy(world.m_main_renderer, m_logoTexture, NULL, &m_logoRect);
    }
    else
    {

        SDL_RenderCopy(world.m_main_renderer, m_backButton.objTexture, NULL, &m_backButton.objectRect);

        SDL_RenderCopy(world.m_main_renderer, m_framerButton.objTexture, NULL, &m_framerButton.objectRect);

        SDL_RenderCopy(world.m_main_renderer, m_startButton.objTexture, NULL, &m_startButton.objectRect);

        SDL_RenderCopy(world.m_main_renderer, m_additionButton.objTexture, NULL, &m_additionButton.objectRect);
        SDL_RenderCopy(world.m_main_renderer, m_subtractionButton.objTexture, NULL, &m_subtractionButton.objectRect);
        SDL_RenderCopy(world.m_main_renderer, m_multiplicationButton.objTexture, NULL, &m_multiplicationButton.objectRect);
        SDL_RenderCopy(world.m_main_renderer, m_divisionButton.objTexture, NULL, &m_divisionButton.objectRect);

        if (checkA)  SDL_RenderCopy(world.m_main_renderer, m_CheckTexture, NULL, &m_additionButton.objectRect);
        if (checkS)  SDL_RenderCopy(world.m_main_renderer, m_CheckTexture, NULL, &m_subtractionButton.objectRect);
        if (checkM)  SDL_RenderCopy(world.m_main_renderer, m_CheckTexture, NULL, &m_multiplicationButton.objectRect);
        if (checkD)  SDL_RenderCopy(world.m_main_renderer, m_CheckTexture, NULL, &m_divisionButton.objectRect);
    }

}

void Menu::EnlargeButtons(Vector2 coor, SDL_Rect& rect, SDL_Rect startRect)
{

    double currentBW = 0;
    double currentBH = 0;

    double bonusW = 10;
    double bonusH = 10;

    double maxWidth = startRect.w + 80;
    double maxHeight = startRect.h + 80;

    if (MouseIsInRect(coor, rect))
    {
        if (rect.w <= maxWidth)
        {
            currentBW += bonusW;
            currentBH += bonusH;

            rect.w = startRect.w + currentBW;
            rect.h = startRect.h + currentBH;
            rect.x = startRect.x - currentBW / 2;
            rect.y = startRect.y - currentBH / 2;
        }
    }
    else {

        currentBW = 0;
        currentBH = 0;

        rect = startRect;

    }


}


