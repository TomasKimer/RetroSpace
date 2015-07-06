// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   IUpdatableObject.h
  *  @brief  Rozhrani aktualizovatelneho objektu.
  */

#pragma once

#include "GameTime.h"

namespace GameFramework
{
    /**
     * Rozhrani objektu s moznosti aktualizace.
     */
    class IUpdatableObject
    {
    public:
        virtual ~IUpdatableObject() {}
        virtual void Update(const GameTime & gameTime) = 0;
    };
}