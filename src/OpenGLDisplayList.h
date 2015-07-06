// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   OpenGLDisplayList.h
  *  @brief  Prace s OpenGL display listem.
  */

#pragma once

#include "OpenGLPrerequisites.h"
#include "Vector2.h"
#include <string>

namespace GameFramework
{
    /**
     * Prace s display listem v OpenGL.
     */
    class OpenGLDisplayList
    {
    public:
        OpenGLDisplayList(void);
        ~OpenGLDisplayList(void);

        void Delete();
        
        void Generate(int range);
        void NewList(int offset);
        void EndList();

        void AddRectangle(Point2f start, Point2f end, Vector2f texStart, Vector2f texEnd);
        void Translate(float x, float y, float z);

        void ExecuteString(const std::string & str, int offset = 0) const;

    private:
        GLuint m_base;
        int m_range;
    };
}