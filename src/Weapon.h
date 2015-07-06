// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Weapon.h
  *  @brief  Zbran vystrelujici a spravujici projektily.
  */

#pragma once

#include "GameObject.h"
#include "Projectile.h"
#include <list>
#include "ShipResources.h"
#include "WeaponTypes.h"

namespace RetroSpace
{ 
    /**
     * Zbran.
     */
    class Weapon : public GameObject
    {
    public:
        Weapon(void);
        virtual ~Weapon(void);
    
        bool Fire(Vector2f position, float rotation, ShipResources & shipResources, TimeSpan fireTime);
    
        virtual void Update(const GameTime & gameTime);    
        virtual void Draw(Renderer & renderer);

        void Reset();    
        float ProjectileCollide(const GameObject & obj);
    
        virtual void SetOnResize(Size2i screenSize);
        void SetPlanet(Planet *planet) { m_refPlanet = planet; }
        
        void SetType(WeaponTypes::Attributes & attr) { m_attr = &attr; }
        WeaponTypes::Attributes & GetType() { return *m_attr; }
    
    private:
        bool m_fire;
        unsigned int m_firedCount;
        TimeSpan m_lastFireTime;
    
        Planet *m_refPlanet;
        WeaponTypes::Attributes *m_attr;            
        std::list<Projectile *> m_projectiles;
    };
}
