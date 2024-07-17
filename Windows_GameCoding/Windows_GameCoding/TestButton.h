#pragma once
#include "Button.h"

class TestButton : public Button
{
	using Super = Button;
public:
	TestButton ( );
	virtual ~TestButton ( ) override;

	virtual void BeginPlay ( ) override;
	virtual void Tick ( ) override;
	virtual void Render ( HDC hdc ) override;


};

// UI 에서 이런식으로 상속하여 사용하는 것보다는
// 콜백 함수를 사용하는 편이 좋다