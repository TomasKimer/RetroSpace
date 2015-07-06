// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   MathHelper.cpp
  *  @brief  Pomocne matematicke funkce.
  */

#include "MathHelper.h"

namespace GameFramework
{

float MathHelper::Angle(Vector2f srcPoint, Vector2f dstPoint)
{
    Vector2f dir = dstPoint - srcPoint;
    float angle = std::atan(dir.y/dir.x);
    return RadianToDegree(angle);
}

bool MathHelper::CircleLinesegmentIntersection(const Vector2f & center, float radius,
                                               const Vector2f & lineStart, const Vector2f & lineEnd)
{
    Vector2f dir = lineEnd - lineStart;
    Vector2f diff = center - lineStart;
    
    float t = (diff.Dot(dir)) / (dir.Dot(dir));
    
    t = Clamp(t, 0.0f, 1.0f);
    
    Vector2f closest = lineStart + (dir * t);
    Vector2f d = center - closest;
    
    float distsqr = d.Dot(d);
    
    return distsqr <= sqr(radius);
}
        
}
