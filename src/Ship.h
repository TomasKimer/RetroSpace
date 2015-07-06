// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Ship.h
  *  @brief  Funkcionalita vesmirne lode.
  */

#pragma once

#include "MovableSpaceObject.h"
#include "MathHelper.h"
#include "ParticleEffectFactory.h"
#include "Weapon.h"
#include "ShipResources.h"
#include "Powerup.h"
#include "Random.h"
#include "Shape.h"
#include <vector>

namespace RetroSpace
{ 
    /**
     * Vesmirna lod.
     */
    class Ship : public MovableSpaceObject
    {
    public:
        /**
         * Nastaveni lode.
         */
        struct Attributes
        {
            float maxSpeed, slowdownSpeed, accelerateSpeed, turnSpeed;            
            ShipResources::Attributes resources;
        };
        
        /**
         * Nastaveni barev lode.
         */
        struct Colors
        {
            Color frame, inner;
            Color trailStart, trailEnd;     
            Color explodeStart, explodeEnd;
    
            Colors() {}
            Colors(const Color & frame, const Color & inner,
                   const Color & trailStart, const Color & trailEnd,
                   const Color & explodeStart, const Color & explodeEnd):
                   frame(frame), inner(inner), trailStart(trailStart), trailEnd(trailEnd),
                   explodeStart(explodeStart), explodeEnd(explodeEnd) {}
        };

    public:
        Ship(void);
        virtual ~Ship(void);
    
        void Accelerate(float value = 1.f) { m_accelerateValue += (value * m_attr->accelerateSpeed) / 1000.0f; }
        void Turn(float value = 1.f) { m_turnValue += value * m_attr->turnSpeed; }
        void RotateAtPoint(Point2i pos);
        void FireWeapon() { m_fire = true; }        
        void TransferEnergyShield() { m_resources.Transfer(); }
        
        void ApplyPowerup(Powerup::Attributes & attr);        
        void Hit(float damage);
        bool IsDestroyed() { return m_destroyed; }
        void Reset(Vector2f pos, float rot);
        void ResetRandom(Vector2f topLeft, Vector2f bottomRight);          
        
        virtual void Update(const GameTime & gameTime);
        virtual void Draw(Renderer & renderer);
    
        void SetColors(Colors & colors);
        void SetAttributes(Attributes & attr);        
        virtual void SetOnResize(Size2i screenSize);
        virtual void SetPlanet(Planet *planet);
        void SetWeaponTypes(WeaponTypes & wt);
        
        Weapon & GetWeapon() { return m_weapon; }
        ShipResources & GetResources() { return m_resources; } 
    
    private:
        float m_accelerateValue, m_turnValue;
        bool m_destroyed, m_justHit, m_fire;
    
        ParticleEmitter m_explodeGenerator, m_trailGenerator;
        ParticleEffect  *m_explodeBuilder,  *m_trailBuilder;
        
        Weapon m_weapon;
        WeaponTypes *m_refWeaponTypes;
    
        Shape m_shipShape;
    
        ShipResources m_resources;
        Colors *m_colors;
        Attributes *m_attr;

        Random m_random;

        void Explode();
    };
}
