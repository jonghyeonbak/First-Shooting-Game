#include "stdafx.h"
#include "BladeShield.h"
#include "ObjMgr.h"


CBladeShield::CBladeShield()
{
}


CBladeShield::~CBladeShield()
{
	Release();
}

void CBladeShield::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 5.f;
	m_fDistance = 50.f;
}

int CBladeShield::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_fAngle += m_fSpeed;

	m_pTarget = CObjMgr::Get_Instance()->Get_Object(OBJID::PLAYER);
	m_tInfo.fX = m_pTarget->Get_Info().fX + (m_fDistance * cosf(m_fAngle * PI / 180.f));
	m_tInfo.fY = m_pTarget->Get_Info().fY - (m_fDistance * sinf(m_fAngle * PI / 180.f));

	Update_Rect();

	return OBJ_LIFE;
}

void CBladeShield::Late_Update(void)
{
}

void CBladeShield::Render(HDC hDC)
{
	//MoveToEx(hDC, m_tInfo.fX, m_tInfo.fY, NULL);
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

}

void CBladeShield::Release(void)
{
}
