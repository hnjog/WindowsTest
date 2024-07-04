#include "pch.h"
#include"FlipbookActor.h"
#include"Flipbook.h"
#include"Sprite.h"
#include"TimeManager.h"
#include"SceneManager.h"
#include"Texture.h"

FlipbookActor::FlipbookActor ( )
{
}

FlipbookActor::~FlipbookActor ( )
{
}

void FlipbookActor::BeginPlay ( )
{
	Super::BeginPlay ( );
}

void FlipbookActor::Tick ( )
{
	Super::Tick ( );

	if ( _flipbook == nullptr )
		return;

	const FlipbookInfo& info = _flipbook->GetInfo ( );
	// loop 아닌데 재생 끝남
	if ( info.loop == false && _idx == info.end ) 
		return;

	float delta = GET_SINGLE ( TimeManager )->GetDeltaTime ( );

	_sumTime += delta;

	int32 frameCount = ( info.end - info.start + 1 );
	// 다음으로 넘어가야할 시간
	// = 총 시간 / 총 애니메이션 프레임 카운트
	float nextFrame = info.duration / frameCount;

	if ( _sumTime >= nextFrame )
	{
		_sumTime = 0.f;
		// 초과시 다시 돌아가도록
		// 어차피 idx 가 end이고 loop가 안켜졌다면 위에서 걸러짐
		_idx = ( _idx + 1 ) % frameCount; 
	}

}

void FlipbookActor::Render ( HDC hdc )
{
	Super::Render ( hdc );

	if ( _flipbook == nullptr )
		return;

	const FlipbookInfo& info = _flipbook->GetInfo ( );

	::TransparentBlt ( hdc ,
		( int32 ) _pos.x - info.size.x / 2 ,
		( int32 ) _pos.y - info.size.y / 2 ,
		info.size.x ,
		info.size.y ,
		info.texture->GetDC ( ) ,
		( info.start + _idx ) * info.size.x ,
		info.line * info.size.y ,
		info.size.x ,
		info.size.y ,
		info.texture->GetTransparent ( )
	);

}

void FlipbookActor::SetFlipbook ( Flipbook* flipbook )
{
	// null 이 아니고
	// 똑같은 녀석을 집어넣으려 한 경우
	if ( flipbook && _flipbook == flipbook )
		return;

	_flipbook = flipbook;
	Reset ( );
}

void FlipbookActor::Reset ( )
{
	_sumTime = 0.f;
	_idx = 0;
}
