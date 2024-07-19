#include"pch.h"
#include"TilemapActor.h"
#include"Tilemap.h"
#include"Sprite.h"
#include"ResourceManager.h"
#include"SceneManager.h"
#include"InputManager.h"

TilemapActor::TilemapActor ( )
{
}

TilemapActor::~TilemapActor ( )
{
}

void TilemapActor::BeginPlay ( )
{
	Super::BeginPlay ( );
}

void TilemapActor::Tick ( )
{
	Super::Tick ( );
}

void TilemapActor::Render ( HDC hdc )
{
	Super::Render (hdc );

	if ( _tilemap == nullptr )
		return;

	if ( _showDebug == false )
		return;

	const Vec2Int mapSize = _tilemap->GetMapSize ( );
	const int32 tileSize = _tilemap->GetTileSize ( );

	vector<vector<Tile>>& tiles = _tilemap->GetTiles ( );

	Sprite* spriteO = GET_SINGLE ( ResourceManager )->GetSprite ( L"TileO" );
	Sprite* spriteX = GET_SINGLE ( ResourceManager )->GetSprite ( L"TileX" );

	Vec2 cameraPos = GET_SINGLE ( SceneManager )->GetCameraPos ( );

	for ( int32 y = 0; y < mapSize.y; y++ )
	{
		for ( int32 x = 0; x < mapSize.x; x++ )
		{
			//TODO
			if ( x < 0 || x >= mapSize.x )
				continue;
			if ( y < 0 || y >= mapSize.x )
				continue;

			switch ( tiles[y][x].value )
			{
			case 0:
			{
				::TransparentBlt ( hdc ,
					0 ,
					0 ,
					TILE_SIZEX ,
					TILE_SIZEY ,
					spriteO->GetDC ( ) ,
					spriteO->GetPos ( ).x ,
					spriteO->GetPos ( ).y ,
					TILE_SIZEX ,
					TILE_SIZEY ,
					spriteO->GetTransparent ( )
					);
			}
				break;

			}

		}

	}

}
