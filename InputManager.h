#pragma once

#include <utility>

#include <SDL.h>
#include <fstream>
#include <string>

#include "defines.h"
#include "Engine.h"

    /*
    * \brief input handler
    * In order to use this class first you must init it from the World
    * if you need any variable you can pass it by reference
    * don't call SDL_PollEvent or SDL_GetKeyboardState anywhere else
    */

    class InputManager
    {
    public:
        InputManager();
        ~InputManager();

        bool m_mouseIsClicked;
        bool m_mouseIsDoubleClicked;
        bool m_drag;
        bool m_shootIsPressed;
        bool m_mouseIsHolded;
        bool m_mouseFirstClicked;
        bool m_EnterIsPressed;
        Vector2 m_mouseCoor;
        const Uint8* m_keyboardState;

        int move_up;
        int move_down;
        int move_left;
        int move_right;
        int craft;

        pair<bool, SDL_Scancode> m_up;
        pair<bool, SDL_Scancode> m_down;
        pair<bool, SDL_Scancode> m_left;
        pair<bool, SDL_Scancode> m_right;
        pair<bool, SDL_Scancode> m_craft;
        pair<bool, SDL_Scancode> m_space;

        string getInputData();
        void handleInput(); //< call the SDL_PollEvent fnc and update all variables
        void setMouseMultiply(Vector2f multiplier); //< multiply the mouseCoor corespondingly to the screen resolution

        void init(string path, Vector2 screenCenter); //< read the pre-set controlls in a configFile 
        void startTextInput();
        void stopTextInput();
        string getTextInput();
        void resetText();
   // private:
        SDL_Event m_event;

        Vector2f m_mouseMultiply;

        Vector2* m_playerScreenPos;

        Vector2 m_screenCenter;
        Vector2 m_direction;

        string m_inputData;

        string m_textInput;

        bool m_textInputIsActive;




    };