// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   GameTime.cpp
  *  @brief  Sprava herniho casu.
  */

#include "GameTime.h"
#include "SystemTime.h"

namespace GameFramework
{

GameTime::GameTime(void): m_elapsedBest(999999)
{
}

GameTime::~GameTime(void)
{
}

void GameTime::Init()
{
    m_start = TimeSpan::FromMs(SystemTime::TickCount());
    m_previous = m_start;
}

void GameTime::Update()
{
    m_current = TimeSpan::FromMs(SystemTime::TickCount());
    
    m_elapsed = m_current - m_previous;
    m_total = m_current - m_start;

    if (m_total > TimeSpan::FromMs(1000))  // wait for app start
    {
        if (m_elapsed < m_elapsedBest) m_elapsedBest = m_elapsed;
        if (m_elapsed > m_elapsedWorst) m_elapsedWorst = m_elapsed;
    }

    m_previous = m_current;
}

void GameTime::Reset()
{
    Init();
    m_elapsedBest = TimeSpan::FromMs(999999);
    m_elapsedWorst = TimeSpan::FromMs(0);
}

}
