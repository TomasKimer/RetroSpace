// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   PowerupSystem.h
  *  @brief  Sprava systemu vsech bonusu.
  */

#pragma once

#include "GameObject.h"
#include "Powerup.h"
#include "Random.h"
#include <list>
#include "Log.h"

namespace RetroSpace
{ 
    /**
     * Sprava systemu bonusu.
     */
    class PowerupSystem : public IBasicGameObject
    {
    public:
        /**
         * Nastaveni systemu bonusu.
         */
        struct Attributes
        {
            unsigned int maxPowerups;
            TimeSpan minInterval, maxInterval;
            Size2i notGenerateBorder;
            float shieldBonusValue, energyBonusValue;
        };

        /**
         * Nastaveni barev bonusu.
         */
        struct Colors
        {
            Color color[Powerup::TYPE_LAST];
        };
        
        PowerupSystem(void);
        virtual ~PowerupSystem(void);
    
        virtual void Update(const GameTime & gameTime);    
        virtual void Draw(Renderer & renderer);
    
        Powerup::Attributes * PowerupCollide(const GameObject & obj);    
        void Reset();
    
        void SetOnResize(Size2i screenSize);    
        void SetNotGenerateObjects(GameObject & obj1, GameObject & obj2, GameObject & obj3);

        void GenerateNext();
        void BuildPowerups();

        Powerup::Attributes & GetPowerupAttributes(Powerup::Type pt) { return m_powerupAttr[pt]; }
        
        void SetFont(SpriteFont & font) { m_font = &font; }
        void SetAttributes(Attributes & attr) { m_attr = &attr; }
        void SetColors(Colors & colors) { m_colors = &colors; }
    
    private:
        std::list<Powerup *> m_activePowerups;
        Random m_random;
        TimeSpan m_nextGenerateInterval, m_lastGenerateInterval;
        Size2i m_screenSize;
        GameObject *m_notGenerateObj[3];

        Attributes *m_attr; 
        Colors *m_colors;
        Powerup::Attributes m_powerupAttr[Powerup::TYPE_LAST];
        SpriteFont *m_font;
    };
}
