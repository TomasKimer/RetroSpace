// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ColorSettings.cpp
  *  @brief  Nacitani a ukladani barevnych hodnot objektu.
  */

#include "ColorSettings.h"

namespace RetroSpace
{

ColorSettings::ColorSettings(void)
{
    m_settingsName = "Color";
    
    // ship 1
    m_defaultValues.shipColors[0].frame          = Color(0.5f, 0.9f, 1.0f, 0.75f );
    m_defaultValues.shipColors[0].inner          = Color(0.5f, 0.9f, 1.0f, 0.125f);
    m_defaultValues.shipColors[0].trailStart     = Color(0.7f, 0.9f, 1.0f);        
    m_defaultValues.shipColors[0].trailEnd       = Color::Gray(0.f);
    m_defaultValues.shipColors[0].explodeStart   = Color::Gray();
    m_defaultValues.shipColors[0].explodeEnd     = Color(0.5f, 4.0f, 5.0f, 1.0f);  
    // ship 2
    m_defaultValues.shipColors[1].frame          = Color(0.7f, 0.4f, 0.9f, 0.75f );
    m_defaultValues.shipColors[1].inner          = Color(0.7f, 0.4f, 0.9f, 0.125f);
    m_defaultValues.shipColors[1].trailStart     = Color(0.8f, 0.6f, 0.9f);        
    m_defaultValues.shipColors[1].trailEnd       = Color::Gray(0.f);
    m_defaultValues.shipColors[1].explodeStart   = Color::Gray();
    m_defaultValues.shipColors[1].explodeEnd     = Color(3.0f, 0.5f, 5.0f, 1.0f);  
    
    // player 1 gui
    m_defaultValues.playerGuiColors[0].name        = Color(0.5f, 0.9f, 1.0f, 0.65f);
    m_defaultValues.playerGuiColors[0].score       = Color(0.5f, 0.9f, 1.0f, 1.0f); 
    m_defaultValues.playerGuiColors[0].barsFrame   = Color::Gray();
    m_defaultValues.playerGuiColors[0].barsCriticalFrame = Color(1.0f, 0.0f, 0.0f, 1.f);
    m_defaultValues.playerGuiColors[0].shieldBar   = Color(0.5f, 0.9f, 1.0f, 0.8f); 
    m_defaultValues.playerGuiColors[0].shieldLabel = Color(0.5f, 0.9f, 1.0f, 0.8f);
    m_defaultValues.playerGuiColors[0].energyBar   = Color(0.5f, 0.9f, 1.0f, 0.45f);
    m_defaultValues.playerGuiColors[0].energyLabel = Color(0.5f, 0.9f, 1.0f, 0.8f);
    // player 2 gui
    m_defaultValues.playerGuiColors[1].name        = Color(0.7f, 0.4f, 0.9f, 0.65f);
    m_defaultValues.playerGuiColors[1].score       = Color(0.7f, 0.4f, 0.9f, 1.0f); 
    m_defaultValues.playerGuiColors[1].barsFrame   = Color::Gray();
    m_defaultValues.playerGuiColors[1].barsCriticalFrame = Color(1.0f, 0.0f, 0.0f, 1.f);
    m_defaultValues.playerGuiColors[1].shieldBar   = Color(0.7f, 0.4f, 0.9f, 0.8f); 
    m_defaultValues.playerGuiColors[1].shieldLabel = Color(0.7f, 0.4f, 0.9f, 0.8f);
    m_defaultValues.playerGuiColors[1].energyBar   = Color(0.7f, 0.4f, 0.9f, 0.45f);
    m_defaultValues.playerGuiColors[1].energyLabel = Color(0.7f, 0.4f, 0.9f, 0.8f);
    
    // player status
    m_defaultValues.playerStatusColor[0]         = Color(0.5f, 0.9f, 1.0f, 1.0f);        
    m_defaultValues.playerStatusColor[1]         = Color(0.7f, 0.4f, 0.9f, 1.0f);
    
    // general status
    m_defaultValues.statusColor                  = Color::White(0.9f);

    // powerups
    m_defaultValues.powerupColors.color[Powerup::TYPE_ENERGY]        = Color(255u, 0u, 128u, 153u);
    m_defaultValues.powerupColors.color[Powerup::TYPE_SHIELD]        = Color(231u, 221u, 48u, 153u);
    m_defaultValues.powerupColors.color[Powerup::TYPE_WEAPON_ROCKET] = Color(255u, 128u, 0u, 153u);
    m_defaultValues.powerupColors.color[Powerup::TYPE_WEAPON_LASER]  = Color(32u, 64u, 255u, 153u);

    // planet
    m_defaultValues.planetColor = Color(0.5f, 0.5f, 1.0f, 0.35f);

    // background
    m_defaultValues.backgndColors.lines     = Color(0.5f, 0.5f, 1.f, 0.05f);
    m_defaultValues.backgndColors.mainLines = Color(0.5f, 0.5f, 1.f, 0.1f);
    m_defaultValues.backgndColors.stars     = Color::Gray(0.6f);

    // weapons
    m_defaultValues.weaponColors.col[WeaponTypes::WT_CANNON].color        = Color(200u, 200u, 255u, 255u);
    m_defaultValues.weaponColors.col[WeaponTypes::WT_CANNON].explodeStart = Color::Gray();
    m_defaultValues.weaponColors.col[WeaponTypes::WT_CANNON].explodeEnd   = Color::White();
    
    m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].color        = Color(0u, 64u, 128u, 255u);
    m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].explodeStart = Color(1.0f, 1.0f, 0.75f, 1.0f);
    m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].explodeEnd   = Color(1.0f, 0.5f, 0.5f, 1.0f);
    m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].trailStart   = Color(1.0f, 0.8f, 0.8f, 1.0f);
    m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].trailEnd     = Color(238u, 194u, 45u, 0u);

    m_defaultValues.weaponColors.col[WeaponTypes::WT_LASER].trailStart    = Color(32u, 64u, 255u, 204u);
    m_defaultValues.weaponColors.col[WeaponTypes::WT_LASER].trailEnd      = Color(32u, 64u, 255u, 0u);
}

