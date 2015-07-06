// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   KeyValueDeserializer.h
  *  @brief  Deserializace dat ruznych typu formatu klic=hodnota.
  */

#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Vector2.h"
#include "Color.h"
#include "TimeSpan.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Log.h"

namespace GameFramework
{
    /**
     * Deserializace dat klic=hodnota.
     */
    class KeyValueDeserializer
    {
    public:
        KeyValueDeserializer(void);
        ~KeyValueDeserializer(void);
    
        bool ReadFromFile(const std::string &filename);
        void Clear() { m_valueMap.clear(); }        
    
        template <typename T>
        bool Load(const std::string & key, T & outValue, T defaultValue = T()) const
        {
            ValueMap::const_iterator it = m_valueMap.find(key);
            if (it == m_valueMap.end())                     // not found
            {
                Log::Msg("KeyValueDeserializer::Entry for key " + key + " not found, using default");
                outValue = defaultValue;
                return false;
            }
    
            T parsed;
            if (ParseType<T>::Parse((*it).second, parsed)) 
            {
                outValue = parsed;                          // ok
                return true;
            }
            else                                            // parse failed
            {
                Log::Msg("KeyValueDeserializer::Parsing value for key " + key + " failed, using default");
                outValue = defaultValue;
                return false;
            }
        }

    private:
        typedef std::map<std::string, std::string> ValueMap; 
        ValueMap m_valueMap; 

        template<typename T>
        static bool ParseBasic(const std::string & value, T & parsed)
        {
            std::istringstream is(value);
            is >> parsed;
            return true;
        }

        template<typename T>
        static bool ParseEnum(const std::string & value, T & parsed)
        {
            std::istringstream is(value);
            int tmp;
            is >> tmp;
            parsed = static_cast<T>(tmp);
            return true;
        }

        template<typename T>
        static bool ParseVector2(const std::string & value, Vector2<T> & parsed)
        {
            int commaPos = value.find(",");
            std::string str = value.substr(0, commaPos);
            ParseBasic(str, parsed.x);
            str = value.substr(commaPos + 1);
            ParseBasic(str, parsed.y);
            return true;
        };

        template<typename T> struct ParseType;
    };

    template<> struct KeyValueDeserializer::ParseType<int>
    {
        static bool Parse(const std::string & value, int & parsed) { return ParseBasic(value, parsed); }
    };

    template<> struct KeyValueDeserializer::ParseType<unsigned int>
    {
        static bool Parse(const std::string & value, unsigned int & parsed) { return ParseBasic(value, parsed); }
    };
    
    template<> struct KeyValueDeserializer::ParseType<float>
    {
        static bool Parse(const std::string & value, float & parsed) { return ParseBasic(value, parsed); }
    };
    
    template<> struct KeyValueDeserializer::ParseType<bool>
    {
        static bool Parse(const std::string & value, bool & parsed) { return ParseBasic(value, parsed); }
    };

    template<> struct KeyValueDeserializer::ParseType<KeyCode>
    {
        static bool Parse(const std::string & value, KeyCode & parsed) { return ParseEnum(value, parsed); }
    };

    template<> struct KeyValueDeserializer::ParseType<BtnCode>
    {
        static bool Parse(const std::string & value, BtnCode & parsed) { return ParseEnum(value, parsed); }
    };
    
    template<> struct KeyValueDeserializer::ParseType<std::string>
    {
        static bool Parse(const std::string & value, std::string & parsed)
        {
            parsed = value;
            return true;
        }
    };        
    
    template<> struct KeyValueDeserializer::ParseType<Vector2f>
    {
        static bool Parse(const std::string & value, Vector2f & parsed) { return ParseVector2(value, parsed); }
    };
    
    template<> struct KeyValueDeserializer::ParseType<Size2i>
    {
        static bool Parse(const std::string & value, Size2i & parsed) { return ParseVector2(value, parsed); }
    };
    
    template<> struct KeyValueDeserializer::ParseType<Color>
    {
        static bool Parse(const std::string & value, Color & parsed)
        {
            int commaPos = value.find(",");
            std::string strVal = value.substr(0, commaPos);
            unsigned int parsedColor;
            ParseBasic(strVal, parsedColor);
            parsed.Ri(parsedColor);
            std::string strRemain = value.substr(commaPos + 1);
            
            commaPos = strRemain.find(",");
            strVal = strRemain.substr(0, commaPos);
            ParseBasic(strVal, parsedColor);
            parsed.Gi(parsedColor);
            strRemain = strRemain.substr(commaPos + 1);
    
            commaPos = strRemain.find(",");
            strVal = strRemain.substr(0, commaPos);
            ParseBasic(strVal, parsedColor);
            parsed.Bi(parsedColor);
            strVal = strRemain.substr(commaPos + 1);
            
            ParseBasic(strVal, parsedColor);
            parsed.Ai(parsedColor);
                        
            return true;
        }
    };
    
    template<> struct KeyValueDeserializer::ParseType<TimeSpan>
    {
        static bool Parse(const std::string & value, TimeSpan & parsed)
        {
            unsigned int parsedVal;
            ParseBasic(value, parsedVal);
            parsed = TimeSpan::FromMs(parsedVal);
            return true;
        }
    };
}
