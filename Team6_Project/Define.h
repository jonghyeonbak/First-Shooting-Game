#pragma once
#ifndef  __DEFINE_H__
#define   __DEFINE_H__			// 매크로, 컴파일러가 실행되기 전에 전처리기에서 단순 치환

#define WINCX	 1280			// 윈도우 가로 사이즈
#define WINCY	  800			// 윈도우 세로 사이즈

#define PURE	  = 0			// 순수 가상 함수임을 알리기 위해 0을 넣는데, 가독성을 높이기위해 만듬.

#define OBJ_LIFE	0			// 인스턴스(물체)가 살아있다면 0 반환
#define OBJ_DEAD	1			// 인스턴스(물체)가 죽었다면 1 반환

#define PI			3.141592f	// 파이, 각도와 라디안 변환할 때 사용

// 일반적으로 컴퓨터는 라디안 형식이다
#define DEGREE_RADIAN(p)	((p) * (PI/180))	// 각도 -> 라디안.
#define RADIAN_DEGREE(p)	((p) * (180/PI))	// 라디안 -> 각도

extern	HWND		g_hWnd;						// HWND으로 핸들을 사용하기 위해 선언.
// HWND의 값은 숫자인데, 이 윈도우의 번호가 몇 번이다를 알고 있어야 운영체제에서 관리 가능하다.
extern	POINT		Point;						// 대상의 좌표를 알기위해 선언
extern  DWORD		m_Dir;						// GetTickCount처럼 시간을 담기위해 선언

#endif // ! __DEFINE_H__