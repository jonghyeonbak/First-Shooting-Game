#include "stdafx.h"
#include "Monster_Carrier.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Monster_Guided.h"
#include "Monster_UFO.h"


CMonster_Carrier::CMonster_Carrier()
	:Carrier_Time(0), m_Switch(false)
{
}


CMonster_Carrier::~CMonster_Carrier()
{

	CObjMgr::m_count += 1;						// 나오는 횟수 조절하는 변수
	if (3 == CObjMgr::m_count && m_Switch == false)
	{
		CObj* pObj = nullptr;
		pObj = CAbstractFactory<CMonster_UFO>::Create();
		CObjMgr::Get_Instance()->Add_Object(OBJID::UFO, pObj);
		m_Switch = true;
	}
	
}

void CMonster_Carrier::Initialize(void)
{

	m_tInfo.fCX = 200.f;
	m_tInfo.fCY = 200.f;

	m_tGun.x = m_tInfo.fX;
	m_tGun.y = m_tInfo.fY;

	m_fDistance = 100.f;

	m_fSpeed = 2.f;

	m_tStat = { 200, 200, 250 };
}

int CMonster_Carrier::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_tStat.iHp == 0)
	{
		return OBJ_DEAD;
	}

	switch (m_eDir)
	{
	case BULLET::UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case BULLET::DOWN:
		m_tInfo.fY += m_fSpeed;
		break;
	}

	if (Carrier_Time + 3000 <= GetTickCount())
	{
		CObj*	pObj = nullptr;

		pObj = CAbstractFactory<CMonster_Guided>::Create();
		CObjMgr::Get_Instance()->Add_Object(OBJID::MONSTER_GUIDED, pObj);
		Carrier_Time = GetTickCount();
	}

	Update_Rect();

	return OBJ_LIFE;
}

void CMonster_Carrier::Late_Update(void)
{
	m_tGun.x = long(m_tInfo.fX - (cosf(m_fAngle * PI / 180.f) * m_fDistance));
	m_tGun.y = long(m_tInfo.fY + (sinf(m_fAngle * PI / 180.f) * m_fDistance));

	if (0 >= m_tInfo.fY)
	{
		m_eDir = BULLET::DOWN;
	}
	if (WINCY <= m_tInfo.fY)
	{
		m_eDir = BULLET::UP;
	}
}

void CMonster_Carrier::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));

	Ellipse(hDC, m_tRect.left-40, m_tRect.top, m_tRect.right+30, m_tRect.bottom);
	//160, 200, 230, 200
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left +80, m_tRect.top+10, m_tRect.right , m_tRect.bottom-120);
	Ellipse(hDC, m_tRect.left - 40, m_tRect.top+100, m_tRect.right + 30, m_tRect.bottom-95);

	// 포신 그리기
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	LineTo(hDC, (int)m_tGun.x, (int)m_tGun.y);
	myBrush = (HBRUSH)SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	DeleteObject(oldBrush);
}

void CMonster_Carrier::Release(void)
{
}
