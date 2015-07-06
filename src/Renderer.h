// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Renderer.h
  *  @brief  Zakladni rozhrani pro praci s vykreslovaci knihovnou.
  */

#pragma once

#include <iostream>
#include <vector>

#include "Color.h"
#include "Texture.h"
#include "SpriteFont.h"
#include "Vector2.h"
#include "Matrix.h"
#include "Shape.h"

namespace GameFramework
{
    /**
     * Baze pro vykreslovaci cast.
     */
    class Renderer
    {
    public:
        Renderer(void): m_rendererName("default") {}
        virtual ~Renderer(void) {}
    
        // init, destroy
        virtual void Create() = 0;    
        virtual void Initialize() = 0;
        virtual void Reinitialize() {}
    
        // viewport, clear
        virtual void SetViewport(Point2i start, Size2i size) = 0;
        virtual void Clear() = 0;
        virtual void Flush() = 0;
    
         // matrix
        virtual void GetModelviewMatrix(Matrix & matrix) = 0;
        virtual void SetModelviewMatrix(const Matrix & matrix) = 0;
        virtual void SetProjectionMatrix(const Matrix & matrix) = 0;
    
        // draw 2D
        virtual void DrawLine(Point2f start, Point2f end, float width = 1.f) = 0;
        virtual void DrawString(const std::string & text, const SpriteFont & font) = 0;
        virtual void DrawShape(const Shape & shape) = 0;
        virtual void DrawWireSphere(float r, int slices, int stacks, float wireWidth = 1.f) = 0;
    
        virtual void SetColor(const Color & color) = 0;
    
        // enable/disable
        virtual void SetBlending(bool enable) = 0;
        virtual void SetTexturing(bool enable) = 0;
        virtual void SetLineSmooth(bool enable) = 0;    
    
        // factory
        virtual Texture * CreateTexture() = 0;
        virtual SpriteFont * CreateSpriteFont() = 0;        
      
        Size2i GetViewportSize() const { return m_viewportSize; }
        virtual std::string GetRendererName() const { return m_rendererName; };
    
    protected:
        Size2i m_viewportSize;
        std::string m_rendererName;
    };
}