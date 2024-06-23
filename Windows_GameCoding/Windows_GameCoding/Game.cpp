#include "pch.h"
#include "Game.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"

Game::Game()
{
}

Game::~Game()
{
	GET_SINGLE(SceneManager)->Clear();
	GET_SINGLE(ResourceManager)->Clear();
	// 진짜 마지막에 넣는것이 좋긴 함
	_CrtDumpMemoryLeaks();
	// 주소가 안나온다면 보통 전역 변수 등이 나중에 지워지는 것을 의심
	// 그래서 진짜 프로그램이 끝나는 시점에서 체크하는 것이 좋음
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	_hdc = ::GetDC(hwnd);

	::GetClientRect(hwnd, &_rect);

	// hdc와 호환되는 dc 생성
	_hdcBack = ::CreateCompatibleDC(_hdc);
	// _hdc와 호환되는 비트맵 생성 (텍스쳐 같은 2d 화면용)
	_bmpBack = ::CreateCompatibleBitmap(_hdc, _rect.right, _rect.bottom);

	// dc와 비트맵 연결 (그릴 장치에 그릴 텍스쳐를 끼워넣는 느낌?)
	// 이후 _hdcBack에 그려지는 것은 해당 비트맵에 적용된다 (반환값 : 이전에 선택된 비트맵)
	HBITMAP prev = (HBITMAP)::SelectObject(_hdcBack, _bmpBack);
	::DeleteObject(prev); // 이전 것은 삭제 (메모리 누수 방지)


	GET_SINGLE(TimeManager)->Init();
	GET_SINGLE(InputManager)->Init(hwnd);
	GET_SINGLE(SceneManager)->Init();
	GET_SINGLE(ResourceManager)->Init(hwnd,fs::path(L"D:\\Practice\\WindowsTest\\Windows_GameCoding\\Resources" ) );

	GET_SINGLE(SceneManager)->ChangeScene(SceneType::DevScene);
}

void Game::Update()
{
	GET_SINGLE(TimeManager)->Update();
	GET_SINGLE(InputManager)->Update();
	GET_SINGLE(SceneManager)->Update();
}

void Game::Render()
{
	uint64 fps = GET_SINGLE(TimeManager)->GetFps();
	float deltaTime = GET_SINGLE(TimeManager)->GetDeltaTime();

	GET_SINGLE ( SceneManager )->Render ( _hdcBack );

	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		wstring str = std::format(L"Mouse({0},{1})",mousePos.x,mousePos.y);
		::TextOut(_hdcBack, 20, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	{
		wstring str = std::format(L"FPS({0}), DT({1} ms)", fps, static_cast<int32>(deltaTime * 1000));
		::TextOut(_hdcBack, 650, 10, str.c_str(), static_cast<int32>(str.size()));
	}

	// Double Buffering

	// 고속 복사 (memcpy랑 비슷)
	::BitBlt(_hdc, 0, 0, _rect.right, _rect.bottom, _hdcBack, 0, 0, SRCCOPY);
	::PatBlt(_hdcBack, 0, 0, _rect.right, _rect.bottom, WHITENESS); // 하얀색 채우기 (새로 그릴 버퍼를 비워준다)

	// 버퍼를 2개 만들어
	// '한 번'에 그려준 뒤
	// 이후 결과물을 바꿔치는 방식
	// 버퍼를 하나 사용하면, 
	// 다른 하나를 '새로' 그릴 때, 덮어씌우기 때문에 '깜빡 거림'
	// 그래픽 작업이 '직접적인 DC(화면 장치 컨텍스트' 에서 이루어짐
	// 
	// UI와 캐릭터, 이펙트를 순서대로 그릴 때,
	// 싱글 버퍼인 경우, 각자를 '그릴 때' 마다 화면을 지우고 다시 그리기에
	// 마치 덮어쓰거나, 깜빡 거리는 현상이 보일 수 있음
	// 그러나 더블 버퍼링의 경우,
	// '다 그린 후,' 스와핑을 해주기에 그러한 현상이 없음
	//

}
