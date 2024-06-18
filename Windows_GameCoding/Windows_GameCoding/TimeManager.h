#pragma once
#include"Defines.h"

class TimeManager
{
	DECLARE_SINGLE(TimeManager);

public:
	void Init();
	void Update();

	uint64 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }

private:
	uint64 _frequency = 0;
	uint64 _prevCount = 0;
	float _deltaTime = 0.f;

private:
	uint64 _frameCount = 0;
	float _frameTime = 0.f;
	uint64 _fps = 0;

};

