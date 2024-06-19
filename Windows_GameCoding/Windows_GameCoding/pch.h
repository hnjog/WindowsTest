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

#include"Utils.h"