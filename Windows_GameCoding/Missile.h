#pragma once
#include "Object.h"
class Missile :
    public Object
{
public:
    Missile();
    virtual ~Missile();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    void setAngle(float angle) { _angle = angle; }

protected:
    float _angle = 0.f;

    float _sumTime = 0.f;
    // _target이 '없어졌'을 때,
    Object* _target = nullptr;
};

