// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   FpsCounter.h
  *  @brief  Pocitani snimku za vterinu.
  */

#pragma once

#include "IUpdatableObject.h"
#include "GameTime.h"
#include <ostream>
#include <iomanip>

namespace GameFramework
{
    /**
     * Citac snimku za vterinu.
     */
    class FpsCounter : IUpdatableObject
    {
    public:
        FpsCounter(): m_current(0.0f), m_average(0.0f), m_best(0.0f), m_worst(999.0f),
                      m_totalFrames(0), m_frameCount(0) {}
        
        virtual void Update(const GameTime & gameTime);
        
        void Reset();
        
        float Current() const { return m_current; }
        float Average() const { return m_average; }
        float Best()    const { return m_best; }
        float Worst()   const { return m_worst; }    
        unsigned int TotalFrames() const { return m_totalFrames; }      
    
        friend std::ostream& operator << (std::ostream& o, const FpsCounter & v)
        {
            o << "current: " << std::setw(7) << std::fixed << std::setprecision(4) << v.Current() << ", avg: " <<
                std::setw(7) << v.Average() << ", worst: " << std::setw(7) << v.Worst() << ", best: " << std::setw(7) << v.Best();
            return o;
        }
    
    private:
        float m_current, m_average, m_best, m_worst;
        unsigned int m_totalFrames;
    
        TimeSpan m_totalElapsedTime;
        unsigned int m_frameCount;
    };
}