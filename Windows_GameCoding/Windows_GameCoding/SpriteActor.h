#pragma once

#include "Actor.h"

class Sprite;

class SpriteActor : public Actor
{
	using Super = Actor; // 언리얼 방식 -> 부모 클래스에서 넣어둔 공용 부분을 가져다 쓰기 위함
public:
	SpriteActor ( );
	virtual ~SpriteActor ( ) override;

	virtual void BeginPlay ( )override;
	virtual void Tick ( )override;
	virtual void Render ( HDC hdc )override;

	void SetSprite ( Sprite* sprite ) { _sprite = sprite; }

protected:
	Sprite* _sprite = nullptr;

};

