// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Random.h
  *  @brief  Generovani pseudonahodnych cisel.
  */

#pragma once

#include <cstdlib>
#include <ctime>

namespace GameFramework
{
#define RAND_FUNC std::rand()

    /**
     * Generovani pseudonahodnych cisel se zadanymi rozsahy.
     */
    class Random
    {
    public:
        Random() { Seed(); }
        Random(unsigned int seed) { Seed(seed); }
        
        void Seed() { Seed(static_cast<unsigned int>(time(0))); }
        void Seed(unsigned int seed) { srand(seed); }
        
        inline float NextFloat() { return (float)randFunc() / (float)(RAND_MAX); }    
        inline float NextFloat(float min, float max) { return NextFloat() * (max - min) + min; }
    
        inline int Next() { return randFunc(); }
        inline int Next(int max) { return randFunc() % max; }
        inline int Next(int min, int max) { return randFunc() % (max - min + 1) + min; }
    
    private:
        inline int randFunc() { return RAND_FUNC; }
    };
}