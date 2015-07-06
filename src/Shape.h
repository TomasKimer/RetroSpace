// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Shape.h
  *  @brief  Prace s vykreslitelnym tvarem.
  */

#pragma once

#include <vector>
#include "Vector2.h"
#include "Vector3.h"
#include "MathHelper.h"
#include "Random.h"
#include "Color.h"

namespace GameFramework
{
    /**
     * Vykreslovany tvar.
     */
    class Shape
    {
    public:
        /**
         * Styl vykreslovani.
         */
        enum Style
        {
            SS_LINE = 0,
            SS_LINE_LOOP,
            SS_FILL,
            SS_POINT
        };
    
    public:
        Shape(void);
        ~Shape(void);
    
        // add
        void AddPoint(const Point2f & point);
        void AddPoint(const Point3f & point);
        
        void AddLine(const Point2f & start, const Point2f & end);
        void AddLine(const Point3f & start, const Point3f & end);
        
        void AddCircle(float r, int segments = 40);    
        void AddRectangle(const Point2f & start, const Point2f & end);
        void AddCube(float size);
        void AddBlock(float sizeX, float sizeY, float sizeZ);
        void AddPyramid(float sizeX, float sizeY, float sizeZ);
        void AddLetter(char c, float sizeX, float sizeY);
        
        void AddRandom(Size2i range, int count);
        void AddColor(const Color & color);
    
        // edit
        void EditVertex(unsigned int index, const Point2f & newVertex);
        void EditRectangleStartVertex(const Point2f & startVertex);
        void EditRectangleEndVertex(const Point2f & endVertex);
        void EditRectangleVertices(const Point2f & start, const Point2f & end);
        
        void MakeArrays();
        void Clear();
    
        // get
        inline float * GetVertexArray() const { return m_vertexArray; }
        inline unsigned int GetVertexCount() const { return m_vertexArraySize; }
    
        inline float * GetTexCoordArray() const { return m_texCoordArray; }
        inline unsigned int GetTexCoordCount() const { return m_texCoordArraySize; }
    
        inline float * GetColorArray() const { return m_colorArray; }
        inline unsigned int GetColorCount() const { return m_colorArraySize; }

        inline Style GetStyle() const { return m_style; }
        inline void SetStyle(Style style) { m_style = style; }

        inline float GetLineWidth() const { return m_lineWidth; }
        inline void SetLineWidth(float width) { m_lineWidth = width; }
    
    private:
        std::vector<Point3f>  m_vertices;
        std::vector<Vector2f> m_texCoords;
        std::vector<Color>    m_colors;
    
        float *m_vertexArray;
        unsigned int m_vertexArraySize;
        
        float *m_texCoordArray;
        unsigned int m_texCoordArraySize;
    
        float *m_colorArray;
        unsigned int m_colorArraySize;

        Style m_style;
        float m_lineWidth;
    };
}