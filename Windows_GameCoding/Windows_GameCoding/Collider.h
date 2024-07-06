#pragma once

#include"Component.h"

class BoxCollider;
class SphereCollider;

class Collider : public Component
{
	using Super = Component;
public:
	Collider ( ColliderType colliderType );
	virtual ~Collider ( ) override;

	virtual void BeginPlay ( ) override;
	virtual void TickComponent ( ) override;
	virtual void Render ( HDC hdc ) override;

	virtual bool CheckCollision ( Collider* other );

	ColliderType GetColliderType ( ) { return _colliderType; }
	void SetShowDebug ( bool show ) { _showDebug = show; }
	
public:
	static bool CheckCollisionBox2Box ( BoxCollider* b1, BoxCollider* b2 );
	static bool CheckCollisionSphere2Box ( SphereCollider* s1, BoxCollider* b1 );
	static bool CheckCollisionSphere2Sphere ( SphereCollider* s1, SphereCollider* s2 );

protected:
	ColliderType _colliderType;
	bool _showDebug = true;

	// 부딪힌 녀석을 체크?
public:
	// 이거 서로 참조
	unordered_set<Collider*> _collisionMap;
};