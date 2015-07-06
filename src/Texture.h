// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Texture.h
  *  @brief  Prace s texturou.
  */

#pragma once

#include <string>
#include "Vector2.h"

namespace GameFramework
{
    /**
     * Baze pro praci s texturou.
     */
    class Texture
    {
    public:
        Texture(void): m_bpp(0) {}
        virtual ~Texture(void) {}
    
        virtual void Load(const std::string & filename) = 0;
        virtual void Unload() {}
    
        virtual void Bind() {}
    
        Size2i GetSize() { return m_size; }
        int GetBPP() { return m_bpp; }
    
    protected:
        Size2i m_size;
        int m_bpp;
    };
}