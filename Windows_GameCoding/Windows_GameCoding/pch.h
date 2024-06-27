#pragma once

#include"Types.h"
#include"Defines.h"
#include"Enums.h"
#include"Values.h"

#include<Windows.h>
#include<vector>
#include<list>
#include<map>
#include<unordered_map>
#include<string>
#include<algorithm>

using namespace std;

// c++ 20
#include <format>
#include <filesystem>

namespace fs = std::filesystem;

// memory check
// 추적? (서버 작업 등에선 임의의 new를 만들어 작업할 수 있음)

#define _CRTDEBG_MAP_ALLOC
#include<cstdlib>
#include<crtdbg.h>

#ifdef _DEBUG
// 현재 실행 중인 파일의 몇 번째 줄에서 new 가 선언되었는지 확인 가능
#define new new(_NORMAL_BLOCK,__FILE__,__LINE__)
// 체크하고 싶은 녀석에게

#endif

// 특정한 라이브러리를 링커에게 링크하도록 지시
// #include 와의 비교
// #include 는 '전처리기 지시문' 이라서
// '컴파일 이전에 미리 복붙' -> 실행 파일 용량 커짐 +
// 라이브러리 크기에 따라서 컴파일 시간이 늘어날 수 있음
// 
// 반면 #pragma comment 는
// '링크 지시문' 이기에 실행 파일의 크기를 줄일 수 있으며,
// 컴파일 시간 역시 줄일 수 있음
// 다만, 일부 플랫폼에 종속적(ex : Windows)이다 (+ 가독성 이슈)
//
#pragma comment(lib,"msimg32.lib")

#include"Utils.h"