ColorSettings::~ColorSettings(void)
{
}

void ColorSettings::LoadDefaultValues()
{
    m_values = m_defaultValues;
}

void ColorSettings::LoadValues(const KeyValueDeserializer & kvd)
{
    LoadShipColors(0, kvd);
    LoadShipColors(1, kvd);
    
    LoadPlayerGuiColors(0, kvd);
    LoadPlayerGuiColors(1, kvd);

    kvd.Load("Player1Status", m_values.playerStatusColor[0], m_defaultValues.playerStatusColor[0]);
    kvd.Load("Player2Status", m_values.playerStatusColor[1], m_defaultValues.playerStatusColor[1]);

    kvd.Load("Status", m_values.statusColor, m_defaultValues.statusColor);

    kvd.Load("PowerupShield", m_values.powerupColors.color[Powerup::TYPE_SHIELD]       , m_defaultValues.powerupColors.color[Powerup::TYPE_SHIELD]       );
    kvd.Load("PowerupEnergy", m_values.powerupColors.color[Powerup::TYPE_ENERGY]       , m_defaultValues.powerupColors.color[Powerup::TYPE_ENERGY]       );
    kvd.Load("PowerupRocket", m_values.powerupColors.color[Powerup::TYPE_WEAPON_ROCKET], m_defaultValues.powerupColors.color[Powerup::TYPE_WEAPON_ROCKET]);
    kvd.Load("PowerupLaser" , m_values.powerupColors.color[Powerup::TYPE_WEAPON_LASER] , m_defaultValues.powerupColors.color[Powerup::TYPE_WEAPON_LASER] );

    kvd.Load("Planet", m_values.planetColor, m_defaultValues.planetColor);

    kvd.Load("BackgroundLines"    , m_values.backgndColors.lines    , m_defaultValues.backgndColors.lines    );
    kvd.Load("BackgroundMainLines", m_values.backgndColors.mainLines, m_defaultValues.backgndColors.mainLines);
    kvd.Load("BackgroundStars"    , m_values.backgndColors.stars    , m_defaultValues.backgndColors.stars    );

    // weapons
    kvd.Load("WeaponCannonColor"       , m_values.weaponColors.col[WeaponTypes::WT_CANNON].color       , m_defaultValues.weaponColors.col[WeaponTypes::WT_CANNON].color       ); 
    kvd.Load("WeaponCannonExplodeStart", m_values.weaponColors.col[WeaponTypes::WT_CANNON].explodeStart, m_defaultValues.weaponColors.col[WeaponTypes::WT_CANNON].explodeStart);
    kvd.Load("WeaponCannonExplodeEnd"  , m_values.weaponColors.col[WeaponTypes::WT_CANNON].explodeEnd  , m_defaultValues.weaponColors.col[WeaponTypes::WT_CANNON].explodeEnd  );

    kvd.Load("WeaponRocketColor"       , m_values.weaponColors.col[WeaponTypes::WT_ROCKET].color       , m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].color       );
    kvd.Load("WeaponRocketExplodeStart", m_values.weaponColors.col[WeaponTypes::WT_ROCKET].explodeStart, m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].explodeStart);
    kvd.Load("WeaponRocketExplodeEnd"  , m_values.weaponColors.col[WeaponTypes::WT_ROCKET].explodeEnd  , m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].explodeEnd  );
    kvd.Load("WeaponRocketTrailStart"  , m_values.weaponColors.col[WeaponTypes::WT_ROCKET].trailStart  , m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].trailStart  );
    kvd.Load("WeaponRocketTrailEnd"    , m_values.weaponColors.col[WeaponTypes::WT_ROCKET].trailEnd    , m_defaultValues.weaponColors.col[WeaponTypes::WT_ROCKET].trailEnd    );

    kvd.Load("WeaponLaserTrailStart"   , m_values.weaponColors.col[WeaponTypes::WT_LASER].trailStart   , m_defaultValues.weaponColors.col[WeaponTypes::WT_LASER].trailStart   );
    kvd.Load("WeaponLaserTrailEnd"     , m_values.weaponColors.col[WeaponTypes::WT_LASER].trailEnd     , m_defaultValues.weaponColors.col[WeaponTypes::WT_LASER].trailEnd     );
}

