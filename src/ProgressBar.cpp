// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ProgressBar.cpp
  *  @brief  Zobrazeni ukazatele stavu.
  */

#include "ProgressBar.h"

namespace RetroSpace
{

ProgressBar::ProgressBar(void): m_minValue(0.f), m_maxValue(100.f), m_currentValue(0.f), m_size(125.f, 9.f), m_frameColor(Color::Gray())
{
    SetBorders(2.f, 2.f);
    UpdateDstPoint();

    m_frameShape.SetStyle(Shape::SS_LINE_LOOP);
    m_frameShape.AddRectangle(Point2f(), m_size);
    m_frameShape.MakeArrays();
    
    m_innerShape.SetStyle(Shape::SS_FILL);
    m_innerShape.AddRectangle(m_innerStart, m_dstPoint);
    m_innerShape.MakeArrays();
}

ProgressBar::~ProgressBar(void)
{
}

void ProgressBar::SetBorders(float borderX, float borderY)
{
    m_innerStart.x = borderX;
    m_innerStart.y = borderY;

    m_innerEnd.x = m_size.x - borderX;
    m_innerEnd.y = m_size.y - borderY;    
}

void ProgressBar::SetValue(float value)
{
    m_currentValue = value;
    UpdateDstPoint();
    m_innerShape.EditRectangleEndVertex(m_dstPoint);
}

void ProgressBar::SetMaxValue(float value)
{
    m_maxValue = value;
}

void ProgressBar::SetSize(Size2f barSize)
{
    m_size = barSize;
}

void ProgressBar::UpdateDstPoint()
{
    float segments = m_innerEnd.x - m_innerStart.x;
    m_dstPoint.x =  m_innerStart.x + ((segments / (m_maxValue - m_minValue)) * (m_currentValue - m_minValue));   
    m_dstPoint.y = m_innerEnd.y;
}

void ProgressBar::Draw(Renderer & renderer)
{
    ApplyTransformation(renderer);    

    renderer.SetColor(m_frameColor);
    renderer.DrawShape(m_frameShape);
    
    renderer.SetColor(m_innerColor);    
    renderer.DrawShape(m_innerShape);
}

}
