#include "stdafx.h"
#include "KF15_Bullet.h"
#include "ObjMgr.h"

CKF15_Bullet::CKF15_Bullet()
	:m_bStart(true), m_bCenter1(false), m_bCenter2(false), m_bCenter3(false), m_bCenter4(false)
{
}


CKF15_Bullet::~CKF15_Bullet()
{
}
void CKF15_Bullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_pTarget = nullptr;
	m_pTarget = CObjMgr::Get_Instance()->Get_Object(OBJID::MONSTER_KF15);

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;

	m_tPlayerTarget = nullptr;
	m_tPlayerTarget = CObjMgr::Get_Instance()->Get_Object(OBJID::PLAYER);



	m_tInfoTemp.fX = m_pTarget->Get_Info().fX;
	m_tInfoTemp.fY = m_pTarget->Get_Info().fY;

	m_fSpeed = 5.f;
}

int CKF15_Bullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;
	if (true == m_bStart)
	{
		if (m_tInfo.fX > m_tPlayerTarget->Get_Info().fX && m_tInfo.fY < m_tPlayerTarget->Get_Info().fY)
		{
			m_bCenter1 = true;
		}
		if (m_tInfo.fX < m_tPlayerTarget->Get_Info().fX && m_tInfo.fY < m_tPlayerTarget->Get_Info().fY)
		{
			m_bCenter2 = true;
		}
		if (m_tInfo.fX < m_tPlayerTarget->Get_Info().fX && m_tInfo.fY > m_tPlayerTarget->Get_Info().fY)
		{
			m_bCenter3 = true;
		}
		if (m_tInfo.fX > m_tPlayerTarget->Get_Info().fX && m_tInfo.fY > m_tPlayerTarget->Get_Info().fY)
		{
			m_bCenter4 = true;
		}
		//스위치 만들것!
		m_bStart = (false);
	}
	if (true == m_bCenter1)
	{
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY += m_fSpeed;
	}
	if (true == m_bCenter2)
	{
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY += m_fSpeed;
	}
	if (true == m_bCenter3)
	{
		m_tInfo.fX += m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
	}
	if (true == m_bCenter4)
	{
		m_tInfo.fX -= m_fSpeed;
		m_tInfo.fY -= m_fSpeed;
	}


	Update_Rect();

	return OBJ_LIFE;
}

void CKF15_Bullet::Late_Update(void)
{

	
}

void CKF15_Bullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CKF15_Bullet::Release(void)
{
}
