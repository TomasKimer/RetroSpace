// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   TimeSpan.h
  *  @brief  Reprezentace casoveho udaje.
  */

#pragma once

namespace GameFramework
{
    /**
     * Reprezentace casoveho udaje.
     */
    class TimeSpan
    {
    public:
        TimeSpan(): m_ms(0) {}
        TimeSpan(unsigned int ms): m_ms(ms) {}
    
        inline unsigned int ms() const { return m_ms; }
        inline float s() const { return m_ms / 1000.0f; }
    
        static inline TimeSpan FromMs(unsigned int ms) { return TimeSpan(ms); }
        static inline TimeSpan FromS(unsigned int s) { return TimeSpan(s * 1000); }
        static inline TimeSpan Zero() { return TimeSpan(); }
        
        inline TimeSpan operator -  (const TimeSpan & ts) const { return TimeSpan(m_ms -  ts.m_ms); }
        inline TimeSpan operator +  (const TimeSpan & ts) const { return TimeSpan(m_ms +  ts.m_ms); }
        inline TimeSpan operator += (const TimeSpan & ts)       { return TimeSpan(m_ms += ts.m_ms); }
        inline TimeSpan operator += (unsigned int ms)           { return TimeSpan(m_ms += ms);      }
        inline bool     operator == (const TimeSpan & ts) const { return m_ms == ts.m_ms; }
        inline bool     operator != (const TimeSpan & ts) const { return m_ms != ts.m_ms; }
        inline bool     operator >  (const TimeSpan & ts) const { return m_ms >  ts.m_ms; }
        inline bool     operator >= (const TimeSpan & ts) const { return m_ms >= ts.m_ms; }
        inline bool     operator <  (const TimeSpan & ts) const { return m_ms <  ts.m_ms; }
        inline bool     operator <= (const TimeSpan & ts) const { return m_ms <= ts.m_ms; }
    
    private:
        unsigned int m_ms;
    };
}