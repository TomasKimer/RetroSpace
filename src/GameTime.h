// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   GameTime.h
  *  @brief  Sprava herniho casu.
  */

#pragma once

#include "TimeSpan.h"
#include <ostream>
#include <iomanip>

namespace GameFramework
{
    /**
     * Sprava herniho casu.
     */
    class GameTime
    {
    public:
        GameTime(void);
        ~GameTime(void);
    
        inline TimeSpan Elapsed() const { return m_elapsed; }
        inline TimeSpan Total() const { return m_total; }
        inline TimeSpan Current() const { return m_current; }
    
        TimeSpan ElapsedBest() const { return m_elapsedBest; }
        TimeSpan ElapsedWorst() const { return m_elapsedWorst; }
    
        void Init();
        void Update();
        void Reset();
    
        friend std::ostream& operator << (std::ostream& o, const GameTime & v)
        {
           /* o << "current:" << std::setw(3) << v.Elapsed().ms() << " ms, worst:" <<
                std::setw(3) << v.ElapsedWorst().ms() << " ms, best:" << std::setw(3) << v.ElapsedBest().ms();*/
            o << std::setw(3) << v.Elapsed().ms() << " ms";
            return o;
        }
    
    private:    
        TimeSpan m_total, m_elapsed, m_current;
        TimeSpan m_elapsedBest, m_elapsedWorst;
        
        TimeSpan m_start, m_previous;
    };
}