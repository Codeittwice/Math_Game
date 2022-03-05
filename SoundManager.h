#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include <SDL.h>
#include <fstream>
#include <string>
#include <iostream>
#include "defines.h"

using namespace std;

/*! \brief Used to play sound effect and music
*/

class SoundManager
{
public:
    SoundManager();
    virtual ~SoundManager();

    void init(string configFile);
    void destroyChunks();
    void play(string sound);
    void stop(string sound);

    string Background_Music_str;
    string Menu_Music_str;
    string Button_Click_str;
    string Wrong_Answer_str;
    string Right_Answer_str;

    Mix_Chunk* Background_Music;
    Mix_Chunk* Menu_Music;
    Mix_Chunk* Button_Click;
    Mix_Chunk* Wrong_Answer;
    Mix_Chunk* Right_Answer;

protected:

private:
};

#endif // SOUNDMANAGER_H
