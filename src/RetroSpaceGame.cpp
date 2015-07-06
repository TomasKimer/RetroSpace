// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   RetroSpaceGame.cpp
  *  @brief  Hlavni logika aplikace.
  */

#include "RetroSpaceGame.h"
#include <sstream>

namespace RetroSpace
{

RetroSpaceGame::RetroSpaceGame(void): m_fontMain(0), m_fontFps(0)
{
}

RetroSpaceGame::~RetroSpaceGame(void)
{
}

void RetroSpaceGame::BeforeCreate(FrameworkSettings & frameworkSettings)
{
    frameworkSettings.DefaultValues().windowTitle = WINDOW_TITLE;
    Game::BeforeCreate(frameworkSettings);
}

void RetroSpaceGame::Initialize(void)
{
    Game::Initialize();
    
    m_colorSettings.Load(DEFAULT_COLOR_FILE);
    m_gameSettings.Load(DEFAULT_GAME_FILE);
    m_controlsSettings.Load(DEFAULT_CONTROLS_FILE);
    
    m_fontMain = GetRenderer()->CreateSpriteFont();
    m_fontMain->Create("spritefont_main.bmp", Size2i(16, 16), Size2i(64, 64));
    
    if (m_gameSettings.Values().showFps)
    {
        m_fontFps = GetRenderer()->CreateSpriteFont();
        m_fontFps->Create("spritefont_fps.bmp", Size2i(16, 16), Size2i(16, 16), -6);

        m_textFps.SetFont(*m_fontFps);
        m_textFps.SetScale(Vector2f(0.5f, 0.5f));
    } 

    m_statusText.SetFont(*m_fontMain);
    m_statusText.SetScale(Vector2f(1.5f, 1.5f));

    int x = GetWindow()->GetSize().x;
    int y = GetWindow()->GetSize().y;    

    m_player[0].GetShip().SetAttributes(m_gameSettings.Values().ship);
    m_player[0].GetShip().SetColors(m_colorSettings.GetShipColors(0));
    m_player[0].GetShip().SetPlanet(&m_planet);
    m_player[0].GetShip().SetWeaponTypes(m_weaponTypes);    

    m_player[1].GetShip().SetAttributes(m_gameSettings.Values().ship);
    m_player[1].GetShip().SetColors(m_colorSettings.GetShipColors(1));
    m_player[1].GetShip().SetPlanet(&m_planet);
    m_player[1].GetShip().SetWeaponTypes(m_weaponTypes);
    m_player[1].GetShip().SetRotation(m_player[0].GetShip().GetRotation() + 180.0f);

    
    m_player[0].SetName("Player 1");
    m_playerGUI[0].SetValues(m_player[0], *m_fontMain, m_powerupSystem);
    m_playerGUI[0].SetColors(m_colorSettings.GetPlayerGuiColors(0));    
    
    m_player[1].SetName("Player 2");    
    m_playerGUI[1].SetValues(m_player[1], *m_fontMain, m_powerupSystem);    
    m_playerGUI[1].SetColors(m_colorSettings.GetPlayerGuiColors(1));
    
    m_planet.SetAttributes(m_gameSettings.Values().planet);
    m_planet.SetColor(m_colorSettings.Values().planetColor);

    m_background.SetColors(m_colorSettings.Values().backgndColors);
    
    m_powerupSystem.SetAttributes(m_gameSettings.Values().powerupSys);
    m_powerupSystem.SetColors(m_colorSettings.Values().powerupColors);
    m_powerupSystem.SetNotGenerateObjects(m_planet, m_player[0].GetShip(), m_player[1].GetShip());
    m_powerupSystem.SetFont(*m_fontMain);
    m_powerupSystem.BuildPowerups();

    m_weaponTypes.SetSettings(m_gameSettings.Values().weapon);
    m_weaponTypes.SetColors(m_colorSettings.Values().weaponColors);
    m_weaponTypes.BuildTypes();

    m_controls.SetPlayerControls(m_controlsSettings.Values().ctrls[0], m_controlsSettings.Values().ctrls[1],
                                 m_controlsSettings.DefaultValues().ctrls[0], m_controlsSettings.DefaultValues().ctrls[1]);    
    m_controls.SetInputDevices(*GetKeyboard(), *GetMouse());
    
    m_menu.SetValues(*m_fontMain, m_controls, m_planet);

    OnResize(GetWindow()->GetSize());
}

void RetroSpaceGame::Deinitialize(void)
{
    if (m_fontMain)
        delete m_fontMain;
    
    if (m_fontFps)
        delete m_fontFps;
    
    m_colorSettings.Save();
    m_gameSettings.Save();
    m_controlsSettings.Save();

    Game::Deinitialize();
}

void RetroSpaceGame::Resize(Size2i newSize)
{
    Game::Resize(newSize);
    OnResize(newSize);    
}

void RetroSpaceGame::OnResize(Size2i newSize)
{
    RenderWindow *w = GetWindow();
    
    GetRenderer()->SetViewport(Point2i(0, 0), w->GetSize());
    Matrix projection; projection.Ortho(0.f, 0.f, static_cast<float>(w->GetSize().x), static_cast<float>(w->GetSize().y), -50.f, 50.f);
    GetRenderer()->SetProjectionMatrix(projection);

    if (m_gameSettings.Values().showFps)
    {
        m_textFps.SetCenterPoint(Vector2f(w->GetSize().x / 2.f, 0.f));
        m_textFps.SetPosition(Vector2f(0.f, w->GetSize().y - m_textFps.GetHeight()));
        m_textFps.CenterTextX();
    }
    m_statusText.SetCenterPoint(Vector2f(w->GetSize().x / 2.f, w->GetSize().y / 4.f));
    m_statusText.CenterText();
    m_planet.SetPosition(Vector2f(w->GetSize().x / 2.f, w->GetSize().y / 2.f));

    m_playerGUI[0].SetPositions(Vector2f(),
        Vector2f(0.f, 10.f),
        Point2f(w->GetSize().x / 4.f, 0.f),
        Vector2f(7.f, w->GetSize().y - m_playerGUI[0].GetEnergyBar().GetSize().y - 7.f),
        Vector2f(0.f, - m_playerGUI[0].GetShieldBar().GetSize().y - 5.f));

    m_playerGUI[1].SetPositions(Vector2f(w->GetSize().x - m_playerGUI[1].GetPlayerText().GetWidth(), 0.0f),
        Vector2f(0.f, 10.f),
        Point2f(w->GetSize().x * 0.75f, 0.f),
        Vector2f(w->GetSize().x - m_playerGUI[1].GetEnergyBar().GetSize().x - 7.f, w->GetSize().y - m_playerGUI[0].GetEnergyBar().GetSize().y - 7.f),
        Vector2f(0.f, - m_playerGUI[1].GetShieldBar().GetSize().y - 5.f), false);
     
    m_player[0].GetShip().SetOnResize(w->GetSize()); 
    m_player[1].GetShip().SetOnResize(w->GetSize());
    m_powerupSystem.SetOnResize(w->GetSize());
    
    // reset ships
    m_player[0].GetShip().SetPosition(Vector2f(w->GetSize().x/4.0f - 50.0f, w->GetSize().y/4.0f));
    m_player[1].GetShip().SetPosition(static_cast<Vector2f>(GetWindow()->GetSize()) - m_player[0].GetShip().GetPosition());

    m_background.SetOnResize(w->GetSize());
    
    m_menu.SetOnResize(w->GetSize());
}

void RetroSpaceGame::KeyDown(KeyCode key)
{
    Game::KeyDown(key);

    // handle menu
    if (m_menu.IsActive())
    {
        HandleMenuResult(m_menu.PassKeyDown(key));
        return;
    }    
    
    switch (key)
    {
        case KC_ESCAPE:
            m_menu.SetActive(true);
            break;
    }

    // buffered game controls
    std::pair<Controls::Action, int> action = m_controls.KeyboardAction(key);
    switch (action.first)
    {
        case Controls::ACT_TRANSFER:
            m_player[action.second].GetShip().TransferEnergyShield();
            break;
        case Controls::ACT_SHOOT:
            m_player[action.second].GetShip().FireWeapon();
            break;
    }
}

void RetroSpaceGame::KeyUp(KeyCode key)
{
    Game::KeyUp(key);
}

void RetroSpaceGame::MouseDown(Point2i curPos, BtnCode button)
{
    Game::MouseDown(curPos, button);
    
    // handle menu
    if (m_menu.IsActive())
    {
        HandleMenuResult(m_menu.PassMouseDown(curPos, button));
        return;
    }
    
    // buffered game controls
    std::pair<Controls::Action, int> action = m_controls.MouseAction(button);
    switch (action.first)
    {
        case Controls::ACT_TRANSFER:
            m_player[action.second].GetShip().TransferEnergyShield();
            break;
        case Controls::ACT_SHOOT:
            m_player[action.second].GetShip().FireWeapon();
            break;
    }
}

void RetroSpaceGame::MouseUp(Point2i curPos, BtnCode button)
{
    Game::MouseUp(curPos, button);
}

void RetroSpaceGame::MouseMove(Point2i curPos)
{
    Game::MouseMove(curPos);
    
    if (m_menu.IsActive())
    {
        m_menu.PassMouseMove(curPos);
        return;
    }
    
    int n;
    if ((n = m_controls.GetMousePlayer()) != -1)        
        m_player[n].GetShip().RotateAtPoint(curPos);
    
}

void RetroSpaceGame::HandleMenuResult(Menu::MenuResult mr)
{
    switch (mr)
    {
        case Menu::MR_EXIT:
            Exit(0);
            break;

        case Menu::MR_NEW_GAME:
            NewGame();
            break;
    }
}

void RetroSpaceGame::HandleInputUnbuffered()
{
    // mouse
    Mouse *m = GetMouse();
    
    int n;
    if ((n = m_controls.MouseAction(*m, Controls::ACT_ACCELERATE)) != -1)
        m_player[n].GetShip().Accelerate();

    // keyboard
    Keyboard *k = GetKeyboard();

    bool pl1, pl2;
    
    m_controls.KeyboardAction(*k, Controls::ACT_ACCELERATE, pl1, pl2);
    if (pl1) m_player[0].GetShip().Accelerate();
    if (pl2) m_player[1].GetShip().Accelerate();
   
    m_controls.KeyboardAction(*k, Controls::ACT_TURN_LEFT, pl1, pl2);
    if (pl1) m_player[0].GetShip().Turn(-1.f);
    if (pl2) m_player[1].GetShip().Turn(-1.f);

    m_controls.KeyboardAction(*k, Controls::ACT_TURN_RIGHT, pl1, pl2);
    if (pl1) m_player[0].GetShip().Turn();
    if (pl2) m_player[1].GetShip().Turn();
}

void RetroSpaceGame::Update(const GameTime & gameTime, const FpsCounter & fpsCounter)
{
    Game::Update(gameTime, fpsCounter);
    
    // fps
    if (m_gameSettings.Values().showFps)
    {
        std::stringstream ss;
        ss << "Diff:" << gameTime << ", FPS - " << fpsCounter;
        m_textFps.SetText(ss.str());
        static bool once = true;
        if (once) { m_textFps.CenterTextX(); once = false; }
    }
    
    if (m_menu.IsActive())
        return;
    
    // input
    HandleInputUnbuffered();

    // ship
    m_player[0].GetShip().Update(gameTime);
    m_player[1].GetShip().Update(gameTime);

    // powerup
    m_powerupSystem.Update(gameTime);

    // planet
    m_planet.Update(gameTime);

    // collisions
    HandleCollisions();

    // handle endgame
    if (m_player[0].GetShip().IsDestroyed() || m_player[1].GetShip().IsDestroyed())
    {        
        std::string statusText;
        Color statusColor;
        
        if (m_player[0].GetShip().IsDestroyed())
        {
            statusText = "Player 2 scores!";      
            statusColor = m_colorSettings.GetPlayerStatusColor(1);
            m_player[1].IncScore();
        }

        if (m_player[1].GetShip().IsDestroyed())
        {
            if (m_player[0].GetShip().IsDestroyed())
            {
                statusText = "Round draw!";
                statusColor = m_colorSettings.GetStatusColor();
            }
            else
            {
                statusText = "Player 1 scores!";
                statusColor = m_colorSettings.GetPlayerStatusColor(0);
            }
            
            m_player[0].IncScore();
        }

        // status
        m_statusText.DisplayStatus(statusText); m_statusText.SetStartColor(statusColor);
        m_statusText.CenterText();            

        NewGame(false);
    }
    
    // player gui update
    m_playerGUI[0].Update(gameTime);
    m_playerGUI[1].Update(gameTime);
    
    // status text update
    m_statusText.Update(gameTime);
}

void RetroSpaceGame::NewGame(bool resetScore)
{
    // projectiles reset
    m_player[0].GetShip().GetWeapon().Reset();
    m_player[1].GetShip().GetWeapon().Reset();
    
    // ships reset
    m_player[0].GetShip().ResetRandom(Vector2f(GetWindow()->GetSize().x / 4.f - 50.f, 50.f),                            // random
                                      Vector2f(GetWindow()->GetSize().x / 4.f - 50.f, GetWindow()->GetSize().y - 50.f));
    m_player[1].GetShip().Reset(static_cast<Vector2f>(GetWindow()->GetSize()) - m_player[0].GetShip().GetPosition(),    // mirror of ship 1
                                m_player[0].GetShip().GetRotation() + 180.f);
    // powerups reset
    m_powerupSystem.Reset();

    // score reset
    if (resetScore)
    {
        m_player[0].Reset();
        m_player[1].Reset();
    }
}

void RetroSpaceGame::HandleCollisions()
{
    // projectiles <-> planet
    if (m_planet.IsActive())
    {
        m_player[0].GetShip().GetWeapon().ProjectileCollide(m_planet);
        m_player[1].GetShip().GetWeapon().ProjectileCollide(m_planet);
    }

    // ships <-> powerups
    Powerup::Attributes *powerupAttr = m_powerupSystem.PowerupCollide(m_player[0].GetShip());
    if (powerupAttr)
        m_player[0].GetShip().ApplyPowerup(*powerupAttr);
    
    powerupAttr = m_powerupSystem.PowerupCollide(m_player[1].GetShip());
    if (powerupAttr)
        m_player[1].GetShip().ApplyPowerup(*powerupAttr);
    
    // ships <-> planet
    if (m_planet.IsActive())
    {
        if (m_player[0].GetShip().Collide(m_planet))
            m_player[0].GetShip().Hit(m_gameSettings.Values().ship.resources.shield.maxValue);
        if (m_player[1].GetShip().Collide(m_planet))
            m_player[1].GetShip().Hit(m_gameSettings.Values().ship.resources.shield.maxValue);
    }
    
    // projectiles <-> ships
    float dmg = m_player[1].GetShip().GetWeapon().ProjectileCollide(m_player[0].GetShip());
    if (dmg > 0.f)
        m_player[0].GetShip().Hit(dmg);

    dmg = m_player[0].GetShip().GetWeapon().ProjectileCollide(m_player[1].GetShip());
    if (dmg > 0.f)
        m_player[1].GetShip().Hit(dmg);

    // ship <-> ship
    if (m_player[1].GetShip().Collide(m_player[0].GetShip()))
    {
        m_player[0].GetShip().Hit(100.f);
        m_player[1].GetShip().Hit(100.f);
    }
}

void RetroSpaceGame::Draw()
{
    Game::Draw();
    
    Renderer *r = GetRenderer();
    
    // reset
    r->Clear();
    r->SetModelviewMatrix(Matrix());

    // space
    m_background.Draw(*r);
    m_planet.Draw(*r);   
    
    //ships
    m_player[0].GetShip().Draw(*r);
    m_player[1].GetShip().Draw(*r); 

    // powerups
    m_powerupSystem.Draw(*r);
    
    // text
    m_statusText.Draw(*r);    
    if (m_gameSettings.Values().showFps)
        m_textFps.Draw(*r);

    // player gui - texts, bars
    m_playerGUI[0].Draw(*r);
    m_playerGUI[1].Draw(*r);

    m_menu.Draw(*r);

    r->Flush();
    GetWindow()->SwapBuffers();
}

}