void ColorSettings::SaveValues(KeyValueSerializer & kvs)
{
    SaveShipColors(0, kvs);

    kvs.SaveBlankLine();

    SaveShipColors(1, kvs);

    kvs.SaveBlankLine();

    SavePlayerGuiColors(0, kvs);

    kvs.SaveBlankLine();

    SavePlayerGuiColors(1, kvs);

    kvs.SaveBlankLine();
    
    kvs.Save("Player1Status", m_values.playerStatusColor[0]);
    kvs.Save("Player2Status", m_values.playerStatusColor[1]);
    
    kvs.SaveBlankLine();
    
    kvs.Save("Status", m_values.statusColor);

    kvs.SaveBlankLine();

    kvs.Save("PowerupShield", m_values.powerupColors.color[Powerup::TYPE_SHIELD]       );
    kvs.Save("PowerupEnergy", m_values.powerupColors.color[Powerup::TYPE_ENERGY]       );
    kvs.Save("PowerupRocket", m_values.powerupColors.color[Powerup::TYPE_WEAPON_ROCKET]);
    kvs.Save("PowerupLaser" , m_values.powerupColors.color[Powerup::TYPE_WEAPON_LASER] );

    kvs.SaveBlankLine();

    kvs.Save("Planet", m_values.planetColor);

    kvs.SaveBlankLine();

    kvs.Save("BackgroundLines"    , m_values.backgndColors.lines    );
    kvs.Save("BackgroundMainLines", m_values.backgndColors.mainLines);
    kvs.Save("BackgroundStars"    , m_values.backgndColors.stars    );

    kvs.SaveBlankLine();
    kvs.SaveBlankLine();
    
    // weapons
    kvs.Save("WeaponCannonColor"       , m_values.weaponColors.col[WeaponTypes::WT_CANNON].color       ); 
    kvs.Save("WeaponCannonExplodeStart", m_values.weaponColors.col[WeaponTypes::WT_CANNON].explodeStart);
    kvs.Save("WeaponCannonExplodeEnd"  , m_values.weaponColors.col[WeaponTypes::WT_CANNON].explodeEnd  );

    kvs.SaveBlankLine();

    kvs.Save("WeaponRocketColor"       , m_values.weaponColors.col[WeaponTypes::WT_ROCKET].color       );
    kvs.Save("WeaponRocketExplodeStart", m_values.weaponColors.col[WeaponTypes::WT_ROCKET].explodeStart);
    kvs.Save("WeaponRocketExplodeEnd"  , m_values.weaponColors.col[WeaponTypes::WT_ROCKET].explodeEnd  );
    kvs.Save("WeaponRocketTrailStart"  , m_values.weaponColors.col[WeaponTypes::WT_ROCKET].trailStart  );
    kvs.Save("WeaponRocketTrailEnd"    , m_values.weaponColors.col[WeaponTypes::WT_ROCKET].trailEnd    );

    kvs.SaveBlankLine();

    kvs.Save("WeaponLaserTrailStart"   , m_values.weaponColors.col[WeaponTypes::WT_LASER].trailStart   );
    kvs.Save("WeaponLaserTrailEnd"     , m_values.weaponColors.col[WeaponTypes::WT_LASER].trailEnd     );
}

