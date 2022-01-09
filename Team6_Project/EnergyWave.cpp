#include "stdafx.h"
#include "EnergyWave.h"


CEnergyWave::CEnergyWave()
	: m_fCenterSpeed(0.f), m_fRevolutionAngle(0.f), m_bStart(true)
{
	ZeroMemory(&m_tCenterPos, sizeof(m_tCenterPos));
	ZeroMemory(&m_tCenterPos2, sizeof(m_tCenterPos2));
}


CEnergyWave::~CEnergyWave()
{
	Release();
}

void CEnergyWave::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_tInfo2.fCX = 20.f;
	m_tInfo2.fCY = 20.f;

	m_fSpeed = 20.f;
	m_fCenterSpeed = 10.f;
	m_fDistance = 20.f;
	m_fRevolutionAngle = 0.f;

	//m_tStat = { 0, 0, 100 };
}

int CEnergyWave::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	if (m_bStart)
	{
		m_tCenterPos.x = m_tInfo.fX;
		m_tCenterPos.y = m_tInfo.fY;

		m_tCenterPos2.x = m_tInfo2.fX;
		m_tCenterPos2.y = m_tInfo2.fY;

		m_fRevolutionAngle = m_fAngle;
		m_bStart = false;
	}


	m_tCenterPos.x += m_fCenterSpeed * cosf(m_fRevolutionAngle * PI / 180.f);
	m_tCenterPos.y -= m_fCenterSpeed * sinf(m_fRevolutionAngle * PI / 180.f);

	m_tCenterPos2.x += m_fCenterSpeed * cosf(m_fRevolutionAngle * PI / 180.f);
	m_tCenterPos2.y -= m_fCenterSpeed * sinf(m_fRevolutionAngle * PI / 180.f);

	m_tInfo.fX = m_tCenterPos.x + (m_fDistance * cosf(m_fAngle * PI / 180.f));
	m_tInfo.fY = m_tCenterPos.y - (m_fDistance * sinf(m_fAngle * PI / 180.f));

	m_tInfo2.fX = m_tCenterPos2.x - (m_fDistance * cosf(m_fAngle * PI / 180.f));
	m_tInfo2.fY = m_tCenterPos2.y + (m_fDistance * sinf(m_fAngle * PI / 180.f));

	m_fAngle += m_fSpeed;

	Update_Rect();

	return OBJ_LIFE;
}

void CEnergyWave::Late_Update(void)
{
	if (0 >= m_tRect.left ||
		WINCX <= m_tRect.right ||
		0 >= m_tRect.top ||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CEnergyWave::Render(HDC hDC)
{
	HBRUSH myBrush, oldBrush;
	myBrush = (HBRUSH)CreateSolidBrush(RGB(95, 224, 220));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);

	Ellipse(hDC, m_tRect.left, m_tRect.top - 40, m_tRect.right, m_tRect.bottom - 40);

	Ellipse(hDC, m_tRect2.left, m_tRect2.top + 40, m_tRect2.right, m_tRect2.bottom + 40);
	myBrush = (HBRUSH)SelectObject(hDC, oldBrush);

	DeleteObject(myBrush);
	DeleteObject(oldBrush);
}

void CEnergyWave::Release(void)
{
}
