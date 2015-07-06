// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Player.h
  *  @brief  Reprezentace hrace.
  */

#pragma once

#include "Ship.h"

namespace RetroSpace
{ 
    /**
     * Sprava jednoho hrace.
     */
    class Player
    {
    public:
        Player(void): m_score(0) {}
        ~Player(void) {}
    
        unsigned int GetScore() { return m_score; }
        void IncScore() { m_score++; }
    
        void SetName(const std::string & name) { m_name = name; }
        std::string & GetName() { return m_name; }
    
        Ship & GetShip() { return m_ship; }

        void Reset() { m_score = 0; }
    
    private:
        unsigned int m_score;
        std::string m_name;
    
        // ship
        Ship m_ship;
    };
}
