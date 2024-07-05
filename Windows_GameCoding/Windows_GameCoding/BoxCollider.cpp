#include "pch.h"
#include"BoxCollider.h"
#include"SceneManager.h"
#include"Actor.h"

BoxCollider::BoxCollider ( )
	:Super ( ColliderType::Box )
{
}

BoxCollider::~BoxCollider ( )
{
	Super::~Collider ( );
}

void BoxCollider::BeginPlay ( )
{
	Super::BeginPlay ( );
}

void BoxCollider::TickComponent ( )
{
	Super::TickComponent ( );
}

void BoxCollider::Render ( HDC hdc )
{
	Super::Render (hdc );

	if ( _showDebug == false )
		return;

	Vec2 cameraPos = GET_SINGLE ( SceneManager )->GetCameraPos ( );
	Vec2 pos = GetOwner ( )->GetPos ( );

	pos.x -= ( cameraPos.x - GWinSizeX / 2 );
	pos.y -= ( cameraPos.y - GWinSizeY / 2 );

	HBRUSH myBrush = ( HBRUSH )::GetStockObject ( NULL_BRUSH );
	HBRUSH oldBrush = ( HBRUSH )::SelectObject ( hdc , myBrush );
	Utils::DrawRect ( hdc , pos , _size.x , _size.y );
	::SelectObject ( hdc , oldBrush );
	::DeleteObject ( myBrush );
}

bool BoxCollider::CheckCollision ( Collider* other )
{
	return false;
}
