// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Keyboard.h
  *  @brief  Rozhrani pro praci s klavesnici.
  */

#pragma once

#include <string>

namespace GameFramework
{
    /**
     * Kody klaves na klavesnici.
     * Nazvy prevzaty z knihovny SDL (SDL_keysym.h).
     */
    enum KeyCode
    {
        KC_UNKNOWN      = 0x0,
        KC_BACKSPACE    = 0x1,
        KC_TAB          = 0x2,
        KC_CLEAR        = 0x3,
        KC_RETURN       = 0x4,
        KC_PAUSE        = 0x5,
        KC_ESCAPE       = 0x6,
        KC_SPACE        = 0x7,
        KC_EXCLAIM      = 0x8,
        KC_QUOTEDBL     = 0x9,
        KC_HASH         = 0xa,
        KC_DOLLAR       = 0xb,
        KC_AMPERSAND    = 0xc,
        KC_QUOTE        = 0xd,
        KC_LEFTPAREN    = 0xe,
        KC_RIGHTPAREN   = 0xf,
        KC_ASTERISK     = 0x10,
        KC_PLUS         = 0x11,
        KC_COMMA        = 0x12,
        KC_MINUS        = 0x13,
        KC_PERIOD       = 0x14,
        KC_SLASH        = 0x15,
        KC_0            = 0x16,
        KC_1            = 0x17,
        KC_2            = 0x18,
        KC_3            = 0x19,
        KC_4            = 0x1a,
        KC_5            = 0x1b,
        KC_6            = 0x1c,
        KC_7            = 0x1d,
        KC_8            = 0x1e,
        KC_9            = 0x1f,
        KC_COLON        = 0x20,
        KC_SEMICOLON    = 0x21,
        KC_LESS         = 0x22,
        KC_EQUALS       = 0x23,
        KC_GREATER      = 0x24,
        KC_QUESTION     = 0x25,
        KC_AT           = 0x26,
        KC_LEFTBRACKET  = 0x27,
        KC_BACKSLASH    = 0x28,
        KC_RIGHTBRACKET = 0x29,
        KC_CARET        = 0x2a,
        KC_UNDERSCORE   = 0x2b,
        KC_BACKQUOTE    = 0x2c,
        KC_A            = 0x2d,
        KC_B            = 0x2e,
        KC_C            = 0x2f,
        KC_D            = 0x30,
        KC_E            = 0x31,
        KC_F            = 0x32,
        KC_G            = 0x33,
        KC_H            = 0x34,
        KC_I            = 0x35,
        KC_J            = 0x36,
        KC_K            = 0x37,
        KC_L            = 0x38,
        KC_M            = 0x39,
        KC_N            = 0x3a,
        KC_O            = 0x3b,
        KC_P            = 0x3c,
        KC_Q            = 0x3d,
        KC_R            = 0x3e,
        KC_S            = 0x3f,
        KC_T            = 0x40,
        KC_U            = 0x41,
        KC_V            = 0x42,
        KC_W            = 0x43,
        KC_X            = 0x44,
        KC_Y            = 0x45,
        KC_Z            = 0x46,
        KC_DELETE       = 0x47,
        KC_KP0          = 0x48,
        KC_KP1          = 0x49,
        KC_KP2          = 0x4a,
        KC_KP3          = 0x4b,
        KC_KP4          = 0x4c,
        KC_KP5          = 0x4d,
        KC_KP6          = 0x4e,
        KC_KP7          = 0x4f,
        KC_KP8          = 0x50,
        KC_KP9          = 0x51,
        KC_KP_PERIOD    = 0x52,
        KC_KP_DIVIDE    = 0x53,
        KC_KP_MULTIPLY  = 0x54,
        KC_KP_MINUS     = 0x55,
        KC_KP_PLUS      = 0x56,
        KC_KP_ENTER     = 0x57,
        KC_KP_EQUALS    = 0x58,
        KC_UP           = 0x59,
        KC_DOWN         = 0x5a,
        KC_RIGHT        = 0x5b,
        KC_LEFT         = 0x5c,
        KC_INSERT       = 0x5d,
        KC_HOME         = 0x5e,
        KC_END          = 0x5f,
        KC_PAGEUP       = 0x60,
        KC_PAGEDOWN     = 0x61,
        KC_F1           = 0x62,
        KC_F2           = 0x63,
        KC_F3           = 0x64,
        KC_F4           = 0x65,
        KC_F5           = 0x66,
        KC_F6           = 0x67,
        KC_F7           = 0x68,
        KC_F8           = 0x69,
        KC_F9           = 0x6a,
        KC_F10          = 0x6b,
        KC_F11          = 0x6c,
        KC_F12          = 0x6d,
        KC_F13          = 0x6e,
        KC_F14          = 0x6f,
        KC_F15          = 0x70,
        KC_NUMLOCK      = 0x71,
        KC_CAPSLOCK     = 0x72,
        KC_SCROLLOCK    = 0x73,
        KC_RSHIFT       = 0x74,
        KC_LSHIFT       = 0x75,
        KC_RCTRL        = 0x76,
        KC_LCTRL        = 0x77,
        KC_RALT         = 0x78,
        KC_LALT         = 0x79,
        KC_RMETA        = 0x7a,
        KC_LMETA        = 0x7b,
        KC_LSUPER       = 0x7c,     
        KC_RSUPER       = 0x7d,     
        KC_MODE         = 0x7e,       
        KC_COMPOSE      = 0x7f,    
        KC_HELP         = 0x80,
        KC_PRINT        = 0x81,
        KC_SYSREQ       = 0x82,
        KC_BREAK        = 0x83,
        KC_MENU         = 0x84,
        KC_POWER        = 0x85,      
        KC_EURO         = 0x86,       
        KC_UNDO         = 0x87, 

        KC_LAST
    };

    /**
     * Sprava klavesnice.
     */
    class Keyboard
    {
    public:
        virtual ~Keyboard(void) {}

        virtual bool IsKeyDown(KeyCode kc) const = 0;
        virtual std::string GetAsString(KeyCode kc) = 0;

        virtual KeyCode KeyDown(int key) = 0;
        virtual KeyCode KeyUp(int key) = 0;
    }; 
}                         