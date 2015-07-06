// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Submenu.cpp
  *  @brief  Reprezentace jednoho podmenu v menu.
  */

#include "Submenu.h"

namespace RetroSpace
{

Submenu::Submenu(SubmenuID id): m_id(id), m_current(IID_FIRST), m_parent(0), m_border(5.f, -4.f)
{
    m_selShape.AddRectangle(Point2f(), Point2f());
    m_selShape.MakeArrays();        
}

Submenu::~Submenu(void)
{
}

void Submenu::Draw(Renderer & renderer)
{
    m_yPos = m_startPos.y;

    for (unsigned int i = 0; i < m_items.size(); i++)
    {
        m_items[i].SetPosition(Vector2f(m_startPos.x, m_yPos));
        m_items[i].SetCenterPoint(Vector2f(m_startPos.x, m_yPos));
        m_items[i].CenterTextX();
        
        m_items[i].Draw(renderer);

        if (static_cast<int>(i) == m_current)
        {
            m_selShape.EditRectangleVertices(Point2f(m_startPos.x-m_menuSize.x+m_border.x, m_yPos+m_border.y),
                                             Point2f(m_startPos.x+m_menuSize.x-m_border.x, m_yPos+m_items[i].GetHeight() - m_border.y));
            renderer.SetModelviewMatrix(Matrix());
            renderer.DrawShape(m_selShape);
        }

        m_yPos += m_items[i].GetHeight() + m_spacing;
    }

    m_height = m_yPos - m_startPos.y - m_spacing;
}

void Submenu::AddItem(const std::string & item)
{
    TextObject it;
    it.SetFont(*m_font);
    it.SetText(item);
    it.SetScale(m_scale);
    m_items.push_back(it);                
}

 void Submenu::Up()
 {
     m_current--;
     if (m_current < 0)
         m_current = static_cast<int>(m_items.size()) - 1;
 }
 
 void Submenu::Down()
 {
     m_current++;
     if (m_current >= static_cast<int>(m_items.size()))
         m_current = 0;
 }

 void Submenu::SelectByMouse(Point2i curPos)
 {
     for (unsigned int i = 0; i < m_items.size(); i++)
     {
         if (curPos.y > i*(m_items[0].GetHeight() + m_spacing) + m_spacing / m_border.y)
             m_current = i;
     }
 }

 Submenu::ItemID Submenu::Selected()
 {
     if (m_current == static_cast<int>(m_items.size()) - 1)
         return IID_LAST;
     else            
         return static_cast<ItemID>(m_current);        
 }

 void Submenu::SetValues(SpriteFont & font, const std::string & label, Vector2f scale,
                float spacingY, Size2f parentSize, Submenu * parent)
 {
     m_font = &font;
     m_label = label;
     m_scale = scale;
     m_spacing = spacingY;
     m_menuSize = parentSize;            
     m_parent = parent;
 }

}
