#pragma once
#include "Object.h"
class Monster :
    public Object
{
public:
    Monster();
    virtual ~Monster();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

public:
    Vector _lookPos = {};
    Vector _lookDir = {};

};