#pragma once
#ifndef __ABSRACTFACTORY_H__
#define __ABSRACTFACTORY_H__			// 추상화 패턴

#include "Obj.h"
#include "Enum.h"

template<typename T>					// 클래스 템플릿 
class CAbstractFactory					
{
public:
	CAbstractFactory() {}
	~CAbstractFactory() {}

public:
	// static 선언으로 인해 이 파일 내에서만 접근 가능
	static CObj*		Create()		// 객체를 인스턴스화 하는 함수
	{
		CObj*		pObj = new T;		// CObj* 타입의 변수를 인스턴스 화 
		pObj->Initialize();				// pObj의 이니셜라이저 함수 호출

		return pObj;					// pObj 반환
	}
	// 대상의 중심 좌표 X,Y, 총알의 방향을 가지고 있는 객체 인스턴스화 하는 함수
	static CObj*		Create(float _fX, float _fY, BULLET::DIR eDir = BULLET::UP)
	{
		CObj*		pObj = new T;		// 객체를 인스턴스화 하는 함수
		pObj->Initialize();				// pObj의 이니셜라이저 함수 호출
		pObj->Set_Pos(_fX, _fY);		// pObj의 중심 좌표 세팅
		pObj->Set_Direction(eDir);		// pObj의 총알 방향 세팅

		return pObj;					// pObj 반환
	}
	// 대상의 중심 좌표 x,y, 각도를 가지고 있는 객체 인스턴스화 하는 함수
	static CObj*		Create(float _fX, float _fY, float _Angle)
	{
		CObj*		pObj = new T;		// 객체를 인스턴스화 하는 함수
		pObj->Initialize();				// pObj의 이니셜라이저 함수 호출
		pObj->Set_Pos(_fX, _fY);		// pObj의 중심 좌표 세팅
		pObj->Set_Angle(_Angle);		// pObj의 각도 세팅

		return pObj;					// pObj 반환
	}
};

#endif