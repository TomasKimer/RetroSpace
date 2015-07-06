// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   PowerupSystem.cpp
  *  @brief  Sprava systemu vsech bonusu.
  */

#include "PowerupSystem.h"

namespace RetroSpace
{

PowerupSystem::PowerupSystem(void)
{
}

PowerupSystem::~PowerupSystem(void)
{
}

void PowerupSystem::Update(const GameTime & gameTime)
{
    if (m_lastGenerateInterval == TimeSpan::Zero())
        m_lastGenerateInterval = gameTime.Current();
    
    if (m_activePowerups.size() >= m_attr->maxPowerups)
        m_lastGenerateInterval = gameTime.Current();
    
    // generate new powerup
    if (gameTime.Current() - m_lastGenerateInterval > m_nextGenerateInterval)
    {
        m_lastGenerateInterval = gameTime.Current();
        GenerateNext();

        if (m_screenSize.x > m_notGenerateObj[0]->GetCollideRadius() * 2 + m_attr->notGenerateBorder.x * 2 &&
            m_screenSize.y > m_notGenerateObj[0]->GetCollideRadius() * 2 + m_attr->notGenerateBorder.y * 2)
        {
            Powerup::Type powerupType = static_cast<Powerup::Type>(m_random.Next(Powerup::TYPE_BLANK + 1, Powerup::TYPE_LAST - 1));
       
            Powerup *newPowerup = new Powerup(m_powerupAttr[powerupType], *m_font);
            do {                                                   
                newPowerup->SetPosition(Vector2f(static_cast<float>(m_random.Next(m_attr->notGenerateBorder.x, m_screenSize.x-m_attr->notGenerateBorder.x)),
                                                 static_cast<float>(m_random.Next(m_attr->notGenerateBorder.y, m_screenSize.y-m_attr->notGenerateBorder.y))));
            } while (newPowerup->Collide(*m_notGenerateObj[0]) || newPowerup->Collide(*m_notGenerateObj[1]) || newPowerup->Collide(*m_notGenerateObj[2]));

            m_activePowerups.push_back(newPowerup);
        }
    }

    // update powerups
    std::list<Powerup *>::iterator it = m_activePowerups.begin();            
    while (it != m_activePowerups.end())
    {
        (*it)->Update(gameTime);
        if (!(*it)->IsAlive())
        {
            delete (*it);
            it = m_activePowerups.erase(it);
        }
        else
            it++;
    }    
}

void PowerupSystem::Draw(Renderer & renderer)
{
    for (std::list<Powerup *>::iterator it = m_activePowerups.begin(); it != m_activePowerups.end(); it++)
        (*it)->Draw(renderer);     
}

Powerup::Attributes * PowerupSystem::PowerupCollide(const GameObject & obj)
{
    for (std::list<Powerup *>::iterator it = m_activePowerups.begin(); it != m_activePowerups.end(); it++)
    {
        if (!(*it)->IsAnimating() && (*it)->Collide(obj))
        {
            Powerup::Attributes *ret = &(*it)->GetAttributes();
            (*it)->OnPickUp();
            return ret;
        }
    } 
    return 0;
}

void PowerupSystem::Reset()
{
    for (std::list<Powerup *>::iterator it = m_activePowerups.begin(); it != m_activePowerups.end(); it++)
        delete (*it);        
    
    m_activePowerups.clear();        
    m_lastGenerateInterval = TimeSpan::Zero(); 
    
    GenerateNext();
}

void PowerupSystem::SetOnResize(Size2i screenSize)
{
    m_screenSize = screenSize;
    Reset();
}

void PowerupSystem::GenerateNext()
{
    m_nextGenerateInterval = TimeSpan::FromMs(static_cast<unsigned int>(m_random.Next(m_attr->minInterval.ms(), m_attr->maxInterval.ms())));
}

void PowerupSystem::SetNotGenerateObjects(GameObject & obj1, GameObject & obj2, GameObject & obj3)
{
    m_notGenerateObj[0] = &obj1;
    m_notGenerateObj[1] = &obj2;
    m_notGenerateObj[2] = &obj3;        
}

void PowerupSystem::BuildPowerups()
{
    // energy
    m_powerupAttr[Powerup::TYPE_ENERGY].type = Powerup::TYPE_ENERGY;
    m_powerupAttr[Powerup::TYPE_ENERGY].bonusValue = m_attr->energyBonusValue;
    
    m_powerupAttr[Powerup::TYPE_ENERGY].shape1.SetStyle(Shape::SS_LINE);
    m_powerupAttr[Powerup::TYPE_ENERGY].shape1.AddCube(16.f);
    m_powerupAttr[Powerup::TYPE_ENERGY].shape1.MakeArrays();
    m_powerupAttr[Powerup::TYPE_ENERGY].color = m_colors->color[Powerup::TYPE_ENERGY];
    
    m_powerupAttr[Powerup::TYPE_ENERGY].shape2.SetStyle(Shape::SS_LINE);
    m_powerupAttr[Powerup::TYPE_ENERGY].shape2.AddLetter('E', 8.f, 14.f);
    m_powerupAttr[Powerup::TYPE_ENERGY].shape2.MakeArrays();
    
    m_powerupAttr[Powerup::TYPE_ENERGY].pickupText = "+Energy";

    // shield
    m_powerupAttr[Powerup::TYPE_SHIELD].type = Powerup::TYPE_SHIELD;
    m_powerupAttr[Powerup::TYPE_SHIELD].bonusValue = m_attr->shieldBonusValue;
    
    m_powerupAttr[Powerup::TYPE_SHIELD].shape1.SetStyle(Shape::SS_LINE_LOOP);
    m_powerupAttr[Powerup::TYPE_SHIELD].shape1.AddCircle(10.f);
    m_powerupAttr[Powerup::TYPE_SHIELD].shape1.MakeArrays();
    m_powerupAttr[Powerup::TYPE_SHIELD].color = m_colors->color[Powerup::TYPE_SHIELD];

    m_powerupAttr[Powerup::TYPE_SHIELD].shape2.SetStyle(Shape::SS_LINE);
    m_powerupAttr[Powerup::TYPE_SHIELD].shape2.AddLetter('S', 8.f, 12.f);
    m_powerupAttr[Powerup::TYPE_SHIELD].shape2.MakeArrays();

    m_powerupAttr[Powerup::TYPE_SHIELD].pickupText = "+Shield";

    // rocket
    m_powerupAttr[Powerup::TYPE_WEAPON_ROCKET].type = Powerup::TYPE_WEAPON_ROCKET;
    
    m_powerupAttr[Powerup::TYPE_WEAPON_ROCKET].shape1.SetStyle(Shape::SS_LINE);
    m_powerupAttr[Powerup::TYPE_WEAPON_ROCKET].shape1.AddPyramid(18.f, 20.f, 18.f);
    m_powerupAttr[Powerup::TYPE_WEAPON_ROCKET].shape1.MakeArrays();
    m_powerupAttr[Powerup::TYPE_WEAPON_ROCKET].color = m_colors->color[Powerup::TYPE_WEAPON_ROCKET];

    m_powerupAttr[Powerup::TYPE_WEAPON_ROCKET].shape2.SetStyle(Shape::SS_LINE);
    m_powerupAttr[Powerup::TYPE_WEAPON_ROCKET].shape2.AddLetter('R', 6.f, 10.f);
    m_powerupAttr[Powerup::TYPE_WEAPON_ROCKET].shape2.MakeArrays();

    m_powerupAttr[Powerup::TYPE_WEAPON_ROCKET].pickupText = "Rocket Launcher";

    // laser
    m_powerupAttr[Powerup::TYPE_WEAPON_LASER].type = Powerup::TYPE_WEAPON_LASER;
    
    m_powerupAttr[Powerup::TYPE_WEAPON_LASER].shape1.SetStyle(Shape::SS_LINE);
    m_powerupAttr[Powerup::TYPE_WEAPON_LASER].shape1.AddBlock(10.f, 20.f, 10.f);
    m_powerupAttr[Powerup::TYPE_WEAPON_LASER].shape1.MakeArrays();
    m_powerupAttr[Powerup::TYPE_WEAPON_LASER].color = m_colors->color[Powerup::TYPE_WEAPON_LASER];
    //m_powerupAttr[Powerup::TYPE_WEAPON_LASER].color1 = Color(159u, 132u, 240u, 128u);

    m_powerupAttr[Powerup::TYPE_WEAPON_LASER].shape2.SetStyle(Shape::SS_LINE);
    m_powerupAttr[Powerup::TYPE_WEAPON_LASER].shape2.AddLetter('L', 8.f, 14.f);
    m_powerupAttr[Powerup::TYPE_WEAPON_LASER].shape2.MakeArrays();

    m_powerupAttr[Powerup::TYPE_WEAPON_LASER].pickupText = "Laser";
}

}
