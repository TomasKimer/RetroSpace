// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Menu.cpp
  *  @brief  Prace s menu.
  */

#include "Menu.h"

namespace RetroSpace
{

Menu::Menu(void): m_active(false), m_selPlayer(0), m_submnuScale(1.0f, 1.4f), m_submnuSpacing(20.f), m_labelSpacing(10.f),
                  m_newMouseAction(Controls::ACT_NONE), m_newKeybAction(Controls::ACT_NONE),
                  m_subMain(Submenu::SUB_MAIN), m_subCtrls(Submenu::SUB_CONTROLS), m_subKeys(Submenu::SUB_KEYS), m_subBtns(Submenu::SUB_BTNS)
{
    m_menuSize = Size2f(MENU_WIDTH / 2.f, MENU_HEIGHT / 2.f);
    
    m_backgndShape.AddRectangle(-m_menuSize, m_menuSize);
    m_backgndShape.MakeArrays();

    m_gettingShape.SetStyle(Shape::SS_FILL);
    m_gettingShape.AddRectangle(Point2f(-80.f, -25.f), Point2f(80.f, 25.f));  // Press key/btn rectangle
    m_gettingShape.MakeArrays();

    m_actSubmnu = &m_subMain;
}

Menu::~Menu(void)
{
}

void Menu::Draw(Renderer & renderer)
{
    if (!m_active)
        return;
    
    ApplyTransformation(renderer);
    renderer.SetBlending(false);
    
    renderer.SetColor(Color(0.05f, 0.05f, 0.05f));
    m_backgndShape.SetStyle(Shape::SS_FILL);
    renderer.DrawShape(m_backgndShape);
    
    renderer.SetLineSmooth(false);
    renderer.SetColor(Color::Gray());
    m_backgndShape.SetStyle(Shape::SS_LINE_LOOP);
    renderer.DrawShape(m_backgndShape);
    renderer.DrawLine(Point2f(-m_menuSize.x, -m_menuSize.y + m_menuLabel.GetHeight() + m_labelSpacing * 2.f),
                      Point2f( m_menuSize.x, -m_menuSize.y + m_menuLabel.GetHeight() + m_labelSpacing * 2.f));        

    renderer.SetBlending(true);

    m_menuLabel.SetText(m_actSubmnu->GetLabel());
    m_menuLabel.CenterTextX();
    m_menuLabel.Draw(renderer);
    
    m_actSubmnu->Draw(renderer);

    if (m_newKeybAction != Controls::ACT_NONE || m_newMouseAction != Controls::ACT_NONE)
    {
        ApplyTransformation(renderer);
        renderer.SetBlending(false);
        renderer.SetColor(Color(0.2f,0.2f,0.2f));
        renderer.DrawShape(m_gettingShape);

        renderer.SetBlending(true);
        if (m_newKeybAction != Controls::ACT_NONE)
            m_gettingText.SetText("Press key");
        else if (m_newMouseAction != Controls::ACT_NONE)
            m_gettingText.SetText("Press btn");
        m_gettingText.CenterText();
        m_gettingText.Draw(renderer);
    }

    renderer.SetLineSmooth(true);

}

void Menu::SetOnResize(Size2i screenSize)
{            
    GameObject::SetOnResize(screenSize);
    m_position = static_cast<Vector2f>(screenSize) / 2.f;

    m_menuLabel.SetPosition(Vector2f(m_position.x, m_position.y - m_menuSize.y + m_labelSpacing));
    m_menuLabel.SetCenterPoint(m_menuLabel.GetPosition()); 
    m_gettingText.SetCenterPoint(m_position);

    m_submnStartPosCenterX = Point2f(m_position.x, m_position.y - m_menuSize.y + m_labelSpacing * 2.f + 
                                     m_submnuSpacing / 2.f + m_menuLabel.GetHeight());
    m_submnStartPosLeft = Point2f(m_submnStartPosCenterX.x - m_menuSize.y + m_subMain.GetBorder().x,
                                  m_submnStartPosCenterX.y + m_subMain.GetBorder().y);

    m_subMain .SetStartPos(m_submnStartPosCenterX);
    m_subCtrls.SetStartPos(m_submnStartPosCenterX);
    m_subKeys .SetStartPos(m_submnStartPosCenterX);
    m_subBtns .SetStartPos(m_submnStartPosCenterX);
}

std::string Menu::GetPlanetText()
{
    std::string activeStatus = "off", gravityStatus = "off";
    
    if (m_refPlanet->IsActive())
    {
        activeStatus = "on";
        if (m_refPlanet->HasGravity())
            gravityStatus = "on";
    }
    return std::string("Planet:" + activeStatus + "," + gravityStatus);
}

std::string Menu::GetControllerText(int playerNum)
{
    std::string controller;
    
    if (m_refControls->GetPlayerControls(playerNum).ctrl == Controls::CTRL_KEYBOARD)
        controller = "Keyboard";
    else if (m_refControls->GetPlayerControls(playerNum).ctrl == Controls::CTRL_MOUSE)
        controller = "Mouse";
    else
        controller = "unsupported";
    
    std::stringstream ss;
    ss << playerNum + 1;

    return std::string("Player " + ss.str() + ": " + controller);
}

void Menu::SetKeysText(Submenu & submenu, int playerNum)
{
    submenu.EditItem(Submenu::IID_FIRST, std::string("Shoot: ")    +
        m_refControls->GetKeyAsString(m_refControls->GetPlayerControls(playerNum).keyb.shoot));
    submenu.EditItem(Submenu::IID_SECOND, std::string("Accel: ")   +
        m_refControls->GetKeyAsString(m_refControls->GetPlayerControls(playerNum).keyb.accel));
    submenu.EditItem(Submenu::IID_THIRD, std::string("Left: " )    +
        m_refControls->GetKeyAsString(m_refControls->GetPlayerControls(playerNum).keyb.turnLeft));
    submenu.EditItem(Submenu::IID_FOURTH, std::string("Right: ")   +
        m_refControls->GetKeyAsString(m_refControls->GetPlayerControls(playerNum).keyb.turnRight));
    submenu.EditItem(Submenu::IID_FIFTH, std::string("Transfer: ") +
        m_refControls->GetKeyAsString(m_refControls->GetPlayerControls(playerNum).keyb.transfer));
}

void Menu::SetButtonsText(Submenu & submenu, int playerNum)
{
    submenu.EditItem(Submenu::IID_FIRST,  std::string("Shoot: ") +
        m_refControls->GetBtnAsString(m_refControls->GetPlayerControls(playerNum).mouse.shoot));
    submenu.EditItem(Submenu::IID_SECOND, std::string("Accel: ") +
        m_refControls->GetBtnAsString(m_refControls->GetPlayerControls(playerNum).mouse.accel));
    submenu.EditItem(Submenu::IID_THIRD,  std::string("Transfer: ") +
        m_refControls->GetBtnAsString(m_refControls->GetPlayerControls(playerNum).mouse.transfer));
}

void Menu::SetValues(SpriteFont & font, Controls & controls, Planet & planet)
{
    m_menuLabel.SetFont(font);
    m_menuLabel.SetScale(m_submnuScale);
    m_gettingText.SetFont(font);

    m_refControls = &controls;
    m_refPlanet = &planet;

    m_subMain.SetValues(font, "Main menu", m_submnuScale, m_submnuSpacing, m_menuSize, 0);
    m_subMain.AddItem("Return to game");
    m_subMain.AddItem("New game");
    m_subMain.AddItem(GetPlanetText());
    m_subMain.AddItem("Controls");
    m_subMain.AddItem("Exit game");

    m_subCtrls.SetValues(font, "Controls", m_submnuScale, m_submnuSpacing, m_menuSize, &m_subMain);
    m_subCtrls.AddItem(GetControllerText(0));
    m_subCtrls.AddItem(GetControllerText(1));
    m_subCtrls.AddItem("Set Pl.1 Keys");
    m_subCtrls.AddItem("Set Pl.2 Keys");
    m_subCtrls.AddItem("Set Pl.1 Buttons");
    m_subCtrls.AddItem("Set Pl.2 Buttons");
    m_subCtrls.AddItem("Back");

    m_subKeys.SetValues(font, "Player n Keys", m_submnuScale, m_submnuSpacing, m_menuSize, &m_subCtrls);
    m_subKeys.AddItem("Shoot: ");
    m_subKeys.AddItem("Accel: ");
    m_subKeys.AddItem("Left: ");
    m_subKeys.AddItem("Right: ");
    m_subKeys.AddItem("Transfer: ");
    m_subKeys.AddItem("Reset to defaults");
    m_subKeys.AddItem("Back");

    m_subBtns.SetValues(font, "Player 1 Buttons", m_submnuScale, m_submnuSpacing, m_menuSize, &m_subCtrls);
    m_subBtns.AddItem("Shoot: ");
    m_subBtns.AddItem("Accel: ");
    m_subBtns.AddItem("Transfer: ");
    m_subBtns.AddItem("Reset to defaults");
    m_subBtns.AddItem("Back");
}

Menu::MenuResult Menu::OnMenuSelect()
{
    // Main Menu
    if (m_actSubmnu->Id() == Submenu::SUB_MAIN)
    {
        if (m_actSubmnu->Selected() == Submenu::IID_FIRST)          // Return to game
            m_active = false;
        else if (m_actSubmnu->Selected() == Submenu::IID_SECOND)    // New game
        {
            m_active = false;
            return MR_NEW_GAME;
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_THIRD)     // Planet
        {
            if (m_refPlanet->IsActive())
            {
                if (m_refPlanet->HasGravity())
                    m_refPlanet->SetHasGravity(false);
                else
                    m_refPlanet->SetActive(false);
            }
            else
            {
                m_refPlanet->SetActive(true);
                m_refPlanet->SetHasGravity(true);
            }                            
            m_actSubmnu->EditItem(Submenu::IID_THIRD, GetPlanetText());
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_FOURTH)    // Controls
            m_actSubmnu = &m_subCtrls;
        else if (m_actSubmnu->Selected() == Submenu::IID_LAST)      // Exit game
            return MR_EXIT;
    }
    // Controls Menu
    else if (m_actSubmnu->Id() == Submenu::SUB_CONTROLS)
    {
        if (m_actSubmnu->Selected() == Submenu::IID_FIRST)          // Player 1: Controller
        {
            if (m_refControls->SwitchPlayerController(0))
                m_actSubmnu->EditItem(Submenu::IID_SECOND, GetControllerText(1));
            m_actSubmnu->EditItem(Submenu::IID_FIRST, GetControllerText(0));                            
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_SECOND)    // Player 2: Controller
        {
            if (m_refControls->SwitchPlayerController(1))
                m_actSubmnu->EditItem(Submenu::IID_FIRST, GetControllerText(0));
            m_actSubmnu->EditItem(Submenu::IID_SECOND, GetControllerText(1)); 
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_THIRD)     // Set Pl1 Keys
        {
            m_actSubmnu = &m_subKeys;
            m_selPlayer = 0;
            m_actSubmnu->EditLabel("Player 1 Keys");
            SetKeysText(*m_actSubmnu, m_selPlayer);
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_FOURTH)    // Set Pl2 Keys
        {
            m_actSubmnu = &m_subKeys;
            m_selPlayer = 1;
            m_actSubmnu->EditLabel("Player 2 Keys");
            SetKeysText(*m_actSubmnu, m_selPlayer);
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_FIFTH)     // Set Pl1 Buttons
        {
            m_actSubmnu = &m_subBtns;
            m_selPlayer = 0;
            m_actSubmnu->EditLabel("Player 1 Buttons");
            SetButtonsText(*m_actSubmnu, m_selPlayer);
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_SIXTH)     // Set Pl2 Buttons
        {
            m_actSubmnu = &m_subBtns;
            m_selPlayer = 1;
            m_actSubmnu->EditLabel("Player 2 Buttons");
            SetButtonsText(*m_actSubmnu, m_selPlayer);
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_LAST)      // Back
            m_actSubmnu = &m_subMain;
    }
    // Set Player Keys
    else if (m_actSubmnu->Id() == Submenu::SUB_KEYS)
    {
        if (m_actSubmnu->Selected() == Submenu::IID_FIRST)          // Shoot
        {
            m_newKeybAction = Controls::ACT_SHOOT;                    
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_SECOND)    // Accelerate
        {
            m_newKeybAction = Controls::ACT_ACCELERATE;                
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_THIRD)     // Turn Left
        {
            m_newKeybAction = Controls::ACT_TURN_LEFT;              
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_FOURTH)    // Turn Right
        {
            m_newKeybAction = Controls::ACT_TURN_RIGHT;                   
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_FIFTH)     // Transfer
        {
            m_newKeybAction = Controls::ACT_TRANSFER;                 
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_SIXTH)     // Reset to Defaults
        {
            m_refControls->SetDefaultKeyboardControls(m_selPlayer);
            SetKeysText(*m_actSubmnu, m_selPlayer);
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_LAST)
            m_actSubmnu = &m_subCtrls;
    }
    // Set Player Buttons
    else if (m_actSubmnu->Id() == Submenu::SUB_BTNS)
    {
        if (m_actSubmnu->Selected() == Submenu::IID_FIRST)          // Shoot
        {
            m_newMouseAction = Controls::ACT_SHOOT;
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_SECOND)    // Accelerate
        {
            m_newMouseAction = Controls::ACT_ACCELERATE;
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_THIRD)     // Transfer
        {
            m_newMouseAction = Controls::ACT_TRANSFER;
        }
        else if (m_actSubmnu->Selected() == Submenu::IID_FOURTH)   // Reset to Defaults
        {
            m_refControls->SetDefaultMouseControls(m_selPlayer);
            SetButtonsText(*m_actSubmnu, m_selPlayer);
        }
        if (m_actSubmnu->Selected() == Submenu::IID_LAST)
            m_actSubmnu = &m_subCtrls;
    }
    return MR_NONE;
}

Menu::MenuResult Menu::PassKeyDown(KeyCode key)
{
    if (m_newMouseAction != Controls::ACT_NONE)
    {
        if (key == KC_ESCAPE)
            m_newMouseAction = Controls::ACT_NONE;
        return MR_NONE;
    }

    if (m_newKeybAction != Controls::ACT_NONE)
    {
        if (key == KC_ESCAPE)
        {
            m_newKeybAction = Controls::ACT_NONE;
            return MR_NONE;
        }

        m_refControls->EditActionKey(m_newKeybAction, m_selPlayer, key);
        SetKeysText(*m_actSubmnu, m_selPlayer);
        m_newKeybAction = Controls::ACT_NONE;
        return MR_NONE;
    }            
    
    switch (key)
    {
        case KC_ESCAPE:
            if (m_actSubmnu->Id() == Submenu::SUB_MAIN)
                m_active = false;
            else if (m_actSubmnu->GetParent() != 0)
                m_actSubmnu = m_actSubmnu->GetParent();
            break;

        case KC_RETURN:
            return OnMenuSelect();
            break;

        case KC_DOWN:
            m_actSubmnu->Down();
            break;

        case KC_UP:
            m_actSubmnu->Up();
            break;
    } 
    return MR_NONE;        
}

Menu::MenuResult Menu::PassMouseDown(Point2i curPos, BtnCode button)
{
    if (m_newKeybAction != Controls::ACT_NONE)
        return MR_NONE;

    if (m_newMouseAction != Controls::ACT_NONE)
    {
        m_refControls->EditActionButton(m_newMouseAction, m_selPlayer, button);
        SetButtonsText(*m_actSubmnu, m_selPlayer);
        m_newMouseAction = Controls::ACT_NONE;
        return MR_NONE;
    }            
    
    if (!IsMouseOverSubmenu(curPos))
        return MR_NONE;
    
    switch (button)
    {
        case BC_LEFT:
            return OnMenuSelect();
    }            
    return MR_NONE;        
}

bool Menu::IsMouseOverSubmenu(Point2i curPos)
{
    float left = m_submnStartPosLeft.x;
    float top = m_submnStartPosLeft.y;
    float right = m_submnStartPosCenterX.x + m_menuSize.x - m_subMain.GetBorder().x;
    float bottom = top + m_actSubmnu->GetHeight() - m_subMain.GetBorder().y * 2.f;

    if (curPos.x > left && curPos.x < right && curPos.y > top && curPos.y < bottom)
        return true;
    return false;
}

void Menu::PassMouseMove(Point2i curPos)
{
    if (m_newKeybAction != Controls::ACT_NONE || m_newMouseAction != Controls::ACT_NONE)
        return;            
    
    if (IsMouseOverSubmenu(curPos))
    {
        curPos -= static_cast<Size2i>(m_submnStartPosLeft);
        m_actSubmnu->SelectByMouse(curPos);        
    }        
}


}
