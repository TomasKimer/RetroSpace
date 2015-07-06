// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   SDLKeyboard.cpp
  *  @brief  Prace s klavesnici pomoci knihovny SDL.
  */

#include "SDLKeyboard.h"

namespace GameFramework
{

SDLKeyboard::SDLKeyboard(void)
{
    KeyboardInit();
}

SDLKeyboard::~SDLKeyboard(void)
{
}

bool SDLKeyboard::IsKeyDown(KeyCode kc) const
{
    return m_keyBuffer[kc];
}

std::string SDLKeyboard::GetAsString(KeyCode kc)
{
    return std::string(SDL_GetKeyName(m_revKeyMap[kc]));
}

KeyCode SDLKeyboard::KeyDown(int key)
{
    KeyCode kc = m_keyMap[(SDLKey)key];
    m_keyBuffer[kc] = true;

    return kc;
}

KeyCode SDLKeyboard::KeyUp(int key)
{
    KeyCode kc = m_keyMap[(SDLKey)key];
    m_keyBuffer[kc] = false;

    return kc;
}

void SDLKeyboard::AssignKey(KeyCode kc, SDLKey sdlk)
{
    m_keyMap.insert(KeyMap::value_type(sdlk, kc));
    m_revKeyMap.insert(RevKeyMap::value_type(kc, sdlk));
}

void SDLKeyboard::KeyboardInit()
{
    memset(&m_keyBuffer, 0, static_cast<size_t>(KC_LAST));

    AssignKey(KC_BACKSPACE   , SDLK_BACKSPACE   );
    AssignKey(KC_TAB         , SDLK_TAB         );
    AssignKey(KC_CLEAR       , SDLK_CLEAR       );
    AssignKey(KC_RETURN      , SDLK_RETURN      );
    AssignKey(KC_PAUSE       , SDLK_PAUSE       );
    AssignKey(KC_ESCAPE      , SDLK_ESCAPE      );
    AssignKey(KC_SPACE       , SDLK_SPACE       );
    AssignKey(KC_EXCLAIM     , SDLK_EXCLAIM     );
    AssignKey(KC_QUOTEDBL    , SDLK_QUOTEDBL    );
    AssignKey(KC_HASH        , SDLK_HASH        );
    AssignKey(KC_DOLLAR      , SDLK_DOLLAR      );
    AssignKey(KC_AMPERSAND   , SDLK_AMPERSAND   );
    AssignKey(KC_QUOTE       , SDLK_QUOTE       );
    AssignKey(KC_LEFTPAREN   , SDLK_LEFTPAREN   );
    AssignKey(KC_RIGHTPAREN  , SDLK_RIGHTPAREN  );
    AssignKey(KC_ASTERISK    , SDLK_ASTERISK    );
    AssignKey(KC_PLUS        , SDLK_PLUS        );
    AssignKey(KC_COMMA       , SDLK_COMMA       );
    AssignKey(KC_MINUS       , SDLK_MINUS       );
    AssignKey(KC_PERIOD      , SDLK_PERIOD      );
    AssignKey(KC_SLASH       , SDLK_SLASH       );
    AssignKey(KC_0           , SDLK_0           );
    AssignKey(KC_1           , SDLK_1           );
    AssignKey(KC_2           , SDLK_2           );
    AssignKey(KC_3           , SDLK_3           );
    AssignKey(KC_4           , SDLK_4           );
    AssignKey(KC_5           , SDLK_5           );
    AssignKey(KC_6           , SDLK_6           );
    AssignKey(KC_7           , SDLK_7           );
    AssignKey(KC_8           , SDLK_8           );
    AssignKey(KC_9           , SDLK_9           );
    AssignKey(KC_COLON       , SDLK_COLON       );
    AssignKey(KC_SEMICOLON   , SDLK_SEMICOLON   );
    AssignKey(KC_LESS        , SDLK_LESS        );
    AssignKey(KC_EQUALS      , SDLK_EQUALS      );
    AssignKey(KC_GREATER     , SDLK_GREATER     );
    AssignKey(KC_QUESTION    , SDLK_QUESTION    );
    AssignKey(KC_AT          , SDLK_AT          );
    AssignKey(KC_LEFTBRACKET , SDLK_LEFTBRACKET );
    AssignKey(KC_BACKSLASH   , SDLK_BACKSLASH   );
    AssignKey(KC_RIGHTBRACKET, SDLK_RIGHTBRACKET);
    AssignKey(KC_CARET       , SDLK_CARET       );
    AssignKey(KC_UNDERSCORE  , SDLK_UNDERSCORE  );
    AssignKey(KC_BACKQUOTE   , SDLK_BACKQUOTE   );
    AssignKey(KC_A           , SDLK_a           );
    AssignKey(KC_B           , SDLK_b           );
    AssignKey(KC_C           , SDLK_c           );
    AssignKey(KC_D           , SDLK_d           );
    AssignKey(KC_E           , SDLK_e           );
    AssignKey(KC_F           , SDLK_f           );
    AssignKey(KC_G           , SDLK_g           );
    AssignKey(KC_H           , SDLK_h           );
    AssignKey(KC_I           , SDLK_i           );
    AssignKey(KC_J           , SDLK_j           );
    AssignKey(KC_K           , SDLK_k           );
    AssignKey(KC_L           , SDLK_l           );
    AssignKey(KC_M           , SDLK_m           );
    AssignKey(KC_N           , SDLK_n           );
    AssignKey(KC_O           , SDLK_o           );
    AssignKey(KC_P           , SDLK_p           );
    AssignKey(KC_Q           , SDLK_q           );
    AssignKey(KC_R           , SDLK_r           );
    AssignKey(KC_S           , SDLK_s           );
    AssignKey(KC_T           , SDLK_t           );
    AssignKey(KC_U           , SDLK_u           );
    AssignKey(KC_V           , SDLK_v           );
    AssignKey(KC_W           , SDLK_w           );
    AssignKey(KC_X           , SDLK_x           );
    AssignKey(KC_Y           , SDLK_y           );
    AssignKey(KC_Z           , SDLK_z           );
    AssignKey(KC_DELETE      , SDLK_DELETE      );
    AssignKey(KC_KP0         , SDLK_KP0         );
    AssignKey(KC_KP1         , SDLK_KP1         );
    AssignKey(KC_KP2         , SDLK_KP2         );
    AssignKey(KC_KP3         , SDLK_KP3         );
    AssignKey(KC_KP4         , SDLK_KP4         );
    AssignKey(KC_KP5         , SDLK_KP5         );
    AssignKey(KC_KP6         , SDLK_KP6         );
    AssignKey(KC_KP7         , SDLK_KP7         );
    AssignKey(KC_KP8         , SDLK_KP8         );
    AssignKey(KC_KP9         , SDLK_KP9         );
    AssignKey(KC_KP_PERIOD   , SDLK_KP_PERIOD   );
    AssignKey(KC_KP_DIVIDE   , SDLK_KP_DIVIDE   );
    AssignKey(KC_KP_MULTIPLY , SDLK_KP_MULTIPLY );
    AssignKey(KC_KP_MINUS    , SDLK_KP_MINUS    );
    AssignKey(KC_KP_PLUS     , SDLK_KP_PLUS     );
    AssignKey(KC_KP_ENTER    , SDLK_KP_ENTER    );
    AssignKey(KC_KP_EQUALS   , SDLK_KP_EQUALS   ); 
    AssignKey(KC_UP          , SDLK_UP          );
    AssignKey(KC_DOWN        , SDLK_DOWN        );
    AssignKey(KC_RIGHT       , SDLK_RIGHT       );
    AssignKey(KC_LEFT        , SDLK_LEFT        );
    AssignKey(KC_INSERT      , SDLK_INSERT      );
    AssignKey(KC_HOME        , SDLK_HOME        );
    AssignKey(KC_END         , SDLK_END         );
    AssignKey(KC_PAGEUP      , SDLK_PAGEUP      );
    AssignKey(KC_PAGEDOWN    , SDLK_PAGEDOWN    );
    AssignKey(KC_F1          , SDLK_F1          );
    AssignKey(KC_F2          , SDLK_F2          );
    AssignKey(KC_F3          , SDLK_F3          );
    AssignKey(KC_F4          , SDLK_F4          );
    AssignKey(KC_F5          , SDLK_F5          );
    AssignKey(KC_F6          , SDLK_F6          );
    AssignKey(KC_F7          , SDLK_F7          );
    AssignKey(KC_F8          , SDLK_F8          );
    AssignKey(KC_F9          , SDLK_F9          );
    AssignKey(KC_F10         , SDLK_F10         );
    AssignKey(KC_F11         , SDLK_F11         );
    AssignKey(KC_F12         , SDLK_F12         );
    AssignKey(KC_F13         , SDLK_F13         );
    AssignKey(KC_F14         , SDLK_F14         );
    AssignKey(KC_F15         , SDLK_F15         );
    AssignKey(KC_NUMLOCK     , SDLK_NUMLOCK     );
    AssignKey(KC_CAPSLOCK    , SDLK_CAPSLOCK    );
    AssignKey(KC_SCROLLOCK   , SDLK_SCROLLOCK   );
    AssignKey(KC_RSHIFT      , SDLK_RSHIFT      );
    AssignKey(KC_LSHIFT      , SDLK_LSHIFT      );
    AssignKey(KC_RCTRL       , SDLK_RCTRL       );
    AssignKey(KC_LCTRL       , SDLK_LCTRL       );
    AssignKey(KC_RALT        , SDLK_RALT        );
    AssignKey(KC_LALT        , SDLK_LALT        );
    AssignKey(KC_RMETA       , SDLK_RMETA       );
    AssignKey(KC_LMETA       , SDLK_LMETA       );
    AssignKey(KC_LSUPER      , SDLK_LSUPER      );
    AssignKey(KC_RSUPER      , SDLK_RSUPER      );
    AssignKey(KC_MODE        , SDLK_MODE        );
    AssignKey(KC_COMPOSE     , SDLK_COMPOSE     );
    AssignKey(KC_HELP        , SDLK_HELP        );
    AssignKey(KC_PRINT       , SDLK_PRINT       );
    AssignKey(KC_SYSREQ      , SDLK_SYSREQ      );
    AssignKey(KC_BREAK       , SDLK_BREAK       );
    AssignKey(KC_MENU        , SDLK_MENU        );
    AssignKey(KC_POWER       , SDLK_POWER       );
    AssignKey(KC_EURO        , SDLK_EURO        );
    AssignKey(KC_UNDO        , SDLK_UNDO        );
}

}