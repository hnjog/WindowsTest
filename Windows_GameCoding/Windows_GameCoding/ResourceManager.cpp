#include "pch.h"
#include "ResourceManager.h"
#include"ResourceBase.h"

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

}

