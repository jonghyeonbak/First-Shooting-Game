#include "stdafx.h"
#include "Monster_Guided.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CMonster_Guided::CMonster_Guided()
{
}


CMonster_Guided::~CMonster_Guided()
{
}

void CMonster_Guided::Initialize(void)
{
	m_tInfo.fCX = 5.f;
	m_tInfo.fCY = 5.f;

	m_pTarget = nullptr;
	m_pTarget = CObjMgr::Get_Instance()->Get_Object(OBJID::MONSTER_CARRIER);

	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY + 30.f;

	m_fSpeed = 5.f;

	m_tStat = { 50, 50, 100 };
}

int CMonster_Guided::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_tStat.iHp == 0)
	{
		return OBJ_DEAD;
	}

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::PLAYER, this);
	if (nullptr != m_pTarget)
	{
		float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
		float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

		float	fDistance = sqrtf(fX * fX + fY * fY);

		float	fRadian = acosf(fX / fDistance);

		m_fAngle = fRadian * 180.f / PI;

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;
	}

	m_tInfo.fX += (m_fSpeed * cosf(m_fAngle * PI / 180.f));
	m_tInfo.fY -= (m_fSpeed * sinf(m_fAngle * PI / 180.f));
	//m_tInfo.fX -= m_fSpeed;

	Update_Rect();


	return OBJ_LIFE;
}

void CMonster_Guided::Late_Update(void)
{
}

void CMonster_Guided::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
	//5,5,5,5   -15, -5, 15, 10
	Rectangle(hDC, m_tRect.left- 20, m_tRect.top-10, m_tRect.right+10, m_tRect.bottom+5);
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Rectangle(hDC, m_tRect.left-20 , m_tRect.top - 10, m_tRect.right -15, m_tRect.bottom + 5);
	Rectangle(hDC, m_tRect.left +5, m_tRect.top - 10, m_tRect.right +10, m_tRect.bottom + 5);
	myBrush = (HBRUSH)SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
	DeleteObject(oldBrush);

}

void CMonster_Guided::Release(void)
{
}
