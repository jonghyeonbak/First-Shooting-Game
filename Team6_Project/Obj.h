#pragma once
#ifndef __OBJ_H__
#define __OBJ_H__					// 객체의 공통된 정보들을 모아놓은 클래스

#include "Define.h"					
#include "Struct.h"
#include "Enum.h"

class CObj												// 많은 클래스들의 부모 클래스
{
public:
	CObj();
	virtual ~CObj();									// 상속받는 클래스가 있으므로 소멸자를 가상으로 생성, 깊은 복사를 위함

public:
	void			Set_Pos(float _fX, float _fY);		// 대상 좌표 세팅
	void			Set_Size(float _fCX, float _fCY);	// 대상 사이즈 세팅
	void			Set_Direction(BULLET::DIR _eDir);	// 대상의 총알 방향 세팅
	void			Set_Dead(void);						// 대상을 죽이는 함수
	void			Set_Hp(int _Damage);				// 대상의 hp를 데미지만큼 감소시키는 함수
	void			Set_Angle(float _fAngle);			// 대상 각도 세팅
	void			Set_Target(CObj* _pTarget);			// 타겟 세팅, 반환 CObj*형 변수
	void			Set_PosX(float _fX);				// 대상 중점 좌표 x 세팅
	void			Set_PosY(float _fY);				// 대상 중점 좌표 y 세팅
	void			Set_Speed(float _fSpeed);			// 대상 스피드 세팅

	const INFO&		Get_Info(void) const { return m_tInfo; }	// INFO 타입의 info 변수를 얻어 반환하는 함수, 포인터 대신 레퍼런스로 참조하는 형태
	const RECT&		Get_Rect(void) const { return m_tRect; }	// const를 붙여 코드의 안전성 향상

public:
	virtual void		Initialize(void)PURE;			// 부모 클래스의 함수이지만, 자식 클래스들도 사용할 것이므로, 순수 가상함수, 오버라이딩
	virtual int			Update(void)PURE;
	virtual void		Late_Update(void)PURE;
	virtual void		Render(HDC hDC)PURE;
	virtual void		Release(void)PURE;

	void				Update_Rect(void);				// rect를 업데이트하는 용도의 함수

protected:
	RECT			m_tRect;							// 4개의 좌표를 가지고 있는 사각형 구조체
	RECT			m_tRect2;
	INFO			m_tInfo;							// struct에 있는 구조체의 정보를 가지고 있는 변수
	INFO			m_tInfo2;
	float			m_fSpeed;							// 스피드
	float			m_fAngle;							// 각도
	float			m_fMaru_Angle;						// 우주선의 각도
	float			m_fDistance;						// 거리
	float			m_fMaru_Distance;
	bool			m_bDead;							// 대상의 생존 유무 확인 bool 변수
	BULLET::DIR		m_eDir;								// 총알 방향 확인 변수
	CObj*			m_pTarget;							// 타겟 변수
	STATUS			m_tStat;							// 대상의 체력, 공격력을 담는 변수

};

#endif // !__OBJ_H__
