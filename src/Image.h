// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Image.h
  *  @brief  Nacitani obrazovych souboru.
  */

#pragma once

#include <string>
#include "Vector2.h"

namespace GameFramework
{
    /**
     * Bazova trida pro bitmapovy obrazek.
     */
    class Image
    {
    public:
        Image(): m_bpp(0), m_bitmap(0) {}
        virtual ~Image() {}
    
        virtual void Load(const std::string & filename) = 0;
        virtual void ConvertBGRtoRGB() {}
        
        unsigned char * GetBitmap() { return m_bitmap; }
        Size2i GetSize() { return m_size; }
        int GetBPP() { return m_bpp; }
    
    protected:
        int m_bpp;
        Size2i m_size;
        unsigned char *m_bitmap;
    };
}