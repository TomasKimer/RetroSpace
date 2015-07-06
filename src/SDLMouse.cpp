// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   SDLMouse.cpp
  *  @brief  Prace s mysi pomoci knihovny SDL.
  */

#include "SDLMouse.h"
#include "SDLPrerequisites.h"

namespace GameFramework
{

SDLMouse::SDLMouse(void): m_visible(true)
{
    MouseInit();
}


SDLMouse::~SDLMouse(void)
{
}

bool SDLMouse::IsBtnDown(BtnCode bc) const
{
    return m_btnBuffer[bc];
}

std::string SDLMouse::GetAsString(BtnCode bc)
{
    std::string name;
    
    switch (bc)
    {
        case BC_LEFT     : name = "left"; break;
        case BC_RIGHT    : name = "right"; break;
        case BC_MIDDLE   : name = "middle"; break;
        case BC_WHEELUP  : name = "wheel up"; break;
        case BC_WHEELDOWN: name = "wheel down"; break;
        case BC_X1       : name = "extra 1"; break;
        case BC_X2       : name = "extra 2"; break;
    }               

    return name;
}

BtnCode SDLMouse::BtnDown(int btn)
{
    BtnCode bc = m_btnMap[btn];
    m_btnBuffer[bc] = true;

    return bc;
}

BtnCode SDLMouse::BtnUp(int btn)
{
    BtnCode bc = m_btnMap[btn];
    m_btnBuffer[bc] = false;

    return bc;
}

void SDLMouse::SetVisible(bool visible)
{
    if (visible)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);

    m_visible = visible;
}

bool SDLMouse::IsVisible()
{
    return m_visible;
}

void SDLMouse::SetPosition(Point2i pos)
{
    SDL_WarpMouse(pos.x, pos.y);
}

#ifndef SDL_BUTTON_X1
#define SDL_BUTTON_X1 6
#endif

#ifndef SDL_BUTTON_X2
#define SDL_BUTTON_X2 7
#endif

void SDLMouse::MouseInit()
{
    memset(&m_btnBuffer, 0, 10);

    m_btnMap.insert(BtnMap::value_type(SDL_BUTTON_LEFT, BC_LEFT));
    m_btnMap.insert(BtnMap::value_type(SDL_BUTTON_RIGHT, BC_RIGHT));
    m_btnMap.insert(BtnMap::value_type(SDL_BUTTON_MIDDLE, BC_MIDDLE));
    m_btnMap.insert(BtnMap::value_type(SDL_BUTTON_WHEELUP, BC_WHEELUP));
    m_btnMap.insert(BtnMap::value_type(SDL_BUTTON_WHEELDOWN, BC_WHEELDOWN));
    m_btnMap.insert(BtnMap::value_type(SDL_BUTTON_X1, BC_X1));
    m_btnMap.insert(BtnMap::value_type(SDL_BUTTON_X2, BC_X2));
}

}