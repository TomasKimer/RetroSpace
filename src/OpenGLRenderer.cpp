// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   OpenGLRenderer.cpp
  *  @brief  Prace s OpenGL vykreslovaci knihovnou.
  */

#include "OpenGLRenderer.h"
#include "MathHelper.h"

namespace GameFramework
{

OpenGLRenderer::OpenGLRenderer(void): quadricObj(0)
{
    m_rendererName = "OpenGL";
}

OpenGLRenderer::~OpenGLRenderer(void)
{
    if (quadricObj)
         gluDeleteQuadric(quadricObj);
}

void OpenGLRenderer::Initialize()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);      // blending
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
}

void OpenGLRenderer::SetViewport(Point2i start, Size2i size)
{
    glViewport(start.x, start.y, size.x, size.y);
    m_viewportSize = size;
}

void OpenGLRenderer::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::Flush()
{
    glFlush();
}

void OpenGLRenderer::DrawShape(const Shape & shape)
{
    if (shape.GetStyle() == Shape::SS_LINE || shape.GetStyle() == Shape::SS_LINE_LOOP)
        glLineWidth(shape.GetLineWidth());
    
    // texture coords
    if (shape.GetTexCoordCount() == shape.GetVertexCount())
    {
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glTexCoordPointer(2, GL_FLOAT, 0, shape.GetTexCoordArray());
    }
    
    // color
    if (shape.GetColorCount() == shape.GetVertexCount())
    {
        glEnableClientState(GL_COLOR_ARRAY);
        glColorPointer(4, GL_FLOAT, 0, shape.GetColorArray());
    }

    //vertex
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, shape.GetVertexArray());
    
    // draw
    glDrawArrays(GetGLShapeStyle(shape.GetStyle()), 0, shape.GetVertexCount());
    
    // disable
    glDisableClientState(GL_VERTEX_ARRAY);
    if (shape.GetTexCoordCount() ==  shape.GetVertexCount())
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    if (shape.GetColorCount() == shape.GetVertexCount())
        glDisableClientState(GL_COLOR_ARRAY);
}

void OpenGLRenderer::DrawLine(Point2f start, Point2f end, float width)
{
    glLineWidth(width);

    glBegin(GL_LINES);
      glVertex2f(start.x, start.y);
      glVertex2f(end.x, end.y);
    glEnd();
}

void OpenGLRenderer::DrawString(const std::string & text, const SpriteFont & font)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    font.DrawString(text);
    glDisable(GL_TEXTURE_2D);
}

void OpenGLRenderer::DrawWireSphere(float r, int slices, int stacks, float wireWidth)
{
    if (quadricObj == 0)
    {
        quadricObj = gluNewQuadric();
        gluQuadricDrawStyle(quadricObj, GLU_LINE);
    }
    glLineWidth(wireWidth);
    gluSphere(quadricObj, r, slices, stacks);   
}

void OpenGLRenderer::SetColor(const Color & color)
{
    glColor4f(color.R(), color.G(), color.B(), color.A());
}

void OpenGLRenderer::PushMatrix()
{
    glPushMatrix();
}

void OpenGLRenderer::PopMatrix()
{
    glPopMatrix();
}

void OpenGLRenderer::GetModelviewMatrix(Matrix & matrix)
{
    float matrixArray[16];
    
    glGetFloatv(GL_MODELVIEW, matrixArray);
    matrix.SetArr(matrixArray);
}

void OpenGLRenderer::SetModelviewMatrix(const Matrix & matrix)
{
    glLoadMatrixf(matrix.GetArr());
}

void OpenGLRenderer::SetProjectionMatrix(const Matrix & matrix)
{
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(matrix.GetArr());
    glMatrixMode(GL_MODELVIEW);
}

GLenum OpenGLRenderer::GetGLShapeStyle(Shape::Style ss)
{
    switch (ss)
    {
        case Shape::SS_LINE:
            return GL_LINES;
            break;

        case Shape::SS_LINE_LOOP:
            return GL_LINE_LOOP;
            break;

        case Shape::SS_FILL:
            return GL_POLYGON;
            break;

        case Shape::SS_POINT:
            return GL_POINTS;
            break;
    }
    
    return 0;
}

void OpenGLRenderer::SetBlending(bool enable)
{
    if (enable)
        glEnable(GL_BLEND);
    else
        glDisable(GL_BLEND);
}

void OpenGLRenderer::SetTexturing(bool enable)
{
    if (enable)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
}

void OpenGLRenderer::SetLineSmooth(bool enable)
{
    if (enable)
        glEnable(GL_LINE_SMOOTH);
    else
        glDisable(GL_LINE_SMOOTH);
}

}
