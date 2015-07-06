// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ControlsSettings.h
  *  @brief  Nacitani a ukladani ovladani hracu.
  */

#pragma once

#include "Settings.h"
#include "Controls.h"

using namespace GameFramework;

namespace RetroSpace
{ 
    /**
     * Konfigurace ovladani.
     */
    class ControlsSettings : public Settings
    {
        /**
         * Ukladane hodnoty.
         */
        struct SettingsValues
        {
            Controls::PlayerControls ctrls[2];            
        };

    public:
        ControlsSettings(void);
        ~ControlsSettings(void);

        virtual void LoadDefaultValues();
        virtual void LoadValues(const KeyValueDeserializer & kvd);
        virtual void SaveValues(KeyValueSerializer & kvs);

        SettingsValues & Values() { return m_values; }
        SettingsValues & DefaultValues() { return m_defaultValues; } 

    private:
        SettingsValues m_values, m_defaultValues;

        void LoadPlayerControls(int num, const KeyValueDeserializer & kvd);
        void SavePlayerControls(int num, KeyValueSerializer & kvs);
    };
}

