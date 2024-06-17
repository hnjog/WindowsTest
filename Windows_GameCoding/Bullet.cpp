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

	// 충돌
	const vector<Object*>& objects = GET_SINGLE ( ObjectManager )->GetObjects ( );
	for ( Object* object : objects )
	{
		if ( object->GetObjectType ( ) != ObjectType::Player )
			continue;

		if ( object == _owner )
			continue;

		// 총알의 위치와 타겟의 pos를 뺌으로서
		// 해당 위치로 향하는 벡터 구함
		Vector dir = _pos - object->GetPos ( );
		// 그러한 벡터의 길이가 총알 크기 와 대상 크기 이하라면
		// 두 요소가 겹쳤다고 판단할 수 있음
		if ( dir.Length ( ) < _radius + object->GetRadius ( ) )
		{
			FortressScene* scene = dynamic_cast< FortressScene* >( GET_SINGLE ( SceneManager )->GetCurrentScene ( ) );
			if ( scene != nullptr )
			{
				scene->ChangePlayerTurn ( );
			}

			// bullet 제거 처리
			GET_SINGLE ( ObjectManager )->Remove ( this );
			return;
		}

	}

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