void ColorSettings::LoadShipColors(int num, const KeyValueDeserializer & kvd)
{
    std::stringstream ss;
    ss << num + 1;
    
    kvd.Load("Ship" + ss.str() + "Frame"       , m_values.shipColors[num].frame       , m_defaultValues.shipColors[num].frame       );
    kvd.Load("Ship" + ss.str() + "Inner"       , m_values.shipColors[num].inner       , m_defaultValues.shipColors[num].inner       );
    kvd.Load("Ship" + ss.str() + "TrailStart"  , m_values.shipColors[num].trailStart  , m_defaultValues.shipColors[num].trailStart  );
    kvd.Load("Ship" + ss.str() + "TrailEnd"    , m_values.shipColors[num].trailEnd    , m_defaultValues.shipColors[num].trailEnd    );
    kvd.Load("Ship" + ss.str() + "ExplodeStart", m_values.shipColors[num].explodeStart, m_defaultValues.shipColors[num].explodeStart);
    kvd.Load("Ship" + ss.str() + "ExplodeEnd"  , m_values.shipColors[num].explodeEnd  , m_defaultValues.shipColors[num].explodeEnd  );
}

void ColorSettings::LoadPlayerGuiColors(int num, const KeyValueDeserializer & kvd)
{
    std::stringstream ss;
    ss << num + 1;

    kvd.Load("Player" + ss.str() + "GuiName"       , m_values.playerGuiColors[num].name       , m_defaultValues.playerGuiColors[num].name       );
    kvd.Load("Player" + ss.str() + "GuiScore"      , m_values.playerGuiColors[num].score      , m_defaultValues.playerGuiColors[num].score      );
    kvd.Load("Player" + ss.str() + "GuiBarsFrame"  , m_values.playerGuiColors[num].barsFrame  , m_defaultValues.playerGuiColors[num].barsFrame  );
    kvd.Load("Player" + ss.str() + "GuiBarsCriticalFrame", m_values.playerGuiColors[num].barsCriticalFrame, m_defaultValues.playerGuiColors[num].barsCriticalFrame);
    kvd.Load("Player" + ss.str() + "GuiShieldBar"  , m_values.playerGuiColors[num].shieldBar  , m_defaultValues.playerGuiColors[num].shieldBar  );
    kvd.Load("Player" + ss.str() + "GuiShieldLabel", m_values.playerGuiColors[num].shieldLabel, m_defaultValues.playerGuiColors[num].shieldLabel);    
    kvd.Load("Player" + ss.str() + "GuiEnergyBar"  , m_values.playerGuiColors[num].energyBar  , m_defaultValues.playerGuiColors[num].energyBar  );
    kvd.Load("Player" + ss.str() + "GuiEnergyLabel", m_values.playerGuiColors[num].energyLabel, m_defaultValues.playerGuiColors[num].energyLabel);
}

void ColorSettings::SaveShipColors(int num, KeyValueSerializer & kvs)
{
    std::stringstream ss;
    ss << num + 1;

    kvs.Save("Ship" + ss.str() + "Frame"       , m_values.shipColors[num].frame       );
    kvs.Save("Ship" + ss.str() + "Inner"       , m_values.shipColors[num].inner       );
    kvs.Save("Ship" + ss.str() + "TrailStart"  , m_values.shipColors[num].trailStart  );
    kvs.Save("Ship" + ss.str() + "TrailEnd"    , m_values.shipColors[num].trailEnd    );
    kvs.Save("Ship" + ss.str() + "ExplodeStart", m_values.shipColors[num].explodeStart);
    kvs.Save("Ship" + ss.str() + "ExplodeEnd"  , m_values.shipColors[num].explodeEnd  );
}

void ColorSettings::SavePlayerGuiColors(int num, KeyValueSerializer & kvs)
{
    std::stringstream ss;
    ss << num + 1;

    kvs.Save("Player" + ss.str() + "GuiName"       , m_values.playerGuiColors[num].name       );
    kvs.Save("Player" + ss.str() + "GuiScore"      , m_values.playerGuiColors[num].score      );
    kvs.Save("Player" + ss.str() + "GuiBarsFrame"  , m_values.playerGuiColors[num].barsFrame  );
    kvs.Save("Player" + ss.str() + "GuiBarsCriticalFrame", m_values.playerGuiColors[num].barsCriticalFrame);
    kvs.Save("Player" + ss.str() + "GuiShieldBar"  , m_values.playerGuiColors[num].shieldBar  );
    kvs.Save("Player" + ss.str() + "GuiShieldLabel", m_values.playerGuiColors[num].shieldLabel);    
    kvs.Save("Player" + ss.str() + "GuiEnergyBar"  , m_values.playerGuiColors[num].energyBar  );
    kvs.Save("Player" + ss.str() + "GuiEnergyLabel", m_values.playerGuiColors[num].energyLabel);
}

}