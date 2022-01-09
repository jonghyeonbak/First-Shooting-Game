#include "stdafx.h"
#include "Ufo_Bullet.h"
#include "ObjMgr.h"

CUfo_Bullet::CUfo_Bullet()
{
}


CUfo_Bullet::~CUfo_Bullet()
{
}

void CUfo_Bullet::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_pTarget = nullptr;
	m_pTarget = CObjMgr::Get_Instance()->Get_Object(OBJID::UFO);
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY + 30.f;

	m_fSpeed = 1.f;
}

int CUfo_Bullet::Update(void)
{
	
	/*m_tInfo.fX = m_pTarget->Get_Info().fX + (m_fDistance * cosf(m_fAngle * PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - (m_fDistance * sinf(m_fAngle * PI / 180.f));*/
	
	if (true == m_bDead)
		return OBJ_DEAD;
	m_tInfo.fY += m_fSpeed;

	Update_Rect();

	return OBJ_LIFE;
}

void CUfo_Bullet::Late_Update(void)
{
	if (0 >= m_tRect.left ||
		WINCX <= m_tRect.right ||
		0 >= m_tRect.top ||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}

}

void CUfo_Bullet::Render(HDC hDC)
{
	HBRUSH myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));

	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);


	SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
}

void CUfo_Bullet::Release(void)
{
}