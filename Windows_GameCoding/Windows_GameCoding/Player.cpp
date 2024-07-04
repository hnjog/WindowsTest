#include "pch.h"
#include"Player.h"
#include"InputManager.h"
#include"ResourceManager.h"
#include"Flipbook.h"
#include"TimeManager.h"

Player::Player ( )
{
	{
		Texture* texture = GET_SINGLE ( ResourceManager )->GetTexture ( L"PlayerUp" );
		Flipbook* fb = GET_SINGLE(ResourceManager)->CreateFlipbook(L"FB_MoveUp");
		fb->SetInfo ( { texture,L"FB_MoveUp",{200,200},0,9,1,0.5f } );
	}
	
}

Player::~Player ( )
{
}

void Player::BeginPlay ( )
{
	Super::BeginPlay ( );
}

void Player::Tick ( )
{
	Super::Tick ( );

	if ( GET_SINGLE ( InputManager )->GetButton ( KeyType::W ) )
	{

	}
}

void Player::Render ( HDC hdc )
{
	Super::Render ( hdc );
}
