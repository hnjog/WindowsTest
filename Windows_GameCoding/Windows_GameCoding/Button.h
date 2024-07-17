#pragma once

#include"UI.h"

class Sprite;

enum ButtonState
{
	BS_Default,
	//BS_Hovered,
	BS_Pressed,
	BS_Clicked,
	//
	BS_MaxCount,
};

class Button : public UI
{
	using Super = UI;
public:
	Button ( );
	virtual ~Button ( ) override;

	virtual void BeginPlay ( ) override;
	virtual void Tick ( )override;
	virtual void Render ( HDC hdc )override;

	Sprite* GetSprite ( ButtonState state ) { return _sprites[ state ]; }

	void SetCurrentSprite ( Sprite* sprite ) { _currentSprite = sprite; }
	void SetSprite ( Sprite* sprite , ButtonState state ) { _sprites[ state ] = sprite; }
	void SetButtonState ( ButtonState state );

	void OnClickButton ( ) {}

protected:
	Sprite* _currentSprite = nullptr;
	Sprite* _sprites[ BS_MaxCount ] = {};
	ButtonState _state = BS_Default;

	float _sumTime = 0.f;

public:
	// 함수 포인터 + 함수 객체를 모두 쉽게 사용 가능한 훌륭한 녀석
	std::function<void ( void )> _onClick = nullptr;

	// 템플릿을 이용한 마개조 대리자
	template<typename T>
	void AddOnClickDelegate ( T* owner , void ( T::* func )() )
	{
		_onClick = [owner, func]( )
			{
				(owner->*func) ( );
			};
	}
};