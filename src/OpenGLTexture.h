// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   OpenGLTexture.h
  *  @brief  Konkretni prace s texturou pro OpenGL.
  */

#pragma once

#include "OpenGLPrerequisites.h"
#include "Texture.h"
#include <string>

namespace GameFramework
{
    /**
     * Reprezentace textury v OpenGL.
     */
    class OpenGLTexture : public Texture
    {
    public:
        OpenGLTexture(void);
        virtual ~OpenGLTexture(void);
    
        virtual void Load(const std::string & filename);
        virtual void Unload();
    
        virtual void Bind();
    
    private:
        GLuint m_name;
        bool m_created;
    };
}