// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   FpsCounter.cpp
  *  @brief  Pocitani snimku za vterinu.
  */

#include "FpsCounter.h"

namespace GameFramework
{

void FpsCounter::Reset()
{
    m_current = 0.0f;
    m_average = 0.0f;
    m_best = 0.0f;
    m_worst = 999.0f;
    m_totalFrames = 0;
    
    m_frameCount = 0;
    m_totalElapsedTime = 0;
}

void FpsCounter::Update(const GameTime & gameTime)
{
    m_totalElapsedTime += gameTime.Elapsed();
    m_frameCount++;

    if (m_totalElapsedTime > 1000)
    {
        m_current = static_cast<float>(m_frameCount) / static_cast<float>(m_totalElapsedTime.ms()) * 1000.0f;            
        
        if (m_current > m_best ) m_best  = m_current;
        if (m_current < m_worst) m_worst = m_current;
    
        if (m_average == 0.0f)
            m_average = m_current;
        else
            m_average = (m_average + m_current) / 2.0f;
        
        m_frameCount = 0;
        m_totalElapsedTime = TimeSpan::Zero();        
    }
   
    m_totalFrames++;
}
    
}