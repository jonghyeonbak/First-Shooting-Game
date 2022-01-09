#include "stdafx.h"
#include "Obj.h"


CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f)
	, m_fDistance(0.f)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));			// 구조체의 메모리를 0으로 초기화
	ZeroMemory(&m_tRect, sizeof(m_tRect));
}


CObj::~CObj()
{
}
void CObj::Set_Hp(int _Damage)						
{
	m_tStat.iHp -= _Damage;
}

void CObj::Set_Size(float _fCX, float _fCY)
{
	m_tInfo.fCX = _fCX;
	m_tInfo.fCY = _fCY;
}

void CObj::Set_Speed(float _fSpeed)
{
	m_fSpeed = _fSpeed;
}

void CObj::Set_Pos(float _fX, float _fY)
{
	m_tInfo.fX = _fX;
	m_tInfo.fY = _fY;

	m_tInfo2.fX = _fX;
	m_tInfo2.fY = _fY;
}

void CObj::Set_Direction(BULLET::DIR _eDir)
{
	m_eDir = _eDir;
}

void CObj::Set_Dead(void)					// 대상을 죽이는 함수
{
	m_bDead = true;
}

void CObj::Set_Angle(float _fAngle)
{
	m_fAngle = _fAngle;
}

void CObj::Set_Target(CObj* _pTarget)
{
	m_pTarget = _pTarget;
}

void CObj::Set_PosX(float _fX)
{
	m_tInfo.fX += _fX;
}

void CObj::Set_PosY(float _fY)
{
	m_tInfo.fY += _fY;
}

void CObj::Update_Rect(void)
{
	m_tRect.left = long(m_tInfo.fX - (m_tInfo.fCX * 0.5f));   // 사각형 왼쪽 좌표 = m_tInfo의 중점좌표x - (m_tInfo의 가로 사이즈 /2)
 // 그림을 그려보면 바로 알 수 있음. 0에서부터 사각형의 왼쪽까지의 거리가 나옴, 그 말인 즉슨 사각형의 왼쪽 좌표가 나옴
	m_tRect.right = long(m_tInfo.fX + (m_tInfo.fCX * 0.5f));
	m_tRect.top = long(m_tInfo.fY - (m_tInfo.fCY * 0.5f));
	m_tRect.bottom = long(m_tInfo.fY + (m_tInfo.fCY * 0.5f));

	m_tRect2.left = long(m_tInfo2.fX - (m_tInfo2.fCX * 0.5f));
	m_tRect2.right = long(m_tInfo2.fX + (m_tInfo2.fCX * 0.5f));
	m_tRect2.top = long(m_tInfo2.fY - (m_tInfo2.fCY * 0.5f));
	m_tRect2.bottom = long(m_tInfo2.fY + (m_tInfo2.fCY * 0.5f));
}
