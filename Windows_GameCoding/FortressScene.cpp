#include "pch.h"
#include "FortressScene.h"
#include "UIManager.h"
#include "Player.h"
#include "LineMesh.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TimeManager.h"

FortressScene::FortressScene()
{
}

FortressScene::~FortressScene()
{
}

void FortressScene::Init()
{
	GET_SINGLE(UIManager)->Init();

	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::MissileTank);
		player->SetPlayerId(0);
		player->SetPlayerTurn(true);

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 100,400 });
	}

	{
		Player* player = GET_SINGLE(ObjectManager)->CreateObject<Player>();
		player->SetPlayerType(PlayerType::CanonTank);
		player->SetPlayerId(1);
		player->SetPlayerTurn(false);

		GET_SINGLE(ObjectManager)->Add(player);

		player->SetPos(Vector{ 700,400 });
	}

}

void FortressScene::Update()
{
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (auto* object : objects)
	{
		object->Update();
	}

	_sumTime += deltaTime;
	if (_sumTime >= 1)
	{
		_sumTime = 0.f;

		// UIManger의 데이터를 가져다 쓰는 방식으로
		// 본래는 해당 Scene이나 다른 주체에서 관리하는 것이 더 바람직하긴 하다
		int32 time = GET_SINGLE(UIManager)->GetRemainTime();
		time = max(0, time - 1);
		GET_SINGLE(UIManager)->SetRemainTime(time);

		if (time == 0)
			ChangePlayerTurn();
	}
}

void FortressScene::Render(HDC hdc)
{
	GET_SINGLE(UIManager)->Render(hdc);

	const vector<Object*> objects = GET_SINGLE(ObjectManager)->GetObjects();

	for (auto* object : objects)
	{
		object->Render(hdc);
	}
}

void FortressScene::ChangePlayerTurn()
{
	// player가 2명일 때의 가정
	if (_playerTurn == 1)
	{

	}
	else
	{

	}
}
