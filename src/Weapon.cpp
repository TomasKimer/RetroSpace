// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Weapon.cpp
  *  @brief  Zbran vystrelujici a spravujici projektily.
  */

#include "Weapon.h"

namespace RetroSpace
{

Weapon::Weapon(void): m_fire(false), m_firedCount(0u), m_refPlanet(0), m_attr(0)
{
}

Weapon::~Weapon(void)
{
}

bool Weapon::Fire(Vector2f position, float rotation, ShipResources &shipResources, TimeSpan fireTime)
{
    if (m_firedCount < m_attr->weap.maxAtTime && fireTime - m_lastFireTime > m_attr->weap.cooldownTime)
    {
        if (shipResources.EnergyDown(m_attr->weap.energyCost))
        {
            m_fire = true;
            SetPosition(position);
            SetRotation(rotation);  
            m_lastFireTime = fireTime;
            return true;
        }
        else
            return false;
    }
    return true;
}

void Weapon::Update(const GameTime & gameTime)
{
    if (m_fire)
    {
        m_fire = false;

        Projectile *newProjectile = new Projectile(m_position, m_rotation, m_matrix, m_attr->proj);
        newProjectile->SetOnResize(m_screenSize);
        newProjectile->SetPlanet(m_refPlanet);
        
        m_projectiles.push_back(newProjectile);
        m_firedCount++;
    }

    std::list<Projectile *>::iterator it = m_projectiles.begin();
    while (it != m_projectiles.end())
    {
        (*it)->Update(gameTime);
        if (!(*it)->IsAlive())
        {
            delete (*it);
            it = m_projectiles.erase(it);
        }
        else if (!(*it)->IsArmed() && !(*it)->ArmedChecked())
        {
            m_firedCount--;
        }
        else
            it++;
    }    
}

void Weapon::Draw(Renderer & renderer)
{          
    for (std::list<Projectile *>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++)
        (*it)->Draw(renderer);        
}

void Weapon::Reset()
{
    for (std::list<Projectile *>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++)
        (*it)->Explode();
}

float Weapon::ProjectileCollide(const GameObject & obj)
{
    for (std::list<Projectile *>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++)
        if ((*it)->Collide(obj))
            return (*it)->GetDamage();
    return 0.f;
}

void Weapon::SetOnResize(Size2i screenSize)
{
    GameObject::SetOnResize(screenSize);
    for (std::list<Projectile *>::iterator it = m_projectiles.begin(); it != m_projectiles.end(); it++)
        (*it)->SetOnResize(m_screenSize);
}

}