// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Projectile.h
  *  @brief  Sprava jednoho vystreleneho projektilu.
  */

#pragma once

#include "MovableSpaceObject.h"
#include "ParticleEffectFactory.h"
#include "WeaponTypes.h"
#include "Log.h"

namespace RetroSpace
{ 
    /**
     * Projektil vystreleny ze zbrane.
     */
    class Projectile : public MovableSpaceObject
    {
    public:
        Projectile(const Vector2f & position, float rotation, const Matrix & parentMatrix,
                   WeaponTypes::Attributes::Projectile & attr);
        virtual ~Projectile(void);
    
        virtual void Update(const GameTime & gameTime);
        virtual void Draw(Renderer & renderer);

        virtual bool Collide(const GameObject & obj);
    
        bool IsAlive() { return m_alive; }
        bool IsArmed() { return m_armed; }
        bool ArmedChecked();
    
        void Explode() { m_explode = true; }
        float GetDamage() { return m_attr->damage; }
    
    private:
        TimeSpan m_endTime;
        bool m_alive, m_armed, m_explode, m_checked;

        WeaponTypes::Attributes::Projectile *m_attr;        
        ParticleEmitter m_trailGenerator, m_explodeGenerator;
    };
}

