// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Powerup.h
  *  @brief  Sprava jednoho bonusu.
  */

#pragma once

#include "GameObject.h"
#include "TimeSpan.h"
#include "Shape.h"
#include "WeaponTypes.h"
#include "TextObject.h"

namespace RetroSpace
{ 
    /**
     * Reprezentace jednoho bonusu na hraci plose.
     */
    class Powerup : public GameObject
    {
    public:
        /**
         * Typy bonusu.
         */
        enum Type
        {
            TYPE_BLANK = 0,
            TYPE_ENERGY,
            TYPE_SHIELD,
            TYPE_WEAPON_ROCKET,
            TYPE_WEAPON_LASER,

            TYPE_LAST            
        };    
        
        /**
         * Naastaveni bonusu.
         */
        struct Attributes
        {
            Type type;
            float bonusValue;
            std::string pickupText;

            Shape shape1, shape2;
            Color color;
            Vector2f rotation;
    
            Attributes(): type(TYPE_BLANK) {}
        };
    
    public:
        Powerup();
        Powerup(Attributes & attr, SpriteFont & font);        
        virtual ~Powerup();
    
        virtual void Update(const GameTime & gameTime);        
        virtual void Draw(Renderer & renderer);
        virtual void SetPosition(Vector2f position);

        void OnPickUp();
    
        Attributes & GetAttributes() { return *m_attr; }
        void SetAttributes(Attributes & attr) { m_attr = &attr; }
        void SetRotateSpeedDiv(float val) { m_rotSpeedDiv = val; }

        void ForceColor(const Color & color) { m_forceColor = color; };

        bool IsAlive() { return m_alive; }
        bool IsAnimating() { return m_animating; }    
    
    private:
        Color m_forceColor;
        float m_rot, m_sin, m_rotSpeedDiv;         
        Attributes *m_attr; 

        // pickup animation variables
        TimeSpan m_endTime, m_lifeTime;
        bool m_alive, m_animating, m_justPicked, m_levitate;
        Color m_endColor, m_startColor, m_color, m_textColor;
        float m_textYPos, m_scaleVal;
        TextObject m_pickupText;
    };
}
