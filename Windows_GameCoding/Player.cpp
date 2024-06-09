#include "pch.h"
#include "Player.h"
#include"TimeManager.h"
#include"InputManager.h"
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
	if (_playerTurn == false)
		return;

	float delta = GET_SINGLE(TimeManager)->GetDeltaTime();

	if (GET_SINGLE(InputManager)->GetButton(KeyType::A))
	{
		_dir = Dir::Left;
		_pos.x -= _stat.speed * delta;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::D))
	{
		_dir = Dir::Right;
		_pos.x += _stat.speed * delta;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::W))
	{
		//_pos.y -= _stat.speed * delta;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::S))
	{
		//_pos.y += _stat.speed * delta;
	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::Q))
	{

	}

	if (GET_SINGLE(InputManager)->GetButton(KeyType::E))
	{

	}

	if (GET_SINGLE(InputManager)->GetButtonDown(KeyType::SpaceBar))
	{

	}
}

void Player::Render(HDC hdc)
{
	float v = 1.0f;

	if (_dir == Dir::Right)
	{
		v = -1.0f;
	}

	const LineMesh* mesh= GET_SINGLE(ResourceManager)->GetLineMesh(GetMeshKey());
	if (mesh)
	{
		
		mesh->Render(hdc,_pos,0.5f * v,0.5f);
	}

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	//Utils::DrawLine(hdc, _pos, GetFirePos());

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);
}

wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank)
		return L"MissileTank";

	return L"CanonTank";
}
