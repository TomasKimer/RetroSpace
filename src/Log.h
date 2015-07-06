// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Log.h
  *  @brief  Logovani udalosti.
  */

#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace GameFramework
{
    const std::string DEF_FILENAME("game.log");
    
    /**
     * Logovani udalosti.
     */
    class Log
    {
    public:
        ~Log(void);
    
        static void Create(const std::string & filename = DEF_FILENAME);
        static void Destroy();
        static void Msg(const std::string & msg);
    
        /**
         * Logovani pomoci streamu.
         */
        class LogStream
        {
        public:            
            /**
             * Indikace konce streamu.
             */
            struct Flush {};
        
            LogStream() {}            
            LogStream(const LogStream& ls)
            {    
                m_cache.str(ls.m_cache.str());
            }
            
            ~LogStream()
            {                
                if (m_cache.tellp() > 0)  // flush pri zruseni
                    m_instance->logMsg(m_cache.str());
            }
        
            template <typename T>
            LogStream& operator<< (const T& v)
            {
                m_cache << v;
                return *this;
            }
        
            LogStream& operator<< (const Flush& v)
            {
                m_instance->logMsg(m_cache.str());
                m_cache.str("");
                return *this;            
            }
        
        private:
            std::stringstream m_cache;
        };
    
        static LogStream Stream();
    
    private:
        Log(void);
        static Log *m_instance;
    
        void logMsg(const std::string & msg);
    
        LogStream m_stream;
    
        std::ofstream m_output;
    };
}