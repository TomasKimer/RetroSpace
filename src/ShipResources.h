// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ShipResources.h
  *  @brief  Sprava obnovitelnych lodnich zdroju.
  */

#pragma once

#include "IUpdatableObject.h"
#include "ShipResource.h"

namespace RetroSpace
{
    /**
     * Vlastnosti lodi - stity a energie.
     */
    class ShipResources : public IUpdatableObject
    {
    public:
        /**
         * Nastaveni vlastnosti.
         */
        struct Attributes
        {
            ShipResource::Attributes energy;
            ShipResource::Attributes shield;
        };

    public:
        ShipResources();
        
        virtual void Update(const GameTime & gameTime);
    
        void Transfer();
    
        void Renew() { m_energy.Renew(); m_shield.Renew(); }
    
        bool ShieldDown(float value) { return m_shield.DownPostCheck(value); }
        bool EnergyDown(float value) { return m_energy.DownPreCheck(value); }
    
        ShipResource & Energy() { return m_energy; }
        ShipResource & Shield() { return m_shield; }

        void SetAttributes(Attributes & attr);
    
    private:
        ShipResource m_energy, m_shield;
    };
}