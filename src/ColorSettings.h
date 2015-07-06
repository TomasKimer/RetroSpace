// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ColorSettings.h
  *  @brief  Nacitani a ukladani barevnych hodnot objektu.
  */

#pragma once

#include "Settings.h"
#include "Color.h"
#include "PlayerGUI.h"
#include "Ship.h"
#include "PowerupSystem.h"
#include "WeaponTypes.h"
#include "Background.h"

namespace RetroSpace
{ 
    /**
     * Konfigurace barev.
     */
    class ColorSettings : public Settings
    {
        /**
         * Ukladane hodnoty.
         */
        struct SettingsValues
        {
            Ship::Colors shipColors[2];
            PlayerGUI::Colors playerGuiColors[2];
            PowerupSystem::Colors powerupColors;
            Background::Colors backgndColors;
            Color playerStatusColor[2], statusColor, planetColor;
            WeaponTypes::Colors weaponColors;
        };
    
    public:
        ColorSettings(void);
        ~ColorSettings(void);
    
        virtual void LoadDefaultValues();
        virtual void LoadValues(const KeyValueDeserializer & kvd);
        virtual void SaveValues(KeyValueSerializer & kvs);
    
        Ship::Colors & GetShipColors(int i) { return m_values.shipColors[i % 2]; }
        PlayerGUI::Colors & GetPlayerGuiColors(int i) { return m_values.playerGuiColors[i % 2]; }
        Color & GetPlayerStatusColor(int i) { return m_values.playerStatusColor[i % 2]; }
        Color & GetStatusColor() { return m_values.statusColor; }

        SettingsValues & Values() { return m_values; }
        SettingsValues & DefaultValues() { return m_defaultValues; }  
    
    private:
        SettingsValues m_values, m_defaultValues;

        void LoadShipColors(int num, const KeyValueDeserializer & kvd);
        void SaveShipColors(int num, KeyValueSerializer & kvs);

        void LoadPlayerGuiColors(int num, const KeyValueDeserializer & kvd);
        void SavePlayerGuiColors(int num, KeyValueSerializer & kvs);
    };
}

