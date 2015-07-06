// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   OpenGLDisplayList.cpp
  *  @brief  Prace s OpenGL display listem.
  */

#include "OpenGLDisplayList.h"

namespace GameFramework
{

OpenGLDisplayList::OpenGLDisplayList(void): m_range(0)
{
}

OpenGLDisplayList::~OpenGLDisplayList(void)
{
    Delete();
}

void OpenGLDisplayList::Delete()
{
    if (m_range > 0)
    {
        glDeleteLists(m_base, m_range);
        m_range = 0;
    }
}

void OpenGLDisplayList::Generate(int range)
{
    m_base = glGenLists(range);
    m_range = range;
}

void OpenGLDisplayList::NewList(int offset)
{
    glNewList(m_base + offset, GL_COMPILE);
}

void OpenGLDisplayList::EndList()
{
    glEndList();
}

void OpenGLDisplayList::AddRectangle(Point2f start, Point2f end, Vector2f texStart, Vector2f texEnd)
{
    glBegin(GL_QUADS);
        
        glTexCoord2f(texStart.x, texStart.y);
        glVertex2f(start.x, start.y);

        glTexCoord2f(texEnd.x, texStart.y);
        glVertex2f(end.x, start.y);
        
        glTexCoord2f(texEnd.x, texEnd.y);
        glVertex2f(end.x, end.y);
        
        glTexCoord2f(texStart.x, texEnd.y);
        glVertex2f(start.x, end.y);

    glEnd();
}

void OpenGLDisplayList::Translate(float x, float y, float z)
{
    glTranslatef(x, y, z);
}

void OpenGLDisplayList::ExecuteString(const std::string & str, int offset) const
{
    glListBase(m_base + offset);    
    glCallLists(str.length(), GL_UNSIGNED_BYTE, str.c_str());
}

}
