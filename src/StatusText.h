// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   StatusText.h
  *  @brief  Zobrazeni stavoveho textu.
  */

#pragma once

#include "TextObject.h"
#include "TimeSpan.h"
#include "Color.h"

namespace RetroSpace
{ 
    /**
     * Stavovy text s casovanym prechodem do koncove barvy.
     */
    class StatusText : public TextObject
    {
    public:
        StatusText(void);
        virtual ~StatusText(void);
    
        virtual void Update(const GameTime & gameTime);    
        virtual void Draw(Renderer & renderer);        
    
        void DisplayStatus(const std::string & text);
    
        void SetStartColor(Color color);
    
    private:
        Color m_startColor, m_endColor;
        TimeSpan m_endTime, m_duration;
    
        bool m_displaying;       
    };
}

