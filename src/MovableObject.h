// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   MovableObject.h
  *  @brief  Pohybujici se herni objekt.
  */

#pragma once

#include "GameObject.h"
#include "MathHelper.h"

namespace RetroSpace
{ 
    /**
     * Objekt s moznosti pohybu (rychlosti a smeru).
     */
    class MovableObject : public GameObject
    {
    public:
        MovableObject(void);
        virtual ~MovableObject(void);
    
        virtual void Draw(Renderer & renderer) {}
        virtual void Update(const GameTime & gameTime);
    
        virtual void SetVelocity(Vector2f velocity) { m_velocity = velocity; }
        virtual void SetVelocity(Vector2f velocity, float angle);
    
        virtual void RotateToVelocity();
    
        virtual Vector2f GetVelocity() { return m_velocity; }
        virtual void ReverseVelocity() { m_velocity = -m_velocity; }
    
    protected:
        Vector2f m_velocity, m_acceleration;
    };
}
