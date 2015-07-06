// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   RenderWindowSelector.h
  *  @brief  Vyber a vytvoreni konkretniho okna.
  */

#pragma once

#include "SDLWindow.h"
#include <string>
#include <stdexcept>

namespace GameFramework
{
#define DEFAULT_WINDOW_MANAGER SDLWindow()

    /**
     * Vyber knihovny pro spravu okna.
     */
    class RenderWindowSelector
    {
    public:
        static RenderWindow *CreateRenderWindow(const std::string & windowManager)
        {
            if (windowManager == "default")
                return new DEFAULT_WINDOW_MANAGER;
            else if (windowManager == "SDL")
                return new SDLWindow();
            else
                throw std::invalid_argument("Unsupported window manager: " + windowManager);
        }
    
    private:
        RenderWindowSelector() {}
    };
}