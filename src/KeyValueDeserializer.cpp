// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   KeyValueDeserializer.cpp
  *  @brief  Deserializace dat ruznych typu formatu klic=hodnota.
  */

#include "KeyValueDeserializer.h"

namespace GameFramework
{

KeyValueDeserializer::KeyValueDeserializer(void)
{
}

KeyValueDeserializer::~KeyValueDeserializer(void)
{
}

bool KeyValueDeserializer::ReadFromFile(const std::string &filename)
{
    std::ifstream file;
    file.open(filename.c_str(), std::ios::in);
    if (file.fail())
        return false;
    
    m_valueMap.clear();
    
    std::string line;

    while (std::getline(file, line))
    {
        if (line.length() == 0)
            continue;
        
        int delimPos = line.find("=");
        std::string key = line.substr(0, delimPos);
        std::string val = line.substr(delimPos + 1);
        
        if (!m_valueMap.insert(ValueMap::value_type(key, val)).second)
            Log::Msg("KeyValueDeserializer::Duplicate entry for key " + key + " found, skipping");
    }

    file.close();
    return true;
}

}