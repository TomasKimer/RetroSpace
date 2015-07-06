// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Menu.h
  *  @brief  Prace s menu.
  */

#pragma once

#include "GameObject.h"
#include "Shape.h"
#include "TextObject.h"
#include "Controls.h"
#include "Planet.h"
#include "Submenu.h"
#include <sstream>

namespace RetroSpace
{
    /**
     * Herni nabidka.
     */
    class Menu : public GameObject
    {
    public:
        /** sirka menu */
        static const int MENU_WIDTH = 350;
        
        /** vyska menu */
        static const int MENU_HEIGHT = 350;

        /**
         * Vracena volba v menu.
         */
        enum MenuResult
        {
            MR_NEW_GAME,
            MR_EXIT,
            MR_NONE
        };        

    public:        
        Menu(void);
        ~Menu(void);

        virtual void Draw(Renderer & renderer);
        virtual void SetOnResize(Size2i screenSize);

        std::string GetPlanetText();
        std::string GetControllerText(int playerNum);

        void SetKeysText(Submenu & submenu, int playerNum);
        void SetButtonsText(Submenu & submenu, int playerNum);

        virtual void SetValues(SpriteFont & font, Controls & controls, Planet & planet);

        MenuResult OnMenuSelect();       
        MenuResult PassKeyDown(KeyCode key);
        MenuResult PassMouseDown(Point2i curPos, BtnCode button);
        bool IsMouseOverSubmenu(Point2i curPos);        
        void PassMouseMove(Point2i curPos);

        bool IsActive() { return m_active; }
        void SetActive(bool active) { m_active = active; }

    private:
        bool m_active, m_gettingKey, m_gettingBtn;
        int m_selPlayer;
        float m_submnuSpacing, m_labelSpacing;
        
        Point2f m_submnStartPosCenterX, m_submnStartPosLeft;
        Vector2f m_submnuScale;
        Size2f m_menuSize;
        
        Controls::Action m_newMouseAction, m_newKeybAction;
        
        Submenu *m_actSubmnu;
        Submenu m_subMain, m_subCtrls, m_subKeys, m_subBtns;

        Shape m_backgndShape, m_gettingShape;
        TextObject m_menuLabel, m_gettingText;

        Controls *m_refControls;
        Planet *m_refPlanet;
    };
}
