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
	static bool CheckCollisionBox2Box ( BoxCollider* b1 , BoxCollider* b2 );
	static bool CheckCollisionSphere2Box ( SphereCollider* s1 , BoxCollider* b1 );
	static bool CheckCollisionSphere2Sphere ( SphereCollider* s1 , SphereCollider* s2 );

	void SetCollisionLayer ( COLLISION_LAYER_TYPE layer ) { _collisionLayer = layer; }
	COLLISION_LAYER_TYPE GetCollisionLayer ( ) { return _collisionLayer; }

	void SetCollisionFlag ( uint32 flag ) { _collisionFlag = flag; }
	uint32 GetCollisionFlag ( ) { return _collisionFlag; }

	void ResetCollisionFlag ( ) { _collisionFlag = 0; }
	void AddCollisionFlagLayer ( COLLISION_LAYER_TYPE layer );
	void RemoveCollisionFlagLayer ( COLLISION_LAYER_TYPE layer );

protected:
	ColliderType _colliderType;
	bool _showDebug = true;

public:
	// 이거 서로 참조
	unordered_set<Collider*> _collisionMap;

	COLLISION_LAYER_TYPE _collisionLayer = CLT_OBJECT;

	// 비트 플래그를 통하여 특정 타입의 레이어만 충돌하도록
	uint32 _collisionFlag = 0xFFFFFFFF;
};