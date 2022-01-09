#include "stdafx.h"
#include "Monster_Warm.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"
#include "Warm_Bullet.h"

CMonster_Warm::CMonster_Warm()
{
}

CMonster_Warm::~CMonster_Warm()
{
}

void CMonster_Warm::Set_Bullet(list<CObj*>* _pBullet)								 // 총알 세팅
{
	m_pBullet = _pBullet;
}
void CMonster_Warm::Initialize(void)
{
	m_tInfo.fX = 1000.f;
	m_tInfo.fY = 700.f;

	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_tGun1.x = m_tInfo.fX;
	m_tGun1.y = m_tInfo.fY;

	m_tGun2.x = m_tInfo.fX;
	m_tGun2.y = m_tInfo.fY;

	m_fSpeed = 1.f;


	m_fDistance = 3.f;

	m_tStat = { 4000, 4000, 150 };
}

int CMonster_Warm::Update(void)				// 업데이트
{
	if (true == m_bDead)					// 지렁이가 죽었으면 
		return OBJ_DEAD;					// obj_dead 반환

	if (m_tStat.iHp == 0)					// hp가 0이면
	{
		return OBJ_DEAD;					// 삭제
	}

	m_tInfo.fX += m_fSpeed;


	++m_iFPS;
	if (m_dwTime + 1000 < GetTickCount()) // 1초에 한번 씩 수행
	{
		pObj = CAbstractFactory<CWarm_Bullet>::Create(float(m_tInfo.fX-20), float(m_tInfo.fY+15), BULLET::LEFT);
		CObjMgr::Get_Instance()->Add_Object(OBJID::WARM, pObj);

		m_dwTime = GetTickCount();  
		m_iFPS = 0;
	
	}

	Update_Rect();

	return OBJ_LIFE;
}

void CMonster_Warm::Late_Update(void)												
{
	if ((0 >= m_tRect.left) || (WINCX  <= m_tRect.right))				
		m_fSpeed *= -1.f;							

	m_tGun1.x = long(m_tInfo.fX + (cosf(m_fAngle * PI / 180.f) * m_fDistance));
	m_tGun1.y = long(m_tInfo.fY - (sinf(m_fAngle * PI / 180.f) * m_fDistance));

}

void CMonster_Warm::Render(HDC hDC)													
{
	//RGB(255, 0, 0)  #ffff00
	HBRUSH myBrush, myBrush2, myBrush3, myBrush4, myBrush5;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(192, 255, 0));
	myBrush2 = (HBRUSH)CreateSolidBrush(RGB(129, 193, 71));
	myBrush3 = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	myBrush4 = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	myBrush5 = (HBRUSH)CreateSolidBrush(RGB(255, 212, 0));

	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	//얼굴 몸통
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	myBrush = (HBRUSH)SelectObject(hDC, myBrush2);
	Ellipse(hDC, m_tRect.left + 50, m_tRect.top + 20, m_tRect.right + 40 , m_tRect.bottom + 12);
	myBrush2 = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left + 90, m_tRect.top + 27, m_tRect.right + 80, m_tRect.bottom + 17);
	myBrush = (HBRUSH)SelectObject(hDC, myBrush2);
	Ellipse(hDC, m_tRect.left + 130, m_tRect.top + 27, m_tRect.right + 120, m_tRect.bottom + 17);
	myBrush2 = (HBRUSH)SelectObject(hDC, myBrush);
	Ellipse(hDC, m_tRect.left + 160, m_tRect.top + 15, m_tRect.right + 140, m_tRect.bottom -5 );
	
	//눈
	myBrush = (HBRUSH)SelectObject(hDC, myBrush3);
	Ellipse(hDC, m_tRect.left + 7, m_tRect.top +20, m_tRect.right - 43, m_tRect.bottom - 25);
	Ellipse(hDC, m_tRect.left + 25, m_tRect.top + 20, m_tRect.right - 25, m_tRect.bottom - 25);

	myBrush3 = (HBRUSH)::SelectObject(hDC, myBrush4);
	Rectangle(hDC, m_tRect.left + 15, m_tRect.top + 50, m_tRect.right - 30, m_tRect.bottom - 20);

	// 더듬이
	myBrush4 = (HBRUSH)SelectObject(hDC, myBrush5);
	MoveToEx(hDC, (int)m_tInfo.fX-30, (int)m_tInfo.fY-40, nullptr);
	LineTo(hDC, (int)m_tGun1.x-23, (int)m_tGun1.y-20);
	Ellipse(hDC, m_tRect.left - 10, m_tRect.top  -17, m_tRect.right -55, m_tRect.bottom -65);

	MoveToEx(hDC, (int)m_tInfo.fX-3, (int)m_tInfo.fY - 30, nullptr);
	LineTo(hDC, (int)m_tGun1.x -15, (int)m_tGun1.y - 45);
	Ellipse(hDC, m_tRect.left + 25, m_tRect.top -17, m_tRect.right - 50, m_tRect.bottom - 65);

	myBrush5 = (HBRUSH)::SelectObject(hDC, oldBrush);

	DeleteObject(myBrush);
	DeleteObject(myBrush2);
	DeleteObject(myBrush3);
	DeleteObject(myBrush4);
	DeleteObject(myBrush5);
	DeleteObject(oldBrush);

}

void CMonster_Warm::Release(void)
{

}
