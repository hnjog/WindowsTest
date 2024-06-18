#pragma once
#include "Scene.h"

class EditScene :
	public Scene
{
public:
	EditScene();
	virtual ~EditScene();

	// 순수 가상 함수
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

private:
	vector<pair<POINT, POINT>> _lines;

	bool _setOrigin = true;
	POINT _lastPos = {};
};