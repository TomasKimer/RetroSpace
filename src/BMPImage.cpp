// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   BMPImage.cpp
  *  @brief  Nacitani obrazovych souboru typu BMP.
  */

#include "BMPImage.h"
#include "Log.h"
#include <stdexcept>

namespace GameFramework
{

BMPImage::BMPImage(void)
{
}

BMPImage::~BMPImage(void)
{
    if (m_bitmap)
        delete [] m_bitmap;
}

void BMPImage::Load(const std::string & filename)
{
    std::ifstream file;
    file.open(filename.c_str(), std::ios::binary);
    if (file.fail())
        throw std::invalid_argument("Error opening BMP file " + filename);

    FileInfoHeader fileInfo;    
    file.read(reinterpret_cast<char*>(&fileInfo), sizeof(FileInfoHeader));
    
    if(fileInfo.bfType != 0x4D42)  // 19778
        throw std::invalid_argument("The file is not a BMP file");
    
    BitmapInfoHeader bitmapInfo;
    file.read(reinterpret_cast<char*>(&bitmapInfo), sizeof(BitmapInfoHeader));

    if (bitmapInfo.biBitCount != 24) // supports only 24bit, else load RGBQUAD
        throw std::invalid_argument("Unsupported image bit count");

    unsigned long bitmapSize = fileInfo.bfSize - fileInfo.bfOffBits;
    if(bitmapSize > 3)
    {
        m_bitmap = new unsigned char[bitmapSize];
        
        file.seekg(fileInfo.bfOffBits, std::ios::beg);  // skip color palette 
        file.read(reinterpret_cast<char*>(m_bitmap), bitmapSize);
    }
    else
        throw std::invalid_argument("Bitmap missing or too small");
        
    if (bitmapInfo.biCompression != 0L)
        throw std::invalid_argument("Bitmap file is compressed, unsupported");

    file.close();

    m_size.x = bitmapInfo.biWidth;
    m_size.y = bitmapInfo.biHeight;
    m_bpp = bitmapInfo.biBitCount;

    Log::Msg("BMP image '" + filename + "' loaded");
}

void BMPImage::ConvertBGRtoRGB()
{
    for (int i = 0; i < m_size.x * m_size.y * (m_bpp >> 3); i += m_bpp >> 3) 
    {
        unsigned char tmp = m_bitmap[i];
        m_bitmap[i] = m_bitmap[i+2];
        m_bitmap[i+2] = tmp;
    }
}

}