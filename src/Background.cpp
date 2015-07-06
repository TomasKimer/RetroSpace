// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Background.cpp
  *  @brief  Zobrazeni pozadi hraci plochy.
  */

#include "Background.h"
#include <cmath>

namespace RetroSpace
{

Background::Background(void)
{
}

Background::~Background(void)
{
}

void Background::SetOnResize(Size2i screenSize)
{
    GameObject::SetOnResize(screenSize);
    
    m_starsShape.Clear();
    m_starsShape.SetStyle(Shape::SS_POINT);
    m_starsShape.AddRandom(screenSize, (screenSize.x * screenSize.y) / 400);
    m_starsShape.MakeArrays();
    
    int gridSize = 8;

    m_gridXShape.Clear();
    m_gridXShape.SetStyle(Shape::SS_LINE);
    for (int y = 0; y < screenSize.y; y += gridSize) 
    {
        if (y % (gridSize * 4) == 0)
        {
            m_gridXShape.AddColor(m_colors->mainLines);
            m_gridXShape.AddColor(m_colors->mainLines);
        }
        else
        {
            m_gridXShape.AddColor(m_colors->lines);
            m_gridXShape.AddColor(m_colors->lines);
        }

        m_gridXShape.AddLine(Point2f(0.f, (float)y), Point2f((float)screenSize.x, (float)y));
    }
    m_gridXShape.MakeArrays();

    m_gridYShape.Clear();
    m_gridYShape.SetStyle(Shape::SS_LINE);
    for (int x = 0; x < screenSize.x; x += gridSize)
    {
        if (x % (gridSize * 4) == 0)
        {
            m_gridYShape.AddColor(m_colors->mainLines);
            m_gridYShape.AddColor(m_colors->mainLines);
        }
        else
        {
            m_gridYShape.AddColor(m_colors->lines);
            m_gridYShape.AddColor(m_colors->lines);
        }
        m_gridYShape.AddLine(Point2f((float)x, 0.f), Point2f((float)x, (float)screenSize.y));
    }
    m_gridYShape.MakeArrays();

}

void Background::Draw(Renderer & renderer)
{
    renderer.SetBlending(true);
    renderer.SetColor(m_colors->stars);
    renderer.DrawShape(m_starsShape);

    renderer.SetLineSmooth(false);

    renderer.DrawShape(m_gridXShape);
    renderer.DrawShape(m_gridYShape);

    renderer.SetLineSmooth(true);
}

}