#include "stdafx.h"
#include "Monster_KF15.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"
#include "KF15_Bullet.h"

CMonster_KF15::CMonster_KF15()
	:m_tTime(0)
{
}


CMonster_KF15::~CMonster_KF15()
{
}

void CMonster_KF15::Initialize(void)
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;
	
	m_fSpeed = 2.f;
	m_fDistance = 425.f;

	m_fGun_Distance = 100.f;
	m_tTime = GetTickCount();

	m_tStat = { 50, 50, 300 };
}

int CMonster_KF15::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_tStat.iHp == 0)
	{
		return OBJ_DEAD;
	}

	m_fAngle += m_fSpeed;

	m_pTarget = CObjMgr::Get_Instance()->Get_Object(OBJID::PLAYER);

	m_tInfo.fX = m_pTarget->Get_Info().fX + (m_fDistance * cosf(m_fAngle * PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - (m_fDistance * sinf(m_fAngle * PI / 180.f));

	if (m_tTime + 1000 <= GetTickCount())
	{
		CObj*	pObj = nullptr;
		pObj = CAbstractFactory<CKF15_Bullet>::Create(float(m_tGun.x), float(m_tGun.y), m_fAngle);
		CObjMgr::Get_Instance()->Add_Object(OBJID::KF15_BULLET, pObj);
		m_tTime = GetTickCount();
	}

	Update_Rect();

	return OBJ_LIFE;
}

void CMonster_KF15::Late_Update(void)
{
	m_tGun.x = long(m_tInfo.fX - (cosf(m_fAngle * PI / 180.f) * m_fGun_Distance));
	m_tGun.y = long(m_tInfo.fY + (sinf(m_fAngle * PI / 180.f) * m_fGun_Distance));
}

void CMonster_KF15::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(170, 176, 173));

	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	// 포신 그리기
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tGun.x, (int)m_tGun.y);
	myBrush = (HBRUSH)SelectObject(hDC, oldBrush);

	DeleteObject(myBrush);
	DeleteObject(oldBrush);
}

void CMonster_KF15::Release(void)
{
}
