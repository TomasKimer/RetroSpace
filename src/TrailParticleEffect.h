// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   TrailParticleEffect.h
  *  @brief  Casticovy efekt tryskoveho pohonu.
  */

#pragma once

#include "ParticleEmitter.h"
#include "Random.h"

namespace RetroSpace
{ 
    /**
     * Casticovy efekt trysek.
     */
    class TrailParticleEffect : public ParticleEffect
    {
    public:
        TrailParticleEffect() { m_endColor = Color::Gray(0.1f); m_lineWidth = 1.5f; }
    
        virtual Vector2f Velocity()
        {
            float n = m_random.NextFloat(-0.25f, 0.25f); //35
                
            m_velocity = Vector2f(-1.0f, n);
            m_velocity.Normalize();
                
            float ratio = m_random.NextFloat(0.175f, 0.275f);
    
            return m_velocity * ratio;
        }
    
        virtual Vector2f Position()
        {
            if (m_particleNumber % 2 == 0)
                return Vector2f(0.f, 5.f);
            else
                return Vector2f(0.f, -5.f);
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
            return TimeSpan::FromMs(m_random.Next(200, 400));
        }
    
        virtual float LineLength()
        {
            return 12.f;
        }
    
        virtual float LineWidth()
        {
            return m_lineWidth;
        }
    
        virtual bool ShortenLine()
        {
            return false;
        }
    
    private:
        Random m_random;
        Vector2f m_velocity;
    };
}