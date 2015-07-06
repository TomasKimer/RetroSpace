// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Planet.h
  *  @brief  Planeta na hraci plose.
  */

#pragma once

#include "GameObject.h"
#include "Shape.h"

namespace RetroSpace
{ 
    /**
     * Planeta na hraci plose.
     */
    class Planet : public GameObject
    {
    public:
        /**
         * Nastaveni planety.
         */
        struct Attributes
        {
            bool active, hasGravity;
            float gravityStrength;
        };

    public:        
        Planet(void);
        virtual ~Planet(void);
    
        virtual void Draw(Renderer & renderer);
        virtual void Update(const GameTime & gameTime);
    
        void SetActive(bool active) { m_attr->active = active; }
        bool IsActive() { return m_attr->active; }
    
        void SetGravityStrength(float power) { m_attr->gravityStrength = power; }
        float GetGravityStrength() { return m_attr->gravityStrength; }

        void SetHasGravity(bool val) { m_attr->hasGravity = val; }
        bool HasGravity() { return m_attr->hasGravity; }

        void SetAttributes(Attributes & attr) { m_attr = &attr; }
        Attributes & GetAttributes() { return *m_attr; }

        void SetColor(const Color & color) { m_color = color; }
    
    private:
        float m_rot;
        Matrix m2;
        Color m_color;
    
        Shape m_planetBkgnd;
        Attributes *m_attr;
    };
}

