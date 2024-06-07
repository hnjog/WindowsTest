#pragma once
#include "Object.h"

enum class PlayerType
{
    CannonTank,
    MissileTank,
};

class Player :
    public Object
{
public:
    Player();
    virtual ~Player();

    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC hdc) override;

    wstring GetMeshKey();

public:
    PlayerType _playerType = PlayerType::CannonTank;
};

