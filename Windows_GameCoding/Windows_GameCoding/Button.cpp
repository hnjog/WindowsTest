#include"pch.h"
#include"Button.h"
#include"InputManager.h"
#include"TimeManager.h"
#include"Sprite.h"

Button::Button ( )
{
}

Button::~Button ( )
{
}

void Button::BeginPlay ( )
{
	Super::BeginPlay ( );

	SetButtonState ( BS_Default );
}

void Button::Tick ( )
{
	POINT mousePos = GET_SINGLE ( InputManager )->GetMousePos ( );
	float delta = GET_SINGLE ( TimeManager )->GetDeltaTime ( );

	if ( IsMouseInRect ( ) )
	{
		int a = 0;
	}
	else
	{

	}

}

void Button::Render ( HDC hdc )
{
	if ( _currentSprite )
	{
		::TransparentBlt ( hdc ,
			( int32 ) _pos.x - _size.x / 2 ,
			( int32 ) _pos.y - _size.y / 2 ,
			_size.x ,
			_size.y ,
			_currentSprite->GetDC ( ) ,
			_currentSprite->GetPos ( ).x ,
			_currentSprite->GetPos ( ).y ,
			_currentSprite->GetSize ( ).x ,
			_currentSprite->GetSize ( ).y ,
			_currentSprite->GetTransparent ( ) );
	}
	else
	{
		Utils::DrawRect ( hdc , _pos , _size.x , _size.y );
	}

}

void Button::SetButtonState ( ButtonState state )
{
	_state = state;

	if ( _sprites[ state ] )
		SetCurrentSprite ( _sprites[ state ] );
}
