// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ShipResource.h
  *  @brief  Reprezentace jednoho obnovitelneho lodniho zdroje.
  */

#pragma once

#include "IUpdatableObject.h"

using namespace GameFramework;

namespace RetroSpace
{ 
    /**
     * Jednotliva vlastnost lode.
     */
    class ShipResource : public IUpdatableObject
    {
    public:
        /**
         * Nastaveni vlastnosti.
         */
        struct Attributes
        {
            float maxValue, incValue;
            TimeSpan incInterval;
        };

    public:
        ShipResource();
    
        virtual void Update(const GameTime & gameTime);
    
        void SetAutoIncrement(float value, TimeSpan interval);
    
        bool DownPostCheck(float value); // shield    
        bool DownPreCheck(float value);  // energy

        void Up(float value);
    
        float GetCurrentValue() { return m_currentValue; }
        void SetCurrentValue(float value) { m_currentValue = value; }
        float GetMaxValue() { return m_attr->maxValue; }
        void SetMaxValue(float value, bool fill = false);
        void Renew() { m_currentValue = m_attr->maxValue; }

        void SetAttributes(Attributes & attr);
    
    private:
        float m_currentValue;
        TimeSpan m_lastInc;
        Attributes *m_attr;
    };
}