// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Particle.h
  *  @brief  Reprezentace jedne castice.
  */

#pragma once

#include "MovableObject.h"
#include "Color.h"
#include "Vector2.h"

namespace RetroSpace
{
    /**
     * Reprezentace jedne vygenerovane castice.
     */
    class Particle : public MovableObject
    {
    public:
        Particle(const Vector2f & velocity, const Vector2f & position, float rotation, const Matrix & parentMatrix, const TimeSpan & lifetime,
                 const Color & startColor, const Color & endColor, float lineLength, bool shortenLine, float lineWidth);
        virtual ~Particle(void);
    
        virtual void Update(const GameTime & gameTime);
        virtual void Draw(Renderer & renderer);
    
        bool IsAlive() { return m_alive; }
    
    private:
        Color m_color, m_startColor, m_endColor;
        TimeSpan m_endTime, m_lifetime;
        float m_lineWidth, m_halfLineLength, m_lenX;
        bool m_alive, m_shortenLine;
        
        Matrix m_parentMatrix;
    };
}

