#include "stdafx.h"
#include "Shotgun_Bullet.h"
#include "AbstractFactory.h"
#include "ObjMgr.h"

CShotgun_Bullet::CShotgun_Bullet()
{
}


CShotgun_Bullet::~CShotgun_Bullet()
{
}

void CShotgun_Bullet::Initialize(void)
{
	m_tInfo.fCX = 25.f;
	m_tInfo.fCY = 25.f;

	m_fSpeed = 3.f;
}

int CShotgun_Bullet::Update(void)
{
	if (true == m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;

	Update_Rect();


	return OBJ_LIFE;
}

void CShotgun_Bullet::Late_Update(void)
{

}

void CShotgun_Bullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CShotgun_Bullet::Release(void)
{
}
