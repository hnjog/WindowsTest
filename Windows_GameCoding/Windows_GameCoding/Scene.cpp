#include "pch.h"
#include "Scene.h"
#include"Actor.h"
#include"UI.h"
#include"TimeManager.h"
#include"SceneManager.h"
#include"CollisionManager.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Init()
{
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->BeginPlay();
		}
	}

	for (UI* ui : _uis)
	{
		ui->BeginPlay();
	}
}

void Scene::Update()
{
	GET_SINGLE(CollisionManager)->Update();

	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->Tick();
		}
	}

	for (UI* ui : _uis)
	{
		ui->Tick();
	}
}

void Scene::Render(HDC hdc)
{
	for (const vector<Actor*>& actors : _actors)
	{
		for (Actor* actor : actors)
		{
			actor->Render(hdc);
		}
	}

	for (UI* ui : _uis)
	{
		ui->Render(hdc);
	}
}

void Scene::AddActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	_actors[actor->GetLayer()].push_back(actor);
}

void Scene::RemoveActor(Actor* actor)
{
	if (actor == nullptr)
		return;

	vector<Actor*>& v = _actors[actor->GetLayer()];

	// std::remove는 삭제할 위치를 찾아주는 것임을 잊지말자
	auto findIt = std::remove(v.begin(), v.end(), actor);
	v.erase(findIt, v.end());
}
