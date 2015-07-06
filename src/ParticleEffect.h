// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ParticleEffect.h
  *  @brief  Zaklad pro casticovy efekt.
  */

#pragma once

#include "Color.h"
#include "Vector2.h"
#include "TimeSpan.h"

using namespace GameFramework;

namespace RetroSpace
{
    /**
     * Baze pro konkretni casticovy efekt.
     */
    class ParticleEffect
    {
    public:
        ParticleEffect(): m_particleNumber(0), m_startColor(Color::Gray()) {}
        virtual ~ParticleEffect() {}   
    
        virtual Vector2f Velocity()   = 0; 
        virtual Vector2f Position()   = 0;
        virtual float    Angle()      = 0;
        virtual Color    StartColor() { return m_startColor; }
        virtual Color    EndColor()   { return m_endColor; }
        virtual TimeSpan LifeTime()   = 0;
    
        virtual float LineLength()  = 0; 
        virtual float LineWidth()   = 0;
        virtual bool  ShortenLine() = 0; 
    
        void SetParticleNumber(int num) { m_particleNumber++; }
        void SetStartColor(const Color & color) { m_startColor = color; }
        void SetEndColor(const Color & color)   { m_endColor = color; }
        void SetColors(const Color & start, const Color & end) { m_startColor = start; m_endColor = end; }
        void SetLifeTime(const TimeSpan & lifetime) { m_lifeTime = lifetime; }
        void SetLineWidth(float width) { m_lineWidth = width; }
    
    protected:
        int m_particleNumber;
        Color m_startColor, m_endColor;
        TimeSpan m_lifeTime;
        float m_lineWidth;
    };
}