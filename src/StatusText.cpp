// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   StatusText.cpp
  *  @brief  Zobrazeni stavoveho textu.
  */

#include "StatusText.h"

namespace RetroSpace
{

StatusText::StatusText(void): m_duration(TimeSpan::FromS(2)), m_displaying(false),
                              m_startColor(Color::White()), m_endColor(Color::White(0.0f))
{
}

StatusText::~StatusText(void)
{
}

void StatusText::SetStartColor(Color color)
{
    m_startColor = color;
    color.A(0.0f);
    m_endColor = color;
}

void StatusText::Update(const GameTime & gameTime)
{
    if (m_endTime == TimeSpan::Zero())
        m_endTime = gameTime.Current() + m_duration;

    if (gameTime.Current() > m_endTime)
        m_displaying = false;

    float percentLife = (float)((m_endTime.ms() - gameTime.Current().ms()) / (float)m_duration.ms());
    m_textColor = Color::Lerp(m_endColor, m_startColor, percentLife);
}

void StatusText::Draw(Renderer & renderer)
{
    if (m_displaying)
        TextObject::Draw(renderer);
}

void StatusText::DisplayStatus(const std::string & text)
{
    m_text = text;
    m_displaying = true;
    m_endTime = TimeSpan::Zero();    
}

}
