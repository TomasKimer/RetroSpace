// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Powerup.cpp
  *  @brief  Sprava jednoho bonusu.
  */

#include "Powerup.h"

namespace RetroSpace
{

Powerup::Powerup(): m_rot(0.f), m_sin(0.f), m_levitate(false), m_attr(0), m_rotSpeedDiv(8.f),
                    m_forceColor(Color::Black()), m_alive(true), m_animating(false)
{
}

Powerup::Powerup(Attributes & attr, SpriteFont & font):
            m_rot(0.f), m_sin(0.f), m_levitate(true), m_attr(&attr), m_rotSpeedDiv(8.f), m_forceColor(Color::Black()),
            m_lifeTime(1000), m_alive(true), m_animating(false), m_textYPos(0.f), m_scaleVal(1.f), m_justPicked(false)
{
    m_collideRadius = 15.0f;
    m_pickupText.SetFont(font);
    m_pickupText.SetText(m_attr->pickupText);
    m_pickupText.SetScale(Vector2f(0.8f, 0.8f));
    m_pickupText.SetColor(m_attr->color);
    
    m_startColor = m_attr->color;
    m_startColor.A(1.f);
    
    m_endColor = m_attr->color;
    m_endColor.A(0.f);
}
        
Powerup::~Powerup()
{
}

void Powerup::Update(const GameTime & gameTime)
{    
    if (m_animating)
    {
        m_justPicked = false;

        if (m_endTime == TimeSpan::Zero())
            m_endTime = gameTime.Current() + m_lifeTime;

        if (gameTime.Current() > m_endTime)
        {            
            m_alive = false;
            return;                
        }

        float percentLife = (float)((m_endTime.ms() - gameTime.Current().ms()) / (float)m_lifeTime.ms());
        m_color = Color::Lerp(m_endColor, m_attr->color, percentLife);
        m_textColor = Color::Lerp(m_endColor, m_startColor, percentLife);                

        m_pickupText.SetColor(m_textColor);
    }
    
    
    UpdateMatrix();
    m_matrix.Rotate(-20.f, 1.f, 0.f, 0.f);
    m_matrix.Rotate(m_rot += gameTime.Elapsed().ms() / m_rotSpeedDiv, 0.f, 1.f, 0.f);
    if (m_levitate)
    {
        m_sin += gameTime.Elapsed().ms();
        m_matrix.Translate(0.f, std::sin(m_sin / 300.f) * 2.f, 0.f);
    }
    if (m_animating)
    {
        m_scaleVal += gameTime.Elapsed().ms() / 300.f;
        m_matrix.Scale(m_scaleVal, m_scaleVal, m_scaleVal);
        m_pickupText.SetPosition(Vector2f(m_pickupText.GetPosition().x, m_textYPos -= gameTime.Elapsed().ms() / m_rotSpeedDiv));

    }
}

void Powerup::Draw(Renderer & renderer)
{
    ApplyMatrix(renderer);

    if (m_forceColor != Color::Black())
        renderer.SetColor(m_forceColor);
    else
    {
        if (m_animating && !m_justPicked)
            renderer.SetColor(m_color);
        else
            renderer.SetColor(m_attr->color);
    }
    
    renderer.DrawShape(m_attr->shape1);
    renderer.DrawShape(m_attr->shape2);            

    if (m_attr->type == TYPE_SHIELD)
    {
        Matrix tmp = m_matrix;

        m_matrix.Rotate(90.f, 0.f, 1.f, 0.f);
        ApplyMatrix(renderer);
        renderer.DrawShape(m_attr->shape1);
        m_matrix = tmp;
    }

    if (m_animating && !m_justPicked)
        m_pickupText.Draw(renderer);
}

void Powerup::SetPosition(Vector2f position)
{
    GameObject::SetPosition(position);
    m_pickupText.SetCenterPoint(Vector2f(m_position.x, m_position.y - 20.f));
    m_pickupText.CenterText();
    m_textYPos = m_pickupText.GetPosition().y;
}

void Powerup::OnPickUp()
{
    m_animating = true;
    m_justPicked = true;
}

}