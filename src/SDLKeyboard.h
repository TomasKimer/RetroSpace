// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   SDLKeyboard.h
  *  @brief  Prace s klavesnici pomoci knihovny SDL.
  */

#pragma once

#include "SDLPrerequisites.h"
#include <map>
#include "Keyboard.h"

namespace GameFramework
{
    /**
     * Implementace spravy klavesnice pomoci knihovny SDL.
     */
    class SDLKeyboard : public Keyboard
    {
    public:
        SDLKeyboard(void);
        virtual ~SDLKeyboard(void);
    
        virtual bool IsKeyDown(KeyCode kc) const;
        virtual std::string GetAsString(KeyCode kc);
    
    private:
        void KeyboardInit();
        
        virtual KeyCode KeyDown(int key);
        virtual KeyCode KeyUp(int key);
        
        typedef std::map<SDLKey, KeyCode> KeyMap;
        typedef std::map<KeyCode, SDLKey> RevKeyMap;
    
        KeyMap m_keyMap;
        RevKeyMap m_revKeyMap;
    
        void AssignKey(KeyCode kc, SDLKey sdlk);
    
        bool m_keyBuffer[KC_LAST];
    };
}