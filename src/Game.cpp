// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Game.cpp
  *  @brief  Zakladni trida pro hru.
  */

#include <stdexcept>
#include "Game.h"
#include "Log.h"

namespace GameFramework
{

Game::Game(void): m_window(0), m_renderer(0), m_haveToExit(false), m_returnCode(0)
{
}

Game::~Game(void)
{
}

int Game::Run(int argc, char *argv[])
{
    try
    {
        Log::Create(DEFAULT_LOG_FILE);
    }
    catch (std::exception & e)
    {
        std::cerr << e.what();
        Log::Destroy();
        return 1;
    }
    
    BeforeCreate(m_fwSettings);
    
    try
    {
        Initialize();
    }
    catch (std::exception & e)
    {
        Log::Msg(e.what());
        
        if (m_window) delete m_window;
        if (m_renderer) delete m_renderer;
        
        Log::Destroy();
        return 1;
    }

    while (m_window->ProcessEvent() && !m_haveToExit)
    {
        Tick();
    }

    Deinitialize();

    Log::Destroy();

    return m_returnCode;
}

void Game::BeforeCreate(FrameworkSettings & frameworkSettings)
{
    m_fwSettings.Load(DEFAULT_CFG_FILE);
}

void Game::Initialize(void)
{
    if (m_fwSettings.Values().windowManager == "SDL" && m_fwSettings.Values().renderer != "OpenGL")
        throw std::invalid_argument("Error: SDL window manager supports only OpenGL renderer");
    
    m_window = RenderWindowSelector::CreateRenderWindow(m_fwSettings.Values().windowManager);
    m_window->Create(m_fwSettings.Values().windowTitle, m_fwSettings.Values().screenSize, m_fwSettings.Values().fullscreen, m_fwSettings.Values().vsync);
    m_window->SetEventCallback(this);
    
    m_renderer = RendererSelector::CreateRenderer(m_fwSettings.Values().renderer);
    m_renderer->Initialize();

    m_gameTime.Init();
}

void Game::Deinitialize(void)
{
    if (m_window)
        m_fwSettings.Values().screenSize = m_window->GetSize();
    m_fwSettings.Save();
    
    if (m_renderer) delete m_renderer;
    if (m_window) delete m_window;
}

void Game::Tick()
{
    m_gameTime.Update();
    m_fpsCounter.Update(m_gameTime);

    Update(m_gameTime, m_fpsCounter);
    Draw();
}

void Game::Update(const GameTime & gameTime, const FpsCounter & fpsCounter)
{
}

void Game::Draw()
{
}

void Game::Exit(int returnCode)
{
    m_returnCode = returnCode;
    m_haveToExit = true;
}

// ---- overriden window events ---- //
void Game::Resize(Size2i newSize)
{
    if (m_window)
        m_window->Resize(newSize);
}

void Game::KeyDown(KeyCode key)
{
}

void Game::KeyUp(KeyCode key)
{
}

void Game::MouseDown(Point2i curPos, BtnCode button)
{
}

void Game::MouseUp(Point2i curPos, BtnCode button)
{
}

void Game::MouseMove(Point2i curPos)
{
}

}