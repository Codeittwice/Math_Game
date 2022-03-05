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
    stream >> tmp >> m_startRect.w;
    stream >> tmp >> m_startRect.h;

    stream >> tmp >> m_exitImg;
    stream >> tmp >> m_exitRect.w;
    stream >> tmp >> m_exitRect.h;

    stream >> tmp >> m_logoImg;
    stream >> tmp >> m_logoRect.w;
    stream >> tmp >> m_logoRect.h;

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



    stream.close();

    ///Apply multiplier to change images to fit the screen

    m_startRect.w *= m_sizeMultiplier;
    m_startRect.h *= m_sizeMultiplier;

    m_exitRect.w *= m_sizeMultiplier;
    m_exitRect.h *= m_sizeMultiplier;

    m_logoRect.w *= m_sizeMultiplier;
    m_logoRect.h *= m_sizeMultiplier;

    ///Perform mathematical formulas to set the position of the buttons

    m_startRect.x = (1920 - m_startRect.w) / 2;
    m_startRect.y = 650;

    m_exitRect.x = (1920 - m_startRect.w) / 2;
    m_exitRect.y = 800;

    m_logoRect.x = (1920 - m_logoRect.w) / 2 + 20;
    m_logoRect.y = 0;


    m_startStartRect = m_startRect;
    m_startExitRect = m_exitRect;

    //////////////BUTTONS/////////////////////


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

    world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Menu_Music_str);


    SDL_SetTextureColorMod(m_additionButton.objTexture, 50, 50, 50);
    SDL_SetTextureColorMod(m_subtractionButton.objTexture, 50, 50, 50);
    SDL_SetTextureColorMod(m_multiplicationButton.objTexture, 50, 50, 50);
    SDL_SetTextureColorMod(m_divisionButton.objTexture, 50, 50, 50);



}

void Menu::update()
{

    ///Check if the mouse is pressed and then if it is on(inside) the buttons and perform their assigned actions
    world.m_gameManager.m_inputManager.handleInput();
    timeSinceLastClick = time(NULL) - lastClick;
    if (timeSinceLastClick >= 1 && world.m_gameManager.m_inputManager.m_mouseIsClicked) 
    {
        lastClick = time(NULL);
        if (!choosingGame && MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_exitRect)) {
            world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

            world.m_gameManager.m_gameState = EXIT;
            //world.m_gameManager.m_quitScene = true;
        }

        if (!choosingGame && MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_startRect)) {
            world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

            choosingGame = true;

            //world.m_gameManager.m_quitScene = true;
        }

        if (choosingGame && MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_startButton.objectRect)) 
        {
            world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);
            if(world.m_gameManager.m_availableOperators.add || world.m_gameManager.m_availableOperators.subtract || 
                world.m_gameManager.m_availableOperators.multiply || world.m_gameManager.m_availableOperators.divide)
            world.m_gameManager.m_gameState = INIT_GAME;
            choosingGame = false;
        }

        if (choosingGame && MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_additionButton.objectRect))
        {
            world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

            if (!world.m_gameManager.m_availableOperators.add)
            {
                world.m_gameManager.m_availableOperators.add = true;
                SDL_SetTextureColorMod(m_additionButton.objTexture, 250, 250, 250);
            }
            else {
                world.m_gameManager.m_availableOperators.add = false;
                SDL_SetTextureColorMod(m_additionButton.objTexture, 50, 50, 50);
            }

        }
        if (choosingGame && MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_subtractionButton.objectRect))
        {
            world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

            if (!world.m_gameManager.m_availableOperators.subtract)
            {
                world.m_gameManager.m_availableOperators.subtract = true;
                SDL_SetTextureColorMod(m_subtractionButton.objTexture, 250, 250, 250);
            }
            else {
                world.m_gameManager.m_availableOperators.subtract = false;
                SDL_SetTextureColorMod(m_subtractionButton.objTexture, 50, 50, 50);
            }
        }
        if (choosingGame && MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_multiplicationButton.objectRect))
        {
            world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

            if (!world.m_gameManager.m_availableOperators.multiply)
            {
                world.m_gameManager.m_availableOperators.multiply = true;
                SDL_SetTextureColorMod(m_multiplicationButton.objTexture, 250, 250, 250);
            }
            else {
                world.m_gameManager.m_availableOperators.multiply = false;
                SDL_SetTextureColorMod(m_multiplicationButton.objTexture, 50, 50, 50);
            }
        }
        if (choosingGame && MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_divisionButton.objectRect))
        {
            world.m_gameManager.m_soundManager.play(world.m_gameManager.m_soundManager.Button_Click_str);

            if (!world.m_gameManager.m_availableOperators.divide)
            {
                world.m_gameManager.m_availableOperators.divide = true;
                SDL_SetTextureColorMod(m_divisionButton.objTexture, 250, 250, 250);
            }
            else {
                world.m_gameManager.m_availableOperators.divide = false;
                SDL_SetTextureColorMod(m_divisionButton.objTexture, 50, 50, 50);
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

}

void Menu::draw()
{
    ///Copiing the textures and handing them to the renderer a.k.a. drawing them on our window
    //SDL_RenderClear(world.m_main_renderer);

    SDL_RenderCopy(world.m_main_renderer, m_objectTexture, NULL, NULL);

    if (!choosingGame)
    {
        SDL_RenderCopy(world.m_main_renderer, m_startTexture, NULL, &m_startRect);
        SDL_RenderCopy(world.m_main_renderer, m_exitTexture, NULL, &m_exitRect);
        SDL_RenderCopy(world.m_main_renderer, m_logoTexture, NULL, &m_logoRect);
    }
    else
    {
        SDL_RenderCopy(world.m_main_renderer, m_startButton.objTexture, NULL, &m_startButton.objectRect);

        SDL_RenderCopy(world.m_main_renderer, m_additionButton.objTexture, NULL, &m_additionButton.objectRect);
        SDL_RenderCopy(world.m_main_renderer, m_subtractionButton.objTexture, NULL, &m_subtractionButton.objectRect);
        SDL_RenderCopy(world.m_main_renderer, m_multiplicationButton.objTexture, NULL, &m_multiplicationButton.objectRect);
        SDL_RenderCopy(world.m_main_renderer, m_divisionButton.objTexture, NULL, &m_divisionButton.objectRect);
    }
    //SDL_RenderPresent(world.m_main_renderer);

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


