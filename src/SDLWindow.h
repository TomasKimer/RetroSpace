// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   SDLWindow.h
  *  @brief  Prace s oknem pomoci knihovny SDL.
  */

#pragma once

#include "RenderWindow.h"
#include "SDLPrerequisites.h"

namespace GameFramework
{
    /**
     * Implementace okna knihovnou SDL.
     */
    class SDLWindow : public RenderWindow
    {
    public:
        SDLWindow(void);
        virtual ~SDLWindow(void);
    
        virtual void Create(const std::string &name, Size2i size, bool fullscreen, bool vsync = true);
        virtual void Resize(Size2i newSize, int fullscreen = -1);
        virtual void SwapBuffers(bool waitForVSync = false);
    
        // window events - input, resize
        virtual bool ProcessEvent(void);
    
    private:
        SDL_Surface *m_screen;
        unsigned int m_flags;
    
        void SetVideoMode(Size2i screenSize, unsigned int flags); 
    };
}