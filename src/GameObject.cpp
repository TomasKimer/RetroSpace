// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   GameObject.cpp
  *  @brief  Zakladni herni objekt.
  */

#include "GameObject.h"

namespace RetroSpace
{

void GameObject::UpdateMatrix()
{
    m_matrix.Identity();
    m_matrix.Translate(m_position.x, m_position.y, 0.0f);
    m_matrix.Rotate(m_rotation, 0.0f, 0.0f, 1.0f);
    m_matrix.Scale(m_scale.x, m_scale.y, 1.0f);
}

void GameObject::ApplyMatrix(Renderer & renderer)
{
    renderer.SetModelviewMatrix(m_matrix);
}

void GameObject::ApplyTransformation(Renderer & renderer)
{        
    UpdateMatrix();
    ApplyMatrix(renderer);
}

bool GameObject::Collide(const GameObject & obj)
{
    if (MathHelper::CircleCircleIntersection(m_position, m_collideRadius, obj.m_position, obj.m_collideRadius))
        return true;
    return false;    
}

}