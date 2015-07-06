// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Projectile.cpp
  *  @brief  Sprava jednoho vystreleneho projektilu.
  */

#include "Projectile.h"

namespace RetroSpace
{

Projectile::Projectile(const Vector2f & position, float rotation, const Matrix & parentMatrix, WeaponTypes::Attributes::Projectile & attr):
                   m_alive(true), m_armed(true), m_checked(false), m_explode(false)
{        
    m_attr = &attr;
    
    SetPosition(position);
    SetVelocity(Vector2f(m_attr->velocity, m_attr->velocity), rotation);
    SetRotation(rotation);  //

    m_gravityMultiplier = m_attr->gravityMultiplier;
    if (m_attr->collideType == WeaponTypes::CT_CIRCLE)
        m_collideRadius = m_attr->collideRadius;

    m_trailGenerator.SetPosition(Vector2f(-10.f, 0.f));
}

Projectile::~Projectile(void)
{
}

void Projectile::Update(const GameTime & gameTime)
{
    m_explodeGenerator.Update(gameTime);        
    
    if (!m_armed && !m_explodeGenerator.IsActive() && !m_trailGenerator.IsActive())
    {
        m_alive = false;
        return;
    }        
    
    if (!m_armed)
    {
        m_trailGenerator.Update(gameTime);
        return;
    }
    
    if (m_endTime == TimeSpan::Zero())
        m_endTime = gameTime.Current() + m_attr->lifeTime;

    if (gameTime.Current() > m_endTime || m_explode)
    {            
        m_armed = false;
        m_explodeGenerator.Emit(m_attr->explodeEffect, m_attr->explodeParticleCount, m_matrix);
        return;
    }
    
    MovableSpaceObject::Update(gameTime);

    RotateToVelocity();

    // update matrix
    m_matrix = Matrix();
    m_matrix.Translate(m_position.x, m_position.y, 0.0f);
    m_matrix.Rotate(m_rotation, 0.0f, 0.0f, 1.0f);
    m_matrix.Translate(m_attr->shapeOffset.x, m_attr->shapeOffset.y, 0);
    
    m_trailGenerator.Emit(m_attr->trailEffect, gameTime.Elapsed().ms() / 2 , this->m_matrix);
    m_trailGenerator.Update(gameTime);
}        

void Projectile::Draw(Renderer & renderer)
{
    m_explodeGenerator.Draw(renderer);
    m_trailGenerator.Draw(renderer);
    
    if (!m_armed)
        return;
    
    ApplyMatrix(renderer);
    renderer.SetColor(m_attr->color);
    renderer.DrawShape(m_attr->shape);
}

bool Projectile::Collide(const GameObject & obj)
{
    if (m_attr->collideType == WeaponTypes::CT_LINE_SEGMENT)
    {
        Point2f projectileStartPos = Point2f(m_matrix.GetXpos(), m_matrix.GetYpos());            
        Matrix tmp = m_matrix;
        tmp.Translate(m_attr->collideSegmentEnd.x, m_attr->collideSegmentEnd.y, 0.f);
        Point2f projectileEndPos = Point2f(tmp.GetXpos(), tmp.GetYpos());

        if (MathHelper::CircleLinesegmentIntersection(obj.GetPosition(), obj.GetCollideRadius(), projectileStartPos, projectileEndPos))
        {
            if (m_armed)
            {                    
                Explode();
                return true;
            }
        }
    }
    else if (m_attr->collideType == WeaponTypes::CT_CIRCLE)
    {
        if (GameObject::Collide(obj))
        {
            if (m_armed)
            {                    
                Explode();
                return true;
            }
        }
    }            
    return false;
}

bool Projectile::ArmedChecked()
{
    if (!m_checked)
    {
        m_checked = true;
        return false;
    }
    return true;
}

}
