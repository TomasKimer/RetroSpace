// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Controls.cpp
  *  @brief  Sprava ovladani pro dva hrace.
  */

#include "Controls.h"

namespace RetroSpace
{

Controls::Controls(void)
{
}

Controls::~Controls(void)
{
}

int Controls::GetMousePlayer()
{
    for (int i = 0; i < 2; i++)
        if (m_playerCtrl[i]->ctrl == CTRL_MOUSE)
            return i;        
    return -1;
}

int Controls::MouseAction(const Mouse & m, Action action)  // unbuffered
{            
    int pl = GetMousePlayer();
    if (pl == -1)
        return -1;
    
    switch (action)
    {
        case ACT_ACCELERATE:
            if (m.IsBtnDown(m_playerCtrl[pl]->mouse.accel))
                return pl;
            break;

        case ACT_SHOOT:
            if (m.IsBtnDown(m_playerCtrl[pl]->mouse.shoot))
                return pl;
            break;
    }
    return -1;
}

void Controls::KeyboardAction(const Keyboard & k, Action action, bool & pl1, bool & pl2)  // unbuffered
{            
    pl1 = false; pl2 = false;
    bool pk1 = m_playerCtrl[0]->ctrl == CTRL_KEYBOARD;
    bool pk2 = m_playerCtrl[1]->ctrl == CTRL_KEYBOARD;
    
    switch (action)
    {
    case ACT_ACCELERATE:
        if (pk1 && k.IsKeyDown(m_playerCtrl[0]->keyb.accel))
            pl1 = true;
        if (pk2 && k.IsKeyDown(m_playerCtrl[1]->keyb.accel))
            pl2 = true;
        break;

    case ACT_SHOOT:
        if (pk1 && k.IsKeyDown(m_playerCtrl[0]->keyb.shoot))
            pl1 = true;
        if (pk2 && k.IsKeyDown(m_playerCtrl[1]->keyb.shoot))
            pl2 = true;
        break;

    case ACT_TURN_LEFT:
        if (pk1 && k.IsKeyDown(m_playerCtrl[0]->keyb.turnLeft))
            pl1 = true;
        if (pk2 && k.IsKeyDown(m_playerCtrl[1]->keyb.turnLeft))
            pl2 = true;
        break;

    case ACT_TURN_RIGHT:
        if (pk1 && k.IsKeyDown(m_playerCtrl[0]->keyb.turnRight))
            pl1 = true;
        if (pk2 && k.IsKeyDown(m_playerCtrl[1]->keyb.turnRight))
            pl2 = true;
        break;
    }
}

std::pair<Controls::Action, int> Controls::MouseAction(BtnCode btn)  // buffered
{
    int pl = GetMousePlayer();
    if (pl == -1)
        return std::make_pair(ACT_NONE, -1);
    
    if (btn == m_playerCtrl[pl]->mouse.transfer)
        return std::make_pair(ACT_TRANSFER, pl);
    else if (btn == m_playerCtrl[pl]->mouse.shoot)
        return std::make_pair(ACT_SHOOT, pl);

    return std::make_pair(ACT_NONE, -1);
}  

std::pair<Controls::Action, int> Controls::KeyboardAction(KeyCode key)  // buffered
{
    bool pk1 = m_playerCtrl[0]->ctrl == CTRL_KEYBOARD;
    bool pk2 = m_playerCtrl[1]->ctrl == CTRL_KEYBOARD;

    if (pk1 && key == m_playerCtrl[0]->keyb.transfer)
        return std::make_pair(ACT_TRANSFER, 0);
    else if (pk2 && key == m_playerCtrl[1]->keyb.transfer)
        return std::make_pair(ACT_TRANSFER, 1);
    else if (pk1 && key == m_playerCtrl[0]->keyb.shoot)
        return std::make_pair(ACT_SHOOT, 0);
    else if (pk2 && key == m_playerCtrl[1]->keyb.shoot)
        return std::make_pair(ACT_SHOOT, 1);

    return std::make_pair(ACT_NONE, -1);
}   

bool Controls::SwitchPlayerController(int pNum, bool force)
{
    if (m_playerCtrl[pNum]->ctrl == CTRL_MOUSE)
        m_playerCtrl[pNum]->ctrl = CTRL_KEYBOARD;
    else if (m_playerCtrl[pNum]->ctrl == CTRL_KEYBOARD)
    {
        int pNum2 = pNum == 0 ? 1 : 0;
        if (m_playerCtrl[pNum2]->ctrl == CTRL_MOUSE)
        {
            if (force)
            {
                m_playerCtrl[pNum2]->ctrl = CTRL_KEYBOARD;
                m_playerCtrl[pNum] ->ctrl = CTRL_MOUSE;
                return true;
            }
        }
        else
        {
            m_playerCtrl[pNum]->ctrl = CTRL_MOUSE;
        }
    }
    return false;  // controller forced
}

void Controls::SetDefaultKeyboardControls(int playerNum)
{
    m_playerCtrl[playerNum]->keyb = m_defaultPlayerCtrl[playerNum]->keyb;
}

void Controls::SetDefaultMouseControls(int playerNum)
{
    m_playerCtrl[playerNum]->mouse = m_defaultPlayerCtrl[playerNum]->mouse;
}

void Controls::EditActionButton(Action action, int playerNum, BtnCode newButton)
{
    switch (action)
    {
        case ACT_ACCELERATE:
            if (newButton == m_playerCtrl[playerNum]->mouse.shoot)
                m_playerCtrl[playerNum]->mouse.shoot = m_playerCtrl[playerNum]->mouse.accel;                    
            else if (newButton == m_playerCtrl[playerNum]->mouse.transfer)
                m_playerCtrl[playerNum]->mouse.transfer = m_playerCtrl[playerNum]->mouse.accel;
            
            m_playerCtrl[playerNum]->mouse.accel = newButton;
            break;

        case ACT_SHOOT:
            if (newButton == m_playerCtrl[playerNum]->mouse.accel)
                m_playerCtrl[playerNum]->mouse.accel = m_playerCtrl[playerNum]->mouse.shoot;                    
            else if (newButton == m_playerCtrl[playerNum]->mouse.transfer)
                m_playerCtrl[playerNum]->mouse.transfer = m_playerCtrl[playerNum]->mouse.shoot;
            
            m_playerCtrl[playerNum]->mouse.shoot = newButton;
            break;

        case ACT_TRANSFER:
            if (newButton == m_playerCtrl[playerNum]->mouse.accel)
                m_playerCtrl[playerNum]->mouse.accel = m_playerCtrl[playerNum]->mouse.transfer;  
            else if (newButton == m_playerCtrl[playerNum]->mouse.shoot)
                m_playerCtrl[playerNum]->mouse.shoot = m_playerCtrl[playerNum]->mouse.transfer;                 
            
            m_playerCtrl[playerNum]->mouse.transfer = newButton;
            break;
    }
}

void Controls::EditActionKey(Action action, int playerNum, KeyCode newKey)
{
    switch (action)
    {
        case ACT_ACCELERATE:
            if (newKey == m_playerCtrl[playerNum]->keyb.shoot)
                m_playerCtrl[playerNum]->keyb.shoot = m_playerCtrl[playerNum]->keyb.accel;                    
            else if (newKey == m_playerCtrl[playerNum]->keyb.turnLeft)
                m_playerCtrl[playerNum]->keyb.turnLeft = m_playerCtrl[playerNum]->keyb.accel; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.turnRight)
                m_playerCtrl[playerNum]->keyb.turnRight = m_playerCtrl[playerNum]->keyb.accel; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.transfer)
                m_playerCtrl[playerNum]->keyb.transfer = m_playerCtrl[playerNum]->keyb.accel;

