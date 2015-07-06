// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Submenu.h
  *  @brief  Reprezentace jednoho podmenu v menu.
  */

#pragma once

#include <vector>
#include "TextObject.h"
#include "Shape.h"

namespace RetroSpace
{
    /**
     * Podmenu pro menu.
     */
    class Submenu : public IDrawableObject
    {
    public:
        /**
         * Identifikace.
         */
        enum SubmenuID
        {
            SUB_MAIN,
            SUB_CONTROLS,
            SUB_KEYS,
            SUB_BTNS
        };

        /**
         * Vybrana polozka.
         */
        enum ItemID
        {
            IID_FIRST = 0,
            IID_SECOND,
            IID_THIRD,
            IID_FOURTH,
            IID_FIFTH,
            IID_SIXTH,
            IID_SEVENTH,
            IID_EIGHTH,
            IID_NINTH,
            IID_TENTH,
            IID_LAST,
        };

    public:
        Submenu(SubmenuID id);
        ~Submenu(void);

        virtual void Draw(Renderer & renderer);
        
        void AddItem(const std::string & item);
        void EditItem(ItemID item, const std::string & newText) { m_items[item].SetText(newText); }
        void EditLabel(const std::string & label) {  m_label = label; }

        void Up();    
        void Down();
        void SelectByMouse(Point2i curPos);
        ItemID Selected();

        void SetValues(SpriteFont & font, const std::string & label, Vector2f scale,
                       float spacingY, Size2f parentSize, Submenu * parent = 0);
        
        void SetStartPos(Vector2f pos) { m_startPos = pos; }
        float GetHeight() { return m_height; }
        Size2i GetBorder() { return m_border; }
        
        std::string & GetLabel() { return m_label; }
        SubmenuID Id() { return m_id; }
        Submenu * GetParent() { return m_parent; }
    
    private:
        std::vector<TextObject> m_items;
        Vector2f m_startPos, m_scale;
        float m_yPos, m_spacing, m_height;
        SpriteFont *m_font;
        SubmenuID m_id;
        std::string m_label;
        int m_current;
        Size2f m_menuSize, m_border;
        Shape m_selShape;
        Submenu *m_parent;
    };
}