// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Mouse.h
  *  @brief  Rozhrani pro praci s mysi.
  */

#pragma once

#include <string>
#include "Vector2.h"

namespace GameFramework
{
    /**
     * Kody tlacitek mysi.
     */
    enum BtnCode
    {
        BC_UNASSIGNED  = 0,
        BC_LEFT        = 1,
        BC_RIGHT       = 2,
        BC_MIDDLE      = 3,
        BC_WHEELUP     = 4,
        BC_WHEELDOWN   = 5,
        BC_X1          = 6,
        BC_X2          = 7,
    };
    
    /**
     * Sprava mysi.
     */
    class Mouse
    {
    public:
        virtual ~Mouse(void) {}
    
        virtual bool IsBtnDown(BtnCode bc) const = 0;
        virtual std::string GetAsString(BtnCode bc) = 0;
        
        virtual void SetVisible(bool visible) = 0;
        virtual bool IsVisible() = 0;    
        virtual void SetPosition(Point2i pos) = 0;
    
        virtual BtnCode BtnDown(int btn) = 0;
        virtual BtnCode BtnUp(int btn) = 0;
    };
}