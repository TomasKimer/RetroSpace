// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   WeaponTypes.h
  *  @brief  Typy a vlastnosti zbrani.
  */

#pragma once

#include "TimeSpan.h"
#include "ParticleEffectFactory.h"
#include "Shape.h"
#include "Vector2.h"

using namespace GameFramework;

namespace RetroSpace
{
    /**
     * Parametry jednotlivych zbrani.
     */
    class WeaponTypes
    {
    public:
        /**
         * Typ zbrane.
         */
        enum Type
        {
            WT_CANNON = 0,
            WT_ROCKET,
            WT_LASER,
            
            WT_LAST
        };

        /**
         * Typ detekce kolize.
         */
        enum CollideType
        {
            CT_CIRCLE = 0,
            CT_LINE_SEGMENT,
        };

        /**
         * Nastaveni zbrani.
         */
        struct Attributes
        {            
            /**
             * Nastaveni pro zbran.
             */
            struct Weapon
            {            
                float energyCost;            
                unsigned int maxAtTime;
                TimeSpan cooldownTime;

                Weapon(): maxAtTime(9999) {}
            } weap;

            /**
             * Nastaveni pro projektil.
             */
            struct Projectile
            {
                Type type;
                TimeSpan lifeTime;
                float damage, velocity, gravityMultiplier;
                
                ParticleEffect *trailEffect, *explodeEffect;
                int explodeParticleCount;
                
                Shape shape;
                Vector2f shapeOffset;
                Color color;
                
                CollideType collideType;
                float collideRadius;
                Vector2f collideSegmentEnd;

                Projectile(): trailEffect(0), explodeEffect(0), gravityMultiplier(20.f),
                              collideType(CT_CIRCLE), collideRadius(10.f), explodeParticleCount(60) {}
            } proj;

            Attributes()  {}
        }; 
        
        /**
         * Nastaveni barev projektilu - ukladane.
         */
        struct ProjColor
        {
            Color color;
            Color trailStart, trailEnd;
            Color explodeStart, explodeEnd;
        };

        /**
         * Nastaveni projektilu - ukladane.
         */
        struct ProjSetting
        {
            float damage, velocity, energyCost, gravityMultiplier;
            TimeSpan cooldown, lifetime;
        };

        /**
         * Ukladane nastaveni vsech projektilu.
         */
        struct Settings
        {
            ProjSetting sett[WT_LAST];
        };

        /**
         * Ukladane nastaveni vsech barev projektilu.
         */
        struct Colors
        {
            ProjColor col[WT_LAST];
        };       


    public:
        WeaponTypes();
        ~WeaponTypes();

        Attributes & GetWeapon(Type type) { return m_attr[type % WT_LAST]; }
        void SetSettings(Settings & sett) { m_sett = &sett; }
        void SetColors(Colors & col) { m_colors = &col; }
        
        void BuildTypes();

    private:
        Attributes m_attr[WT_LAST];
        Settings *m_sett;
        Colors *m_colors;
    };
}