// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ExplodeParticleEffect.h
  *  @brief  Casticovy efekt vybuchu.
  */

#pragma once

#include "ParticleEmitter.h"
#include "Random.h"

namespace RetroSpace
{ 
    /**
     * Casticovy efekt vybuchu.
     */
    class ExplodeParticleEffect : public ParticleEffect
    {
    public:
        ExplodeParticleEffect() { m_lifeTime = TimeSpan::FromMs(1500); m_lineWidth = 1.5f; }
        
        virtual Vector2f Velocity()
        {
            float r = m_random.NextFloat();
            float n = m_random.NextFloat();
                
            m_velocity = Vector2f(r - 0.5f, n - 0.5f);
            m_velocity.Normalize(); 
                
            float ratio = m_random.NextFloat(0.275f, 0.575f);
                
            return m_velocity * ratio;
        }
    
        virtual Vector2f Position()
        {
            return Vector2f::Zero();
        }
    
        virtual float Angle()
        {
            return MathHelper::Angle(Vector2f::Zero(), m_velocity);
        }
    
        virtual Color StartColor()
        {
            return ParticleEffect::StartColor();
        }
        
        virtual Color EndColor()
        {
            return ParticleEffect::EndColor();        
        }
    
        virtual TimeSpan LifeTime()
        {
            return m_lifeTime;
        }
    
        virtual float LineLength()
        {
            return 16.f;
        }
    
        virtual float LineWidth()
        {
            return m_lineWidth;
        }
    
        virtual bool ShortenLine()
        {
            return true;
        }
    
    private:
        Random m_random;
        Vector2f m_velocity;
    };
}