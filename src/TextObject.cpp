// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   TextObject.cpp
  *  @brief  Zobrazovani textu.
  */

#include "TextObject.h"

namespace RetroSpace
{

TextObject::TextObject(): m_font(0)
{
}

TextObject::TextObject(SpriteFont & font, const std::string & text)
{
    SetFont(font);
    SetText(text);
}

TextObject::~TextObject()
{
}

void TextObject::Draw(Renderer & renderer)
{
    renderer.SetColor(m_textColor);
    ApplyTransformation(renderer);
    if (m_font)
        renderer.DrawString(m_text, *m_font);
}

}