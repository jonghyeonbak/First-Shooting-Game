#include "stdafx.h"
#include "Monster_UFO.h"
#include "ObjMgr.h"
#include "Ufo_Bullet.h"
#include "AbstractFactory.h"
#include "Monster_Warm.h"

CMonster_UFO::CMonster_UFO()
	:MonsterTime(0)
{
}


CMonster_UFO::~CMonster_UFO()		// 몬스터가 나오는 순서를 정하기 위해 소멸자에 지렁이 생성
{
	CObj* pObj = nullptr;
	pObj = CAbstractFactory<CMonster_Warm>::Create(1000.f, 700.f, BULLET::LEFT);
	CObjMgr::Get_Instance()->Add_Object(OBJID::WARM, pObj);
}

void CMonster_UFO::Initialize(void)
{
	m_tInfo.fX = 640.f;
	m_tInfo.fY = 350.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	 
	m_fSpeed = 1.f;

	m_tStat = { 2500, 2500, 300 };
}

int CMonster_UFO::Update(void)
{

	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_tStat.iHp == 0)
	{
		return OBJ_DEAD;
	}

	switch (m_eDir)
	{
	case BULLET::LEFT:
		m_tInfo.fX -= m_fSpeed;
		break;
	case BULLET::RIGHT:
		m_tInfo.fX += m_fSpeed;
		break;
	}

	if (MonsterTime + 100 < GetTickCount())
	{
		CObj*	pObj = nullptr;

		pObj = CAbstractFactory<CUfo_Bullet>::Create();
		CObjMgr::Get_Instance()->Add_Object(OBJID::UFO_BULLET, pObj);
		MonsterTime = GetTickCount();
	}

	Update_Rect();

	return OBJ_LIFE;
}

void CMonster_UFO::Late_Update(void)
{
	if (WINCX <= m_tInfo.fX)
	{
		m_eDir = BULLET::LEFT;
	}
	if (0 >= m_tInfo.fX)
	{
		m_eDir = BULLET::RIGHT;
	}
}

void CMonster_UFO::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 128, 0)); 


	Arc(hDC, m_tRect.left - 250, m_tRect.top - 100, m_tRect.right + 250, m_tRect.bottom - 10, 300, 150, 1200, 10);
	Arc(hDC, m_tRect.left - 120, m_tRect.top - 150, m_tRect.right + 100, m_tRect.bottom - 100, 100, 270, 2500, 320);
	Arc(hDC, m_tRect.left - 115, m_tRect.top - 130, m_tRect.right + 100, m_tRect.bottom - 100, 1800, 220, -1200, 250);
	MoveToEx(hDC, (int)m_tInfo.fX - 250, (int)m_tInfo.fY - 26, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 250, (int)m_tInfo.fY - 10);

	MoveToEx(hDC, (int)m_tInfo.fX + 243, (int)m_tInfo.fY - 24, nullptr);
	LineTo(hDC, (int)m_tInfo.fX + 243, (int)m_tInfo.fY - 10);


	Arc(hDC, m_tRect.left - 226, m_tRect.top - 30, m_tRect.right + 220, m_tRect.bottom + 11, -1500, 300, 2500, 320);

	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	Arc(hDC, m_tRect.left - 250, m_tRect.top - 50, m_tRect.right + 250, m_tRect.bottom + 30, -1500, 160, 2500, 187);

	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	Arc(hDC, m_tRect.left - 250, m_tRect.top - 75, m_tRect.right + 250, m_tRect.bottom + 50, -1500, 320, 2500, 320);

	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left - 230, m_tRect.top - 60, m_tRect.right - 240, m_tRect.bottom - 80);
	Ellipse(hDC, m_tRect.left - 170, m_tRect.top - 40, m_tRect.right - 160, m_tRect.bottom - 40);
	Ellipse(hDC, m_tRect.left - 170, m_tRect.top - 40, m_tRect.right - 160, m_tRect.bottom - 40);
	Ellipse(hDC, m_tRect.left - 50, m_tRect.top - 30, m_tRect.right - 40, m_tRect.bottom - 30);
	Ellipse(hDC, m_tRect.left + 70, m_tRect.top - 30, m_tRect.right + 90, m_tRect.bottom - 30);
	Ellipse(hDC, m_tRect.left + 200, m_tRect.top - 40, m_tRect.right + 200, m_tRect.bottom - 50);
	Ellipse(hDC, m_tRect.left + 268, m_tRect.top - 50, m_tRect.right + 240, m_tRect.bottom - 80);

	MoveToEx(hDC, (int)m_tInfo.fX - 90, (int)m_tInfo.fY - 146, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 130, (int)m_tInfo.fY - 101);

	MoveToEx(hDC, (int)m_tInfo.fX - 40, (int)m_tInfo.fY - 154, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 80, (int)m_tInfo.fY - 84);

	MoveToEx(hDC, (int)m_tInfo.fX + 20, (int)m_tInfo.fY - 154, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 10, (int)m_tInfo.fY - 76);

	MoveToEx(hDC, (int)m_tInfo.fX + 60, (int)m_tInfo.fY - 150, nullptr);
	LineTo(hDC, (int)m_tInfo.fX + 40, (int)m_tInfo.fY - 78);

	MoveToEx(hDC, (int)m_tInfo.fX + 100, (int)m_tInfo.fY - 138, nullptr);
	LineTo(hDC, (int)m_tInfo.fX + 90, (int)m_tInfo.fY - 92);


	MoveToEx(hDC, (int)m_tInfo.fX + 100, (int)m_tInfo.fY - 138, nullptr);
	LineTo(hDC, (int)m_tInfo.fX + 90, (int)m_tInfo.fY - 92);

	// 가운데 포탄
	
	MoveToEx(hDC, (int)m_tInfo.fX + 15, (int)m_tInfo.fY + 75, nullptr);
	LineTo(hDC, (int)m_tInfo.fX + 15, (int)m_tInfo.fY + 105);

	MoveToEx(hDC, (int)m_tInfo.fX - 10, (int)m_tInfo.fY + 75, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 10, (int)m_tInfo.fY + 105);
	Ellipse(hDC, m_tRect.left + 15, m_tRect.top + 120, m_tRect.right - 10, m_tRect.bottom + 90);

	// 오른쪽 포탄
	MoveToEx(hDC, (int)m_tInfo.fX + 250, (int)m_tInfo.fY + 22, nullptr);
	LineTo(hDC, (int)m_tInfo.fX + 285, (int)m_tInfo.fY + 50);

	MoveToEx(hDC, (int)m_tInfo.fX + 230, (int)m_tInfo.fY + 34, nullptr);
	LineTo(hDC, (int)m_tInfo.fX + 275, (int)m_tInfo.fY + 55);

	Ellipse(hDC, m_tRect.left + 290, m_tRect.top + 70, m_tRect.right + 260, m_tRect.bottom + 30);

	// 왼쪽 포탄
	MoveToEx(hDC, (int)m_tInfo.fX - 230, (int)m_tInfo.fY + 35, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 250, (int)m_tInfo.fY + 47);

	MoveToEx(hDC, (int)m_tInfo.fX - 200, (int)m_tInfo.fY + 47, nullptr);
	LineTo(hDC, (int)m_tInfo.fX - 240, (int)m_tInfo.fY + 53);

	Ellipse(hDC, m_tRect.left - 230, m_tRect.top + 70, m_tRect.right - 260, m_tRect.bottom + 30);

	myBrush = (HBRUSH)SelectObject(hDC, oldBrush);

	DeleteObject(myBrush);
	DeleteObject(oldBrush);


}

void CMonster_UFO::Release(void)
{

}
