#include"pch.h"
#include"SpriteRenderer.h"
#include"Sprite.h"

void SpriteRenderer::Start ( )
{
}

void SpriteRenderer::Update ( )
{
}

void SpriteRenderer::Render ( HDC hdc )
{
	if ( _sprite == nullptr )
		return;

	Vec2Int size = _sprite->GetSize ( );

	//Test
	::BitBlt ( hdc ,
		50,//( int32 ) _pos.x - size.x / 2 , // 정식적으로는 Owner를 사용하여 GameObject를 가져오는 방식
		500,//( int32 ) _pos.y - size.y / 2 , // 
		size.x ,
		size.y ,
		_sprite->GetDC ( ) ,
		_sprite->GetPos ( ).x ,
		_sprite->GetPos ( ).y ,
		SRCCOPY );
}
