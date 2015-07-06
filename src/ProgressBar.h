// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ProgressBar.h
  *  @brief  Zobrazeni ukazatele stavu.
  */

#pragma once

#include "GameObject.h"
#include "Shape.h"

namespace RetroSpace
{ 
    /**
     * Ukazatel stavu.
     */
    class ProgressBar :  public GameObject
    {
    public:
        ProgressBar(void);
        virtual ~ProgressBar(void);
    
        virtual void Draw(Renderer & renderer);      
        
        void SetValue(float value);
        void SetMaxValue(float value);
        void SetBorders(float borderX, float borderY);
        void SetSize(Size2f barSize);
    
        void SetFrameColor(const Color & color) { m_frameColor = color; }
        void SetInnerColor(const Color & color) { m_innerColor = color; }
        Color & GetInnerColor() { return m_innerColor; }
        
        Size2f GetSize() { return m_size; }
    
    private:
        Size2f m_size;
        Point2f m_innerStart, m_innerEnd;
        Point2f m_dstPoint;
        
        float m_minValue, m_maxValue;
        float m_currentValue;
    
        Color m_frameColor, m_innerColor;
        Shape m_frameShape, m_innerShape;
    
        void UpdateDstPoint();
    };
}

