// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   MathHelper.h
  *  @brief  Pomocne matematicke funkce.
  */

#pragma once

#include <cmath>
#include "Vector2.h"

namespace GameFramework
{
    /**
     * Pomocne matematicke funkce.
     */
    class MathHelper
    {
    public:
        static inline float Pi()         { return  3.14159265358979f; }
        static inline float PiOver180()  { return  0.01745329251994f; }
        static inline float PiUnder180() { return 57.29577951308232f; } 
        
        template <typename T>
        static inline T sqr(T x) { return x * x; }
    
        static inline unsigned int round(float x) { return static_cast<unsigned int>(std::floor(x + 0.5f)); }
    
        static inline float DegreeToRadian(float degree) { return degree * PiOver180();  }
        static inline float RadianToDegree(float radian) { return radian * PiUnder180(); }

        template <typename T>
        static inline T Clamp(T val, T min, T max)
        {
            if (val < min)
                val = min;
            if (val > max)
                val = max;
            return val;
        }
    
        static float Angle(Vector2f srcPoint, Vector2f dstPoint);    
        static inline Vector2f Direction(float angle)
        {
            return Vector2f(cos(MathHelper::DegreeToRadian(angle)),
                            sin(MathHelper::DegreeToRadian(angle))).Normalize();
        }        

        // intersections (collision detection)
        static inline bool CirclePointIntersection(const Vector2f & center, float radius, const Vector2f & point)
        {
            if ((center - point).Length() < radius)
                return true;
            return false;
        }

        static inline bool CircleCircleIntersection(const Vector2f & center1, float radius1,
                                                    const Vector2f & center2, float radius2)         
        {
            if ((center1 - center2).Length() < radius1 + radius2)
                return true;
            return false;
        }
        
        static bool CircleLinesegmentIntersection(const Vector2f & center, float radius,
                                                  const Vector2f & lineStart, const Vector2f & lineEnd);    
    private:
        MathHelper() {}
    };
}