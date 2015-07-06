// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   OpenGLSpriteFont.h
  *  @brief  Konkretni prace s pismem z textury pro OpenGL.
  */

#pragma once

#include "OpenGLPrerequisites.h"
#include "OpenGLDisplayList.h"
#include "Texture.h"
#include "SpriteFont.h"
#include <string>

namespace GameFramework
{
    /**
     * Pismo z textury v OpenGL.
     */
    class OpenGLSpriteFont : public SpriteFont
    {
    public:
        OpenGLSpriteFont(void);
        virtual ~OpenGLSpriteFont(void);
    
        virtual void DrawString(const std::string & text) const;
        virtual void Create(const std::string & filename, Size2i glyphCount, Size2i glyphSize, int glyphSpacing = 0, Size2i defaultGlyphSize = Size2i(16, 16));
        
    private:
        OpenGLDisplayList m_dispList;
    };
}

