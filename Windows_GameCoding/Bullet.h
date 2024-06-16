#pragma once
#include "Object.h"
class Bullet : public Object
{
public:
	Bullet();
	virtual ~Bullet();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	void SetSpeed ( Vector speed ) { _speed = speed; }

public:
	Vector _speed = {};
	
};

/*
	속도 (v->) : 거리 변화(s) / 시간(t)
	가속도(a->) : 속도 변화(->v) / 시간(t)


*/ 