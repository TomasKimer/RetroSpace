// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ParticleEmitter.cpp
  *  @brief  Generator castic.
  */

#include "ParticleEmitter.h"
#include "Log.h"

namespace RetroSpace
{

ParticleEmitter::ParticleEmitter(void): m_active(false), m_cooldownTime(TimeSpan::FromMs(0))
{
}

ParticleEmitter::~ParticleEmitter(void)
{
}

void ParticleEmitter::Emit(ParticleEffect *pe, int count, Matrix & matrix, TimeSpan generateTime)
{
    if (!pe)
        return;
    
    if (generateTime != TimeSpan::Zero() && generateTime - m_lastGenerateTime <= m_cooldownTime)
        return;
    
    for (int i = 1; i <= count; i++)
    {
        pe->SetParticleNumber(i);

        // source particle matrix
        m_matrix = matrix;
        m_matrix.Translate(m_position.x, m_position.y, 0.0f);
        m_matrix.Rotate(m_rotation, 0.0f, 0.0f, 1.0f);

        Vector2f velocity = pe->Velocity();

        Particle *newParticle = new Particle(velocity, pe->Position(), pe->Angle(), m_matrix, pe->LifeTime(),
            pe->StartColor(), pe->EndColor(), pe->LineLength(), pe->ShortenLine(), pe->LineWidth());

        m_particles.push_back(newParticle);       
    }

    m_active = true;
    m_lastGenerateTime = generateTime;
}

void ParticleEmitter::Update(const GameTime & gameTime)
{
    if (!m_active) return;

    std::list<Particle *>::iterator it = m_particles.begin();

    if (it == m_particles.end())
    {
        m_active = false;
        return;
    }
    
    while (it != m_particles.end())
    {
        (*it)->Update(gameTime);
        if (!(*it)->IsAlive())
        {
            delete (*it);
            it = m_particles.erase(it);
        }
        else
            it++;
    }
}

 void ParticleEmitter::Draw(Renderer & renderer)
{
    if (!m_active) return;
    
    std::list<Particle *>::iterator it;
    for (it = m_particles.begin(); it != m_particles.end(); it++)
    {
        (*it)->Draw(renderer);        
    }
}

}
