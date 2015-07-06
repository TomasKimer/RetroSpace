// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   MovableObject.cpp
  *  @brief  Pohybujici se herni objekt.
  */

#include "MovableObject.h"

namespace RetroSpace
{

MovableObject::MovableObject(void)
{
}

MovableObject::~MovableObject(void)
{
}

void MovableObject::Update(const GameTime & gameTime)
{
    m_velocity += m_acceleration * static_cast<float>(gameTime.Elapsed().ms());
    m_position += m_velocity * static_cast<float>(gameTime.Elapsed().ms());
}

void MovableObject::SetVelocity(Vector2f velocity, float angle)
{
    m_velocity = MathHelper::Direction(angle) * velocity;
}

void MovableObject::RotateToVelocity()
{
    float angle = MathHelper::Angle(Vector2f::Zero(), m_velocity);
    if (m_velocity.x < 0.0f)
        angle += 180.0f;
    m_rotation = angle;
}

}
