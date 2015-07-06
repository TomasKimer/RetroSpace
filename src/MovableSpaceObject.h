// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   MovableSpaceObject.h
  *  @brief  Pohybujici se vesmirny objekt.
  */

#pragma once

#include "MovableObject.h"
#include "Planet.h"
#include <cmath>

namespace RetroSpace
{
    /**
     * Pohybujici se objekt, s vlivem gravitace a kraju obrazovky.
     */
    class MovableSpaceObject : public MovableObject
    {
    public:
        MovableSpaceObject(void);
        virtual ~MovableSpaceObject(void);
    
        virtual void Draw(Renderer & renderer) {}
        virtual void Update(const GameTime & gameTime);
    
        void SetGravityMultiplier(float val) { m_gravityMultiplier = val; }
        float GetGravityMultiplier() { return m_gravityMultiplier; }

        void SetPlanet(Planet *planet) { m_refPlanet = planet; }    
        
    protected:
        float m_gravityMultiplier;
        Planet *m_refPlanet;
    };
}

