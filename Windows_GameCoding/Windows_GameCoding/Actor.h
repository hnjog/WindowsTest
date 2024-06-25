#pragma once

class Actor
{
public:
	Actor ( );
	virtual ~Actor ( );

	virtual void BeginPlay ( );
	virtual void Tick ( );
	virtual void Render ( HDC hdc );

	void SetPos ( Vec2 pos ) { _pos = pos; }
	Vec2 GetPos ( ) { return _pos; }

protected:
	// 모든 actor가 '반드시' 화면에 그려져야 하진 않는다
	Vec2 _pos = { 0,0 };
};

