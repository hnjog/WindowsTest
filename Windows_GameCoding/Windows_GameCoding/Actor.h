#pragma once

class Component;
class Collider;

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

	void SetLayer ( LAYER_TYPE type ) { _layer = type; }
	LAYER_TYPE GetLayer ( ) { return _layer; }

	void AddComponent ( Component* component );
	void RemoveComponent ( Component* component );

	Component* GetCollider ( );

	// 충돌 이벤트
	virtual void OnComponentBeginOverlap (Collider* collider, Collider* other );
	virtual void OnComponentEndOverlap (Collider* collider, Collider* other );

protected:
	// 모든 actor가 '반드시' 화면에 그려져야 하진 않는다
	Vec2 _pos = { 0,0 };
	Vec2 _destPos = { 0, 0 };
	LAYER_TYPE _layer = LAYER_OBJECT;
	vector<Component*> _components;
};

