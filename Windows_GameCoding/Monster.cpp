#include "pch.h"
#include "Monster.h"
#include"TimeManager.h"
#include"ObjectManager.h"
#include"InputManager.h"

Monster::Monster() :Object(ObjectType::Monster)
{
}

Monster::~Monster()
{
}

void Monster::Init()
{
	_stat.hp = 100;
	_stat.maxHp = 100;
	_stat.speed = 10;

	_pos = Pos{ 400,300 };

	_lookPos = Pos{ 550,70 };
	_lookDir = _lookPos - _pos;
	_lookDir.Normalize();
}

void Monster::Update()
{

}

void Monster::Render(HDC hdc)
{
	Utils::DrawCircle(hdc, _pos, 100);

	HPEN pen = ::CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN oldPen = (HPEN)::SelectObject(hdc, pen);

	{
		Utils::DrawLine(hdc, _pos, _lookPos);
	}

	::SelectObject(hdc, oldPen);
	::DeleteObject(pen);

	////
	Vector mousePos = GET_SINGLE(InputManager)->GetMousePos();
	Vector monsterToMouseDir = mousePos - _pos;
	monsterToMouseDir.Normalize();

	// 현재 위치 -> 마우스 벡터와
	// 현재 위치 -> 바라보는 곳 위치의 벡터를
	// 내적함으로서 cos 값을 가져옴
	// 그걸 역삼각함수를 통해 angle을 구함
	float dot = monsterToMouseDir.Dot(_lookDir);

	// radian으로 뱉음
	float radian = ::acos(dot);  // 0 ~ 180 사이의 값만 튀어나옴 (역함수의 범위적 한계)
	float angle = radian * 180 / 3.14f;

	float cross = _lookDir.Cross(monsterToMouseDir);
	//  
	if (cross < 0)
		angle = 360 - angle;

	// 결과값이 90~ 180 이라면 후방인 걸로 파악할 수 있음
	{
		wstring str = std::format(L"angle({0})", angle);
		Utils::DrawTextW(hdc, { 20,50 }, str);
	}
}
