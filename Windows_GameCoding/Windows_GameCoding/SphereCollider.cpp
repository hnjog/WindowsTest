#include "pch.h"
#include"SphereCollider.h"
#include"SceneManager.h"
#include"Actor.h"
#include"BoxCollider.h"

SphereCollider::SphereCollider ( )
	:Super ( ColliderType::Sphere )
{
}

SphereCollider::~SphereCollider ( )
{
	Super::~Collider ( );
}

void SphereCollider::BeginPlay ( )
{
	Super::BeginPlay ( );
}

void SphereCollider::TickComponent ( )
{
	Super::TickComponent ( );
}

void SphereCollider::Render ( HDC hdc )
{
	Super::Render ( hdc );

	if ( _showDebug == false )
		return;

	Vec2 cameraPos = GET_SINGLE ( SceneManager )->GetCameraPos ( );
	Vec2 pos = GetOwner ( )->GetPos ( );

	pos.x -= ( cameraPos.x - GWinSizeX / 2 );
	pos.y -= ( cameraPos.y - GWinSizeY / 2 );

	HBRUSH myBrush = ( HBRUSH )::GetStockObject ( NULL_BRUSH );
	HBRUSH oldBrush = ( HBRUSH )::SelectObject ( hdc , myBrush );
	Utils::DrawCircle ( hdc , pos , _radius );
	::SelectObject ( hdc , oldBrush );
	::DeleteObject ( myBrush );
}

bool SphereCollider::CheckCollision ( Collider* other )
{
	if ( other == nullptr )
		return false;

	switch ( other->GetColliderType() )
	{
	case ColliderType::Box:
	{
		return CheckCollisionSphere2Box ( this , static_cast<BoxCollider*>( other) );
	}
		break;

	case ColliderType::Sphere:
	{
		return CheckCollisionSphere2Sphere ( this , static_cast< SphereCollider* >( other ) );
	}
		break;

	default:
		break;
	}

	return false;
}
