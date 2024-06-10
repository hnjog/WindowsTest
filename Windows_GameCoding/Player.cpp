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

	if (_playerTurn == true)
	{
		RECT rect;
		rect.bottom = static_cast<LONG>(_pos.y - 60);
		rect.left = static_cast<LONG>(_pos.x - 10);
		rect.right = static_cast<LONG>(_pos.x + 10);
		rect.top = static_cast<LONG>(_pos.y - 80);

		HBRUSH brush = ::CreateSolidBrush(RGB(250, 236, 197));
		HBRUSH oldBrush = (HBRUSH)::SelectObject(hdc, brush);

		::Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);

		::SelectObject(hdc, oldBrush);
		::DeleteObject(brush);
	}

}

wstring Player::GetMeshKey()
{
	if (_playerType == PlayerType::MissileTank)
		return L"MissileTank";

	return L"CanonTank";
}
