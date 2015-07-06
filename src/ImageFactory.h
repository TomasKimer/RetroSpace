// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ImageFactory.h
  *  @brief  Vyber a vytvareni konkretnich typu obrazku.
  */

#include <string>
#include <stdexcept>

#include "BMPImage.h"

namespace GameFramework
{
    /**
     * Vytvareni konkretnich implementaci obrazku.
     */
    class ImageFactory
    {
    public:    
        static Image * CreateImage(const std::string & filename)
        {
            if (filename.find(".bmp") != std::string::npos)
                return new BMPImage();
            //else if <add other formats>
            else
                throw std::invalid_argument("Unsupported image file format");
        };    
        
    private:
        ImageFactory() {}
    };
}