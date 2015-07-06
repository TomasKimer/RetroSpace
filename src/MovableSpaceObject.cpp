// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   MovableSpaceObject.cpp
  *  @brief  Pohybujici se vesmirny objekt.
  */

#include "MovableSpaceObject.h"
#include "MathHelper.h"

namespace RetroSpace
{

MovableSpaceObject::MovableSpaceObject(void): m_gravityMultiplier(1.f), m_refPlanet(0)
{
}

MovableSpaceObject::~MovableSpaceObject(void)
{
}

void MovableSpaceObject::Update(const GameTime & gameTime)
{
    // gravity
    if (m_refPlanet && m_refPlanet->IsActive() && m_refPlanet->HasGravity() && m_gravityMultiplier != 0.f) 
    {
        Vector2f forceDir = m_position - m_refPlanet->GetPosition();
        float factor = (m_refPlanet->GetGravityStrength() * m_gravityMultiplier) / forceDir.LengthSquared();
        m_acceleration -= forceDir.Normalize() * factor;
    }

    MovableObject::Update(gameTime);

    m_acceleration = Vector2f::Zero();

    // screen wrapping
    if (m_screenSize.x > 0 && m_screenSize.y > 0)
    {
        if (m_position.x > static_cast<float>(m_screenSize.x))
            m_position.x = 0.0f;
        if (m_position.x < 0.0f)
            m_position.x = static_cast<float>(m_screenSize.x);
    
        if (m_position.y > static_cast<float>(m_screenSize.y))
            m_position.y = 0.0f;
        if (m_position.y < 0.0f)
            m_position.y = static_cast<float>(m_screenSize.y);
    }
};

}