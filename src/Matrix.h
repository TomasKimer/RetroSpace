// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Matrix.h
  *  @brief  Operace s matici 4x4.
  */

#pragma once

#include <cstring>

namespace GameFramework
{
    /**
     * Reprezentace matice 4x4.
     */
    class Matrix
    {
    public:
        static const unsigned int SIZE = 4;
        static const unsigned int ITEMS = SIZE * SIZE;
    
    public:
        Matrix(bool identity = true);
        Matrix(const float arr[ITEMS]) { SetArr(arr); };
        
        void Identity();
        void Multiply(const Matrix &matrix);
        void Translate(float x, float y, float z);
        void Rotate(float angle, float x, float y, float z);
        void Scale(float x, float y, float z);
    
        void Ortho(float left, float top, float right, float bottom, float zNear = -1.0f, float zFar = 1.0f);
        void Perspective(float fovy, float aspect, float zNear, float zFar);
        void Frustum(float left, float right, float bottom, float top, float zNear, float zFar);
        void LookAt(float eyex, float eyey, float eyez,
                    float centerx, float centery, float centerz,
                    float upx, float upy, float upz);
    
        inline const float * GetArr() const { return m_arr; }
        inline void SetArr(const float arr[ITEMS]) { std::memcpy(m_arr, arr, ITEMS * sizeof(float)); }
    
        inline float GetXpos() const { return m_arr[12]; }
        inline float GetYpos() const { return m_arr[13]; }
        inline float GetZpos() const { return m_arr[14]; }
    
        inline void SetXpos(float xpos) { m_arr[12] = xpos; }
        inline void SetYpos(float ypos) { m_arr[13] = ypos; }
        inline void SetZpos(float zpos) { m_arr[14] = zpos; }
    
        inline float   operator [] (unsigned int index) const { return m_arr[index % ITEMS]; } // get value
        inline float & operator [] (unsigned int index)       { return m_arr[index % ITEMS]; } // set value
        Matrix operator *  (const Matrix &matrix) const;
        Matrix operator *= (const Matrix &matrix);
    
    private:
        float m_arr[ITEMS];    
    };
}