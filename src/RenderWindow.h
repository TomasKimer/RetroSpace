// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   RenderWindow.h
  *  @brief  Zakladni rozhrani pro praci s oknem.
  */

#pragma once

#include <string>
#include "IWindowEventListener.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Vector2.h"

namespace GameFramework
{
    /**
     * Okno pro vykreslovani, se spravou vstupu.
     */
    class RenderWindow
    {
    public:
        RenderWindow(): m_mouse(0), m_keyboard(0), m_eventListener(0), m_fullscreen(false), m_managerName("default") {}
        virtual ~RenderWindow(void) {}
    
        virtual void Create(const std::string & name, Size2i size, bool fullscreen, bool vsync = true) = 0;
        virtual void Resize(Size2i newSize, int fullscreen = -1) = 0;
        virtual void SwapBuffers(bool waitForVSync = false) = 0;
    
        virtual Size2i GetSize() { return m_size; }
        virtual bool IsFullscreen() { return m_fullscreen; }  
    
        // window events - input, resize
        virtual void SetEventCallback(IWindowEventListener *eventListener) { m_eventListener = eventListener; }
        virtual bool ProcessEvent(void) = 0;  
    
        virtual Keyboard * GetKeyboard() { return m_keyboard; }
        virtual Mouse * GetMouse() { return m_mouse; }
        virtual std::string GetManagerName() const { return m_managerName; }
    
    protected:
        Size2i m_size;
        bool m_fullscreen;
        std::string m_managerName;
    
        IWindowEventListener *m_eventListener;    
        Keyboard *m_keyboard;
        Mouse *m_mouse;
    };
}