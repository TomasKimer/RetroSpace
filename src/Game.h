// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Game.h
  *  @brief  Zakladni trida pro hru.
  */

#pragma once

#include "RenderWindowSelector.h"
#include "RendererSelector.h"
#include "GameTime.h"
#include "FpsCounter.h"
#include "MathHelper.h"
#include "Log.h"
#include "FrameworkSettings.h"

/**
 * Herni framework.
 */
namespace GameFramework
{
    const std::string DEFAULT_CFG_FILE = std::string("framework.cfg");
    const std::string DEFAULT_LOG_FILE = std::string("game.log");
    
    /**
     * Zakladni bazova trida pro herni aplikaci.
     */
    class Game : public IWindowEventListener
    {
    public:    
        Game();
        virtual ~Game(void);
    
        int Run(int argc, char *argv[]);
    
    protected:
        virtual void BeforeCreate(FrameworkSettings & frameworkSettings);
        virtual void Initialize(void);
        virtual void Deinitialize(void);
        virtual void Update(const GameTime & gameTime, const FpsCounter & fpsCounter);
        virtual void Draw();
        
        /* Events overriden from IWindowEventListener */    
        virtual void Resize(Size2i newSize);
        virtual void KeyDown(KeyCode key);
        virtual void KeyUp(KeyCode key);
        virtual void MouseDown(Point2i curPos, BtnCode button);
        virtual void MouseUp(Point2i curPos, BtnCode button);
        virtual void MouseMove(Point2i curPos);
   
        void Exit(int returnCode = 0);
        
        RenderWindow * GetWindow() { return m_window; }
        Renderer * GetRenderer() { return m_renderer; }
        Keyboard * GetKeyboard() { return m_window->GetKeyboard(); }
        Mouse * GetMouse() { return m_window->GetMouse(); }
        FrameworkSettings & GetFrameworkSettings() { return m_fwSettings; }
    
    private:
        RenderWindow *m_window;
        Renderer *m_renderer;
        
        GameTime m_gameTime;
        FpsCounter m_fpsCounter;
    
        FrameworkSettings m_fwSettings;
        
        bool m_haveToExit;
        int m_returnCode;
        
        void Tick(void);   
    };
}