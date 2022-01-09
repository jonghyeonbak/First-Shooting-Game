#include "stdafx.h"
#include "DefaultBullet.h"
#include "ObjMgr.h"


CDefaultBullet::CDefaultBullet()
{
}


CDefaultBullet::~CDefaultBullet()
{
}

void CDefaultBullet::Set_Size(float _fCX, float _fCY)
{
	m_tInfo.fCX = _fCX;
	m_tInfo.fCY = _fCY;
}
void CDefaultBullet::Set_Speed(float _fSpeed)
{
	m_fSpeed = _fSpeed;
}

void CDefaultBullet::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 10.f;

	Set_Target();

	//m_tStat = { 0,0,50 };
}

int CDefaultBullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	/*m_fAngle += m_fSpeed;*/

	//m_pTarget = CObjMgr::Get_Instance()->Get_Object(OBJID::PLAYER);
	//m_tInfo.fX = m_pTarget->Get_Info().fX + (m_fDistance * cosf(m_fAngle * PI / 180.f));
	//m_tInfo.fY = m_pTarget->Get_Info().fY - (m_fDistance * sinf(m_fAngle * PI / 180.f));

	Update_Rect();

	return OBJ_LIFE;
}

void CDefaultBullet::Late_Update(void)
{
	if (0 >= m_tRect.left ||
		WINCX <= m_tRect.right ||
		0 >= m_tRect.top ||
		WINCY <= m_tRect.bottom)
	{
		m_bDead = true;
	}
}

void CDefaultBullet::Render(HDC hDC)
{
	//RGB(255, 0, 0)  #ffff00
	HBRUSH myBrush, oldBrush;
	HPEN myPen, oldPen;

	myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 212, 0));
	myPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hDC, myBrush);
	
	//Rectangle(hDC, 0, 0, 20, 20);

	//MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY, nullptr);
	//Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	////LineTo(hDC, (int)m_tGun.x, (int)m_tGun.y);

	Ellipse(hDC, m_tRect.left + 15, m_tRect.top, m_tRect.right + 16, m_tRect.bottom);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right + 10, m_tRect.bottom);
	MoveToEx(hDC, (int)m_tInfo.fX, (int)m_tInfo.fY + 4, nullptr);

	myBrush = (HBRUSH)SelectObject(hDC, oldBrush);
	DeleteObject(myBrush);
 
	oldPen = (HPEN)::SelectObject(hDC, (HGDIOBJ)myPen);
	LineTo(hDC, (int)m_tInfo.fX - 15, (int)m_tInfo.fY + 7);
	LineTo(hDC, (int)m_tInfo.fX - 9, (int)m_tInfo.fY + 2);
	LineTo(hDC, (int)m_tInfo.fX - 30, (int)m_tInfo.fY + 1.5);
	LineTo(hDC, (int)m_tInfo.fX - 10, (int)m_tInfo.fY - 2);
	LineTo(hDC, (int)m_tInfo.fX - 20, (int)m_tInfo.fY - 10);
	LineTo(hDC, (int)m_tInfo.fX - 3, (int)m_tInfo.fY - 4);
	myPen = (HPEN)SelectObject(hDC, oldPen);
	DeleteObject(myPen);
	DeleteObject(oldBrush);
	DeleteObject(oldPen);
}

void CDefaultBullet::Release(void)
{
}
