// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Shape.cpp
  *  @brief  Prace s vykreslitelnym tvarem.
  */

#include "Shape.h"

namespace GameFramework
{

Shape::Shape(void): m_vertexArray(0), m_texCoordArray(0), m_colorArray(0), m_style(SS_LINE_LOOP), m_lineWidth(1.f)
{
}

Shape::~Shape(void)
{
    Clear();
}

void Shape::AddPoint(const Point3f & point)
{
    m_vertices.push_back(point);
}

void Shape::AddPoint(const Point2f & point)
{
    m_vertices.push_back(Point3f(point.x, point.y, 0.f));
}

void Shape::AddLine(const Point2f & start, const Point2f & end)
{
    AddPoint(start);
    AddPoint(end);
}

void Shape::AddLine(const Point3f & start, const Point3f & end)
{
    AddPoint(start);
    AddPoint(end);
}

void Shape::AddCircle(float r, int segments)
{
    float tmp = 2.0f * MathHelper::Pi() / 360.0f;
    int inc = 360 / segments;

    for(int i = 0; i < 360; i += inc)
    {
        float theta = tmp * static_cast<float>(i);
        AddPoint(Point2f(r * std::cos(theta), r * std::sin(theta)));
    }   
}

void Shape::AddRectangle(const Point2f & start, const Point2f & end)
{
    // m_texCoords.push_back(Point2f(0.f, 1.f));
    AddPoint(Point2f(start.x, start.y)); 
    
    // m_texCoords.push_back(Point2f(1.f, 1.f));
    AddPoint(Point2f(end.x  , start.y));
    
    // m_texCoords.push_back(Point2f(1.f, 0.f));
    AddPoint(Point2f(end.x  , end.y  ));
    
    // m_texCoords.push_back(Point2f(0.f, 0.f));
    AddPoint(Point2f(start.x, end.y  ));
}

void Shape::AddCube(float size)
{
    AddBlock(size, size, size);    
}

void Shape::AddBlock(float sizeX, float sizeY, float sizeZ)
{
    float x = sizeX / 2.f;
    float y = sizeY / 2.f;
    float z = sizeZ / 2.f;
    
    // front square
    AddLine(Point3f(-x, -y,  z), Point3f( x, -y,  z));  // top
    AddLine(Point3f(-x, -y,  z), Point3f(-x,  y,  z));  // left
    AddLine(Point3f( x, -y,  z), Point3f( x,  y,  z));  // right
    AddLine(Point3f(-x,  y,  z), Point3f( x,  y,  z));  // bottom

    // connection
    AddLine(Point3f(-x, -y,  z), Point3f(-x, -y, -z));  // top left
    AddLine(Point3f( x, -y,  z), Point3f( x, -y, -z));  // top right
    AddLine(Point3f(-x,  y,  z), Point3f(-x,  y, -z));  // bottom left
    AddLine(Point3f( x,  y,  z), Point3f( x,  y, -z));  // bottom right

    // back square
    AddLine(Point3f(-x, -y, -z), Point3f( x, -y, -z));  // top
    AddLine(Point3f(-x, -y, -z), Point3f(-x,  y, -z));  // left
    AddLine(Point3f( x, -y, -z), Point3f( x,  y, -z));  // right
    AddLine(Point3f(-x,  y, -z), Point3f( x,  y, -z));  // bottom
}

void Shape::AddPyramid(float sizeX, float sizeY, float sizeZ)
{
    float x = sizeX / 2.f;
    float y = sizeY / 2.f;
    float z = sizeZ / 2.f;

    // base
    AddLine(Point3f(-x,  y,  z), Point3f( x,  y,  z));  // front
    AddLine(Point3f(-x,  y,  z), Point3f(-x,  y, -z));  // left
    AddLine(Point3f( x,  y,  z), Point3f( x,  y, -z));  // right
    AddLine(Point3f(-x,  y, -z), Point3f( x,  y, -z));  // back

    // top
    AddLine(Point3f(-x,  y,  z), Point3f( 0, -y,  0));  // front left
    AddLine(Point3f( x,  y,  z), Point3f( 0, -y,  0));  // front right
    AddLine(Point3f(-x,  y, -z), Point3f( 0, -y,  0));  // back left
    AddLine(Point3f( x,  y, -z), Point3f( 0, -y,  0));  // back right
}

void Shape::AddLetter(char c, float sizeX, float sizeY)
{
    float x = sizeX / 2.f;
    float y = sizeY / 2.f;

    switch (c)
    {
        case 'e':
        case 'E':
            AddLine(Point2f(-x, -y), Point2f( x, -y));
            AddLine(Point2f(-x,  0), Point2f( x,  0));
            AddLine(Point2f(-x,  y), Point2f( x,  y));
            AddLine(Point2f(-x, -y), Point2f(-x,  y));
            break;
    
        case 's':
        case 'S':
            AddLine(Point2f(-x, -y), Point2f( x, -y));
            AddLine(Point2f(-x, -y), Point2f( -x, 0));
            AddLine(Point2f(-x,  0), Point2f( x,  0));
            AddLine(Point2f( x,  0), Point2f( x,  y));
            AddLine(Point2f(-x,  y), Point2f( x,  y));
            break;        
        
        case 'r':
        case 'R':
            AddLine(Point2f(-x, -y), Point2f( x, -y));
            AddLine(Point2f(-x,  0), Point2f( x,  0));
            AddLine(Point2f(-x, -y), Point2f(-x,  y));
            AddLine(Point2f( x, -y), Point2f( x,  0));
            AddLine(Point2f(-x,  0), Point2f( x,  y));
            
            break;        
        
        case 'l':
        case 'L':
            AddLine(Point2f(-x, -y), Point2f(-x,  y));
            AddLine(Point2f(-x,  y), Point2f( x,  y));
            break;

        case 'i':
        case 'I':
            AddLine(Point2f( 0, -y), Point2f( 0,  y));
            break;
    }
}

void Shape::AddRandom(Size2i range, int count/*, Random & random*/)
{
    Random random;
    for (int i = 0; i < count; i++)
        AddPoint(Point2f(random.NextFloat(0.f, static_cast<float>(range.x)), random.NextFloat(0.f, static_cast<float>(range.y))));
}

void Shape::AddColor(const Color & color)
{
    m_colors.push_back(color);
}    

void Shape::MakeArrays()
{
    if (m_vertices.size() > 0)
    {
        m_vertexArray = new float[m_vertices.size() * 3];
        for (unsigned int i = 0; i < m_vertices.size(); i++)
        {
            m_vertexArray[i*3]   = m_vertices[i].x;
            m_vertexArray[i*3+1] = m_vertices[i].y;
            m_vertexArray[i*3+2] = m_vertices[i].z;
        }
        m_vertexArraySize = m_vertices.size();
        m_vertices.clear();
    }

    if (m_texCoords.size() > 0)
    {
        m_texCoordArray = new float[m_texCoords.size() * 2];
        for (unsigned int i = 0; i < m_texCoords.size(); i++)
        {
            m_texCoordArray[i*2]   = m_texCoords[i].x;
            m_texCoordArray[i*2+1] = m_texCoords[i].y;
        }
        m_texCoordArraySize = m_texCoords.size();
        m_texCoords.clear();
    }    

    if (m_colors.size() > 0)
    {
        m_colorArray = new float[m_colors.size() * 4];
        for (unsigned int i = 0; i < m_colors.size(); i++)
        {
            m_colorArray[i*4]   = m_colors[i].R();
            m_colorArray[i*4+1] = m_colors[i].G();
            m_colorArray[i*4+2] = m_colors[i].B();
            m_colorArray[i*4+3] = m_colors[i].A();
        }
        m_colorArraySize = m_colors.size();
        m_colors.clear();
    }    
}


void Shape::EditVertex(unsigned int index, const Point2f & newVertex)
{
    m_vertexArray[index*3] = newVertex.x;
    m_vertexArray[index*3+1] = newVertex.y;
}

void Shape::EditRectangleStartVertex(const Point2f & startVertex)
{
    m_vertexArray[0] = m_vertexArray[9]  = startVertex.x;
    m_vertexArray[1] = m_vertexArray[4] = startVertex.y;
}

void Shape::EditRectangleEndVertex(const Point2f & endVertex)
{
    m_vertexArray[3] = m_vertexArray[6]  = endVertex.x;
    m_vertexArray[7] = m_vertexArray[10] = endVertex.y;
}

void Shape::EditRectangleVertices(const Point2f & start, const Point2f & end)
{
    EditRectangleStartVertex(start);
    EditRectangleEndVertex(end);
}

void Shape::Clear()
{
    m_vertices.clear();
    m_texCoords.clear();
    m_colors.clear();
    
    if (m_vertexArray)
    {
        delete [] m_vertexArray;
        m_vertexArray = 0;
    }

    if (m_texCoordArray)
    {
        delete [] m_texCoordArray;
        m_texCoordArray = 0;
    }

    if (m_colorArray)
    {
        delete [] m_colorArray;
        m_colorArray = 0;
    }

    m_vertexArraySize = 0;
    m_texCoordArraySize = 0;
    m_colorArraySize = 0;
}

}