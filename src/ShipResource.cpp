// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ShipResource.cpp
  *  @brief  Reprezentace jednoho obnovitelneho lodniho zdroje.
  */

#include "ShipResource.h"

namespace RetroSpace
{

ShipResource::ShipResource(): m_currentValue(100.f)
{
}

void ShipResource::Update(const GameTime & gameTime)
{
    if (m_attr->incInterval != TimeSpan::Zero())
    {        
        if (m_lastInc == TimeSpan::Zero())
            m_lastInc = gameTime.Current();

        if (gameTime.Current() - m_lastInc > m_attr->incInterval)
        {
            m_currentValue += m_attr->incValue;
            if (m_currentValue > m_attr->maxValue)
                m_currentValue = m_attr->maxValue;
            m_lastInc = gameTime.Current();
        }    
    }
}

void ShipResource::SetAutoIncrement(float value, TimeSpan interval)
{
    m_attr->incValue = value;
    m_attr->incInterval = interval;
}

bool ShipResource::DownPostCheck(float value) // shield
{
    m_currentValue -= value;
    if (m_currentValue <= 0.0f)
    {
        m_currentValue = 0.0f;
        return true;
    }
    return false;
}

bool ShipResource::DownPreCheck(float value)  // energy
{
    if (m_currentValue < value)
        return false;
    else
        m_currentValue -= value;
    return true;
}

void ShipResource::Up(float value)
{
    m_currentValue += value;
    if (m_currentValue > m_attr->maxValue)
        m_currentValue = m_attr->maxValue;
}

void ShipResource::SetMaxValue(float value, bool fill)
{
    m_attr->maxValue = value;
    if (fill)
        m_currentValue = m_attr->maxValue;
}

void ShipResource::SetAttributes(Attributes & attr)
{
    m_attr = &attr;
    m_currentValue = m_attr->maxValue;
}

}