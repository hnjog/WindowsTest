#include "pch.h"
#include "Bullet.h"

Bullet::Bullet ( ) :Object ( ObjectType::Projectile )
{
}

Bullet::~Bullet ( )
{
}

void Bullet::Init ( )
{
}

void Bullet::Update ( )
{
}

void Bullet::Render ( HDC hdc )
{
	Utils::DrawCircle ( hdc , _pos , static_cast< int32 >( _radius ) );
}
