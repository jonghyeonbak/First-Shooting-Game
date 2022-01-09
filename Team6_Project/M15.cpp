#include "stdafx.h"
#include "M15.h"
#include "ObjMgr.h"


CM15::CM15()
{
}


CM15::~CM15()
{
}

void CM15::Initialize(void)
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 5.f;
	m_fDistance = 100.f;
}

int CM15::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_fAngle += m_fSpeed;

	m_pTarget = CObjMgr::Get_Instance()->Get_Object(OBJID::PLAYER);
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;

	//m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	//m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();

	return OBJ_LIFE;
}

void CM15::Late_Update(void)
{
}

void CM15::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	Ellipse(hDC, m_tRect.left + 10, m_tRect.top + 10 , m_tRect.right - 20, m_tRect.bottom - 20);
}

void CM15::Release(void)
{
}
