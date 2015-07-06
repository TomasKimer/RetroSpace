// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   OpenGLTexture.cpp
  *  @brief  Konkretni prace s texturou knihovny OpenGL.
  */

#include "OpenGLTexture.h"
#include "ImageFactory.h"
#include "Log.h"
#include <stdexcept>

namespace GameFramework
{

OpenGLTexture::OpenGLTexture(void): m_created(false)
{
}

OpenGLTexture::~OpenGLTexture(void)
{
    Unload();    
}

void OpenGLTexture::Load(const std::string & filename)
{
    Unload();

    Image *image = ImageFactory::CreateImage(filename);    
    image->Load(filename);
    image->ConvertBGRtoRGB();

    m_size = image->GetSize();
    m_bpp = image->GetBPP();

    glGenTextures(1, &m_name);
    glBindTexture(GL_TEXTURE_2D, m_name);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, m_size.x, m_size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, image->GetBitmap());

    delete image;

    m_created = true;
}

void OpenGLTexture::Unload()
{    
    if (m_created)
    {
        glDeleteTextures(1, &m_name);
        m_created = false;
    }
}

void OpenGLTexture::Bind()
{
    if (m_created)
        glBindTexture(GL_TEXTURE_2D, m_name);    
}

}
