#include "pch.h"
#include"Collider.h"
#include"Actor.h"
#include"BoxCollider.h"
#include"SphereCollider.h"

Collider::Collider ( ColliderType colliderType )
	:_colliderType(colliderType )
{
}

Collider::~Collider ( )
{
	Super::~Component ( );
}

void Collider::BeginPlay ( )
{
	Super::BeginPlay ( );
}

void Collider::TickComponent ( )
{
	Super::TickComponent ( );

}

void Collider::Render ( HDC hdc )
{
	Super::Render ( hdc );
}

bool Collider::CheckCollision ( Collider* other )
{

	return false;
}

bool Collider::CheckCollisionBox2Box ( BoxCollider* b1 , BoxCollider* b2 )
{
	// 두 box 타입간

	return false;
}

bool Collider::CheckCollisionSphere2Box ( SphereCollider* s1 , BoxCollider* b1 )
{
	return false;
}

bool Collider::CheckCollisionSphere2Sphere ( SphereCollider* s1 , SphereCollider* s2 )
{
	Vec2 p1 = s1->GetOwner ( )->GetPos ( );
	float r1 = s1->GetRadius ( );

	Vec2 p2 = s2->GetOwner ( )->GetPos ( );
	float r2 = s2->GetRadius ( );

	Vec2 dir = p1 - p2;
	float dist = dir.Length ( );

	return dist <= r1 + r2;
}
