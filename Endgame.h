#pragma once

#include "Engine.h"

#include <vector>
class Endgame
{
    public:

        Endgame();
        virtual ~Endgame();

        int frameCount;
        int frameCounter;

        vector<string> m_images;
        string m_poceedImage;

        vector<SDL_Texture*> m_textures;
        SDL_Texture* m_proceed_texture;

        SDL_Rect m_win_rect;
        SDL_Rect m_loss_rect;
        SDL_Rect m_proceed_button;
        SDL_Rect m_start_proceed_button;

        void init(string config);
        void update();
        void draw();

    protected:

    private:
};