            m_playerCtrl[playerNum]->keyb.accel = newKey;
            break;

        case ACT_SHOOT:
            if (newKey == m_playerCtrl[playerNum]->keyb.accel)
                m_playerCtrl[playerNum]->keyb.accel = m_playerCtrl[playerNum]->keyb.shoot;                    
            else if (newKey == m_playerCtrl[playerNum]->keyb.turnLeft)
                m_playerCtrl[playerNum]->keyb.turnLeft = m_playerCtrl[playerNum]->keyb.shoot; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.turnRight)
                m_playerCtrl[playerNum]->keyb.turnRight = m_playerCtrl[playerNum]->keyb.shoot; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.transfer)
                m_playerCtrl[playerNum]->keyb.transfer = m_playerCtrl[playerNum]->keyb.shoot;
            
            m_playerCtrl[playerNum]->keyb.shoot = newKey;
            break;

        case ACT_TURN_LEFT:
            if (newKey == m_playerCtrl[playerNum]->keyb.shoot)
                m_playerCtrl[playerNum]->keyb.shoot = m_playerCtrl[playerNum]->keyb.turnLeft;                    
            else if (newKey == m_playerCtrl[playerNum]->keyb.accel)
                m_playerCtrl[playerNum]->keyb.accel = m_playerCtrl[playerNum]->keyb.turnLeft; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.turnRight)
                m_playerCtrl[playerNum]->keyb.turnRight = m_playerCtrl[playerNum]->keyb.turnLeft; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.transfer)
                m_playerCtrl[playerNum]->keyb.transfer = m_playerCtrl[playerNum]->keyb.turnLeft;
            
            m_playerCtrl[playerNum]->keyb.turnLeft = newKey;
            break;

        case ACT_TURN_RIGHT:
            if (newKey == m_playerCtrl[playerNum]->keyb.shoot)
                m_playerCtrl[playerNum]->keyb.shoot = m_playerCtrl[playerNum]->keyb.turnRight;                    
            else if (newKey == m_playerCtrl[playerNum]->keyb.turnLeft)
                m_playerCtrl[playerNum]->keyb.turnLeft = m_playerCtrl[playerNum]->keyb.turnRight; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.accel)
                m_playerCtrl[playerNum]->keyb.accel = m_playerCtrl[playerNum]->keyb.turnRight; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.transfer)
                m_playerCtrl[playerNum]->keyb.transfer = m_playerCtrl[playerNum]->keyb.turnRight;
            
            m_playerCtrl[playerNum]->keyb.turnRight = newKey;
            break;

        case ACT_TRANSFER:
            if (newKey == m_playerCtrl[playerNum]->keyb.shoot)
                m_playerCtrl[playerNum]->keyb.shoot = m_playerCtrl[playerNum]->keyb.transfer;                    
            else if (newKey == m_playerCtrl[playerNum]->keyb.turnLeft)
                m_playerCtrl[playerNum]->keyb.turnLeft = m_playerCtrl[playerNum]->keyb.transfer; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.turnRight)
                m_playerCtrl[playerNum]->keyb.turnRight = m_playerCtrl[playerNum]->keyb.transfer; 
            else if (newKey == m_playerCtrl[playerNum]->keyb.accel)
                m_playerCtrl[playerNum]->keyb.accel = m_playerCtrl[playerNum]->keyb.transfer;
            
            m_playerCtrl[playerNum]->keyb.transfer = newKey;
            break;
    }
}

void Controls::SetPlayerControls(PlayerControls & pl1, PlayerControls & pl2, PlayerControls & defaultPl1, PlayerControls & defaultPl2)
{
    m_playerCtrl[0] = &pl1;
    m_playerCtrl[1] = &pl2;

    m_defaultPlayerCtrl[0] = &defaultPl1;
    m_defaultPlayerCtrl[1] = &defaultPl2;
}
void Controls::SetInputDevices(Keyboard & keyb, Mouse & mouse)
{
    m_refKeyb = &keyb;
    m_refMouse = &mouse;
}

}
