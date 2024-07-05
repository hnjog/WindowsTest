#include "pch.h"
#include"BoxCollider.h"

BoxCollider::BoxCollider ( )
	:Super ( ColliderType::Box )
{
}

BoxCollider::~BoxCollider ( )
{
	Super::~Collider ( );
}

void BoxCollider::BeginPlay ( )
{
	Super::BeginPlay ( );
}

void BoxCollider::TickComponent ( )
{
	Super::TickComponent ( );
}

void BoxCollider::Render ( HDC hdc )
{
	Super::Render (hdc );
}

bool BoxCollider::CheckCollision ( Collider* other )
{
	return false;
}
