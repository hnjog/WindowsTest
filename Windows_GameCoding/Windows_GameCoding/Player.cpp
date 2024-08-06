#include "pch.h"
#include"Player.h"
#include"InputManager.h"
#include"ResourceManager.h"
#include"Flipbook.h"
#include"TimeManager.h"
#include"CameraComponent.h"
#include"Collider.h"
#include"BoxCollider.h"

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

	if ( GET_SINGLE ( InputManager )->GetButton ( KeyType::A ) )
	{
		_pos.x -= speed * delta;
		SetFlipbook ( _flipbookLeft );
	}
	else if ( GET_SINGLE ( InputManager )->GetButton ( KeyType::D ) )
	{
		_pos.x += speed * delta;
		SetFlipbook ( _flipbookRight );
	}
	else if ( GET_SINGLE ( InputManager )->GetButton ( KeyType::SpaceBar ) )
	{
		Jump ( );
	}

	TickGravity ( );
}

void Player::Render ( HDC hdc )
{
	Super::Render ( hdc );
}

void Player::OnComponentBeginOverlap ( Collider* collider , Collider* other )
{
	Super::OnComponentBeginOverlap ( collider , other );

	BoxCollider* b1 = dynamic_cast< BoxCollider* >( collider );
	BoxCollider* b2 = dynamic_cast< BoxCollider* >( other );
	if ( b1 == nullptr || b2 == nullptr )
		return;

	AdjustCollisionPos ( b1 , b2 );

	_onGround = true;
	_jumping = false;
}

void Player::OnComponentEndOverlap ( Collider* collider , Collider* other )
{
	Super::OnComponentEndOverlap ( collider , other );

	BoxCollider* b1 = dynamic_cast< BoxCollider* >( collider );
	BoxCollider* b2 = dynamic_cast< BoxCollider* >( other );
	if ( b1 == nullptr || b2 == nullptr )
		return;

	if ( b2->GetCollisionLayer ( ) == CLT_GROUND )
	{
		_onGround = false;
	}
}

void Player::Jump ( )
{
	if ( _jumping )
		return;

	_jumping = true;
	_onGround = false;
	_speed.y = -500;
}

void Player::TickGravity ( )
{
	float delta = GET_SINGLE ( TimeManager )->GetDeltaTime ( );

	if ( delta > 0.1f )
		return;

	if ( _onGround == true )
		return;

	_speed.y += _gravity * delta;
	_pos.y += _speed.y * delta;
}

void Player::AdjustCollisionPos ( BoxCollider* b1 , BoxCollider* b2 )
{
	RECT r1 = b1->GetRect ( );
	RECT r2 = b2->GetRect ( );

	Vec2 pos = GetPos ( );

	RECT intersect = {};
	if ( ::IntersectRect ( &intersect , &r1 , &r2 ) )
	{
		int32 w = intersect.right - intersect.left;
		int32 h = intersect.bottom - intersect.top;
		const int disValue = 5;
		if ( w > h )
		{
			if ( intersect.top == r2.top )
			{
				pos.y -= h * disValue;
			}
			else
			{
				pos.y += h * disValue;
			}
		}
		else
		{
			if ( intersect.left == r2.left )
			{
				pos.x -= w * disValue;
			}
			else
			{
				pos.x += w * disValue;
			}
		}

	}

	SetPos ( pos );
}
