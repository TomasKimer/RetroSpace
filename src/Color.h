// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Color.h
  *  @brief  Reprezentace 4-hodnotove barvy.
  */

#pragma once

#include <ostream>
#include "MathHelper.h"

namespace GameFramework
{
    /**
     * Reprezentace barvy, vcetne alfa kanalu.
     */
    class Color
    {
    public:
        Color(void): m_r(1.0f), m_g(1.0f), m_b(1.0f), m_a(1.0f) {}
        Color(float r, float g, float b, float a = 1.0f): m_r(r), m_g(g), m_b(b), m_a(a) {}
        Color(unsigned int r, unsigned int g, unsigned int b, unsigned int a = 255)
        {
            m_r = r / 255.f;
            m_g = g / 255.f;
            m_b = b / 255.f;
            m_a = a / 255.f;        
        }
        ~Color(void) {};
        
        // get
        inline float R() const { return m_r; }
        inline float G() const { return m_g; }
        inline float B() const { return m_b; }
        inline float A() const { return m_a; }
        // get uint
        inline unsigned int Ri() const { return static_cast<unsigned int>(m_r * 255.f); }
        inline unsigned int Gi() const { return static_cast<unsigned int>(m_g * 255.f); }
        inline unsigned int Bi() const { return static_cast<unsigned int>(m_b * 255.f); }
        inline unsigned int Ai() const { return static_cast<unsigned int>(m_a * 255.f); }
    
        // set
        inline void R(float r) { m_r = r; }
        inline void G(float g) { m_g = g; }
        inline void B(float b) { m_b = b; }
        inline void A(float a) { m_a = a; }
        // set uint
        inline void Ri(unsigned int r) { m_r = r / 255.f; }
        inline void Gi(unsigned int g) { m_g = g / 255.f; }
        inline void Bi(unsigned int b) { m_b = b / 255.f; }
        inline void Ai(unsigned int a) { m_a = a / 255.f; }
    
        static inline Color Black  (float alpha = 1.0f) { return Color(0.0f, 0.0f, 0.0f, alpha); }
        static inline Color White  (float alpha = 1.0f) { return Color(1.0f, 1.0f, 1.0f, alpha); }
        static inline Color Red    (float alpha = 1.0f) { return Color(1.0f, 0.0f, 0.0f, alpha); }
        static inline Color Green  (float alpha = 1.0f) { return Color(0.0f, 1.0f, 0.0f, alpha); }
        static inline Color Blue   (float alpha = 1.0f) { return Color(0.0f, 0.0f, 1.0f, alpha); }
        static inline Color Cyan   (float alpha = 1.0f) { return Color(0.0f, 1.0f, 1.0f, alpha); }
        static inline Color Magenta(float alpha = 1.0f) { return Color(1.0f, 0.0f, 1.0f, alpha); }
        static inline Color Yellow (float alpha = 1.0f) { return Color(1.0f, 1.0f, 0.0f, alpha); }    
        static inline Color Gray   (float alpha = 1.0f) { return Color(0.5f, 0.5f, 0.5f, alpha); }
        static inline Color Violet (float alpha = 1.0f) { return Color(0.5f, 0.0f, 1.0f, alpha); }    
    
        // linear interpolation
        static inline Color Lerp(Color col1, Color col2, float amount) { return  col1 +  (col2 - col1) * amount; }
    
        inline Color operator +  (const Color & c) const { return Color(m_r + c.m_r, m_g + c.m_g, m_b + c.m_b, m_a + c.m_a); }
        inline Color operator -  (const Color & c) const { return Color(m_r - c.m_r, m_g - c.m_g, m_b - c.m_b, m_a - c.m_a); }
        inline Color operator *  (float f)         const { return Color(m_r * f    , m_g * f    , m_b * f    , m_a * f    ); }
        inline bool  operator != (const Color & c) const { return m_r != c.m_r || m_g != c.m_g || m_b != c.m_b || m_a != c.m_a; }
    
        friend std::ostream& operator << (std::ostream& o, const Color & c)
        {
            o << "r: " << c.Ri() << ", g: " << c.Gi() << ", b: " << c.Bi() << ", a: " << c.Ai();
            return o;
        }
    
    private:
        float m_r, m_g, m_b, m_a;
    };
}