// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   FrameworkSettings.cpp
  *  @brief  Nacitani a ukladani zakladniho nastaveni frameworku.
  */

#include "FrameworkSettings.h"

namespace GameFramework
{

FrameworkSettings::FrameworkSettings(void)
{
    m_settingsName = "Framework";
    
    m_defaultValues.windowManager = "SDL";
    m_defaultValues.renderer = "OpenGL";
    m_defaultValues.windowTitle = "Framework Window";
    m_defaultValues.screenSize = Size2i(960, 600);
    m_defaultValues.fullscreen = false;
    m_defaultValues.vsync = true; 
}

FrameworkSettings::~FrameworkSettings(void)
{
}

void FrameworkSettings::LoadDefaultValues()
{
    m_values = m_defaultValues;
}

void FrameworkSettings::LoadValues(const KeyValueDeserializer & kvd)
{
    m_values.windowTitle = m_defaultValues.windowTitle;
    
    kvd.Load("WindowManager", m_values.windowManager, m_defaultValues.windowManager);
    kvd.Load("Renderer"     , m_values.renderer     , m_defaultValues.renderer);    
    kvd.Load("ScreenSize"   , m_values.screenSize   , m_defaultValues.screenSize);
    kvd.Load("Fullscreen"   , m_values.fullscreen   , m_defaultValues.fullscreen);
    kvd.Load("VSync"        , m_values.vsync        , m_defaultValues.vsync); 
}

void FrameworkSettings::SaveValues(KeyValueSerializer & kvs)
{
    kvs.Save("WindowManager", m_values.windowManager);
    kvs.Save("Renderer"     , m_values.renderer);
    kvs.Save("ScreenSize"   , m_values.screenSize);
    kvs.Save("Fullscreen"   , m_values.fullscreen);
    kvs.Save("VSync"        , m_values.vsync);
}

}
