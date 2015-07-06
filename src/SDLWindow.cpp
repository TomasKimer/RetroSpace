// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   SDLWindow.cpp
  *  @brief  Prace s oknem knihovny SDL.
  */

#include "SDLWindow.h"
#include "SDLKeyboard.h"
#include "SDLMouse.h"
#include "Log.h"
#include <stdexcept>

namespace GameFramework
{

SDLWindow::SDLWindow(void): m_flags(SDL_OPENGL | SDL_RESIZABLE)
{
    m_managerName = "SDL";

    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        throw std::runtime_error(std::string("SDL_Init(SDL_INIT_VIDEO) error: ") + std::string(SDL_GetError()));

    m_keyboard = new SDLKeyboard();
    m_mouse = new SDLMouse();
}

SDLWindow::~SDLWindow(void)
{
    if (m_mouse)
        delete m_mouse;
    if (m_keyboard)
        delete m_keyboard;
    
    SDL_Quit();

    Log::Msg("SDL Window destroyed");
}

void SDLWindow::SetVideoMode(Size2i screenSize, unsigned int flags)
{
    m_screen = SDL_SetVideoMode(screenSize.x, screenSize.y, 0, flags);
    if (m_screen == 0)
        throw std::runtime_error(std::string("SDL_SetVideoMode() error: ") + std::string(SDL_GetError()));
}

void SDLWindow::Create(const std::string &name, Size2i size, bool fullscreen, bool vsync)
{
    unsigned int flags = m_flags;
    if (fullscreen)
        flags |= SDL_FULLSCREEN;
       
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, static_cast<int>(vsync));
    
    SetVideoMode(size, flags);
    SDL_WM_SetCaption(name.c_str(), 0);

    Log::Stream() << "SDL Window created (" << size.x << "x" << size.y << ", fullscreen=" << fullscreen << ")";

    m_size = size;
    m_fullscreen = fullscreen;
}

void SDLWindow::Resize(Size2i newSize, int fullscreen)
{
    unsigned int flags = m_flags;
    bool fs;
    
    if (fullscreen == -1)
        fs = m_fullscreen;
    else
    {
        fs = !(fullscreen == 0);
        m_fullscreen = fs;
    }
        
    if (fs)
        flags |= SDL_FULLSCREEN;
        
    SetVideoMode(newSize, flags);

    Log::Stream() << "SDL Window resized (" << newSize.x << "x" << newSize.y << ", fullscreen=" << fs << ")";

    m_size = newSize;
}

void SDLWindow::SwapBuffers(bool waitForVSync)
{
    SDL_GL_SwapBuffers();
}

bool SDLWindow::ProcessEvent(void)
{
    if (!m_eventListener)
        return false;

    SDL_Event event;    
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_KEYDOWN:
                m_eventListener->KeyDown(m_keyboard->KeyDown(event.key.keysym.sym));
                break;

            case SDL_KEYUP:
                m_eventListener->KeyUp(m_keyboard->KeyUp(event.key.keysym.sym));
                break;

            case SDL_MOUSEBUTTONDOWN:
                m_eventListener->MouseDown(Point2i(event.button.x, event.button.y), m_mouse->BtnDown(event.button.button));
                break;

            case SDL_MOUSEBUTTONUP:
                m_eventListener->MouseUp(Point2i(event.button.x, event.button.y), m_mouse->BtnUp(event.button.button));
                break;

            case SDL_MOUSEMOTION:
                m_eventListener->MouseMove(Point2i(event.button.x, event.button.y));
                break;

            case SDL_VIDEORESIZE:
                m_eventListener->Resize(Size2i(event.resize.w, event.resize.h));
                break;

            case SDL_QUIT:
                return false;
            
            default:
                break;
        }
    }
    
    return true;
}

}