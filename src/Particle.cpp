// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Particle.cpp
  *  @brief  Reprezentace jedne castice.
  */

#include "Particle.h"

namespace RetroSpace
{

Particle::Particle(const Vector2f & velocity, const Vector2f & position, float rotation, const Matrix & parentMatrix, const TimeSpan & lifetime,
                   const Color & startColor, const Color & endColor, float lineLength, bool shortenLine, float lineWidth):
                     m_alive(true), m_parentMatrix(parentMatrix), m_lifetime(lifetime),
                     m_startColor(startColor), m_endColor(endColor), m_shortenLine(shortenLine), m_lineWidth(lineWidth)
{
    SetVelocity(velocity);
    SetPosition(position);
    SetRotation(rotation);

    m_lenX = m_halfLineLength = lineLength / 2.f;
}

Particle::~Particle(void)
{
}

void Particle::Update(const GameTime & gameTime)
{
    if (m_endTime == TimeSpan::Zero())
        m_endTime = gameTime.Current() + m_lifetime;

    if (gameTime.Current() > m_endTime)
        m_alive = false;

    float percentLife = (float)((m_endTime.ms() - gameTime.Current().ms()) / (float)m_lifetime.ms());
    m_color = Color::Lerp(m_endColor, m_startColor, percentLife);
    if (m_shortenLine)
        m_lenX = m_halfLineLength * percentLife;

    MovableObject::Update(gameTime);
    RotateToVelocity();

    // update matrix
    m_matrix = m_parentMatrix;
    m_matrix.Translate(m_position.x, m_position.y, 0.0f);
    m_matrix.Rotate(m_rotation, 0.0f, 0.0f, 1.0f);
}

void Particle::Draw(Renderer & renderer)
{
    ApplyMatrix(renderer);

    renderer.SetColor(m_color);
    renderer.DrawLine(Vector2f(-m_lenX, 0.f), Vector2f(m_lenX, 0.f), m_lineWidth);
}

}
