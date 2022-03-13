#include "SoundManager.h"

SoundManager::SoundManager()
{
    //ctor
}

SoundManager::~SoundManager()
{
    //dtor
}

void SoundManager::init(string configFile)
{
    configFile = "config\\" + configFile;

    ifstream stream;
    string tmp;

    stream.open(configFile.c_str());

    stream >> tmp >> Background_Music_str;
    stream >> tmp >> Button_Click_str;
    stream >> tmp >> Right_Answer_str;
    stream >> tmp >> Right_Answer2_str;
    stream >> tmp >> Right_Answer3_str;
    stream >> tmp >> Wrong_Answer_str;
    stream >> tmp >> Wrong_Answer2_str;
    stream >> tmp >> Wrong_Answer3_str;
    stream >> tmp >> Menu_Music_str;
    stream >> tmp >> Credits_str;
    stream >> tmp >> EndGame_str;

    stream.close();

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == - 1)
    {
        printf("s", Mix_GetError());
    }

    Background_Music = Mix_LoadWAV(("music\\" + Background_Music_str).c_str());
    Button_Click = Mix_LoadWAV(("music\\" + Button_Click_str).c_str());
    Right_Answer = Mix_LoadWAV(("music\\" + Right_Answer_str).c_str());
    Right_Answer2 = Mix_LoadWAV(("music\\" + Right_Answer2_str).c_str());
    Right_Answer3 = Mix_LoadWAV(("music\\" + Right_Answer3_str).c_str());
    Wrong_Answer = Mix_LoadWAV(("music\\" + Wrong_Answer_str).c_str());
    Wrong_Answer2 = Mix_LoadWAV(("music\\" + Wrong_Answer2_str).c_str());
    Wrong_Answer3 = Mix_LoadWAV(("music\\" + Wrong_Answer3_str).c_str());
    Menu_Music = Mix_LoadWAV(("music\\" + Menu_Music_str).c_str());
    Credits = Mix_LoadWAV(("music\\" + Credits_str).c_str());
    EndGame = Mix_LoadWAV(("music\\" + EndGame_str).c_str());
}

void SoundManager::play(string sound)
{
    /*  We set aside channels from which later we can play sound.
    * 
    *   
    *    We check which sound we have and then load it. Set on which channel we want to play it and how many times to repeat.
    *   Then we set volume to the channel we want.
    */

    Mix_AllocateChannels(12);

    if(sound == Background_Music_str)
    {
        Mix_PlayChannel(1, Background_Music, INT_MAX);
        Mix_Volume(1, 10);
    }
    if (sound == Button_Click_str)
    {
        Mix_PlayChannel(2, Button_Click, 0);
        Mix_Volume(2, 60);
    }
    if (sound == Right_Answer_str)
    {
        Mix_PlayChannel(3, Right_Answer, 0);
        Mix_Volume(3, 200);
    }
    if (sound == Wrong_Answer_str)
    {
        Mix_PlayChannel(4, Wrong_Answer, 0);
        Mix_Volume(4, 200);
    }
    if (sound == Menu_Music_str)
    {
        Mix_PlayChannel(5, Menu_Music, INT_MAX);
        Mix_Volume(5, 5);
    }
    if (sound == Credits_str)
    {
        Mix_PlayChannel(6, Credits, 0);
        Mix_Volume(6, 30);
    }
    if (sound == Right_Answer2_str)
    {
        Mix_PlayChannel(7, Right_Answer2, 0);
        Mix_Volume(7, 200);
    }
    if (sound == Right_Answer3_str)
    {
        Mix_PlayChannel(8, Right_Answer3, 0);
        Mix_Volume(8, 200);
    }
    if (sound == EndGame_str)
    {
        Mix_PlayChannel(9, EndGame, INT_MAX);
        Mix_Volume(9, 50);
    }
    if (sound == Wrong_Answer2_str)
    {
        Mix_PlayChannel(10, Wrong_Answer2, 0);
        Mix_Volume(10, 200);
    }
    if (sound == Wrong_Answer3_str)
    {
        Mix_PlayChannel(11, Wrong_Answer3, 0);
        Mix_Volume(11, 200);
    }
}

void SoundManager::stop(string sound)
{

    if (sound == Background_Music_str)
    {
        Mix_HaltChannel(1);
    }
    if (sound == Button_Click_str)
    {
        Mix_HaltChannel(2);
    }
    if (sound == Right_Answer_str)
    {
        Mix_HaltChannel(3);
    }
    if (sound == Wrong_Answer_str)
    {
        Mix_HaltChannel(4);
    }
    if (sound == Menu_Music_str)
    {
        Mix_HaltChannel(5);
    }
    if (sound == Menu_Music_str)
    {
        Mix_HaltChannel(6);
    }
    if (sound == Right_Answer2_str)
    {
        Mix_HaltChannel(7);
    }
    if (sound == Right_Answer3_str)
    {
        Mix_HaltChannel(8);
    }
    if (sound == EndGame_str)
    {
        Mix_HaltChannel(9);
    }
    if (sound == Wrong_Answer2_str)
    {
        Mix_HaltChannel(10);
    }
    if (sound == Wrong_Answer3_str)
    {
        Mix_HaltChannel(11);
    }
}

void SoundManager::destroyChunks()
{
    /*Mix_FreeChunk(Background_Music);
    Background_Music = NULL;*/

}
