// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ParticleEmitter.h
  *  @brief  Generator castic.
  */

#pragma once

#include "GameObject.h"
#include "Particle.h"
#include "ParticleEffect.h"
#include <list>

namespace RetroSpace
{ 
    /**
     * Generator castic.
     */
    class ParticleEmitter : public GameObject
    {
    public:
        ParticleEmitter(void);
        virtual ~ParticleEmitter(void);
    
        void Emit(ParticleEffect *pb, int count, Matrix & matrix, TimeSpan generateTime = TimeSpan::Zero());
        virtual void Update(const GameTime & gameTime);
        virtual void Draw(Renderer & renderer);  
    
        bool IsActive() { return m_active; }
        void SetCooldown(const TimeSpan & time) { m_cooldownTime = time; }
    
    private:
        std::list<Particle *> m_particles;
        bool m_active;
    
        TimeSpan m_lastGenerateTime, m_cooldownTime;
    };
}

