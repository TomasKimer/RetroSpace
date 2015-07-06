// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   GameSettings.h
  *  @brief  Nacitani a ukladani herni konfigurace.
  */

#pragma once

#include "Settings.h"
#include "Vector2.h"
#include "TimeSpan.h"
#include "PowerupSystem.h"
#include "WeaponTypes.h"
#include "Planet.h"
#include "Ship.h"
#include <string>

using namespace GameFramework;

namespace RetroSpace
{ 
     /**
     * Herni konfigurace.
     */
    class GameSettings : public Settings
    {
        /**
         * Struktura ukladanych hodnot.
         */
        struct SettingsValues
        {
            // planet
            Planet::Attributes planet;
            
            // ship            
            Ship::Attributes ship;
    
            // powerup system
            PowerupSystem::Attributes powerupSys;
            
            // weapons
            WeaponTypes::Settings weapon;

            // fps
            bool showFps;
        };
    
    public:
        GameSettings(void);
        ~GameSettings(void);
    
        virtual void LoadDefaultValues();
        virtual void LoadValues(const KeyValueDeserializer & kvd);
        virtual void SaveValues(KeyValueSerializer & kvs);
       
        SettingsValues & Values() { return m_values; }
        SettingsValues & DefaultValues() { return m_defaultValues; }    
    
    private:
        SettingsValues m_values, m_defaultValues;

        void LoadWeapon(WeaponTypes::Type type, const std::string & name, const KeyValueDeserializer & kvd);
        void SaveWeapon(WeaponTypes::Type type, const std::string & name, KeyValueSerializer & kvs);
    };
}
