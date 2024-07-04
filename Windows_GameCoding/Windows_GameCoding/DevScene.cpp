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
#include"Flipbook.h"

DevScene::DevScene ( )
{
}

DevScene::~DevScene ( )
{

	for ( vector<Actor*>& actors : _actors )
	{
		for ( Actor* actor : actors )
		{

			SAFE_DELETE ( actor );
		}

		actors.clear ( );
	}
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
		Texture* texture = GET_SINGLE ( ResourceManager )->GetTexture ( L"PlayerUp" );
		Flipbook* fb = GET_SINGLE ( ResourceManager )->CreateFlipbook ( L"FB_MoveUp" );
		fb->SetInfo ( { texture,L"FB_MoveUp",{200,200},0,9,1,0.5f } );
	}

	{
		Texture* texture = GET_SINGLE ( ResourceManager )->GetTexture ( L"PlayerDown" );
		Flipbook* fb = GET_SINGLE ( ResourceManager )->CreateFlipbook ( L"FB_MoveDown" );
		fb->SetInfo ( { texture,L"FB_MoveDown",{200,200},0,9,1,0.5f } );
	}

	{
		Texture* texture = GET_SINGLE ( ResourceManager )->GetTexture ( L"PlayerLeft" );
		Flipbook* fb = GET_SINGLE ( ResourceManager )->CreateFlipbook ( L"FB_MoveLeft" );
		fb->SetInfo ( { texture,L"FB_MoveLeft",{200,200},0,9,1,0.5f } );
	}

	{
		Texture* texture = GET_SINGLE ( ResourceManager )->GetTexture ( L"PlayerRight" );
		Flipbook* fb = GET_SINGLE ( ResourceManager )->CreateFlipbook ( L"FB_MoveRight" );
		fb->SetInfo ( { texture,L"FB_MoveRight",{200,200},0,9,1,0.5f } );
	}

	{
		Player* player = new Player ( );
		AddActor ( player );
	}

	{
		Sprite* sprite = GET_SINGLE ( ResourceManager )->GetSprite ( L"Stage01" );

		SpriteActor* background = new SpriteActor ( );
		background->SetSprite ( sprite );
		background->SetLayer ( LAYER_BACKGROUND );
		const Vec2Int size = sprite->GetSize ( );
		background->SetPos ( Vec2 ( size.x / 2 , size.y / 2 ) );
		AddActor ( background );
	}



	for ( const vector<Actor*>& actors : _actors )
	{
		for ( Actor* actor : actors )
		{
			actor->BeginPlay ( );
		}
	}


}

void DevScene::Update ( )
{
	float delta = GET_SINGLE ( TimeManager )->GetDeltaTime ( );

	for ( const vector<Actor*>& actors : _actors )
	{
		for ( Actor* actor : actors )
		{
			actor->Tick ( );
		}
	}
}

void DevScene::Render ( HDC hdc )
{

	for ( const vector<Actor*>& actors : _actors )
	{
		for ( Actor* actor : actors )
		{
			actor->Render ( hdc );
		}
	}
}

void DevScene::AddActor ( Actor* actor )
{
	if ( actor == nullptr )
		return;

	_actors[ actor->GetLayer ( ) ].push_back ( actor );
}

void DevScene::RemoveActor ( Actor* actor )
{
	if ( actor == nullptr )
		return;

	vector<Actor*>& v = _actors[ actor->GetLayer ( ) ];

	// std::remove는 삭제할 위치를 찾아주는 것임을 잊지말자
	auto findIt = std::remove ( v.begin ( ) , v.end ( ) , actor );
	v.erase ( findIt,v.end() );
}
