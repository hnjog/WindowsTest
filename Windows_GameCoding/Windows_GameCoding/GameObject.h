#pragma once

class Component;

// 유니티 방식 최상위 객체
// '컴포넌트' 개념 방식 (언리얼도 사용하지만, 유니티는 '부품화 경향이 강함'
class GameObject
{
public:
	GameObject ( );
	virtual ~GameObject ( );

	virtual void Start ( );
	virtual void Update ( );
	virtual void Render ( HDC hdc );

	void SetPos ( Vec2 pos ) { _pos = pos; }
	Vec2 GetPos ( ) { return _pos; }

	void AddComponent ( Component* component );


protected:
	Vec2 _pos = { 0,0 };
	vector<Component*> _components;
};