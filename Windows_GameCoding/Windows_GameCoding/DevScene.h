#pragma once
#include "Scene.h"

class Actor;

class DevScene : public Scene
{
public:
	DevScene();
	virtual ~DevScene();

	// 순수 가상 함수
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

public:
	Actor* _background;
};

