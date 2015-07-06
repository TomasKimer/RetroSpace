// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Settings.h
  *  @brief  Nacitani a ukladani nastaveni.
  */

#pragma once

#include <string>
#include "KeyValueSerializer.h"
#include "KeyValueDeserializer.h"

namespace GameFramework
{
    /**
     * Baze pro konfigurace.
     */
    class Settings
    {
    public:
        Settings(void);
        virtual ~Settings(void);
    
        void Load(const std::string & filename);
        void Save(const std::string & filename = std::string());
    
        virtual void LoadDefaultValues() = 0;
        virtual void LoadValues(const KeyValueDeserializer & kvd) = 0;
        virtual void SaveValues(KeyValueSerializer & kvs) = 0;
    
    protected:
        std::string m_filename, m_settingsName;
    };
}