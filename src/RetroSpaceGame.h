// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   RetroSpaceGame.h
  *  @brief  Hlavni logika aplikace.
  */

#pragma once

#include "Game.h"

#include "TextObject.h"
#include "Player.h"
#include "Background.h"
#include "Planet.h"
#include "StatusText.h"
#include "PlayerGUI.h"
#include "PowerupSystem.h"
#include "Menu.h"
#include "Controls.h"
#include "ColorSettings.h"
#include "GameSettings.h"
#include "ControlsSettings.h"
#include <string>

using namespace GameFramework;

/**
 * Logika hry.
 */
namespace RetroSpace
{
    const std::string DEFAULT_COLOR_FILE    = std::string("colors.cfg");
    const std::string DEFAULT_GAME_FILE     = std::string("game.cfg");
    const std::string DEFAULT_CONTROLS_FILE = std::string("controls.cfg");
    const std::string WINDOW_TITLE          = std::string("RetroSpace v1.0");
    
    /**
     * Hlavni trida ridici celou aplikaci.
     */
    class RetroSpaceGame : public Game
    {
    public:
        RetroSpaceGame(void);
        virtual ~RetroSpaceGame(void);
    
    private:
        virtual void BeforeCreate(FrameworkSettings & frameworkSettings);
        virtual void Initialize(void);
        virtual void Deinitialize(void);
        virtual void Update(const GameTime & gameTime, const FpsCounter & fpsCounter);
        virtual void Draw();
        virtual void Resize(Size2i newSize);
        virtual void KeyDown(KeyCode key);
        virtual void KeyUp(KeyCode key);
        virtual void MouseDown(Point2i curPos, BtnCode button);
        virtual void MouseUp(Point2i curPos, BtnCode button);
        virtual void MouseMove(Point2i curPos);
    
        void OnResize(Size2i newSize);
    
    private:    
        // font
        SpriteFont *m_fontMain, *m_fontFps;
    
        // texts
        TextObject m_textFps;
        StatusText m_statusText;
    
        // space
        Background m_background;
        Planet m_planet;
        WeaponTypes m_weaponTypes;
    
        // gui
        PlayerGUI m_playerGUI[2];
        
        // objects
        Player m_player[2];
        PowerupSystem m_powerupSystem;

        // menu, controls
        Menu m_menu;
        Controls m_controls;
    
        // settings
        ColorSettings m_colorSettings;
        GameSettings  m_gameSettings;
        ControlsSettings m_controlsSettings;
        
        // methods
        void HandleCollisions();
        void HandleInputUnbuffered();
        void HandleMenuResult(Menu::MenuResult mr);
        void NewGame(bool resetScore = true);
    };
}
