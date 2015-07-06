// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   TextObject.h
  *  @brief  Zobrazovani textu.
  */

#pragma once

#include "GameObject.h"
#include "SpriteFont.h"
#include "Color.h"
#include <string>

namespace RetroSpace
{ 
    /**
     * Vypis textu na obrazovku.
     */
    class TextObject : public GameObject
    {
    public:
        TextObject();
        TextObject(SpriteFont & font, const std::string & text = "");
        virtual ~TextObject();
    
        virtual void Draw(Renderer & renderer);    
        virtual void Update(const GameTime & gameTime) {}
    
        void SetText(const std::string & text) { m_text = text; }
        void SetFont(SpriteFont & font) { m_font = &font; }
        void SetColor(const Color & color) { m_textColor = color; }
        void SetCenterPoint(Point2f centerPoint) { m_centerPoint = centerPoint; }
    
        void CenterTextX() { m_position.x = m_centerPoint.x - GetWidth()  / 2.f; }
        void CenterTextY() { m_position.y = m_centerPoint.y - GetHeight() / 2.f; }
        void CenterText()  { CenterTextX(); CenterTextY(); }
        
        float GetWidth() { return m_font ? m_font->StringWidth(m_text) * m_scale.x : 0; }
        float GetHeight() { return m_font ? m_font->StringHeight() * m_scale.y : 0; }
    
        Color GetColor() { return m_textColor; }
    
    protected:
        std::string m_text;
        Color m_textColor;
        SpriteFont *m_font;
        Point2f m_centerPoint;
    };
}