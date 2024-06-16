#include "pch.h"
#include "Bullet.h"
#include"TimeManager.h"
#include"ObjectManager.h"
#include"SceneManager.h"
#include"FortressScene.h"
#include"UIManager.h"

Bullet::Bullet ( ) :Object ( ObjectType::Projectile )
{
}

Bullet::~Bullet ( )
{
}

void Bullet::Init ( )
{
	_radius = 20.f;
}

void Bullet::Update ( )
{
	float delta = GET_SINGLE ( TimeManager )->GetDeltaTime ( );

	// wind
	float windPercent = GET_SINGLE ( UIManager )->GetWindPercent ( );
	_speed.x += 10 * delta * windPercent;

	// gravity
	_speed.y += 1000 * delta;

	_pos += _speed * delta;

	const double ratio = 1.5;

	if ( _pos.y > GWinSizeY * ratio || _pos.y < -GWinSizeY * ratio ||
		_pos.x > GWinSizeX * ratio || _pos.x < -GWinSizeX * ratio )
	{
		FortressScene* scene = dynamic_cast<FortressScene*>( GET_SINGLE ( SceneManager )->GetCurrentScene ( ));
		if ( scene != nullptr )
		{
			scene->ChangePlayerTurn ( );
		}

		GET_SINGLE ( ObjectManager )->Remove ( this );
		return;
	}

}

void Bullet::Render ( HDC hdc )
{
	Utils::DrawCircle ( hdc , _pos , static_cast< int32 >( _radius ) );
}
