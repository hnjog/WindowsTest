#pragma once

class ResourceBase;

class ResourceManager
{
public:
	DECLARE_SINGLE ( ResourceManager )

	~ResourceManager ( );

public:
	void Init (HWND hwnd, fs::path resourcePath );
	void Clear ( );

	const fs::path& GetResourcePath ( ) { return _resourcePath; }

private:
	// c++ 20 기준으로 제공하는 파일 입출력 방식
	HWND _hwnd;
	fs::path _resourcePath;
};

