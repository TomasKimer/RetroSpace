// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   SpriteFont.h
  *  @brief  Prace s pismem z textury.
  */

#pragma once

#include "Texture.h"
#include "Vector2.h"
#include <string>

namespace GameFramework
{
    /**
     * Baze pro praci s pismem z textury.
     */
    class SpriteFont
    {
    public:
        SpriteFont(void): m_texture(0) {}
        virtual ~SpriteFont(void) {}
    
        virtual void DrawString(const std::string & text) const = 0;        
        virtual void Create(const std::string & filename, Size2i glyphCount, Size2i glyphSize,
                            int glyphSpacing = 0, Size2i defaultGlyphSize = Size2i(16, 16)) = 0;
    
        int StringWidth(const std::string & text) const
        {
            int len = static_cast<int>(text.length());
            return (len * m_defaultGlyphSize.x) + ((len - 1) * m_glyphSpacing);
        };
        int StringHeight() const { return m_defaultGlyphSize.y; }
    
    protected:
        Texture *m_texture;
        Size2i m_glyphSize, m_defaultGlyphSize;
        int m_glyphSpacing;
    };
}