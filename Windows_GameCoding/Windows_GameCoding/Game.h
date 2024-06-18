#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	HWND _hwnd = {}; // Window Handle
	HDC _hdc = {};	 // Device Context Handle

private:
	// Double Buffering
	RECT _rect;
	HDC _hdcBack = {};
	HBITMAP _bmpBack = {};

};

/*
	Handle : 운영 체제 내부 리소스 등을 참조하기 위한 일종의 pointer 혹은 인덱스 와 비슷한 개념

	프로그램이 특정한 리소스를 '필요'로 하지만,
	직접 다루기에는 위험한 경우 (저레벨, ex : 하드웨어)
	OS의 관리를 통해 해당 자원을 쉽고 안전하게 다루기 위함
	(OS의 '추상화' 그리고 '보호' 기능과 관련)

	HWND : 윈도우(창)를 제어
	HDC : 그래픽스 객체 식별, 출력 장치(프린터, 모니터 등)에 대한 그리기 명령을 수행하는데 사용

*/