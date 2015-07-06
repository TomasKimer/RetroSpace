// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   SystemTime.h
  *  @brief  Funkce systemoveho casu.
  */

#include "SDLPrerequisites.h"

namespace GameFramework
{
    /**
     * Prace se systemovym casem.
     */
    class SystemTime
    {
    public:
        static inline unsigned int TickCount() { return SDL_GetTicks(); }
        static void Delay(unsigned int ms) { SDL_Delay(ms); }
    
    private:
        SystemTime() {};  // library class
    };
}