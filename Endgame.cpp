#include "Endgame.h"
#include "Engine.h"
#include "Menu.h"
#include "World.h"
#include<fstream>
extern World world;
Endgame::Endgame()
{
    //ctor
}

Endgame::~Endgame()
{
    //dtor
}

void Endgame::init(string config) {
    fstream stream;
    string tmp;
    stream.open("config\\" + config);
    stream >> tmp >> m_winImage;
    stream >> tmp >> m_lossImage;
    stream >> tmp >> m_poceedImage >> m_proceed_button.w >> m_proceed_button.h;

    stream.close();
    m_proceed_button.x = (1920 - m_proceed_button.w) / 2;
    m_proceed_button.y = (1920 - m_proceed_button.h) / 2;
    m_start_proceed_button = m_proceed_button;
    m_win_texture = LoadTexture(m_winImage, world.m_main_renderer);
    m_proceed_texture = LoadTexture(m_poceedImage, world.m_main_renderer);
}

void Endgame::update() 
{
    if (world.m_gameManager.m_inputManager.m_mouseIsClicked) {
        if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_proceed_button)) {
            
            world.m_gameManager.m_gameState = MENU;
        }
    }
    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor,m_proceed_button,m_start_proceed_button);
}

void Endgame::draw() 
{
    SDL_RenderCopy(world.m_main_renderer, m_win_texture, NULL, NULL);

    SDL_RenderCopy(world.m_main_renderer, m_proceed_texture, NULL, &m_proceed_button);
}
