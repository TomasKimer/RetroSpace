// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Matrix.cpp
  *  @brief  Operace s matici 4x4.
  */

#include "Matrix.h"
#include "MathHelper.h"
#include "Vector3.h"

namespace GameFramework
{

Matrix::Matrix(bool identity)
{
    if (identity)
        Identity();
    else
        std::memset(m_arr, 0, ITEMS * sizeof(float));        
}

void Matrix::Identity()
{
    for (unsigned int i = 0; i < ITEMS; i++)
        m_arr[i] = static_cast<float>(!(i % (SIZE + 1)));
}

void Matrix::Multiply(const Matrix &matrix)
{
    Matrix res(false);
    
    for (unsigned int i = 0; i < SIZE; i++)
        for (unsigned int j = 0; j < SIZE; j++)
            for (unsigned int k = 0; k < SIZE; k++)
                res.m_arr[i * SIZE + j] += m_arr[k * SIZE + j] * matrix.m_arr[i * SIZE + k];

    SetArr(res.m_arr);
}

void Matrix::Translate(float x, float y, float z)
{
    Matrix tmp;
    
    tmp.m_arr[12] = x;
    tmp.m_arr[13] = y;
    tmp.m_arr[14] = z;
    
    Multiply(tmp);
}

void Matrix::Rotate(float angle, float x, float y, float z)
{
    float s = std::sin(MathHelper::DegreeToRadian(angle));
    float c = std::cos(MathHelper::DegreeToRadian(angle));

    Vector3f v(x, y, z);
    v.Normalize();
    
    x = v.x;
    y = v.y;
    z = v.z;
 
    Matrix tmp;    
    
    tmp.m_arr[0]  = x * x * (1 - c) + c;
    tmp.m_arr[1]  = y * x * (1 - c) + z * s;
    tmp.m_arr[2]  = z * x * (1 - c) - y * s;
    tmp.m_arr[4]  = x * y * (1 - c) - z * s;
    tmp.m_arr[5]  = y * y * (1 - c) + c;
    tmp.m_arr[6]  = z * y * (1 - c) + x * s;
    tmp.m_arr[8]  = x * z * (1 - c) + y * s;
    tmp.m_arr[9]  = y * z * (1 - c) - x * s;
    tmp.m_arr[10] = z * z * (1 - c) + c;
    
    Multiply(tmp);
}

void Matrix::Scale(float x, float y, float z)
{
    Matrix tmp;
    
    tmp.m_arr[0]  = x;
    tmp.m_arr[5]  = y;
    tmp.m_arr[10] = z;
    
    Multiply(tmp);
}

void Matrix::Ortho(float left, float top, float right, float bottom, float zNear, float zFar)
{
    Matrix tmp;

    tmp.m_arr[0]  =  2 / (right - left);
    tmp.m_arr[5]  =  2 / (top - bottom);
    tmp.m_arr[10] = -2 / (zFar - zNear);

    tmp.m_arr[12] = -(right + left) / (right - left);
    tmp.m_arr[13] = -(top + bottom) / (top - bottom);
    tmp.m_arr[14] = -(zFar + zNear) / (zFar - zNear);

    Multiply(tmp);
}

void Matrix::Perspective(float fovy, float aspect, float zNear, float zFar)
{
    fovy = MathHelper::DegreeToRadian(fovy);
    float f = std::cos(fovy / 2.0f) / std::sin(fovy / 2.0f);

    Matrix tmp(false);
    
    tmp.m_arr[0]  = f / aspect;
    tmp.m_arr[5]  = f;
    tmp.m_arr[10] = (zFar + zNear) / (zNear - zFar);
    tmp.m_arr[11] = -1.0f;
    tmp.m_arr[14] = (2 * zFar * zNear) / (zNear - zFar);

    Multiply(tmp);
}

void Matrix::Frustum(float left, float right, float bottom, float top, float zNear, float zFar)
{
    Matrix tmp(false);

    tmp.m_arr[0]  = (2 * zNear) / (right - left);
    tmp.m_arr[5]  = (2 * zNear) / (top - bottom);
    tmp.m_arr[8]  = (right + left) / (right - left);
    tmp.m_arr[9]  = (top + bottom) / (top - bottom);
    tmp.m_arr[10] = -(zFar + zNear) / (zFar - zNear);
    tmp.m_arr[11] = -1.0f;
    tmp.m_arr[14] = -(2 * zFar * zNear) / (zFar - zNear);

    Multiply(tmp);
}

void Matrix::LookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
    Vector3f f(centerx - eyex, centery - eyey, centerz - eyez);
    Vector3f up(upx, upy, upz);
    
    f.Normalize();
    up.Normalize();

    Vector3f s = f * up;
    Vector3f u = s * f;

    Matrix tmp;
    
    tmp.m_arr[0]  =  s.x;
    tmp.m_arr[1]  =  u.x;
    tmp.m_arr[2]  = -f.x;
    
    tmp.m_arr[4]  =  s.y;
    tmp.m_arr[5]  =  u.y;
    tmp.m_arr[6]  = -f.y;
    
    tmp.m_arr[8]  =  s.z;
    tmp.m_arr[9]  =  u.z;
    tmp.m_arr[10] = -f.z;

    Multiply(tmp);
    Translate(-eyex, -eyey, -eyez);
}

Matrix Matrix::operator * (const Matrix &matrix) const
{
    Matrix tmp(*this);
    tmp.Multiply(matrix);

    return tmp;
}

Matrix Matrix::operator *= (const Matrix &matrix)
{
    Multiply(matrix);

    return *this;
}

}
