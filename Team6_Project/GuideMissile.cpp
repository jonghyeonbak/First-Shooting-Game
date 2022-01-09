#include "stdafx.h"
#include "GuideMissile.h"
#include "ObjMgr.h"

CGuideMissile::CGuideMissile()
{
}

CGuideMissile::~CGuideMissile()
{
	Release();
}

void CGuideMissile::Initialize(void)
{
	m_tInfo.fX = 200.f;
	m_tInfo.fY = 100.f;

	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;
	m_fSpeed = 5.f;
	
	m_tStat = { 0, 0, 100 };
}

int CGuideMissile::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Target(OBJID::UFO, this);		// 가까운 몬스터 타겟을 설정


	if (nullptr != m_pTarget)
	{
		float	fX = m_pTarget->Get_Info().fX - m_tInfo.fX;				// 몬스터의 좌표
		float	fY = m_pTarget->Get_Info().fY - m_tInfo.fY;

		float	fDistance = sqrtf(fX * fX + fY * fY);		// 몬스터와 미사일간의 빗변길이(거리)

		float	fRadian = acosf(fX / fDistance);

		m_fAngle = fRadian * 180.f / PI;

		if (m_pTarget->Get_Info().fY > m_tInfo.fY)
			m_fAngle *= -1.f;
	}

	m_tInfo.fX += (m_fSpeed * cosf(m_fAngle * PI / 180.f));
	m_tInfo.fY -= (m_fSpeed * sinf(m_fAngle * PI / 180.f));

	Update_Rect();

	return OBJ_LIFE;
}

void CGuideMissile::Late_Update(void)
{
	if (0 >= m_tRect.left ||
		WINCX <= m_tRect.right ||
		0 >= m_tRect.top ||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CGuideMissile::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CGuideMissile::Release(void)
{
}
