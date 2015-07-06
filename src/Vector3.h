// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Vector3.h
  *  @brief  Prace s 3-rozmernym vektorem.
  */

#pragma once

#include <ostream>
#include <cmath>

namespace GameFramework
{
    /**
     * Reprezentace 3-rozmerneho vektoru.
     */
    template <typename T>
    struct Vector3
    {
        T x, y, z;
    
        Vector3(void): x((T)0), y((T)0), z((T)0) {}
        Vector3(const Vector3<T> &v): x(v.x), y(v.y), z(v.z) {}
        Vector3(T x, T y, T z): x(x), y(y), z(z) {}

        inline T LengthSquared(void) const { return x * x + y * y + z * z; }
        inline T Length(void) const { return std::sqrt(LengthSquared()); }

        Vector3<T> Normalize(void)
        {
            T len = Length();      
            
            if (len == static_cast<T>(0))
                return *this;
            
            x /= len;
            y /= len;
            z /= len;
    
            return *this;
        }

        inline Vector3<T> operator * (T n) const { return Vector3<T>(x * n, y * n, z * n); }
        inline Vector3<T> operator * (const Vector3<T> & v) const { return Vector3<T>(x * v.x, y * v.y, z * v.z); }
    
    
        friend std::ostream& operator << (std::ostream& o, const Vector3<T> & v)
        {
            o << "x: " << v.x << ", y: " << v.y << ", z: " << v.z;
            return o;
        }
    
    };
    
    typedef Vector3<float> Vector3f;
    typedef Vector3f Point3f;
}