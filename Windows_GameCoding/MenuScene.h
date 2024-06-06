#pragma once
#include "Scene.h"
class MenuScene : public Scene
{
public:
	MenuScene();
	virtual ~MenuScene();

	// 순수 가상 함수
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;



};

