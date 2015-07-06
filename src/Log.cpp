// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Log.cpp
  *  @brief  Logovani udalosti.
  */

#include "Log.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <stdexcept>

namespace GameFramework
{

Log *Log::m_instance = 0;

Log::Log(void)
{
}

Log::~Log(void)
{
    if (m_instance->m_output.is_open())
        m_instance->m_output.close();
}

void Log::Create(const std::string & filename)
{
    if (!m_instance)
    {
        m_instance = new Log;
        m_instance->m_output.open(filename.c_str(), std::ios::out);
        if (m_instance->m_output.fail())
            throw std::runtime_error("Failed to open Log file " + filename + " for writing");
    }
}

void Log::Destroy()
{
    if (m_instance)
    {        
        delete m_instance;
        m_instance = 0;
    }
}

void Log::Msg(const std::string & msg)
{
    Create();
    m_instance->logMsg(msg);
}

Log::LogStream Log::Stream()
{
    Create();
    return m_instance->m_stream;
}

void Log::logMsg(const std::string & msg)
{
    time_t actTime;
    time(&actTime);
    tm *locTime = localtime(&actTime);
    std::stringstream timestamp;
    
    timestamp << std::setw(2) << std::setfill('0') << locTime->tm_hour
       << ":" << std::setw(2) << std::setfill('0') << locTime->tm_min
       << ":" << std::setw(2) << std::setfill('0') << locTime->tm_sec
       << ": ";    

#ifdef _DEBUG
    std::cerr << timestamp.str() << msg << std::endl;
#endif

    m_output << timestamp.str() << msg << std::endl;
    m_output.flush();
}

}
