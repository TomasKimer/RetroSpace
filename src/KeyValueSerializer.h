// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   KeyValueSerializer.h
  *  @brief  Serializace dat ruznych typu formatu klic=hodnota.
  */

#pragma once

#include <vector>
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
     * Serializace dat klic=hodnota.
     */
    class KeyValueSerializer
    {
    public:
        KeyValueSerializer(void);
        ~KeyValueSerializer(void);    
        
        void WriteToFile(const std::string &filename);
        void Clear() { m_saveVec.clear(); }        
    
        template <typename T>
        bool Save(const std::string & key, const T & value)
        {
            std::string strVal;
            if (!ParseType<T>::ToString(value, strVal))
                return false;
    
            m_saveVec.push_back(SaveItem(key, strVal));
            
            return true;
        }
    
        void SaveBlankLine() { m_saveVec.push_back(SaveItem()); }
    
    private:      
        /**
         * Ukladana dvojice.
         */
        struct SaveItem
        {
            std::string key, value;
            SaveItem() {}
            SaveItem(std::string key, std::string value): key(key), value(value) {}
        };
        std::vector<SaveItem> m_saveVec;
    
        template<typename T>
        static bool ToStringBasic(const T & value, std::string & outStr)
        {
            std::stringstream ss;
            ss << value;
            outStr = ss.str();
            return true;
        } 

        template<typename T>
        static bool ToStringEnum(const T & value, std::string & outStr)
        {
            std::stringstream ss;
            ss << static_cast<int>(value);
            outStr = ss.str();
            return true;
        }
    
        template<typename T>
        static bool ToStringVector2(const Vector2<T> & value, std::string & outStr)
        {
            std::stringstream ss;
            ss << value.x << "," << value.y;
            outStr = ss.str();
            return true;
        };

        template<typename T> struct ParseType;
    };

    // specializations
    template<> struct KeyValueSerializer::ParseType<int>
    {
        static bool ToString(int value, std::string & outStr) { return ToStringBasic(value, outStr); }
    };

    template<> struct KeyValueSerializer::ParseType<unsigned int>
    {
        static bool ToString(unsigned int value, std::string & outStr) { return ToStringBasic(value, outStr); }
    };
    
    template<> struct KeyValueSerializer::ParseType<float>
    {
        static bool ToString(float value, std::string & outStr) { return ToStringBasic(value, outStr); }
    };
    
    template<> struct KeyValueSerializer::ParseType<bool>
    {
        static bool ToString(bool value, std::string & outStr) { return ToStringBasic(value, outStr); }
    };

    template<> struct KeyValueSerializer::ParseType<KeyCode>
    {
        static bool ToString(KeyCode value, std::string & outStr) { return ToStringEnum(value, outStr); }
    };

    template<> struct KeyValueSerializer::ParseType<BtnCode>
    {
        static bool ToString(BtnCode value, std::string & outStr) { return ToStringEnum(value, outStr); }
    };
    
    template<> struct KeyValueSerializer::ParseType<std::string>
    {
        static bool ToString(const std::string & value, std::string & outStr)
        {
            outStr = value;
            return true;
        }
    };

    template<> struct KeyValueSerializer::ParseType<Vector2f>
    {
        static bool ToString(const Vector2f & value, std::string & outStr) {return ToStringVector2(value, outStr); }
    };
    
    template<> struct KeyValueSerializer::ParseType<Size2i>
    {
        static bool ToString(const Size2i & value, std::string & outStr) { return ToStringVector2(value, outStr); }
    };
    
    template<> struct KeyValueSerializer::ParseType<Color>
    {
        static bool ToString(const Color & value, std::string & outStr)
        {
            std::stringstream ss;
            ss << value.Ri() << "," << value.Gi() << "," << value.Bi() << "," << value.Ai();
            outStr = ss.str();
            return true;
        }
    };
    
    template<> struct KeyValueSerializer::ParseType<TimeSpan>
    {
        static bool ToString(const TimeSpan & value, std::string & outStr)
        {
            return ToStringBasic(value.ms(), outStr);
        }
    };
}