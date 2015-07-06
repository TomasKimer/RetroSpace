// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   GameSettings.cpp
  *  @brief  Nacitani a ukladani herni konfigurace.
  */

#include "GameSettings.h"

namespace RetroSpace
{

GameSettings::GameSettings(void)
{
    m_settingsName = "Game"; 

    // ship
    m_defaultValues.ship.maxSpeed = 0.5f;
    m_defaultValues.ship.slowdownSpeed = 0.00025f;
    m_defaultValues.ship.accelerateSpeed = 0.2f;
    m_defaultValues.ship.turnSpeed = 0.3f;
    
    // ship Resources
    m_defaultValues.ship.resources.shield.maxValue = 100.f;
    m_defaultValues.ship.resources.energy.maxValue = 100.f;
    m_defaultValues.ship.resources.shield.incInterval = TimeSpan::FromMs(500);
    m_defaultValues.ship.resources.shield.incValue = 1.f;
    m_defaultValues.ship.resources.energy.incInterval = TimeSpan::FromS(2);
    m_defaultValues.ship.resources.energy.incValue = 5.f;

    // planet
    m_defaultValues.planet.active = true;
    m_defaultValues.planet.hasGravity = true;
    m_defaultValues.planet.gravityStrength = 1.f;

    // powerup system
    m_defaultValues.powerupSys.maxPowerups = 5u;
    m_defaultValues.powerupSys.minInterval = TimeSpan::FromS(2);
    m_defaultValues.powerupSys.maxInterval = TimeSpan::FromS(6);
    m_defaultValues.powerupSys.notGenerateBorder = Size2i(25, 50);
    m_defaultValues.powerupSys.shieldBonusValue = 35.f;
    m_defaultValues.powerupSys.energyBonusValue = 40.f;

    // weapons
    m_defaultValues.weapon.sett[WeaponTypes::WT_CANNON].cooldown   = TimeSpan::FromMs(100);
    m_defaultValues.weapon.sett[WeaponTypes::WT_CANNON].energyCost = 2.5f;
    m_defaultValues.weapon.sett[WeaponTypes::WT_CANNON].lifetime   = TimeSpan::FromMs(650);
    m_defaultValues.weapon.sett[WeaponTypes::WT_CANNON].damage     = 5.f;
    m_defaultValues.weapon.sett[WeaponTypes::WT_CANNON].velocity   = 0.75;
    m_defaultValues.weapon.sett[WeaponTypes::WT_CANNON].gravityMultiplier = 20.f;

    m_defaultValues.weapon.sett[WeaponTypes::WT_ROCKET].cooldown   = TimeSpan::FromMs(800);
    m_defaultValues.weapon.sett[WeaponTypes::WT_ROCKET].energyCost = 20.f;
    m_defaultValues.weapon.sett[WeaponTypes::WT_ROCKET].lifetime   = TimeSpan::FromMs(1250);
    m_defaultValues.weapon.sett[WeaponTypes::WT_ROCKET].damage     = 30.f;
    m_defaultValues.weapon.sett[WeaponTypes::WT_ROCKET].velocity   = 0.75f;
    m_defaultValues.weapon.sett[WeaponTypes::WT_ROCKET].gravityMultiplier = 20.f;

    m_defaultValues.weapon.sett[WeaponTypes::WT_LASER].cooldown   = TimeSpan::FromMs(1000);
    m_defaultValues.weapon.sett[WeaponTypes::WT_LASER].energyCost = 50.f;
    m_defaultValues.weapon.sett[WeaponTypes::WT_LASER].lifetime   = TimeSpan::FromMs(50);
    m_defaultValues.weapon.sett[WeaponTypes::WT_LASER].damage     = 90.f;
    m_defaultValues.weapon.sett[WeaponTypes::WT_LASER].velocity   = 0.001f;
    m_defaultValues.weapon.sett[WeaponTypes::WT_LASER].gravityMultiplier = 0.f;

    // fps    
    m_defaultValues.showFps = true;
}

GameSettings::~GameSettings(void)
{

}

void GameSettings::LoadDefaultValues()
{
    m_values = m_defaultValues;
}

void GameSettings::LoadValues(const KeyValueDeserializer & kvd)
{
    // ship
    kvd.Load("ShipMaxSpeed"       , m_values.ship.maxSpeed       , m_defaultValues.ship.maxSpeed       );
    kvd.Load("ShipFrictionMult"   , m_values.ship.slowdownSpeed  , m_defaultValues.ship.slowdownSpeed  );
    kvd.Load("ShipAccelerateSpeed", m_values.ship.accelerateSpeed, m_defaultValues.ship.accelerateSpeed);
    kvd.Load("ShipTurnSpeed"      , m_values.ship.turnSpeed      , m_defaultValues.ship.turnSpeed      );
    
    // ship Resources
    kvd.Load("ShipMaxShield"            , m_values.ship.resources.shield.maxValue   , m_defaultValues.ship.resources.shield.maxValue   );
    kvd.Load("ShipMaxEnergy"            , m_values.ship.resources.energy.maxValue   , m_defaultValues.ship.resources.energy.maxValue   );
    kvd.Load("ShipShieldRegenIntervalMs", m_values.ship.resources.shield.incInterval, m_defaultValues.ship.resources.shield.incInterval);
    kvd.Load("ShipShieldRegenValue"     , m_values.ship.resources.shield.incValue   , m_defaultValues.ship.resources.shield.incValue   );
    kvd.Load("ShipEnergyRegenIntervalMs", m_values.ship.resources.energy.incInterval, m_defaultValues.ship.resources.energy.incInterval);
    kvd.Load("ShipEnergyRegenValue"     , m_values.ship.resources.energy.incValue   , m_defaultValues.ship.resources.energy.incValue   );
    
    // planet
    kvd.Load("PlanetActive"      , m_values.planet.active      , m_defaultValues.planet.active      );
    kvd.Load("PlanetGravity"     , m_values.planet.hasGravity  , m_defaultValues.planet.hasGravity  );
    kvd.Load("PlanetGravityStrength", m_values.planet.gravityStrength, m_defaultValues.planet.gravityStrength);
    
    // powerup system
    kvd.Load("PowerupMaxSimult"     , m_values.powerupSys.maxPowerups      , m_defaultValues.powerupSys.maxPowerups      );
    kvd.Load("PowerupIntervalMinMs" , m_values.powerupSys.minInterval      , m_defaultValues.powerupSys.minInterval      );
    kvd.Load("PowerupIntervalMaxMs" , m_values.powerupSys.maxInterval      , m_defaultValues.powerupSys.maxInterval      );
    kvd.Load("PowerupNotGenBorder"  , m_values.powerupSys.notGenerateBorder, m_defaultValues.powerupSys.notGenerateBorder);
    kvd.Load("PowerupShieldBonusVal", m_values.powerupSys.shieldBonusValue , m_defaultValues.powerupSys.shieldBonusValue );
    kvd.Load("PowerupEnergyBonusVal", m_values.powerupSys.energyBonusValue , m_defaultValues.powerupSys.energyBonusValue );

    // weapons
    LoadWeapon(WeaponTypes::WT_CANNON, "Cannon", kvd);
    LoadWeapon(WeaponTypes::WT_ROCKET, "Rocket", kvd);
    LoadWeapon(WeaponTypes::WT_LASER, "Laser", kvd);

    // fps
    kvd.Load("ShowFPS"      , m_values.showFps, m_defaultValues.showFps);
}

void GameSettings::SaveValues(KeyValueSerializer & kvs)
{
    // ship
    kvs.Save("ShipMaxSpeed"       , m_values.ship.maxSpeed       );
    kvs.Save("ShipFrictionMult"   , m_values.ship.slowdownSpeed  );
    kvs.Save("ShipAccelerateSpeed", m_values.ship.accelerateSpeed);
    kvs.Save("ShipTurnSpeed"      , m_values.ship.turnSpeed      );
    
    // ship Resources
    kvs.Save("ShipMaxShield"            , m_values.ship.resources.shield.maxValue   );
    kvs.Save("ShipMaxEnergy"            , m_values.ship.resources.energy.maxValue   );
    kvs.Save("ShipShieldRegenIntervalMs", m_values.ship.resources.shield.incInterval);
    kvs.Save("ShipShieldRegenValue"     , m_values.ship.resources.shield.incValue   );
    kvs.Save("ShipEnergyRegenIntervalMs", m_values.ship.resources.energy.incInterval);
    kvs.Save("ShipEnergyRegenValue"     , m_values.ship.resources.energy.incValue   );

    kvs.SaveBlankLine();
    
    // planet
    kvs.Save("PlanetActive"      , m_values.planet.active      );
    kvs.Save("PlanetGravity"     , m_values.planet.hasGravity  );
    kvs.Save("PlanetGravityStrength", m_values.planet.gravityStrength);

    kvs.SaveBlankLine();
    
    // powerup system
    kvs.Save("PowerupMaxSimult"     , m_values.powerupSys.maxPowerups      );
    kvs.Save("PowerupIntervalMinMs" , m_values.powerupSys.minInterval      );
    kvs.Save("PowerupIntervalMaxMs" , m_values.powerupSys.maxInterval      );
    kvs.Save("PowerupNotGenBorder"  , m_values.powerupSys.notGenerateBorder);
    kvs.Save("PowerupShieldBonusVal", m_values.powerupSys.shieldBonusValue );
    kvs.Save("PowerupEnergyBonusVal", m_values.powerupSys.energyBonusValue );

    kvs.SaveBlankLine();
    kvs.SaveBlankLine();
    
    // weapons
    SaveWeapon(WeaponTypes::WT_CANNON, "Cannon", kvs);
    
    kvs.SaveBlankLine();
    
    SaveWeapon(WeaponTypes::WT_ROCKET, "Rocket", kvs);
    
    kvs.SaveBlankLine();
    
    SaveWeapon(WeaponTypes::WT_LASER, "Laser", kvs);

    kvs.SaveBlankLine();
    kvs.SaveBlankLine();

    // fps
    kvs.Save("ShowFPS", m_values.showFps); 
}

void GameSettings::LoadWeapon(WeaponTypes::Type type, const std::string & name, const KeyValueDeserializer & kvd)
{
    kvd.Load("Weapon"+ name +"CooldownMs", m_values.weapon.sett[type].cooldown  , m_defaultValues.weapon.sett[type].cooldown  );
    kvd.Load("Weapon"+ name +"EnergyCost", m_values.weapon.sett[type].energyCost, m_defaultValues.weapon.sett[type].energyCost);
    kvd.Load("Weapon"+ name +"LifetimeMs", m_values.weapon.sett[type].lifetime  , m_defaultValues.weapon.sett[type].lifetime  );
    kvd.Load("Weapon"+ name +"Damage"    , m_values.weapon.sett[type].damage    , m_defaultValues.weapon.sett[type].damage    );
    kvd.Load("Weapon"+ name +"Velocity"  , m_values.weapon.sett[type].velocity  , m_defaultValues.weapon.sett[type].velocity  );
    kvd.Load("Weapon"+ name +"GravityMultiplier", m_values.weapon.sett[type].gravityMultiplier, m_defaultValues.weapon.sett[type].gravityMultiplier);
}

void GameSettings::SaveWeapon(WeaponTypes::Type type, const std::string & name, KeyValueSerializer & kvs)
{
    kvs.Save("Weapon"+ name +"CooldownMs", m_values.weapon.sett[type].cooldown  );
    kvs.Save("Weapon"+ name +"EnergyCost", m_values.weapon.sett[type].energyCost);
    kvs.Save("Weapon"+ name +"LifetimeMs", m_values.weapon.sett[type].lifetime  );
    kvs.Save("Weapon"+ name +"Damage"    , m_values.weapon.sett[type].damage    );
    kvs.Save("Weapon"+ name +"Velocity"  , m_values.weapon.sett[type].velocity  );
    kvs.Save("Weapon"+ name +"GravityMultiplier", m_values.weapon.sett[type].gravityMultiplier);
}

}