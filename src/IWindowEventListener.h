// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   IWindowEventListener.h
  *  @brief  Rozhrani pro prijem udalosti okna.
  */

#pragma once

#include "Keyboard.h"
#include "Mouse.h"

namespace GameFramework
{
    /**
     * Rozhrani pro udalosti okna.
     */
    class IWindowEventListener
    {
    public:
        virtual ~IWindowEventListener(void) {}
    
        virtual void Resize(Size2i newSize) = 0;
        
        virtual void KeyDown(KeyCode key) = 0;
        virtual void KeyUp  (KeyCode key) = 0;
    
        virtual void MouseDown(Point2i curPos, BtnCode button) = 0;
        virtual void MouseUp  (Point2i curPos, BtnCode button) = 0;
        virtual void MouseMove(Point2i curPos) = 0;
    };
}