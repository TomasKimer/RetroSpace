// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Planet.cpp
  *  @brief  Planeta na hraci plose.
  */

#include "Planet.h"

namespace RetroSpace
{

Planet::Planet(void): m_rot(0.f)
{
    m_collideRadius = 40.f;

    m_planetBkgnd.SetStyle(Shape::SS_FILL);
    m_planetBkgnd.AddCircle(52.f);
    m_planetBkgnd.MakeArrays();
}

Planet::~Planet(void)
{    
}

void Planet::Update(const GameTime & gameTime)
{        
    UpdateMatrix();
    m2 = m_matrix;
    m_matrix.Rotate(85.f, 1.f, 0.f, 0.f);
    m_matrix.Rotate(22.5f, 0.f, 1.f, 0.f);
    
    float rotateVal = 0.f;
    if (m_attr->hasGravity)
        rotateVal = gameTime.Elapsed().ms() / 75.f;

    if (m_attr->active)
        m_matrix.Rotate(m_rot += rotateVal, 0.f, 0.f, 1.f);
}

void Planet::Draw(Renderer & renderer)
{    
    if (!m_attr->active) return;

    Matrix tmp = m_matrix;
    m_matrix = m2;
    ApplyMatrix(renderer);
    
    renderer.SetBlending(false);
    renderer.SetColor(Color(0.0f, 0.0f, 0.0f));
    renderer.DrawShape(m_planetBkgnd);
    renderer.SetBlending(true);

    m_matrix = tmp;
    ApplyMatrix(renderer);
    
    renderer.SetTexturing(false);  
    renderer.SetColor(m_color);  
    renderer.DrawWireSphere(42.5f, 14, 14); 
}

}
