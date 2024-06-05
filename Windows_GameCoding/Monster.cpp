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

	// ���� ��ġ -> ���콺 ���Ϳ�
	// ���� ��ġ -> �ٶ󺸴� �� ��ġ�� ���͸�
	// ���������μ� cos ���� ������
	// �װ� ���ﰢ�Լ��� ���� angle�� ����
	float dot = monsterToMouseDir.Dot(_lookDir);

	// radian���� ����
	float radian = ::acos(dot);  // 0 ~ 180 ������ ���� Ƣ��� (���Լ��� ������ �Ѱ�)
	float angle = radian * 180 / 3.14f;

	float cross = _lookDir.Cross(monsterToMouseDir);
	//  
	if (cross < 0)
		angle = 360 - angle;

	// ������� 90~ 180 �̶�� �Ĺ��� �ɷ� �ľ��� �� ����
	{
		wstring str = std::format(L"angle({0})", angle);
		Utils::DrawTextW(hdc, { 20,50 }, str);
	}
}
