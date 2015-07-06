// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   SDLMouse.h
  *  @brief  Prace s mysi pomoci knihovny SDL.
  */

#pragma once

#include <map>
#include "Mouse.h"

namespace GameFramework
{
    /**
     * Implementace spravy mysi pomoci knihovny SDL.
     */
    class SDLMouse : public Mouse
    {
    public:
        SDLMouse(void);
        virtual ~SDLMouse(void);
    
        virtual bool IsBtnDown(BtnCode bc) const;
        virtual std::string GetAsString(BtnCode bc);
    
        virtual void SetVisible(bool visible);
        virtual bool IsVisible();
        virtual void SetPosition(Point2i pos);
        
    private:
        void MouseInit();
    
        virtual BtnCode BtnDown(int btn);
        virtual BtnCode BtnUp(int btn);
    
        typedef std::map<int, BtnCode> BtnMap;
        BtnMap m_btnMap;
        bool m_btnBuffer[10];
    
        bool m_visible;
    };
}