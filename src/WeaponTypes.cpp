// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   WeaponTypes.cpp
  *  @brief  Typy a vlastnosti zbrani.
  */

#include "WeaponTypes.h"

namespace RetroSpace
{

WeaponTypes::WeaponTypes()
{
}

WeaponTypes::~WeaponTypes()
{
    for (int i = 0; i < WT_LAST; i++)
    {
        if (m_attr[i].proj.trailEffect)
            delete m_attr[i].proj.trailEffect;
        if (m_attr[i].proj.explodeEffect)
            delete m_attr[i].proj.explodeEffect;
    }        
}

void WeaponTypes::BuildTypes()
{
    // --- Canon ---
    m_attr[WT_CANNON].weap.cooldownTime = TimeSpan::FromMs(100); //250 unbuffered
    m_attr[WT_CANNON].weap.energyCost = m_sett->sett[WT_CANNON].energyCost;

    m_attr[WT_CANNON].proj.type = WT_CANNON;
    m_attr[WT_CANNON].proj.lifeTime = m_sett->sett[WT_CANNON].lifetime;      
    m_attr[WT_CANNON].proj.damage = m_sett->sett[WT_CANNON].damage;
    m_attr[WT_CANNON].proj.gravityMultiplier = m_sett->sett[WT_CANNON].gravityMultiplier;
    m_attr[WT_CANNON].proj.velocity = m_sett->sett[WT_CANNON].velocity;
    m_attr[WT_CANNON].proj.shapeOffset = Vector2f(14.f, 0.f);
    m_attr[WT_CANNON].proj.color = m_colors->col[WT_CANNON].color;

    m_attr[WT_CANNON].proj.shape.SetLineWidth(1.0f);
    m_attr[WT_CANNON].proj.shape.AddLine(Point2f(-2.5f, -3.f), Point2f(10.f, 0.f));
    m_attr[WT_CANNON].proj.shape.AddPoint(Point2f(-2.5f,  3.f));
    m_attr[WT_CANNON].proj.shape.MakeArrays();

    m_attr[WT_CANNON].proj.explodeEffect = ParticleEffectFactory::CreateParticleEffect(ParticleEffectFactory::EXPLODE);
    m_attr[WT_CANNON].proj.explodeEffect->SetLifeTime(200);
    m_attr[WT_CANNON].proj.explodeEffect->SetLineWidth(1.f);
    m_attr[WT_CANNON].proj.explodeEffect->SetStartColor(m_colors->col[WT_CANNON].explodeStart);
    m_attr[WT_CANNON].proj.explodeEffect->SetEndColor(m_colors->col[WT_CANNON].explodeEnd);
    m_attr[WT_CANNON].proj.explodeParticleCount = 10;
    
    
    // --- Rocket ---
    m_attr[WT_ROCKET].weap.cooldownTime = m_sett->sett[WT_ROCKET].cooldown;
    m_attr[WT_ROCKET].weap.energyCost = m_sett->sett[WT_ROCKET].energyCost;
    
    m_attr[WT_ROCKET].proj.type = WT_ROCKET;
    m_attr[WT_ROCKET].proj.lifeTime = m_sett->sett[WT_ROCKET].lifetime;           
    m_attr[WT_ROCKET].proj.damage = m_sett->sett[WT_ROCKET].damage;
    m_attr[WT_ROCKET].proj.gravityMultiplier = m_sett->sett[WT_ROCKET].gravityMultiplier;
    m_attr[WT_ROCKET].proj.velocity = m_sett->sett[WT_ROCKET].velocity;
    m_attr[WT_ROCKET].proj.shapeOffset = Vector2f(14.f, 0.f);
    m_attr[WT_ROCKET].proj.color = m_colors->col[WT_ROCKET].color; //Color(1.0f, 0.5f, 0.5f, 1.0f);
    
    m_attr[WT_ROCKET].proj.shape.SetStyle(Shape::SS_LINE);            
    m_attr[WT_ROCKET].proj.shape.SetLineWidth(2.0f);
    m_attr[WT_ROCKET].proj.shape.AddLine(Point2f(-2.5f, -5.f), Point2f(10.f, 0.f));
    m_attr[WT_ROCKET].proj.shape.AddLine(Point2f(-2.5f,  5.f), Point2f(10.f, 0.f));  
    m_attr[WT_ROCKET].proj.shape.MakeArrays();

    m_attr[WT_ROCKET].proj.explodeEffect = ParticleEffectFactory::CreateParticleEffect(ParticleEffectFactory::EXPLODE);
    m_attr[WT_ROCKET].proj.explodeEffect->SetStartColor(m_colors->col[WT_ROCKET].explodeStart);
    m_attr[WT_ROCKET].proj.explodeEffect->SetEndColor(m_colors->col[WT_ROCKET].explodeEnd);
    m_attr[WT_ROCKET].proj.explodeEffect->SetLineWidth(1.f);

    m_attr[WT_ROCKET].proj.trailEffect = ParticleEffectFactory::CreateParticleEffect(ParticleEffectFactory::SHIP_TRAIL);
    m_attr[WT_ROCKET].proj.trailEffect->SetStartColor(m_colors->col[WT_ROCKET].trailStart);
    m_attr[WT_ROCKET].proj.trailEffect->SetEndColor(m_colors->col[WT_ROCKET].trailEnd);
    
    
    // --- Laser ---
    m_attr[WT_LASER].weap.cooldownTime = m_sett->sett[WT_LASER].cooldown;
    m_attr[WT_LASER].weap.energyCost = m_sett->sett[WT_LASER].energyCost;
    
    m_attr[WT_LASER].proj.type = WT_LASER;
    m_attr[WT_LASER].proj.lifeTime = m_sett->sett[WT_LASER].lifetime;           
    m_attr[WT_LASER].proj.damage = m_sett->sett[WT_LASER].damage;
    m_attr[WT_LASER].proj.gravityMultiplier = m_sett->sett[WT_LASER].gravityMultiplier;
    m_attr[WT_LASER].proj.velocity = m_sett->sett[WT_LASER].velocity;
    m_attr[WT_LASER].proj.shapeOffset = Vector2f(16.f, 0.f);

    m_attr[WT_LASER].proj.shape.SetLineWidth(3.5f);
    m_attr[WT_LASER].proj.shape.AddLine(Vector2f(0.f,0.f), Vector2f(200.f, 0.f));
    m_attr[WT_LASER].proj.shape.AddColor(m_colors->col[WT_LASER].trailStart);
    m_attr[WT_LASER].proj.shape.AddColor(m_colors->col[WT_LASER].trailEnd);
    m_attr[WT_LASER].proj.shape.MakeArrays();

    m_attr[WT_LASER].proj.collideType = CT_LINE_SEGMENT;
    m_attr[WT_LASER].proj.collideSegmentEnd = Vector2f(200.f, 0.f);
}

}