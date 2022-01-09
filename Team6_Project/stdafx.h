// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include <vector>						// 벡터 사용 용도, 하지만 사용하지 않았음
#include <list>							// 리스트 사용 용도, 총알 & OBJID 담기 위함
#include <algorithm>					// 알고리즘 함수 사용 용도, for_each() 

using namespace std;					// c++ 표준 라이브러리 사용 용도, std안에 다 있음