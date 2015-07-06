// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Background.h
  *  @brief  Zobrazeni pozadi hraci plochy.
  */

#pragma once

#include "GameObject.h"
#include <string>
#include "Shape.h"

namespace RetroSpace
{ 
    /**
     * Pozadi herni plochy.
     */
    class Background : public GameObject
    {
    public:
        /**
         * Nastaveni barev.
         */
        struct Colors
        {
            Color lines, mainLines;
            Color stars;
        };
    
    public:
        Background(void);
        virtual ~Background(void);
    
        virtual void Draw(Renderer & renderer);
        virtual void SetOnResize(Size2i screenSize);

        void SetColors(Colors & colors) { m_colors = &colors; }
    
    private:
        Shape m_starsShape;
        Shape m_gridXShape, m_gridYShape;
        Colors *m_colors;
    };
}

