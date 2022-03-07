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
    stream >> tmp >> frameCount;
    for (int i = 0; i < frameCount; i++)
    {
        stream >> tmp;
        m_images.push_back("EndGame\\" + tmp);
    }
    stream >> tmp >> m_poceedImage >> m_proceed_button.w >> m_proceed_button.h;

    stream.close();
    m_proceed_button.x = (1920 - m_proceed_button.w) / 2;
    m_proceed_button.y = (1920 - m_proceed_button.h) / 2;
    m_start_proceed_button = m_proceed_button;
    for (int i = 0; i < frameCount; i++)
    {
        m_textures.push_back(LoadTexture(m_images[i], world.m_main_renderer));
    }

    m_proceed_texture = LoadTexture(m_poceedImage, world.m_main_renderer);
    frameCounter = 0;
}

void Endgame::update() 
{
    //D("UPDATE");
    if (world.m_gameManager.m_inputManager.m_mouseIsClicked) {
        if (MouseIsInRect(world.m_gameManager.m_inputManager.m_mouseCoor, m_proceed_button)) {

            world.m_gameManager.m_gameState = MENU;

            //world.m_gameManager.m_gameboard.deleteSession();
        }
    }
    EnlargeButtons(world.m_gameManager.m_inputManager.m_mouseCoor,m_proceed_button,m_start_proceed_button);

    //D(frameCounter/3);
    if (frameCounter < 3 * frameCount - 1)  frameCounter++;
    else
        frameCounter = 0;

}

void Endgame::draw() 
{
   
    SDL_RenderCopy(world.m_main_renderer, m_textures[frameCounter/3], NULL, NULL);

    SDL_RenderCopy(world.m_main_renderer, m_proceed_texture, NULL, &m_proceed_button);
}
