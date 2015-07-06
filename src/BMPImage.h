// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   BMPImage.h
  *  @brief  Nacitani obrazovych souboru typu BMP.
  */

#pragma once

#include "Image.h"
#include <string>
#include <fstream>

namespace GameFramework
{
    /**
     * Obrazek typu BMP.
     */
    class BMPImage : public Image
    {
    public:
        #pragma pack(push,1)
        /**
         * Hlavicka souboru.
         */
        struct FileInfoHeader { 
            unsigned short bfType; 
            unsigned long  bfSize; 
            unsigned short bfReserved1; 
            unsigned short bfReserved2; 
            unsigned long  bfOffBits; 
        };
        
        /**
         * Hlavicka bitmapy.
         */
        struct BitmapInfoHeader {
          unsigned long  biSize; 
          long           biWidth; 
          long           biHeight; 
          unsigned short biPlanes; 
          unsigned short biBitCount; 
          unsigned long  biCompression; 
          unsigned long  biSizeImage; 
          long           biXPelsPerMeter; 
          long           biYPelsPerMeter; 
          unsigned long  biClrUsed; 
          unsigned long  biClrImportant; 
        };
        #pragma pack(pop)
        
    public:    
        BMPImage(void);
        virtual ~BMPImage(void);
    
        virtual void Load(const std::string & filename);
        virtual void ConvertBGRtoRGB();
    
    private:
    
    };
}