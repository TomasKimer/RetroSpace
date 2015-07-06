// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   RendererSelector.h
  *  @brief  Vyber a vytvoreni konkretniho rendereru.
  */

#pragma once

#include "OpenGLRenderer.h"
#include <string>
#include <stdexcept>

namespace GameFramework
{
#define DEFAULT_RENDERER OpenGLRenderer()

    /**
     * Vyber konkretni knihovny pro vykreslovani.
     */
    class RendererSelector
    {
    public:
        static Renderer *CreateRenderer(const std::string & renderer)
        {
            if (renderer == "default")
                return new DEFAULT_RENDERER;
            else if (renderer == "OpenGL")
                return new OpenGLRenderer();
            else
                throw std::invalid_argument("Unsupported renderer: " + renderer);
        };
    
    private:
        RendererSelector() {}
    };
}