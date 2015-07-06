// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   IBasicGameObject.h
  *  @brief  Rozhrani zakladniho herniho objektu.
  */

#pragma once

#include "IUpdatableObject.h"
#include "IDrawableObject.h"

namespace GameFramework
{
    /**
     * Rozhrani objektu s moznosti aktualizace a vykresleni.
     */
    class IBasicGameObject : public IUpdatableObject, public IDrawableObject
    {
    public:
        virtual ~IBasicGameObject() {}
        virtual void Update(const GameTime & gameTime) = 0;
        virtual void Draw(Renderer & renderer) = 0;
    };
}