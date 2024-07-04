#include "pch.h"
#include"SpriteActor.h"
#include"Sprite.h"
#include"SceneManager.h"

SpriteActor::SpriteActor ( )
{
}

SpriteActor::~SpriteActor ( )
{
}

void SpriteActor::BeginPlay ( )
{
	// 부모꺼 먼저 호출하는 방식
	Super::BeginPlay ( );
}

void SpriteActor::Tick ( )
{
	Super::Tick ( );
}

void SpriteActor::Render ( HDC hdc )
{
	Super::Render ( hdc );

	if ( _sprite == nullptr )
		return;

	Vec2Int size = _sprite->GetSize ( );

	// 좌표계 변환을 위함
	Vec2 cameraPos = GET_SINGLE ( SceneManager )->GetCameraPos ( );

	::TransparentBlt ( hdc ,
		( int32 ) _pos.x - size.x / 2 - ((int32)cameraPos.x - GWinSizeX / 2),
		( int32 ) _pos.y - size.y / 2 - ((int32)cameraPos.y - GWinSizeY / 2),
		size.x ,
		size.y ,
		_sprite->GetDC ( ) ,
		_sprite->GetPos ( ).x ,
		_sprite->GetPos ( ).y ,
		size.x ,
		size.y ,
		_sprite->GetTransparent ( ) );

}
