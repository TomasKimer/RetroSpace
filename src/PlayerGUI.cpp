// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   PlayerGUI.cpp
  *  @brief  Zobrazeni GUI jednoho hrace.
  */

#include "PlayerGUI.h"
#include <sstream>

namespace RetroSpace
{

void PlayerGUI::Update(const GameTime & gameTime)
{
    // score update
    std::stringstream ss;
    ss << m_refPlayer->GetScore();        
    m_textScore.SetText(ss.str()); m_textScore.CenterTextX();

    // progress bars update
    m_energyBar.SetValue(m_refPlayer->GetShip().GetResources().Energy().GetCurrentValue());
        
    m_shieldBar.SetValue(m_refPlayer->GetShip().GetResources().Shield().GetCurrentValue());
    if (m_refPlayer->GetShip().GetResources().Energy().GetCurrentValue() < m_refPlayer->GetShip().GetWeapon().GetType().weap.energyCost)
        m_energyBar.SetFrameColor(m_colors->barsCriticalFrame);
    else
        m_energyBar.SetFrameColor(m_colors->barsFrame);

    if (m_refPlayer->GetShip().GetResources().Shield().GetCurrentValue() < m_shieldCriticalValue)
        m_shieldBar.SetFrameColor(m_colors->barsCriticalFrame);
    else
        m_shieldBar.SetFrameColor(m_colors->barsFrame);

    WeaponTypes::Type type = m_refPlayer->GetShip().GetWeapon().GetType().proj.type;
    if (type != WeaponTypes::WT_CANNON)
    {
        Powerup::Type pType;
        pType = (type == WeaponTypes::WT_ROCKET) ? Powerup::TYPE_WEAPON_ROCKET : Powerup::TYPE_WEAPON_LASER;

        m_powerup.SetAttributes(m_refPowerupSystem->GetPowerupAttributes(pType));
        
        (pType == Powerup::TYPE_WEAPON_ROCKET) ? m_powerupText.SetText("Rocket L.") : m_powerupText.SetText("Laser");
        
        float powerupTextPosX;
        powerupTextPosX = m_labelsLeft ? m_powerup.GetPosition().x + 20.f : m_powerup.GetPosition().x - m_powerupText.GetWidth() - 20.f;
        m_powerupText.SetPosition(Vector2f(powerupTextPosX, m_powerup.GetPosition().y + 4.4f));
     
        m_powerup.Update(gameTime);
    }
}

void PlayerGUI::Draw(Renderer & renderer)
{
    m_textScore.Draw(renderer);
    m_textPlayer.Draw(renderer);

    m_energyBar.Draw(renderer);
    m_shieldBar.Draw(renderer);

    m_S.Draw(renderer);
    m_E.Draw(renderer);

    if (m_refPlayer->GetShip().GetWeapon().GetType().proj.type != WeaponTypes::WT_CANNON)
    {
        m_powerup.Draw(renderer);
        m_powerupText.Draw(renderer);
    }
}

void PlayerGUI::SetValues(Player & player, SpriteFont & font, PowerupSystem & ps)
{
    m_refPlayer = &player;
    m_refPowerupSystem = &ps;
    
    m_textPlayer.SetFont(font);
    m_textPlayer.SetText(player.GetName());
    
    m_textScore.SetFont(font);
    m_textScore.SetText("0");
    m_textScore.SetScale(Vector2f(2.0f, 2.0f));

    m_energyBar.SetMaxValue(m_refPlayer->GetShip().GetResources().Energy().GetMaxValue());
    m_shieldBar.SetMaxValue(m_refPlayer->GetShip().GetResources().Shield().GetMaxValue());

    m_shieldCriticalValue = m_refPlayer->GetShip().GetResources().Shield().GetMaxValue() / 10.f;

    m_S.SetFont(font);
    m_S.SetText("s");
    m_E.SetFont(font);
    m_E.SetText("e");

    m_powerupText.SetFont(font);
    m_powerupText.SetScale(Vector2f(0.7f, 0.7f));
}

void PlayerGUI::SetColors(Colors & colors)
{
    m_textPlayer.SetColor(colors.name);
    m_textScore.SetColor(colors.score);
    
    m_shieldBar.SetInnerColor(colors.shieldBar);
    m_shieldBar.SetFrameColor(colors.barsFrame);

    m_energyBar.SetInnerColor(colors.energyBar);
    m_energyBar.SetFrameColor(colors.barsFrame);

    m_S.SetColor(colors.shieldLabel);
    m_E.SetColor(colors.energyLabel);

    m_powerup.ForceColor(colors.shieldBar);
    m_powerupText.SetColor(colors.shieldBar);

    m_colors = &colors;
}

void PlayerGUI::SetPositions(const Vector2f & namePos, const Vector2f & scorePos, const Vector2f & scoreCenter,
                             const Vector2f & energyPos, const Vector2f & shieldOffsetPos, bool labelsLeft)
{
    m_labelsLeft = labelsLeft;
    
    m_textPlayer.SetPosition(namePos);
    
    m_textScore.SetPosition(scorePos);
    m_textScore.SetCenterPoint(scoreCenter);
    m_textScore.CenterTextX();

    Vector2f shieldPos = energyPos + shieldOffsetPos;
    float xOffset = 3.f, yOffset = -4.f;
   
    float width = m_E.GetWidth();
    float widthS = m_S.GetWidth();

    if (!labelsLeft)
    {
        width *= -1.f;
        widthS *= -1.f;
    }

    float xPos = energyPos.x;
    float xPosS = shieldPos.x;
    
    if (!labelsLeft)
    {
        xPos += m_energyBar.GetSize().x + width + xOffset;
        xPosS += m_shieldBar.GetSize().x + widthS + xOffset;
    }
    else
    {    
        xPos -= xOffset;
        xPosS -= xOffset;
    }
    
    m_E.SetPosition(Vector2f(xPos, energyPos.y + yOffset));
    m_S.SetPosition(Vector2f(xPosS, energyPos.y + shieldOffsetPos.y + yOffset));
    
    m_energyBar.SetPosition(Vector2f(energyPos.x+width, energyPos.y));
    m_shieldBar.SetPosition(Vector2f(energyPos.x + shieldOffsetPos.x + widthS, energyPos.y + shieldOffsetPos.y));
    
    float powerupPosX;
    if (labelsLeft)
        powerupPosX = m_shieldBar.GetPosition().x + 5.f;
    else
        powerupPosX = m_shieldBar.GetPosition().x + m_shieldBar.GetSize().x - 5.f;
    
    m_powerup.SetPosition(Vector2f(powerupPosX, m_shieldBar.GetPosition().y - 23.f));
}

}