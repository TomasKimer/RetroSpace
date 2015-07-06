// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ShipResources.cpp
  *  @brief  Sprava obnovitelnych lodnich zdroju.
  */

#include "ShipResources.h"

namespace RetroSpace
{

ShipResources::ShipResources()
{
}

void ShipResources::Update(const GameTime & gameTime)
{
    m_energy.Update(gameTime);
    m_shield.Update(gameTime);
}

void ShipResources::Transfer()
{
    if (m_energy.GetCurrentValue() == 0.f || m_shield.GetCurrentValue() == 0.f)
        return;
    
    float tmp = m_energy.GetCurrentValue();
    m_energy.SetCurrentValue(m_shield.GetCurrentValue());
    m_shield.SetCurrentValue(tmp);    
}

 void ShipResources::SetAttributes(Attributes & attr)
{
    m_energy.SetAttributes(attr.energy);
    m_shield.SetAttributes(attr.shield);
}

}