// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   IDrawableObject.h
  *  @brief  Rozhrani kreslitelneho objektu.
  */

#pragma once

#include "Renderer.h"

namespace GameFramework
{
    /**
     * Rozhrani objektu s moznosti vykresleni.
     */
    class IDrawableObject
    {
    public:
        virtual ~IDrawableObject() {}
        virtual void Draw(Renderer & renderer) = 0;
    };
}