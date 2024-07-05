#include "pch.h"
#include"Collider.h"

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
