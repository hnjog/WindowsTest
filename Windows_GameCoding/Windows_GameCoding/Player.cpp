#include "pch.h"
#include"Player.h"
#include"InputManager.h"
#include"ResourceManager.h"
#include"Flipbook.h"
#include"TimeManager.h"
#include"CameraComponent.h"
#include"Collider.h"

Player::Player ( )
{
	_flipbookUp = GET_SINGLE ( ResourceManager )->GetFlipbook ( L"FB_MoveUp" );
	_flipbookDown = GET_SINGLE ( ResourceManager )->GetFlipbook ( L"FB_MoveDown" );
	_flipbookLeft = GET_SINGLE ( ResourceManager )->GetFlipbook ( L"FB_MoveLeft" );
	_flipbookRight = GET_SINGLE ( ResourceManager )->GetFlipbook ( L"FB_MoveRight" );

	CameraComponent* camera = new CameraComponent ( );
	AddComponent ( camera );
}

Player::~Player ( )
{
}

void Player::BeginPlay ( )
{
	Super::BeginPlay ( );

	SetFlipbook ( _flipbookRight );
}

void Player::Tick ( )
{
	Super::Tick ( );

	float delta = GET_SINGLE ( TimeManager )->GetDeltaTime ( );
	const float speed = 200.f;

	if ( GET_SINGLE ( InputManager )->GetButton ( KeyType::W ) )
	{
		_pos.y -= speed * delta;
		SetFlipbook ( _flipbookUp );
	}
	else if ( GET_SINGLE ( InputManager )->GetButton ( KeyType::S ) )
	{
		_pos.y += speed * delta;
		SetFlipbook ( _flipbookDown );
	}
	else if ( GET_SINGLE ( InputManager )->GetButton ( KeyType::A ) )
	{
		_pos.x -= speed * delta;
		SetFlipbook ( _flipbookLeft );
	}
	else if ( GET_SINGLE ( InputManager )->GetButton ( KeyType::D ) )
	{
		_pos.x += speed * delta;
		SetFlipbook ( _flipbookRight );
	}
}

void Player::Render ( HDC hdc )
{
	Super::Render ( hdc );
}

void Player::OnComponentBeginOverlap ( Collider* collider , Collider* other )
{
	Super::OnComponentBeginOverlap (collider,other );
}

void Player::OnComponentEndOverlap ( Collider* collider , Collider* other )
{
	Super::OnComponentEndOverlap (collider,other );
}
