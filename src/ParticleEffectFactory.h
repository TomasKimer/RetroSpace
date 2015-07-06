// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   ParticleEffectFactory.h
  *  @brief  Vytvareni casticovych efektu.
  */

#pragma once

#include "ExplodeParticleEffect.h"
#include "TrailParticleEffect.h"
#include <stdexcept>

namespace RetroSpace
{ 
    /**
     * Vytvareni konkretnich casticovych efektu.
     */
    class ParticleEffectFactory
    {
    public:
        /**
         * Typ efektu.
         */
        enum Effect
        {
            EXPLODE = 1,
            SHIP_TRAIL
        };
    
    public:
        static ParticleEffect *CreateParticleEffect(Effect effectId)
        {
            switch (effectId)
            {
                case EXPLODE:
                    return new ExplodeParticleEffect();
                    break;
                case SHIP_TRAIL:
                    return new TrailParticleEffect();
                    break;
                default:
                    throw new std::invalid_argument("Unknown effect"); 
            }
        }
    };
}