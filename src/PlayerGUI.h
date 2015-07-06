// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   PlayerGUI.h
  *  @brief  Zobrazeni GUI jednoho hrace.
  */

#pragma once

#include "TextObject.h"
#include "ProgressBar.h"
#include "Player.h"
#include "PowerupSystem.h"

namespace RetroSpace
{ 
    /**
     * GUI jednoho hrace.
     */
    class PlayerGUI : public IBasicGameObject
    {
    public:
        /**
         * Barevne nastaveni.
         */
        struct Colors
        {            
            Color score, name;         
            Color energyBar, shieldBar, barsFrame, barsCriticalFrame;
            Color energyLabel, shieldLabel;
        };
    
    public:
        PlayerGUI(): m_powerupActive(false) { m_powerup.SetRotateSpeedDiv(6.f); }
    
        virtual void Update(const GameTime & gameTime);
        virtual void Draw(Renderer & renderer);
    
        void SetValues(Player & player, SpriteFont & font, PowerupSystem & ps);
    
        void SetColors(Colors & colors);
        void SetPositions(const Vector2f & namePos, const Vector2f & scorePos, const Vector2f & scoreCenter,
                          const Vector2f & energyPos, const Vector2f & shieldOffsetPos, bool labelsLeft = true);
    
        ProgressBar & GetEnergyBar() { return m_energyBar; }
        ProgressBar & GetShieldBar() { return m_shieldBar; }
        TextObject & GetScoreText()  { return m_textScore; }
        TextObject & GetPlayerText() { return m_textPlayer; }
    
    private:
        Player *m_refPlayer;
        PowerupSystem *m_refPowerupSystem;
        Powerup m_powerup;
        Colors *m_colors;
        bool m_powerupActive, m_labelsLeft;
        float m_shieldCriticalValue;

        ProgressBar m_energyBar, m_shieldBar;  // bars
        TextObject m_textPlayer, m_textScore;  // texts

        TextObject m_E, m_S;
        TextObject m_powerupText;
    };
}