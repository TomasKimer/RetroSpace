// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   GameObject.h
  *  @brief  Zakladni herni objekt.
  */

#pragma once

#include "IBasicGameObject.h"
#include "Vector2.h"
#include "Matrix.h"

using namespace GameFramework;

namespace RetroSpace
{ 
    /**
     * Zaklad pro herni objekty.
     */
    class GameObject : public IBasicGameObject
    {
    public:
        GameObject(): m_rotation(0.0f), m_scale(1.0f, 1.0f), m_collideRadius(10.0f) {}
        virtual ~GameObject() {}
    
        virtual void Update(const GameTime & gameTime) {}
        virtual void Draw(Renderer & renderer) {}
    
        virtual void SetPosition(Vector2f position) { m_position = position; }
        virtual void SetScale(Vector2f scale) { m_scale = scale; }
        virtual void SetRotation(float angle) { m_rotation = angle; }
    
        virtual Vector2f GetPosition() const { return m_position; }
        virtual float GetRotation() const { return m_rotation; }
        virtual float GetCollideRadius() const { return m_collideRadius; }
    
        virtual bool Collide(const GameObject & obj);
    
        virtual void UpdateMatrix();
        virtual void ApplyMatrix(Renderer & renderer);
    
        virtual void SetOnResize(Size2i screenSize) { m_screenSize = screenSize; }
    
    protected:
        Vector2f m_position, m_scale;
        float m_rotation;
        float m_collideRadius;
        Matrix m_matrix;
        Size2i m_screenSize;   
    
        virtual void ApplyTransformation(Renderer & renderer);
    };
}