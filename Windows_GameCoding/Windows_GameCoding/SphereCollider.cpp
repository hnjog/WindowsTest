#include "pch.h"
#include"SphereCollider.h"

SphereCollider::SphereCollider ( )
	:Super(ColliderType::Sphere )
{
}

SphereCollider::~SphereCollider ( )
{
	Super::~Collider ( );
}

void SphereCollider::BeginPlay ( )
{
	Super::BeginPlay ( );
}

void SphereCollider::TickComponent ( )
{
	Super::TickComponent ( );
}

void SphereCollider::Render ( HDC hdc )
{
	Super::Render (hdc );
}

bool SphereCollider::CheckCollision ( Collider* other )
{
	return false;
}
