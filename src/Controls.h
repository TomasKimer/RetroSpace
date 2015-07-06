// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Controls.h
  *  @brief  Sprava ovladani pro dva hrace.
  */

#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include <utility>

using namespace GameFramework;

namespace RetroSpace
{
    /**
     * Sprava ovladani.
     */
    class Controls
    {
    public:
        /**
         * Mozne ovladane akce.
         */
        enum Action
        {
            ACT_ACCELERATE,
            ACT_TURN_LEFT,
            ACT_TURN_RIGHT,
            ACT_SHOOT,
            ACT_TRANSFER,
            ACT_NONE
        };

        /**
         * Ovladac.
         */
        enum Controller
        {
            CTRL_KEYBOARD,
            CTRL_MOUSE,
            CTRL_NONE
        };

        /**
         * Nastaveni tlacitek mysi.
         */
        struct MouseControls
        {
            BtnCode accel, shoot, transfer;
        };

        /**
         * Nastaveni klaves.
         */
        struct KeyboardControls
        {
            KeyCode accel, shoot, turnLeft, turnRight, transfer;
        };

        /**
         * Celkove nastaveni jednoho hrace.
         */
        struct PlayerControls
        {
            Controller ctrl;
            KeyboardControls keyb;
            MouseControls mouse;
        };

    public:
        Controls(void);
        ~Controls(void);
        
        int GetMousePlayer();

        // unbuffered
        int MouseAction(const Mouse & m, Action action);
        void KeyboardAction(const Keyboard & k, Action action, bool & pl1, bool & pl2);

        // buffered
        std::pair<Action, int> MouseAction(BtnCode btn);
        std::pair<Action, int> KeyboardAction(KeyCode key);

        std::string GetKeyAsString(KeyCode kc) { return m_refKeyb->GetAsString(kc); }
        std::string GetBtnAsString(BtnCode bc) { return m_refMouse->GetAsString(bc); }

        bool SwitchPlayerController(int pNum, bool force = true);

        void SetDefaultKeyboardControls(int playerNum);
        void SetDefaultMouseControls(int playerNum);

        void EditActionButton(Action action, int playerNum, BtnCode newButton);
        void EditActionKey(Action action, int playerNum, KeyCode newKey);

        void SetPlayerControls(PlayerControls & pl1, PlayerControls & pl2, PlayerControls & defaultPl1, PlayerControls & defaultPl2);
        void SetInputDevices(Keyboard & keyb, Mouse & mouse);

        PlayerControls & GetPlayerControls(int num) { return *m_playerCtrl[num % 2]; }

    private:
        PlayerControls *m_playerCtrl[2];
        PlayerControls *m_defaultPlayerCtrl[2];
        Keyboard *m_refKeyb;
        Mouse *m_refMouse;
    };
}

