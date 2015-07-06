// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   KeyValueSerializer.cpp
  *  @brief  Serializace dat ruznych typu formatu klic=hodnota.
  */

#include "KeyValueSerializer.h"
#include <stdexcept>

namespace GameFramework
{

KeyValueSerializer::KeyValueSerializer(void)
{
}

KeyValueSerializer::~KeyValueSerializer(void)
{
}

void KeyValueSerializer::WriteToFile(const std::string &filename)
{
    std::ofstream file;
    file.open(filename.c_str(), std::ios::out);
    if (file.fail())
        throw std::runtime_error("KeyValueSerializer::Opening of file " + filename + " failed");

    for (unsigned int i = 0; i < m_saveVec.size(); i++)
    {
        if (m_saveVec[i].key.length() == 0 && m_saveVec[i].value.length() == 0)
            file << std::endl;
        else        
            file << m_saveVec[i].key + "=" + m_saveVec[i].value << std::endl;
    }

    file.close();
}

}
