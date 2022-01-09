#include "stdafx.h"
#include "Maru.h"
#include "ObjMgr.h"


CMaru::CMaru()
{
}

CMaru::~CMaru()
{
	Release();
}

void CMaru::Initialize(void)
{
	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 3.f;
	m_fDistance = 26.f;
	m_fMaru_Distance = 150.f;
}

int CMaru::Update(void)
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

void CMaru::Late_Update(void)
{
	m_fMaru_Angle = 2.f; 

	m_tMaru[0].x = long(m_tInfo.fX + (cosf(m_fMaru_Angle * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[0].y = long(m_tInfo.fY - (sinf(m_fMaru_Angle * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[1].x = long(m_tInfo.fX - (cosf(m_fMaru_Angle * PI / 180.f) * m_fMaru_Distance));
	m_tMaru[1].y = long(m_tInfo.fY + (sinf(m_fMaru_Angle * PI / 180.f) * m_fMaru_Distance));

	//m_tMaru[2].x = long(m_tInfo.fX + (cosf(( + 90) * PI / 180.f) * m_fMaru_Distance));
	//m_tMaru[2].y = long(m_tInfo.fY - (sinf(( + 90) * PI / 180.f) * m_fMaru_Distance));
	//m_tMaru[3].x = long(m_tInfo.fX - (cosf(( + 90) * PI / 180.f) * m_fMaru_Distance));
	//m_tMaru[3].y = long(m_tInfo.fY + (sinf(( + 90) * PI / 180.f) * m_fMaru_Distance));
}

void CMaru::Render(HDC hDC)
{
	for (int i = 0; i < 4; i++)
	{
		Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	}
}

void CMaru::Release(void)
{
}
