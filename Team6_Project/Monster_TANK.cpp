#include "stdafx.h"
#include "Monster_Tank.h"
#include "Tank_Bullet.h"
#include "ObjMgr.h"
#include "AbstractFactory.h"

CMonster_Tank::CMonster_Tank()
	:dTimer(0)
{
}


CMonster_Tank::~CMonster_Tank()
{
}

void CMonster_Tank::Initialize(void)
{
	m_tInfo.fX = 400.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	
	m_fDown = 0.1f;
	m_fDistance = 40.f;

	m_tGun.x = 0.f;
	m_tGun.y = 0.f;

	m_fSpeed = 2.f;

	m_tStat = { 50, 50, 100 };
}

int CMonster_Tank::Update(void)
{

	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_tStat.iHp == 0)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += m_fSpeed;
	m_tInfo.fY += m_fDown;

	LookPlayer();

	if (GetTickCount() >= dTimer + 3000)
	{	
		CObj* pBullet = CAbstractFactory<CTank_Bullet>::Create(float(m_tGun.x), float(m_tGun.y), m_fAngle);
		static_cast<CTank_Bullet*>(pBullet)->Set_Size(10.f, 10.f);
		static_cast<CTank_Bullet*>(pBullet)->Set_Speed(3.f);

		CObjMgr::Get_Instance()->Add_Object(OBJID::TANK_BULLET, pBullet);
		
		dTimer = GetTickCount();
	}

	Update_Rect();

	return OBJ_LIFE;
}

void CMonster_Tank::Late_Update(void)
{
	//ShootBullet();

	// 포대의 위치 = 몬스터의 중점 + (플레이어의 x,y 좌표) * 거리
	m_tGun.x = long(m_tInfo.fX + (cosf(m_fAngle * PI / 180.f) * m_fDistance));
	m_tGun.y = long(m_tInfo.fY - (sinf(m_fAngle * PI / 180.f) * m_fDistance));

	if ((0 >= m_tRect.left) || (WINCX <= m_tRect.right))
		m_fSpeed *= -1.f;
}

void CMonster_Tank::LookPlayer()
{
	// CObj* m_pTarget = 플레이어와 몬스터의 거리를 계산
	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);

	if (nullptr != m_pTarget)
	{
		// fX = player의 x - monster의 중점x
		float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		// fY = player의 y - monster의 중점y
		float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

		// player와 monster 사이의 거리 
		float	fDistance = sqrtf(fX * fX + fY * fY);
		// 두 중점 간의 각
		float	fRadian = acosf(fX / fDistance);
		// Radian to Degree
		m_fAngle = fRadian * 180.f / PI;
		// 플레이어의 높이가 몬스터보다 높을 경우 위치 바꾸기
		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;
	}

}

//void CMonster_Tank::ShootBullet()
//{
//	if (GetTickCount() >= dTimer + 3000)
//	{
//		CObj* pBullet = CAbstractFactory<CTank_Bullet>::Create(float(m_tGun.x), float(m_tGun.y), m_fAngle);
//		static_cast<CTank_Bullet*>(pBullet)->Set_Size(10.f, 10.f);
//		static_cast<CTank_Bullet*>(pBullet)->Set_Speed(3.f);
//
//		CObjMgr::Get_Instance()->Add_Object(OBJID::TANK_BULLET, pBullet);
//
//		dTimer = GetTickCount();
//	}
//
//}

void CMonster_Tank::Render(HDC hDC)
{
	/*HBRUSH myBrush, oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(36, 116, 0));

	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);*/

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	MoveToEx(hDC, (int)(m_tInfo.fX), (int)(m_tInfo.fY), nullptr);
	LineTo(hDC, (int)m_tGun.x, (int)m_tGun.y);

	/*myBrush = (HBRUSH)SelectObject(hDC, oldBrush);

	DeleteObject(myBrush);
	DeleteObject(oldBrush);*/
}

void CMonster_Tank::Release(void)
{
}


