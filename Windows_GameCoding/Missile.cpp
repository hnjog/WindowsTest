#include "pch.h"
#include "Missile.h"
#include"TimeManager.h"
#include"ObjectManager.h"

Missile::Missile() :Object(ObjectType::Projectile)
{
}

Missile::~Missile()
{
}

void Missile::Init()
{
	_stat.hp = 1;
	_stat.maxHp = 1;
	_stat.speed = 600;
}

void Missile::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (_target == nullptr)
	{
		_pos.x += _stat.speed * deltaTime * cos(_angle);
		_pos.y -= _stat.speed * deltaTime * sin(_angle);

		_sumTime += deltaTime;
		if (_sumTime >= 0.2f)
		{
			// 주변의 target 지정
			const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
			for (Object* object : objects)
			{
				if (object->GetObjectType() == ObjectType::Monster)
				{
					_target = object;
					break;
				}
			}
		}
	}
	else // target을 따라
	{
		// 방향
		Vector dir = _target->GetPos() - GetPos();

		// 정규화
		dir.Normalize();

		// 정규화한 방향으로 델타타임과 스피드 적용
		Vector moveDir = dir * _stat.speed * deltaTime;

		// 현재 위치에 더해줌으로서 적용
		_pos += moveDir;
	}

	// 충돌
	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();
	for (Object* object : objects)
	{
		if (object == this)
			continue;

		if (object->GetObjectType() != ObjectType::Monster)
			continue;

		Pos p1 = GetPos();
		Pos p2 = object->GetPos();

		Vector dir = p2 - p1;

		float dist = dir.Length();

		if (dist < 25)
		{
			// 괜찮나 이거
			GET_SINGLE(ObjectManager)->Remove(object);
			GET_SINGLE(ObjectManager)->Remove(this);
			return;
		}
	}

	// 제거
	if (_pos.y < -100)
	{
		GET_SINGLE(ObjectManager)->Remove(this);
		//...? -> 나 자신을 삭제 요청하고 여기로 다시 오는게 이상한데..?
		// 정확히는 바로 return을 때려야 하고 이 이후로는 코드 작성을 하면 안됨
		// smartPointer를 사용하는 이유..??
		return;
	}
}

void Missile::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 25);
}
