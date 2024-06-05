#include "pch.h"
#include "Player.h"
#include"TimeManager.h"
#include"InputManager.h"
#include"Missile.h"
#include"ObjectManager.h"
#include"ResourceManager.h"
#include"LineMesh.h"

Player::Player() :Object(ObjectType::Player)
{

}

Player::~Player()
{

}

void Player::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 500;

	_pos.x = 400;
	_pos.y = 500;

}

void Player::Update()
{
	float delta = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_pos.x -= _stat.speed * delta;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_pos.x += _stat.speed * delta;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		_pos.y -= _stat.speed * delta;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		_pos.y += _stat.speed * delta;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{
		_barrelAngle += 10 * delta;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{
		_barrelAngle -= 10 * delta;
	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{
		Missile* missile = GET_SINGLE(ObjectManager)->CreateObject<Missile>();
		missile->SetPos(GetFirePos());
		missile->setAngle(_barrelAngle);
		GET_SINGLE(ObjectManager)->Add(missile);
	}
}

void Player::Render(HDC hdc)
{
	const LineMesh* mesh= GET_SINGLE(ResourceManager)->GetLineMesh(L"Player");
	if (mesh)
	{
		mesh->Render(hdc,_pos);
	}

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	Utils::DrawLine(hdc, _pos, GetFirePos());

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

Pos Player::GetFirePos()
{
	Pos firePos = _pos;

	// x좌표에 뭘 더해줘야 할까?
	// cos() = a / c 이기에
	// firePos.x 에 같은 x 축 좌표인 a를 구하기 위해
	// c인 _barreLength를 곱해줌
	firePos.x += _barrelLength * cos(_barrelAngle);
	firePos.y -= _barrelLength * sin(_barrelAngle);

	return firePos;
}
