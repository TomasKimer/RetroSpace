// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   OpenGLRenderer.h
  *  @brief  Prace s OpenGL vykreslovaci knihovnou.
  */

#pragma once

#include "OpenGLPrerequisites.h"
#include "OpenGLTexture.h"
#include "OpenGLSpriteFont.h"
#include "Renderer.h"

namespace GameFramework
{
    /**
     * Vykreslovaci cast pomoci knihovny OpenGL.
     */
    class OpenGLRenderer : public Renderer
    {
    public:
        OpenGLRenderer(void);
        virtual ~OpenGLRenderer(void);
    
        // init, destroy
        virtual void Create() {}
        virtual void Initialize();
    
        // viewport, clear
        virtual void SetViewport(Point2i start, Size2i size);
        virtual void Clear();
        virtual void Flush();
    
        // matrix
        virtual void GetModelviewMatrix(Matrix & matrix);
        virtual void SetModelviewMatrix(const Matrix & matrix);
        virtual void SetProjectionMatrix(const Matrix & matrix);
        virtual void PushMatrix();
        virtual void PopMatrix();
    
        // draw
        virtual void DrawLine(Point2f start, Point2f end, float width = 1.f);
        virtual void DrawString(const std::string & text, const SpriteFont & font);
        virtual void DrawShape(const Shape & shape);
        virtual void DrawWireSphere(float r, int slices, int stacks, float wireWidth = 1.f);    
    
        virtual void SetColor(const Color & color);
    
        // enable/disable
        virtual void SetBlending(bool enable);
        virtual void SetTexturing(bool enable);
        virtual void SetLineSmooth(bool enable);
    
        // factory
        virtual Texture * CreateTexture() { return new OpenGLTexture(); }
        virtual SpriteFont * CreateSpriteFont() { return new OpenGLSpriteFont(); }
    
    private:
        GLenum GetGLShapeStyle(Shape::Style ss);
        GLUquadricObj *quadricObj;
    };
}

