#include "InputManager.h"
#include "World.h";

extern World world;

#include "InputManager.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
    delete m_keyboardState;
}

void InputManager::setMouseMultiply(Vector2f multiplier)
{
    m_mouseMultiply.x = multiplier.x;
    m_mouseMultiply.y = multiplier.y;
}

void startDrag(void* handleInput)
{
    InputManager* inputManager = (InputManager*)handleInput;
    inputManager->m_drag = true;
}

void stopDrag(void* handleInput)
{
    InputManager* inputManager = (InputManager*)handleInput;
    inputManager->m_drag = false;
}

void InputManager::init(string path, Vector2 screenCenter)
{
    path = "config\\" + path;

    fstream stream;
    string tmp;

    stream.open(path);

    stream >> tmp >> move_up;
    stream >> tmp >> move_down;
    stream >> tmp >> move_left;
    stream >> tmp >> move_right;
    stream >> tmp >> craft;

    stream.close();

    m_up.second = (SDL_Scancode)move_up;
    m_down.second = (SDL_Scancode)move_down;
    m_left.second = (SDL_Scancode)move_left;
    m_right.second = (SDL_Scancode)move_right;
    m_craft.second = (SDL_Scancode)craft;

    m_screenCenter = screenCenter;
    /*Vector2f buff;
    buff.x = 1;
    buff.y = 1;
    setMouseMultiply(buff);*/
}

void InputManager::handleInput()
{
    m_EnterIsPressed = false;
    SDL_PollEvent(&m_event);
    SDL_StartTextInput();

    m_keyboardState = SDL_GetKeyboardState(NULL);

    m_mouseIsClicked = false;
    m_mouseIsDoubleClicked = false;
    m_shootIsPressed = false;


    if (m_event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (m_event.button.clicks >= 2)
        {
            m_mouseIsDoubleClicked = true;
        }
        
        m_mouseIsClicked = true;
    }

    if (m_event.type == SDL_MOUSEMOTION)
    {
        SDL_GetGlobalMouseState(&(m_mouseCoor.x), &(m_mouseCoor.y));
        m_mouseCoor.x *= m_mouseMultiply.x;
        m_mouseCoor.y *= m_mouseMultiply.y;
    }

    if (m_textInputIsActive)
    {

        if (m_event.type == SDL_TEXTINPUT || m_event.type == SDL_KEYDOWN)
        {
            if (m_event.type == SDL_KEYDOWN && m_event.key.keysym.sym == SDLK_BACKSPACE && m_textInput.length() > 0)
            {
                m_textInput = m_textInput.substr(0, m_textInput.length() - 1);
            }
            if (m_event.type == SDL_TEXTINPUT || m_event.type == SDL_KEYUP)
            {
                m_textInput += m_event.text.text;
            }
            if (m_event.type == SDL_KEYDOWN && (m_event.key.keysym.sym == SDLK_RETURN || m_event.key.keysym.sym == SDLK_KP_ENTER))
            {
                m_EnterIsPressed = true;
            }
        }
    }
    else
    {
        if (m_keyboardState != NULL)
        {

            if (m_keyboardState[SDL_SCANCODE_SPACE])
            {
                m_space.first = true;
                Sleep(100);
            }
            if (m_keyboardState[m_up.second])
            {
                m_up.first = true;
                m_inputData += "U";
            }
            else
            {
                m_up.first = false;
            }
            if (m_keyboardState[m_down.second])
            {
                m_down.first = true;
                m_inputData += "D";
            }
            else
            {
                m_down.first = false;
            }
            if (m_keyboardState[m_left.second])
            {
                m_left.first = true;
                m_inputData += "L";
            }
            else
            {
                m_left.first = false;
            }
            if (m_keyboardState[m_right.second])
            {
                m_right.first = true;
                m_inputData += "R";
            }
            else
            {
                m_right.first = false;
            }
            if (m_keyboardState[m_craft.second])
            {
                m_craft.first = true;
            }
            else
            {
                m_craft.first = false;
            }
        }
    }

    if (m_mouseIsClicked)
    {
        m_shootIsPressed = true;
        if (!m_mouseIsHolded)
        {
            m_mouseFirstClicked = true;
        }
        else
        {
            m_mouseFirstClicked = false;
        }
        m_mouseIsHolded = true;

    }
    else
    {
        m_shootIsPressed = false;
        m_mouseIsHolded = false;
        m_mouseFirstClicked = false;
    }


    if (m_mouseIsClicked)
    {
        //shoot
    }
}

string InputManager::getInputData()
{
    if (m_inputData != "")
    {
        string returnValue = m_inputData;
        m_inputData.clear();
        return returnValue;
    }

    return m_inputData;
}

void InputManager::startTextInput()
{
    SDL_StartTextInput();

    m_textInput = "";

    m_textInputIsActive = true;
}

void InputManager::stopTextInput()
{
    SDL_StopTextInput();

    m_textInputIsActive = false;
}

string InputManager::getTextInput()
{
    return m_textInput;
}

void InputManager::resetText()
{
    m_textInput = "";
}


