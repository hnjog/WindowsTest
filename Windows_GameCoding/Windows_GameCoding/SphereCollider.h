#pragma once

#include"Collider.h"

class SphereCollider : public Collider
{
	using Super = Collider;
public:
	SphereCollider (  );
	virtual ~SphereCollider ( ) override;

	virtual void BeginPlay ( ) override;
	virtual void TickComponent ( ) override;
	virtual void Render ( HDC hdc ) override;

	virtual bool CheckCollision ( Collider* other );


};