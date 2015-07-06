// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   OpenGLSpriteFont.cpp
  *  @brief  Konkretni prace s pismem z textury pro OpenGL.
  */

#include "OpenGLSpriteFont.h"
#include "OpenGLTexture.h"

namespace GameFramework
{

OpenGLSpriteFont::OpenGLSpriteFont(void)
{
}

OpenGLSpriteFont::~OpenGLSpriteFont(void)
{
    if (m_texture)
        delete m_texture;
}

void OpenGLSpriteFont::Create(const std::string & filename, Size2i glyphCount, Size2i glyphSize, int glyphSpacing, Size2i defaultGlyphSize)
{
    m_texture = new OpenGLTexture();
    m_texture->Load(filename);

    m_dispList.Generate(glyphCount.x * glyphCount.y);
    m_texture->Bind();    

    float tmpX = 1.f / glyphCount.x;
    float tmpY = 1.f / glyphCount.y;
    
    for (int y = 0; y < glyphCount.y; y++)
    {
        for (int x = 0; x < glyphCount.x; x++)
        {
            float cx = static_cast<float>(x) / glyphCount.x;
            float cy = static_cast<float>(y) / glyphCount.y;       

            m_dispList.NewList(y * glyphCount.y + x);
            m_dispList.AddRectangle(Point2f(0.f, 0.f), static_cast<Point2f>(defaultGlyphSize),
                                    Vector2f(cx, 1.f - cy), Vector2f(cx + tmpX, 1.f - cy - tmpY));

            m_dispList.Translate(static_cast<float>(defaultGlyphSize.x + glyphSpacing), 0.0f, 0.0f);
            m_dispList.EndList();
        }
    }

    m_glyphSize = glyphSize;
    m_glyphSpacing = glyphSpacing;
    m_defaultGlyphSize = defaultGlyphSize;
}

void OpenGLSpriteFont::DrawString(const std::string & text) const
{
    m_texture->Bind();
    m_dispList.ExecuteString(text, -32);
}

}