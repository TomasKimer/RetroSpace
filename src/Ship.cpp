// +------------------------------------------------------------+
// |                      RetroSpace v1.0                       |
// |   Retrospektivni hra pro dva hrace s vesmirnou tematikou   |
// |           Bakalarska prace, FIT VUT v Brne, 2011           |
// +------------------------------------------------------------+
/**  @author Tomas Kimer (xkimer00@stud.fit.vutbr.cz)
  *  @date   18.5.2011
  *  @file   Ship.cpp
  *  @brief  Funkcionalita vesmirne lode.
  */

#include "Ship.h"
#include "MathHelper.h"
#include "Log.h"

namespace RetroSpace
{

Ship::Ship(void): m_accelerateValue(0.0f), m_turnValue(0.0f), m_destroyed(false), m_fire(false), m_refWeaponTypes(0), m_justHit(false)
{
    m_explodeBuilder = ParticleEffectFactory::CreateParticleEffect(ParticleEffectFactory::EXPLODE);
    m_trailBuilder   = ParticleEffectFactory::CreateParticleEffect(ParticleEffectFactory::SHIP_TRAIL);
    
    m_trailGenerator.SetPosition(Vector2f(-20, 0));
    
    m_shipShape.SetStyle(Shape::SS_LINE_LOOP);
    m_shipShape.SetLineWidth(2.5f);
    m_shipShape.AddPoint(Point2f(- 9.f,   0.f));
    m_shipShape.AddPoint(Point2f(-13.f,  13.f));
    m_shipShape.AddPoint(Point2f( 13.f,   0.f));
    m_shipShape.AddPoint(Point2f(-13.f, -13.f));
    m_shipShape.MakeArrays();
}

Ship::~Ship(void)
{
    delete m_explodeBuilder;
    delete m_trailBuilder;
}

void Ship::Explode()
{
    m_explodeGenerator.Emit(m_explodeBuilder, 100, this->m_matrix);
}

void Ship::Reset(Vector2f pos, float rot)
{
    SetPosition(pos);
    SetRotation(rot);
    SetVelocity(Vector2f::Zero());
    m_resources.Renew();
    m_weapon.SetType(m_refWeaponTypes->GetWeapon(WeaponTypes::WT_CANNON));
    m_destroyed = false;
}

void Ship::ResetRandom(Vector2f topLeft, Vector2f bottomRight)
{
    Reset(Vector2f(m_random.NextFloat(topLeft.x, bottomRight.x),
                   m_random.NextFloat(topLeft.y, bottomRight.y)),
          m_random.NextFloat(0.f, 360.f));
}

void Ship::Hit(float damage)
{
    m_justHit = true;
    
    m_destroyed = m_resources.ShieldDown(damage);
    if (m_destroyed)
        Explode();
}

void Ship::Update(const GameTime & gameTime)
{
    m_explodeGenerator.Update(gameTime);
    m_resources.Update(gameTime);   
    
    if (m_turnValue != 0.0f)
    {
        m_rotation += m_turnValue * static_cast<float>(gameTime.Elapsed().ms());
        m_turnValue = 0.0f;
    }

    m_acceleration = Vector2f::Zero();
    
    if (m_accelerateValue != 0.0f)
    {
        Vector2f direction = MathHelper::Direction(m_rotation);
        direction *= m_accelerateValue;
        m_acceleration += direction;
        m_accelerateValue = 0.0f;

        UpdateMatrix();
        m_trailGenerator.Emit(m_trailBuilder, std::max(gameTime.Elapsed().ms() / 4, 1U), this->m_matrix, gameTime.Current());
    }

    // friction
    m_acceleration -= m_velocity * m_attr->slowdownSpeed;

    MovableSpaceObject::Update(gameTime);

    // speed limit
    if (m_velocity.Length() > m_attr->maxSpeed)
        m_velocity.SetLength(m_attr->maxSpeed);

    if (m_fire)
    {
        if (!m_weapon.Fire(m_position, m_rotation, m_resources, gameTime.Current()))
        {
            if (m_weapon.GetType().proj.type != WeaponTypes::WT_CANNON)
            {
                m_weapon.SetType(m_refWeaponTypes->GetWeapon(WeaponTypes::WT_CANNON));
                m_weapon.Fire(m_position, m_rotation, m_resources, gameTime.Current());
                m_resources.Energy().Up(m_resources.Energy().GetMaxValue() / 5.f);   
            }
        }
        m_fire = false;
    }
    
    m_trailGenerator.Update(gameTime);
    m_weapon.Update(gameTime);

    UpdateMatrix();
}

void Ship::Draw(Renderer & renderer)
{
    m_explodeGenerator.Draw(renderer);
    m_weapon.Draw(renderer);
    m_trailGenerator.Draw(renderer);
    
    ApplyMatrix(renderer);

    // frame
    if (m_justHit)
    {
        renderer.SetColor(Color::White());
        m_justHit = false;
    }
    else
        renderer.SetColor(m_colors->frame);    
    m_shipShape.SetStyle(Shape::SS_LINE_LOOP);
    renderer.DrawShape(m_shipShape);

    // inner
    renderer.SetColor(m_colors->inner);    
    m_shipShape.SetStyle(Shape::SS_FILL);
    renderer.DrawShape(m_shipShape);
}

void Ship::RotateAtPoint(Point2i pos)
{
    float angle = MathHelper::Angle(m_position, static_cast<Vector2f>(pos));
    
    if (pos.x - m_position.x < 0.0f)
        angle += 180.0f;

    SetRotation(angle);
}

void Ship::ApplyPowerup(Powerup::Attributes & attr)
{
    switch (attr.type)
    {
        case Powerup::TYPE_ENERGY:
            m_resources.Energy().Up(attr.bonusValue);
            break;

        case Powerup::TYPE_SHIELD:
            m_resources.Shield().Up(attr.bonusValue);
            break;

        case Powerup::TYPE_WEAPON_ROCKET:
            m_weapon.SetType(m_refWeaponTypes->GetWeapon(WeaponTypes::WT_ROCKET));
            m_resources.Energy().Renew();
            break;

        case Powerup::TYPE_WEAPON_LASER:
            m_weapon.SetType(m_refWeaponTypes->GetWeapon(WeaponTypes::WT_LASER));
            m_resources.Energy().Renew();
            break;
    }    
}

void Ship::SetColors(Colors & colors)
{
    m_colors = &colors;

    m_trailBuilder->SetStartColor(colors.trailStart);
    m_trailBuilder->SetEndColor(colors.trailEnd);
    
    m_explodeBuilder->SetStartColor(colors.explodeStart);
    m_explodeBuilder->SetEndColor(colors.explodeEnd);
}

void Ship::SetAttributes(Attributes & attr)
{
    m_attr = &attr;
    m_resources.SetAttributes(attr.resources);
}

void Ship::SetOnResize(Size2i screenSize)
{
    MovableSpaceObject::SetOnResize(screenSize);
    m_weapon.SetOnResize(screenSize);
}

void Ship::SetPlanet(Planet *planet)
{
    MovableSpaceObject::SetPlanet(planet);
    m_weapon.SetPlanet(planet);
}

void Ship::SetWeaponTypes(WeaponTypes & wt)
{
    m_refWeaponTypes = &wt;
    m_weapon.SetType(m_refWeaponTypes->GetWeapon(WeaponTypes::WT_CANNON));
}

}
