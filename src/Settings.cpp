// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Settings.cpp
  *  @brief  Nacitani a ukladani nastaveni.
  */

#include "Settings.h"

namespace GameFramework
{

Settings::Settings(void)
{
}

Settings::~Settings(void)
{
}

void Settings::Load(const std::string & filename)
{
    m_filename = filename;

    KeyValueDeserializer kvd;
    
    if (!kvd.ReadFromFile(filename))
    {
        LoadDefaultValues();
        Log::Msg(m_settingsName + "Settings loading from file " + filename + " failed, using default");
        return;
    }
    else
        Log::Msg(m_settingsName + "Settings loaded from file " + filename);

    LoadValues(kvd);    
}

void Settings::Save(const std::string & filename)
{
    std::string saveFile = filename;
    if (filename == std::string())
        saveFile = m_filename;

    KeyValueSerializer kvs;
    SaveValues(kvs);
    kvs.WriteToFile(saveFile);
}

}