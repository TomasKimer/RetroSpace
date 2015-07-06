// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   FrameworkSettings.h
  *  @brief  Nacitani a ukladani zakladniho nastaveni frameworku.
  */

#pragma once

#include "Settings.h"
#include "Vector2.h"

namespace GameFramework
{
    /**
     * Nastaveni frameworku.
     */
    class FrameworkSettings : public Settings
    {
        /**
         * Struktura ukladanych hodnot.
         */
        struct SettingsValues
        {
            std::string windowManager, renderer, windowTitle;
            Size2i screenSize;
            bool fullscreen, vsync;
        };
    
    public:
        FrameworkSettings(void);
        ~FrameworkSettings(void);
    
        virtual void LoadDefaultValues();
        virtual void LoadValues(const KeyValueDeserializer & kvd);
        virtual void SaveValues(KeyValueSerializer & kvs);
       
        SettingsValues & Values() { return m_values; }
        SettingsValues & DefaultValues() { return m_defaultValues; }    
    
    private:
        SettingsValues m_values, m_defaultValues;
    };
}