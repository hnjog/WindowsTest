#include "pch.h"
#include "DevScene.h"
#include"InputManager.h"
#include"TimeManager.h"
#include"ResourceManager.h"
#include"Texture.h"
#include"Sprite.h"
#include"Actor.h"
#include"SpriteActor.h"
#include"Player.h"
#include"GameObject.h"
#include"SpriteRenderer.h"
#include"PlayerMoveScript.h"

DevScene::DevScene ( )
{
}

DevScene::~DevScene ( )
{
}

void DevScene::Init ( )
{
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"Stage01" , L"Sprite\\Map\\Stage01.bmp" );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"Tile" , L"Sprite\\Map\\Tile.bmp" , RGB ( 128 , 128 , 128 ) );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"Sword" , L"Sprite\\Item\\Sword.bmp" );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"Potion" , L"Sprite\\UI\\Mp.bmp" );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"PlayerDown" , L"Sprite\\Player\\PlayerDown.bmp" , RGB ( 128 , 128 , 128 ) );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"PlayerUp" , L"Sprite\\Player\\PlayerUp.bmp" , RGB ( 128 , 128 , 128 ) );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"PlayerLeft" , L"Sprite\\Player\\PlayerLeft.bmp" , RGB ( 128 , 128 , 128 ) );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"PlayerRight" , L"Sprite\\Player\\PlayerRight.bmp" , RGB ( 128 , 128 , 128 ) );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"Start" , L"Sprite\\UI\\Start.bmp" );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"Edit" , L"Sprite\\UI\\Edit.bmp" );
	GET_SINGLE ( ResourceManager )->LoadTexture ( L"Exit" , L"Sprite\\UI\\Exit.bmp" );

	GET_SINGLE ( ResourceManager )->CreateSprite ( L"Stage01" , GET_SINGLE ( ResourceManager )->GetTexture ( L"Stage01" ) );
	GET_SINGLE ( ResourceManager )->CreateSprite ( L"TileO" , GET_SINGLE ( ResourceManager )->GetTexture ( L"Tile" ) , 0 , 0 , 48 , 48 );
	GET_SINGLE ( ResourceManager )->CreateSprite ( L"TileX" , GET_SINGLE ( ResourceManager )->GetTexture ( L"Tile" ) , 48 , 0 , 48 , 48 );
	GET_SINGLE ( ResourceManager )->CreateSprite ( L"Start_Off" , GET_SINGLE ( ResourceManager )->GetTexture ( L"Start" ) , 0 , 0 , 150 , 150 );
	GET_SINGLE ( ResourceManager )->CreateSprite ( L"Start_On" , GET_SINGLE ( ResourceManager )->GetTexture ( L"Start" ) , 150 , 0 , 150 , 150 );
	GET_SINGLE ( ResourceManager )->CreateSprite ( L"Edit_Off" , GET_SINGLE ( ResourceManager )->GetTexture ( L"Edit" ) , 0 , 0 , 150 , 150 );
	GET_SINGLE ( ResourceManager )->CreateSprite ( L"Edit_On" , GET_SINGLE ( ResourceManager )->GetTexture ( L"Edit" ) , 150 , 0 , 150 , 150 );
	GET_SINGLE ( ResourceManager )->CreateSprite ( L"Exit_Off" , GET_SINGLE ( ResourceManager )->GetTexture ( L"Exit" ) , 0 , 0 , 150 , 150 );
	GET_SINGLE ( ResourceManager )->CreateSprite ( L"Exit_On" , GET_SINGLE ( ResourceManager )->GetTexture ( L"Exit" ) , 150 , 0 , 150 , 150 );

	{
		Sprite* sprite = GET_SINGLE ( ResourceManager )->GetSprite ( L"Stage01" );

		SpriteActor* background = new SpriteActor ( );
		background->SetSprite ( sprite );

		const Vec2Int size = sprite->GetSize ( );
		background->SetPos ( Vec2( size.x/2,size.y/2 ) );
		_background = background;
	}

	{
		Sprite* sprite = GET_SINGLE ( ResourceManager )->GetSprite ( L"Start_On" );

		Player* player = new Player ( );
		player->SetSprite ( sprite );

		const Vec2Int size = sprite->GetSize ( );
		player->SetPos ( Vec2 ( size.x / 2 , size.y / 2 ) );
		_player = player;
	}

	{
		// 컴포넌트 방식
		GameObject* player = new GameObject ( );
		player->SetPos ( { 500,500 } );

		{
			Sprite* sprite = GET_SINGLE ( ResourceManager )->GetSprite ( L"Start_On" );
			SpriteRenderer* sr = new SpriteRenderer ( );
			sr->SetSprite ( sprite );
			player->AddComponent ( sr );
		}

		{
			PlayerMoveScript* pm = new PlayerMoveScript ( );
			player->AddComponent ( pm );
		}

		_go = player;
	}

	_background->BeginPlay ( );
	_player->BeginPlay ( );

	_go->Start ( );
}

void DevScene::Update ( )
{
	float delta = GET_SINGLE ( TimeManager )->GetDeltaTime ( );

	_background->Tick ( );
	_player->Tick ( );
	_go->Update ( );
}

void DevScene::Render ( HDC hdc )
{
	_background->Render ( hdc );
	_player->Render ( hdc );
	_go->Render ( hdc );
}
