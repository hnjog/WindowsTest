#include "pch.h"
#include "ResourceManager.h"
#include"ResourceBase.h"
#include"Texture.h"

ResourceManager::~ResourceManager ( )
{
	Clear ( );
}

void ResourceManager::Init ( HWND hwnd, fs::path resourcePath )
{
	_hwnd = hwnd;
	_resourcePath = resourcePath;

	//fs::current_path()  : 현재 경로
	//_resourcePath.relative_path() : 상대 경로
	//fs::absolute(_resourcePath ) : 절대경로 등등이 존재하니 필요 시 검색

}

void ResourceManager::Clear ( )
{
	for ( auto& item : _textures )
		SAFE_DELETE ( item.second );

	_textures.clear ( );
}

Texture* ResourceManager::LoadTexture ( const wstring& key , const wstring& path , uint32 transparent )
{
	if ( _textures.find ( key ) != _textures.end ( ) )
	{
		return _textures[ key ];
	}

	// /로 합치기
	fs::path fullPath = _resourcePath / path;

	Texture* texture = new Texture ( );
	texture->LoadBmp ( _hwnd , fullPath.c_str ( ) );
	texture->SetTransparent ( transparent );
	_textures[ key ] = texture;

	return texture;
}

