#include "pch.h"
#include"CollisionManager.h"
#include"Collider.h"
#include"Actor.h"

void CollisionManager::Init ( )
{
}

void CollisionManager::Update ( )
{
	vector<Collider*>& colliders = _colliders;

	for ( int32 i = 0; i < colliders.size ( ); i++ )
	{
		for ( int32 j = i + 1; j < colliders.size ( ); j++ )
		{
			Collider* src = colliders[ i ];
			Collider* dest = colliders[ j ];

			if ( src->CheckCollision ( dest ) )
			{
				// 충돌
			}
			else
			{
				// 충돌 아님
			}
		}
	}

}

void CollisionManager::AddCollider ( Collider* collider )
{
	_colliders.push_back ( collider );
}

void CollisionManager::RemoveCollider ( Collider* collider )
{
	auto it= std::remove ( _colliders.begin ( ) , _colliders.end ( ) , collider );
	_colliders.erase ( it , _colliders.end ( ) );
}
