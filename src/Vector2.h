// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Vector2.h
  *  @brief  Prace s 2-rozmernym vektorem.
  */

#pragma once

#include <ostream>
#include <cmath>

namespace GameFramework
{
    /**
     * Reprezentace 2-rozmerneho vektoru.
     */
    template <typename T>
    struct Vector2
    {
        T x, y;
    
        Vector2(void): x(static_cast<T>(0)), y(static_cast<T>(0)) {}
        Vector2(const Vector2<T> &v): x(v.x), y(v.y) {}    
        Vector2(T x, T y): x(x), y(y) {}
        
        template<typename U>
        Vector2(const Vector2<U> &v): x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}         
    
        inline T LengthSquared(void) const { return x * x + y * y; }
        inline T Length(void) const { return std::sqrt(LengthSquared()); }

        inline Vector2<T> SetLength(float length)
        {
            Normalize();
            (*this) *= length;
            return *this;
        }
        
        Vector2<T> Normalize(void)
        {
            T len = Length();      
            
            if (len == static_cast<T>(0))
                return *this;
            
            *this /= len;
    
            return *this;
        }
    
        // operators
        inline Vector2<T> operator +  (const Vector2<T> & v) const { return Vector2<T>(x + v.x, y + v.y);   }
        inline Vector2<T> operator +  (T n)                  const { return Vector2<T>(x + n, y + n);       }
        inline Vector2<T> operator -  (const Vector2<T> & v) const { return Vector2<T>(x - v.x, y - v.y);   }
        inline Vector2<T> operator -  (T n)                  const { return Vector2<T>(x - n, y - n);       }
        inline Vector2<T> operator -  (void)                 const { return Vector2<T>(-x, -y);             }
        inline Vector2<T> operator += (const Vector2<T> & v)       { return Vector2<T>(x += v.x, y += v.y); }
        inline Vector2<T> operator += (T n)                        { return Vector2<T>(x += n, y += n);     }
        inline Vector2<T> operator -= (const Vector2<T> & v)       { return Vector2<T>(x -= v.x, y -= v.y); }
        inline Vector2<T> operator -= (T n)                        { return Vector2<T>(x -= n, y -= n);     }
        inline Vector2<T> operator *  (T n)                  const { return Vector2<T>(x * n, y * n);       }
        inline Vector2<T> operator *= (T n)                        { return Vector2<T>(x *= n, y *= n);     }
        inline Vector2<T> operator *  (const Vector2<T> & v) const { return Vector2<T>(x * v.x, y * v.y);   }
        inline Vector2<T> operator *= (const Vector2<T> & v)       { return Vector2<T>(x *= v.x, y *= v.y); }
        inline Vector2<T> operator /  (T n)                  const { return Vector2<T>(x / n, y / n);       }
        inline Vector2<T> operator /= (T n)                        { return Vector2<T>(x /= n, y /= n);     }
        inline T          operator ^  (const Vector2<T> & v) const { return (x * v.x + y * v.y);            } // dot
        inline T                   Dot(const Vector2<T> & v) const { return (x * v.x + y * v.y);            }
        inline bool       operator == (const Vector2<T> & v) const { return (x == v.x && y == v.y);         }
    
        static inline Vector2<T> Zero() { return Vector2<T>(); }    
    
        // conversions
        template<typename U>
        inline Vector2<T> operator +  (const Vector2<U> & v) const { return Vector2<T>(x + static_cast<T>(v.x), y + static_cast<T>(v.y));   }
    
        template<typename U>
        inline Vector2<T> operator -  (const Vector2<U> & v) const { return Vector2<T>(x - static_cast<T>(v.x), y - static_cast<T>(v.y));   }
    
        template<typename U>
        inline Vector2<T> operator =  (const Vector2<U> & v) { return Vector2<T>(static_cast<T>(v.x), static_cast<T>(v.y));   }
    
        template<typename U>
        inline operator Vector2<U>() { return Vector2<U>(static_cast<U>(x), static_cast<U>(y)); }
    
    
        friend std::ostream& operator << (std::ostream& o, const Vector2<T> & v)
        {
            o << "x: " << v.x << ", y: " << v.y;
            return o;
        }
    };
    
    typedef Vector2<float> Vector2f;
    typedef Vector2<int>   Vector2i;
    typedef Vector2f       Point2f;
    typedef Vector2i       Point2i;
    typedef Vector2f       Size2f;
    typedef Vector2i       Size2i;
}